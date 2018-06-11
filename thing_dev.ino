#include <EEPROM.h>
#include <U8g2lib.h>
#include <U8x8lib.h>
#include <Metro.h>
#include <Space_Invaders.h>
#include <Adafruit_GFX.h>
#include <ESP8266WiFi.h>
#include <dummy.h>

const char* ssid     = "attwifi";
const char* password = NULL;
const char* host = "irl.depaul.edu";
WiFiClient client;


//Space invader stuff
byte level = 1;
unsigned int score = 0;
char bounce; //the enemy bounces off the wall
char play = 0; // 0 - play, 1 - pause, 2 - defeat
int delayTrigger = 100;
bool flipCompleted = false;
#define nr_enemy 12
#define chance_shoot 4


Enemy *enemy[nr_enemy];
Bullet *ShipBullet = new Bullet();
Bullet *EnemyBullet = new Bullet();
Ship *ship;

static unsigned char PROGMEM over[] =
{
  B01100010,
  B10010100,
  B10011000,
  B10010000,
  B11111110,
  B00000000,
  B10000010,
  B10010010,
  B10010010,
  B10010010,
  B11111110,
  B00000000,
  B11111000,
  B00000100,
  B00000010,
  B00000100,
  B11111000,
  B00000000,
  B01111100,
  B10000010,
  B10000010,
  B10000010,
  B01111100
};

static unsigned char PROGMEM game[] =
{
  B10000010,
  B10010010,
  B10010010,
  B10010010,
  B11111110,
  B00000000,
  B11111110,
  B01000000,
  B00111000,
  B01000000,
  B11111110,
  B00000000,
  B00111110,
  B01001000,
  B10001000,
  B01001000,
  B00111110,
  B00000000,
  B01001110,
  B10001010,
  B10000010,
  B10000010,
  B01111100
};

static const unsigned char PROGMEM pause[] = {
  B00000000,
  B00000000,
  B10000010,
  B10010010,
  B10010010,
  B10010010,
  B11111110,
  B00000000,
  B01001100,
  B10010010,
  B10010010,
  B10010010,
  B01100100,
  B00000000,
  B11111100,
  B00000010,
  B00000010,
  B00000010,
  B11111100,
  B00000000,
  B00111110,
  B01001000,
  B10001000,
  B01001000,
  B00111110,
  B00000000,
  B01100000,
  B10010000,
  B10010000,
  B10010000,
  B11111110,
  B00000000
};
#define X_width 23
#define X_height 19
static unsigned char X_icon[] = {
  0x00, 0x00, 0x00, 0xc0, 0x80, 0x01, 0xc0, 0xc1, 0x01, 0x80, 0xc1, 0x00,
  0x80, 0xe3, 0x00, 0x00, 0x63, 0x00, 0x00, 0x77, 0x00, 0x00, 0x3e, 0x00,
  0x00, 0x1c, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x3e, 0x00,
  0x00, 0x77, 0x00, 0x00, 0x63, 0x00, 0x80, 0xe3, 0x00, 0x80, 0xc1, 0x00,
  0xc0, 0xc1, 0x01, 0xc0, 0x80, 0x01, 0x00, 0x00, 0x00
};

#define O_width 23
#define O_height 19
static unsigned char O_icon[] = {
  0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x7e, 0x00,
  0x00, 0x66, 0x00, 0x00, 0xe7, 0x00, 0x00, 0xc3, 0x00, 0x80, 0xc3, 0x01,
  0x80, 0x81, 0x01, 0x80, 0x81, 0x01, 0x80, 0x81, 0x01, 0x80, 0xc3, 0x01,
  0x00, 0xc3, 0x00, 0x00, 0xe7, 0x00, 0x00, 0x66, 0x00, 0x00, 0x7e, 0x00,
  0x00, 0x3c, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00
};

#define BPIN 4 //button pin
#define counter 1000 //debounce time

int thotcoin_counter=0;
int thotcoin_betting=0;
int pickaxe;    
int wifi;   
int coin_n=10;    
int lastcoinstate;    
int thot_rand;
int states[10];
int index_state = 0;

bool isBooting = true;
bool menuActive = false;
bool menuPricing = true;
int menuPricingTimer = 100;
int bootCounter = 0;
int textCounter = 0;
int menuSelection = 0;
int lastButtonStateL = 0;
int lastButtonStateR = 0;
int lastButtonStateEnter = 0;

/*    
 * EEPROM BIT SPACES    
 * 0 = THOTCOIN   
 * 20 = PICK AXE     
 * 21 = coin_n (the multiplier for getting thotcoin)    
 */ 

Metro s = Metro(300), b = Metro(150), e = Metro(1000);

U8G2_UC1701_EA_DOGS102_1_4W_SW_SPI u8g2(U8G2_R0, 14, 13, 15, 12);
//pin for Left button
const int buttonPinL = 0;
//pin for Right
const int buttonPinR = 5;
//pin for Middle
const int buttonPinEnter = 4;
//current state of buttons
int buttonStateL = 0;
int buttonStateR = 0;
int buttonStateEnter = 0;
//for Menu System
int8_t curMenuItem = 0;
//Debounce for preventing multiple keypresses on just one keypress
uint32_t lastDebounceTime = 0;
uint16_t debounceTime = 250;

const int wifiWaitTime = 200;
int counterForWifi;

/*from other guy's example. see below comment for explanation */
const char *GetStringLine(uint8_t line_idx, const char *str ) { //Assumes strings, separated by '\n' in "str". Returns the string at index "line_idx". First strng has line_idx = 0
  char e;
  uint8_t line_cnt = 1;

  if ( line_idx == 0 )
    return str;

  for (;;)
  {
    e = *str;
    if ( e == '\0' )
      break;
    str++;
    if ( e == '\n' )
    {
      if ( line_cnt == line_idx )
        return str;
      line_cnt++;
    }
  }
  return NULL;  /* line not found */
}
/* These three methods execute the actions of buttonPress */
void buttonOne() {
  //Serial.println("button one is pressed!");
  if (--curMenuItem < 0) {
    curMenuItem = 0;
  } else {
    // curMenuItem--;
  }
}
void buttonTwo() {
  /*
  Serial.println("button two is pressed!");
  if (++curMenuItem > menuItemsCount - 1) {
    //curMenuItem = 0;
  } else {
    //curMenuItem++;
  }
  */
}
void buttonThree(int8_t menuItemsCountTemp) {
  //Serial.println("button three is pressed!");
  if (++curMenuItem > menuItemsCountTemp - 1) {
    curMenuItem = 0;
  } else {
    // curMenuItem++;
  }
}
/* Check what buttons are pressed */
void buttonPress(int8_t menuItemsCountTemp) {
  buttonStateL = digitalRead(buttonPinL);
  buttonStateR = digitalRead(buttonPinR);
  buttonStateEnter = digitalRead(buttonPinEnter);
  if (buttonStateL == LOW) {
    if ((millis() - lastDebounceTime) > debounceTime) {
      lastDebounceTime = millis();
      buttonOne();
    }
  }
  else if (buttonStateEnter == LOW) {
    if ((millis() - lastDebounceTime) > debounceTime) {
      lastDebounceTime = millis();
      buttonTwo();
    }
  }
  else if (buttonStateR == LOW) {
    if ((millis() - lastDebounceTime) > debounceTime) {
      lastDebounceTime = millis();
      buttonThree(menuItemsCountTemp);
    }
  }
}

void drawMenu(const char *title, uint8_t start_pos, const char *line, uint8_t m_items, uint8_t heading) {
    byte x {0}; byte y {0};
    u8g2.setFont(u8g2_font_5x7_mf);
    u8g2.setFontRefHeightAll();
    x = (100 - u8g2.getStrWidth(title)) / 2;
    y = u8g2.getAscent() - u8g2.getDescent();
    u8g2.setDrawColor(2);
    if(heading==0){
      y=0;
    } else{
      u8g2.drawStr(x, y + 12, title);
      y = 25;
      u8g2.drawHLine(0, 20, 127);
    }

    for (byte  i = 0; i < m_items; i++) {
      const char *msg = GetStringLine(i, line);
      if (i == start_pos) {
        u8g2.drawBox(0, y + 2, 127, u8g2.getAscent() - u8g2.getDescent() + 2);
      }
      else
        x = (128 - u8g2.getStrWidth(msg)) / 2;
      y = y + 2 + u8g2.getAscent() - u8g2.getDescent();
      u8g2.drawStr(x, y, msg);
    }
}

/*Exits to the main menu if left and right buttons are pressed*/
void checkDoublePress() {
  buttonStateL = digitalRead(buttonPinL);
  buttonStateR = digitalRead(buttonPinR);
  if(buttonStateL == LOW && buttonStateR == LOW){
    menuPricing = true;
    menuActive = true;  
  }
}


void setup(void) {
  for (int n = 0; n < 10; n++){
   states[n] = 0; // Unpressed
  }
  //Serial monitor must be set to 115200 read speed
  Serial.begin(115200);
  EEPROM.begin(512);
  
  //Use the lines below to erase coins
  //EEPROM.put(0,0);
  //EEPROM.commit();
  
  EEPROM.get(0,thotcoin_counter);
  Serial.println(EEPROM.read(21));
 if(thotcoin_counter<0){
    EEPROM.put(0, 0);
    EEPROM.commit();
  }
  if(EEPROM.read(21)<0 || EEPROM.read(21) == 255 || EEPROM.read(21) == 0){ 
    EEPROM.write(21,10);
    EEPROM.commit();
  }
  if(EEPROM.read(20)<0 || EEPROM.read(20) == 255){
    EEPROM.write(20,0);
    EEPROM.commit();
  }
  if(EEPROM.read(100)<0 || EEPROM.read(100) == 255 || EEPROM.read(100)==0){
    EEPROM.put(0,1);
    EEPROM.write(100,1);
    EEPROM.commit();
  }
 
  delay(100);
  counterForWifi = 0;
  //Pullup enables the internal resistor pull up for each pin
  pinMode(buttonPinL, INPUT_PULLUP);
  pinMode(buttonPinR, INPUT_PULLUP);
  pinMode(buttonPinEnter, INPUT_PULLUP);
  bootCounter = 0;
  u8g2.begin(buttonPinEnter, U8X8_PIN_NONE, U8X8_PIN_NONE, buttonPinL, buttonPinR, U8X8_PIN_NONE);
  initGame(level);
 
  WiFi.begin(ssid, password);
}


void loop(void) {
  runBoot();
  checkDoublePress();
  if (menuActive) {
    showMenu();
    e.check();
  }
  else if(menuSelection == 0){
    thotcoin();
  }
  else if(menuSelection == 1){
    thotstore();
  }
  else if(menuSelection == 2){
    runSpaceInvaders();
  }
  else if(menuSelection == 3){
    casino();
  }
  else if(menuSelection == 4){
    allyourcoin();
  }
  else if(menuSelection == 5){
   onemilliondollars();
  }
  else if(menuSelection == 6){
   konami();
  }
  else if(menuSelection == 7){
  }
  else if(menuSelection == 8){
  }
  else if(menuSelection == 9){
    internet();
  }
  
  ESP.wdtFeed();
}

