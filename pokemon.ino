void pokemon(){
  internet();
  int8_t menuItemsCount = 6;
  buttonStateEnter = digitalRead(buttonPinEnter);
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_5x7_mf);
    u8g2.setFontRefHeightAll();
    u8g2.setDrawColor(1);

    drawMenu("POKEMON", curMenuItem, "Up\nDown\nLeft\nRight\nA\nB", menuItemsCount,0);

    if (buttonStateEnter != lastcoinstate) {
      if(curMenuItem==0){
        //Up
      } else if (curMenuItem==1){
        //Down
      } else if (curMenuItem==2){
        //Left
      } else if (curMenuItem==3){
        //Right
      } else if (curMenuItem==4){
        //A
      } else if (curMenuItem==5){
        //B
      }
      delay(50);
    }
    lastcoinstate = buttonStateEnter;
  } while (u8g2.nextPage() );
}
