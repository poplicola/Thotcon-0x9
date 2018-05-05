void buttonsPressed() {
  buttonStateL = digitalRead(buttonPinL);
  buttonStateR = digitalRead(buttonPinR);
  buttonStateEnter = digitalRead(buttonPinEnter);
   if(menuActive){
    if(buttonStateL != lastButtonStateL){
      if(buttonStateL==LOW){
       if(menuSelection >0){
        menuSelection --;
       }
      }
      delay(50);
    }
    lastButtonStateL=buttonStateL;
    if(buttonStateR != lastButtonStateR){
      if(buttonStateR==LOW){
       if(menuSelection <9){
        menuSelection ++;
       }
      }
      delay(50);
    }
    lastButtonStateR=buttonStateR;
     if(buttonStateEnter != lastButtonStateEnter){
      if(buttonStateEnter==LOW){
   //     menuActive = false;
                  //Serial.println(level_check(200,33));
       if(menuSelection == 0){
        menuActive = false;
       }
       else if (menuSelection == 1){
        if(level_check(250,30) == 1){
        menuActive = false;
        }
        
       }
       else if (menuSelection == 2){
        if(level_check(1500,31) == 1){

        menuActive = false;
        }
       }
       
       else if (menuSelection == 3){
        if(level_check(25000,32) == 1){
        menuActive = false;
        }
       }
       else if (menuSelection == 4){
        if(level_check(50000,33) == 1){
        menuActive = false;
        }
      }
       else if (menuSelection == 5){
        if(level_check(1000000,34) == 1){
        menuActive = false;
        }
       }
       else if (menuSelection == 6){
        menuActive = false;
       }
       else if (menuSelection == 9){
        menuActive = false;
       }
       
       
      }
      delay(50);
    }
    lastButtonStateEnter=buttonStateEnter;
   }
   else if (play == 0) {
    if(buttonStateEnter == LOW){
       addBullet(ship->getX(), ship->getY(), -3, 1);
      }
    }
}

void showMenu(){
  buttonsPressed();
  if(menuPricing){
    u8g2.firstPage();
    do{
     u8g2.setFont(u8g2_font_5x8_mr);
          u8g2.setBitmapMode(1);
    u8g2.setDrawColor(1);
    u8g2.drawVLine(24,0,64);
    u8g2.drawVLine(48,0,64);
    u8g2.drawHLine(0,20,72);
    u8g2.drawHLine(0,41,72);
    u8g2.setDrawColor(2);
    //slot 1
    u8g2.drawXBM( 0, 0, X_width, X_height, X_icon);
    u8g2.drawStr(34,13,"1");
    u8g2.drawStr(56,13,"10");
   u8g2.drawStr(5,34,"25k");
    u8g2.drawStr(29,34,"50k");
    u8g2.drawStr(56,34,"1m");
    //u8g2.drawStr(7,55,"1m");
    //u8g2.drawStr(30,55,"1m");
    //u8g2.drawStr(56,55,"1m");

    u8g2.setFont(u8g2_font_helvB12_tf);
    u8g2.setFontMode(1);
    u8g2.drawStr(82, 28, "T");
    u8g2.drawStr(82, 43, "P");
    u8g2.drawStr(82, 58, "P");
    u8g2.drawFrame(76,11,22,51);
      menuPricing = false;
    } while (u8g2.nextPage());
    delay(2300);
    } else {
  u8g2.firstPage();
  do {
    u8g2.setBitmapMode(1);
    u8g2.setDrawColor(1);
    u8g2.drawVLine(24,0,64);
    u8g2.drawVLine(48,0,64);
    u8g2.drawHLine(0,20,72);
    u8g2.drawHLine(0,41,72);
    
    if(menuSelection <3){
    u8g2.drawBox(1 + (menuSelection * 25), 1, 21, 18);
    } else if (menuSelection >=3 && menuSelection < 6){
      u8g2.drawBox(1 + ((menuSelection -3) * 25), 22, 21, 18);
    } else if (menuSelection >=6 && menuSelection < 9){
      u8g2.drawBox(1 + ((menuSelection -6) * 25), 43, 21, 18);
    } else {
      u8g2.drawBox(77,12,20,49);
    }
    u8g2.setDrawColor(2);

    //slot 1
    u8g2.drawXBM( 0, 0, X_width, X_height, X_icon);
    //slot 2
    if(level_check(1,30) == 2){
    u8g2.drawXBM( 25, 0, X_width, X_height, X_icon);
    } else {
      u8g2.drawXBM( 25, 0, X_width, X_height, O_icon);
    }
    //slot 3
    if(level_check(10,31) == 2){
    u8g2.drawXBM( 49, 0, X_width, X_height, X_icon);
    } else {
      u8g2.drawXBM( 49, 0, X_width, X_height, O_icon);
    }
    //slot 4
    if(level_check(10,32) == 2){
    u8g2.drawXBM( 0, 22, X_width, X_height, X_icon);
    } else {
      u8g2.drawXBM( 0, 22, X_width, X_height, O_icon);
    }
    //slot 5
    if(level_check(10,33) == 2){
    u8g2.drawXBM( 25, 22, X_width, X_height, X_icon);
    } else {
      u8g2.drawXBM( 25, 22, X_width, X_height, O_icon);
    }
    //slot 6
    if(level_check(10,34) == 2){
    u8g2.drawXBM( 49, 22, X_width, X_height, X_icon);
    } else {
      u8g2.drawXBM( 49, 22, X_width, X_height, O_icon);
    }
    //slot 7
    if(level_check(10,34) == 2){
    u8g2.drawXBM( 0, 42, X_width, X_height, X_icon);
    } else {
      u8g2.drawXBM( 0, 42, X_width, X_height, O_icon);
    }
    //slot 8
    u8g2.drawXBM( 25, 42, X_width, X_height, O_icon);
    //slot 9
    u8g2.drawXBM( 49, 42, X_width, X_height, O_icon);
    
    u8g2.setFont(u8g2_font_helvB12_tf);
    u8g2.setFontMode(1);
    u8g2.drawStr(82, 28, "T");
    u8g2.drawStr(82, 43, "P");
    u8g2.drawStr(82, 58, "P");
    u8g2.drawFrame(76,11,22,51);
  } while (u8g2.nextPage());
    }
}
