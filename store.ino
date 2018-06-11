void thotstore(){
  int8_t menuItemsCount = 3;
  EEPROM.get(0,thotcoin_counter);
  pickaxe=EEPROM.read(20);
  wifi=EEPROM.read(21);
  buttonStateEnter = digitalRead(buttonPinEnter);
  u8g2.firstPage();
  do {
    byte x {0}; byte y {0};
    char str[8];
    itoa( thotcoin_counter, str, 10 );
    u8g2.setFont(u8g2_font_5x7_mf);
    u8g2.setFontRefHeightAll();
    u8g2.setDrawColor(2);
    u8g2.setFontMode(1);
    if(pickaxe==0 || pickaxe==255){// Change this to 255 before putting on badge REMOVE
      drawMenu("THOTCOIN STORE", curMenuItem, "Pick Axe x2 -$5\nLOCKED\nLOCKED", menuItemsCount, 1);
    } else if(pickaxe==5){
      drawMenu("THOTCOIN STORE", curMenuItem, "PURCHASED\nPick Axe x3 -$25\nLOCKED", menuItemsCount, 1);
    } else if(pickaxe==10){
      drawMenu("THOTCOIN STORE", curMenuItem, "PURCHASED\nPURCHASED\nPick Axe x4 -$50", menuItemsCount, 1);
    } else if (pickaxe==15 && wifi==0){
      drawMenu("THOTCOIN STORE", curMenuItem, "PURCHASED\nPURCHASED\nPURCHASED -$150", menuItemsCount, 1);
      EEPROM.write(30,2);
      EEPROM.commit();
    }
    
    // 0 = pick axe x2, 1 = pick axe x3, 2 = pick axe x4
    if (buttonStateEnter != lastcoinstate) {
      if(curMenuItem==0 && thotcoin_counter>=5 && buttonStateEnter==LOW){
        thotcoin_counter=thotcoin_counter-5;
        EEPROM.put(0, thotcoin_counter);
        EEPROM.write(20, 5);
        EEPROM.commit();
      } else if  (curMenuItem==1 && thotcoin_counter>=25 && buttonStateEnter==LOW && pickaxe==5){
        thotcoin_counter=thotcoin_counter-25;
        EEPROM.put(0, thotcoin_counter);
        EEPROM.write(20, 10);
        EEPROM.commit();
      } else if  (curMenuItem==2 && thotcoin_counter>=50 && buttonStateEnter==LOW && pickaxe==10){
        thotcoin_counter=thotcoin_counter-50;
        EEPROM.put(0, thotcoin_counter);
        EEPROM.write(20, 15);
        EEPROM.commit();
      } else if  (curMenuItem==3 && thotcoin_counter>=50 && buttonStateEnter==LOW && pickaxe==15){
        thotcoin_counter=thotcoin_counter-50;
        EEPROM.put(0, thotcoin_counter);
        EEPROM.write(21,1);
        EEPROM.commit();
      }
      delay(50);
    }
    lastcoinstate = buttonStateEnter;
    u8g2.drawBox(0,0,102,10);
    u8g2.setCursor(0,8);
    u8g2.print(str);
    u8g2.setCursor(50,8);
    u8g2.print("Coin");
    buttonPress(menuItemsCount);
  } while (u8g2.nextPage() );  
}
