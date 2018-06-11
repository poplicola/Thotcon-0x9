void internet(){
  MD5Builder md5;
  md5.begin();
  md5.add(WiFi.macAddress());
  md5.calculate();
  if (!client.connected()) {
   u8g2.firstPage();
  do {
    u8g2.drawStr(20,30,"loading...");
    } while (u8g2.nextPage());
    if (client.connect(host, 6667)) {
      while (client.connected())
      {
        checkDoublePress();
        if (client.available())
        {
           String line = client.readStringUntil('\n');
        }
      delay(5000);
      client.print("USER  us 8 *  : TC Badge2\r\n");
      if (client.available())
        {
           String line = client.readStringUntil('\n');
        }
      delay(2000);
      client.print("NICK t" + md5.toString().substring(0,29) + "\r\n");
      delay(2000);
      client.print("JOIN #thotcoin\r\n");
       if (client.available())
        {
           String line = client.readStringUntil('\n');
        }
      delay(7000);
  
   buttonStateL = digitalRead(buttonPinL);
   buttonStateR = digitalRead(buttonPinR);
   if(buttonStateL == LOW && buttonStateR == LOW){
    menuActive = true;
    client.stop();
    break;
   }
      handle_irc_connection();
      buttonStateL = digitalRead(buttonPinL);
   buttonStateR = digitalRead(buttonPinR);
   if(buttonStateL == LOW && buttonStateR == LOW){
    menuActive = true;
    client.stop();
    break;
   }
      }
    } 
    else {
      delay(2000);
    }
  }
}
  
#define IRC_BUFSIZE  32
char from[IRC_BUFSIZE];
char type[IRC_BUFSIZE];
char to[IRC_BUFSIZE];
int8_t menuItemsCount = 6;
void handle_irc_connection() {
  char c;
  while(true) {
   buttonStateL = digitalRead(buttonPinL);
   buttonStateR = digitalRead(buttonPinR);
   if(buttonStateL == LOW && buttonStateR == LOW){
    menuActive = true;
    break;
   }
   buttonPress(menuItemsCount);
    u8g2.firstPage();
  do {
    drawMenu("POKEMON", curMenuItem, "Up\nDown\nLeft\nRight\nA\nB", menuItemsCount,0);
    } while (u8g2.nextPage());
    if (buttonStateEnter != lastcoinstate) {
      if(curMenuItem==0){
        //Up
        client.print("PRIVMSG #thotcoin up\r\n");
      } else if (curMenuItem==1){
        client.print("PRIVMSG #thotcoin down\r\n");
      } else if (curMenuItem==2){
        //Left
        client.print("PRIVMSG #thotcoin left\r\n");
      } else if (curMenuItem==3){
        //Right
        client.print("PRIVMSG #thotcoin right\r\n");
      } else if (curMenuItem==4){
        //A
        client.print("PRIVMSG #thotcoin Z\r\n");
      } else if (curMenuItem==5){
        //B
        client.print("PRIVMSG #thotcoin X\r\n");
      }
      delay(500);
    }
    lastcoinstate = buttonStateEnter;
    ESP.wdtFeed();
    if(client.available()) {
      c = client.read();
    }
    else {
      continue;
    }
   
    if(c == ':') {
      memset(from, 0, sizeof(from));
      memset(type, 0, sizeof(type));
      memset(to, 0, sizeof(to));
      
      read_until(' ', from);
      read_until(' ', type);
      read_until(' ', to);
     
      if(strcmp(type, "PRIVMSG") == 0) {
        print_nick(from);
        ignore_until(':');
        print_until('\r');
      }
      else {
        
        ignore_until('\r');
      } 
    }
   
    else if (c == 'P') {
      char buf[5];
      memset(buf, 0, sizeof(buf));
      buf[0] = c;
      for(int i = 1; i < 4; i++) {
        c = client.read();
        buf[i] = c;
      }
      ignore_until('\r');
      if(strcmp(buf, "PING") == 0) {
        client.println("PONG\r");
        //Serial.println("PING->PONG");
      }
    }
  } 
   
}

void print_nick(char buffer[]) {
  for(int i = 0; i < IRC_BUFSIZE - 1; i++) {
    if(buffer[i] == '!') { 
      break; 
    }    
  }
}

int read_until(char abort_c, char buffer[]) {
  int bytes_read = 0;
  memset(buffer, 0, sizeof(buffer));
  for(int i = 0; i < IRC_BUFSIZE - 1; i++) {
    if (client.available()) {
      char c = client.read();  
      bytes_read++;
      if(c == abort_c) {
        return bytes_read;
      }
      else if (c == '\n') {
        return bytes_read;
      }
      buffer[i] = c;
    }
  }
  ignore_until(abort_c);
  return bytes_read;
}

void ignore_until(char c) {
  while(true){
    checkDoublePress();
    if (client.available()) {
      char curr_c = client.read();
      if (curr_c == c) {
        return;  
      }
    }
  }
}

void print_until(char c) {
  while(true){
    if (client.available()) {
      char curr_c = client.read();
      if (curr_c == c) {
        return;
      }
    }
  }
}



// reads characters from the connection until
// it hits the given character.
void print_until_endline() {
  while(true){
    checkDoublePress();
    if (client.available()) {
      char curr_c = client.read();
      if (curr_c == '\r') {
        curr_c = client.read();
        if (curr_c == '\n') { return; }
      }
    }
  }
}

