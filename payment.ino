int level_check(int pay_out, int eeprom_place){
  int eeprom_value;
  EEPROM.get(0,thotcoin_counter);
  eeprom_value=EEPROM.read(eeprom_place);
      
  if(eeprom_value==255 || eeprom_value==0){ 
    if(thotcoin_counter>=pay_out){
      thotcoin_counter=thotcoin_counter-pay_out;
      EEPROM.put(0, thotcoin_counter);
      EEPROM.write(eeprom_place,1); 
      EEPROM.commit();
      return 1;
    } else if(eeprom_value==1){
      return 1; //If game is paid for
    } else if(eeprom_value==2){
      return 2; //If game is beaten
    }
  } 
}

