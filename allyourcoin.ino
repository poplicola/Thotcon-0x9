void allyourcoin(){
  int8_t menuItemsCount = 1;
  EEPROM.get(0,thotcoin_counter);
  buttonStateEnter = digitalRead(buttonPinEnter);
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_5x7_mf);
    u8g2.setFontRefHeightAll();
    u8g2.setDrawColor(2);
    u8g2.setFontMode(1);
    u8g2.drawStr(0,10,"All Your Coin");
    u8g2.drawStr(0,20,"Are Belong to Us");
  } while (u8g2.nextPage() );
}
