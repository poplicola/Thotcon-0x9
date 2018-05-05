
void casino() {
  //delay(3000);  // connect, get your random number, maybe you loose or win some coin based on odd or even.  The terrible float math brings variances on the order of tens to hundreds
  // if (!client.connected()) {
  u8g2.setFont(u8g2_font_5x8_mr);
  if (client.connect(host, 42782)) {
    //delay(500);
    long coin = client.parseInt();
    if (delayTrigger > 0) {
       u8g2.firstPage();
    do {
        u8g2.drawStr(10, 20, "flipping coin...");
        u8g2.drawStr(5,30, "betting half");
        u8g2.drawStr(5,40,"of thotcoins...");
        delayTrigger --;
    }while(u8g2.nextPage());
    }
      else {
        if(coin % 2){
          EEPROM.get(0,thotcoin_betting);
          thotcoin_betting =  (int)thotcoin_betting*1.5;
          EEPROM.put(0,thotcoin_betting);
          EEPROM.commit();
          flipCompleted = true;
        } else {
          EEPROM.get(0,thotcoin_betting);
          thotcoin_betting = (int)thotcoin_betting*0.5;
          EEPROM.put(0,thotcoin_betting);
          EEPROM.commit();
          flipCompleted = true;
        }
        u8g2.firstPage();
    do {
        if (coin % 2)
        {
          u8g2.drawStr(20, 30, "Win coin: ");
          
           
        }
        else {
          u8g2.drawStr(20, 30, "Lost coin: ");
          
           
        }
       
        }while(u8g2.nextPage());
      } 
  if (flipCompleted){
    delay(3000);
    flipCompleted = false;
    menuActive = true;
    delayTrigger = 10;
  }
}}

