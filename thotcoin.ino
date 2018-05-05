// TODO: Switch everything over to EEPROM

void thotcoin() {
  EEPROM.get(0,thotcoin_counter);
  pickaxe=EEPROM.read(20);
  //Serial.println(EEPROM.read(20));
  coin_n=EEPROM.read(21);
  //Serial.println(EEPROM.read(21));
  u8g2.firstPage();
  do {
    byte x {0}; byte y {0};
    char str[8];
    itoa( thotcoin_counter, str, 10 );
    u8g2.setFont(u8g2_font_5x7_mf);
    u8g2.setFontRefHeightAll();
    x = 10;
    y = 20;
    u8g2.setDrawColor(2);
    u8g2.drawStr(x, y, "THOTCOIN MINER:");
    u8g2.drawStr(x, y + 10, "THE GAME");
    u8g2.drawStr(x, y + 30, str);
    buttonStateEnter = digitalRead(buttonPinEnter);

    if (buttonStateEnter != lastcoinstate) {
      if (buttonStateEnter == LOW) {
      
        Serial.println("INSIDE == LOW");
        thot_rand = random(0, coin_n);
        if (thot_rand == 9) {
          coin_n = (int)coin_n * 1.5;
          if(pickaxe==0){// Change this to 255 before putting on badge REMOVE
            thotcoin_counter+=255;
          } else{
            thotcoin_counter=thotcoin_counter+(255*pickaxe);
          }
          EEPROM.put(0, thotcoin_counter);
          EEPROM.write(21,coin_n);
          EEPROM.commit();
        }
      }
      delay(50);
    }
    lastcoinstate = buttonStateEnter;

    u8g2.drawBox(0,0,102,10);
    u8g2.setCursor(0,8);
    if(pickaxe==5){
      u8g2.print("Pick Axe x2");
    } else if(pickaxe==10){
      u8g2.print("Pick Axe x3");
    } else if(pickaxe==15){
      u8g2.print("Pick Axe x4");
    }

    // MENU BACK
  } while (u8g2.nextPage() );
}
