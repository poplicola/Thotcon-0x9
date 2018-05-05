String makeMD5 (String text){
  byte bbuff[16];
  String hash = "";
      MD5Builder nonce_md5;  
      nonce_md5.begin();
      nonce_md5.add(text);  
      nonce_md5.calculate();  
      nonce_md5.getBytes(bbuff);
      for ( byte i = 0; i < 16; i++) hash += byte2hex(bbuff[i]);
      return hash;   
}

String byte2hex(byte Zahl){
  String Hstring = String(Zahl, HEX);
  if (Zahl < 16){Hstring = "0" + Hstring;}
  return Hstring;
}
