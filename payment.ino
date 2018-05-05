int level_check(int pay_out, int eeprom_place){
  int eeprom_value;
  EEPROM.get(0,thotcoin_counter);
  eeprom_value=EEPROM.read(eeprom_place);
      
  if(eeprom_value==255 || eeprom_value==0){ // 255 is the initial EEPROM value (i.e. if you've never paid/played
//Serial.println(eeprom_value);
    if(thotcoin_counter>=pay_out){
      thotcoin_counter=thotcoin_counter-pay_out;
      EEPROM.put(0, thotcoin_counter);
      EEPROM.write(eeprom_place,1); // Swap 255 for 1
      EEPROM.commit();
      return 1;
    } else if(eeprom_value==1){
      return 1; // 1 should be the value if you've paid for the game
    } else if(eeprom_value==2){
      return 2; // 2 should be the value if you've beaten the game
    }
  } 
}

