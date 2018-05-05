void initGame(int lvl) {
  s = Metro(300), b = Metro(150), e = Metro(1000);
  s.reset();
  b.reset();
  e.reset();
  if (lvl == 1) {
    ship =  new Ship(51, 60);
    score = 0;
  }
  else {
    ship->setX(51);
    ship->setY(62); //reset ship position
  }
  //Enemy initialization
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 3; j++) {
      enemy[(i - 1) * 3 + j - 1] = new Enemy(10 * i + 2, 30 - 9 * (j - 1), lvl);
    }
  }
  //draw the level
  drawShip(ship->getX(), ship->getY());
  drawLives(ship->getLives());
  for (int i = 0; i < nr_enemy; i++) {
    drawEnemy(enemy[i]->getX(), enemy[i]->getY());
  }
}
void drawShip(int ShipX, int ShipY) {
  u8g2.drawBox(ShipX - 5, ShipY, 2, 3);
  u8g2.drawBox(ShipX - 1, ShipY, 2, 3);
  u8g2.drawBox(ShipX - 3, ShipY + 1, 3, 2);
  u8g2.drawVLine(ShipX - 3, ShipY - 3, 3);
}

void drawEnemy(int x, int y) {
  u8g2.drawBox(x - 3, y - 2, 7, 3);
  u8g2.drawPixel(x - 3, y + 1);
  u8g2.drawPixel(x - 3, y + - 3);
  //u8g2.drawPixel(x - 3, y + 3);
  u8g2.drawPixel(x + 3, y + 1);
  u8g2.drawPixel(x + 3, y - 3);
  //u8g2.drawVLine(x - 3, y - 1, 3);
  //u8g2.drawPixel(x - 1, y - 1);
  //u8g2.drawPixel(x - 1, y + 1);
}


void moveShip() {
  buttonStateL = digitalRead(buttonPinL);
  buttonStateR = digitalRead(buttonPinR);
  buttonStateEnter = digitalRead(buttonPinEnter);
  if (buttonStateL == LOW) {
    ship->move(-1);
    drawShip(ship->getX(), ship->getY());
  }
  if (buttonStateR == LOW) {
    ship->move(1);
    drawShip(ship->getX(), ship->getY());
  }
}

void moveBullet() {
  if (ShipBullet->getExist() == 1) {
    //the bullet exists
    u8g2.drawHLine(ShipBullet->getX(), ShipBullet->getY(), 3);
    ShipBullet->move();
    u8g2.drawHLine(ShipBullet->getX(), ShipBullet->getY(), 3);
    for (int i = 0; i < nr_enemy; i++) {
      if (ShipBullet->collisionEnemy(enemy[i]) == 1) {
        enemy[i]->setDead();
        score += 100;
      }
    }
  }
  if (EnemyBullet->getExist() == 1) {//the bullet exists
    u8g2.drawHLine(EnemyBullet->getX(), EnemyBullet->getY(), 3);
    EnemyBullet->move();
    u8g2.drawVLine(EnemyBullet->getX() + 3, EnemyBullet->getY(), 5);
    if (EnemyBullet->collisionShip(ship) == 1) {
      ship->setLives(ship->getLives() - 1);
      ship->setX(51);
      ship->setY(60);
    }
  }
}
int remaining_enemys() {
  int k = 0;
  for (int i = 0; i < nr_enemy; i++) {
    if (enemy[i]->Alive()) {
      k++;
    }
  }
  return k;
}

void moveEnemy() {
  bounce = 0;
  //Serial.print("before loop: ");
          //Serial.println(ESP.getFreeHeap());
  for (int i = 0; i < nr_enemy; i++) { //le misc
    if (bounce == 0 && enemy[i]->Alive() == true && enemy[i]->move() == 1) {
      for (int j = 0; j < nr_enemy; j++) { //schimb directia la toti ceilalti
        if (j < i) {
          
          enemy[j]->update(1);
          
        }
        else if (j > i) {
          enemy[j]->update(0);
        }
      }
      bounce = 1;
    }
  }
  //Serial.print("after loop: ");
          //Serial.println(ESP.getFreeHeap());
}
void drawShips() {
  drawShip(ship->getX(), ship->getY());
  drawLives(ship->getLives());
  for (int i = 0; i < nr_enemy; i++) { //desenez toate navele inamice
    if (enemy[i]->Alive()) { //daca inamicul na fost doborat inca
      drawEnemy(enemy[i]->getX(), enemy[i]->getY()); //il desenez
      if (enemy[i]->Defeat()) {
        //play = 2;
      }

      if ((int)random(chance_shoot) == 0) { //enemy shoots bullet
        addBullet(enemy[i]->getX(), enemy[i]->getY(), 3, 0);
      }
    }
  }
  //bullets
  if (ShipBullet->getExist() == 1) {
    u8g2.drawVLine(ShipBullet->getX(), ShipBullet->getY(), 3);
  }
  if (EnemyBullet->getExist() == 1) {
    u8g2.drawVLine(EnemyBullet->getX(), EnemyBullet->getY(), 3);
  }
}
void drawLives(unsigned short int lives) {
  for (int i = 0; i < lives; i++) {
    drawL(2 + i * 7, 1);
  }
}

void drawL(int x, int y) {
  u8g2.drawBox(x + 1, y, 5, 3);
  u8g2.drawPixel(x + 2, y - 1);
  u8g2.drawPixel(x + 4, y - 1);
  u8g2.drawHLine(x + 2, y + 3, 3);
  u8g2.drawPixel(x + 3, y + 4);
}
void addBullet(byte x, byte y, byte newSpeed, char side) {
  //  side == 1 -> my ship, else enemy ship
  if (side == 1 && ShipBullet->getExist() == 0) {
    ShipBullet = new Bullet(x, y, newSpeed);
  }
  else if (side == 0 && EnemyBullet->getExist() == 0) {
    EnemyBullet = new Bullet (x, y, newSpeed);
  }
}

void showPause() {
  // display.clearDisplay();
  //display.drawBitmap(30, 8, pause, 8, 32);
  // display.display();
}
void displayScore( int score){
  u8g2.setFont(u8g2_font_5x8_mr);
  u8g2.setCursor(75, 6);
  u8g2.print(score);
  u8g2.setCursor(0, 0);
}

void runSpaceInvaders() {
  
  ESP.wdtFeed();
  if (e.check() == 1) {
    moveEnemy();
  }
  if (b.check() == 1) {
    moveShip();
    moveBullet();
  }

  u8g2.firstPage();

  do {
    drawShips();
    displayScore(score);
    if (play == 0) {
        buttonsPressed();

        if (ship ->getLives() == 0) {
          level += 1;
          initGame(level);
          u8g2.setFont(u8g2_font_profont22_tf);
          u8g2.drawStr(25,30,"YOU");
          u8g2.drawStr(20,45,"LOSE");
          
          
        }
        else if(remaining_enemys() == 0){
          u8g2.setFont(u8g2_font_profont22_tf);
          //u8g2.drawStr(30,30,"YOU");
          //u8g2.drawStr(28,40,"WIN!");
          u8g2.setFont(u8g2_font_5x8_mr);
          u8g2.drawStr(10,10,"Unlocked DLC:");
          u8g2.drawStr(10,30,"thotcon.org/dlc");
          
          EEPROM.write(31,2);
          EEPROM.commit();
        }
      
    }
    else if (play == 1) {
      buttonsPressed();
      showPause();

    }
    else {
      //displayScore(score);
      buttonsPressed();

    }

  } while (u8g2.nextPage() );
  if (ship ->getLives() == 0) {
          delay(3000);
          menuActive = true;
          play=0; // this should fix the bug where you have to reset the entire device
          level = 1;
          initGame(level);
        }
   else if(remaining_enemys() == 0){
          delay(5000);
          menuActive = true;
        }
}

