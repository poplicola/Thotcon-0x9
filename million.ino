void onemilliondollars(){
  int8_t menuItemsCount = 1;
  EEPROM.get(0,thotcoin_counter);
  buttonStateEnter = digitalRead(buttonPinEnter);
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_5x7_mf);
    u8g2.setFontRefHeightAll();
    u8g2.setDrawColor(2);
    u8g2.setFontMode(1);
    drawMenu("Pay Up", curMenuItem, "1,000,000", menuItemsCount, 1);
  
    if (buttonStateEnter != lastcoinstate) {
      if(curMenuItem==0 && thotcoin_counter>=1000000 && buttonStateEnter==LOW){
        thotcoin_counter=thotcoin_counter-1000000;
        EEPROM.put(0, thotcoin_counter);
        EEPROM.write(21,1);
        EEPROM.commit();
      }
      delay(50);
    }
    lastcoinstate = buttonStateEnter;
    buttonPress(menuItemsCount);
  } while (u8g2.nextPage() );
}
