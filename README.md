# ThotCon 0x9 Game Badge 
*This utilizes the ESP8266 display libraries and WiFi capabilities to:*
>*Display a boot-sequence of scrolling Morse code/binary/QR Code followed by a grid-based menu*
>*The user can then select **Space Invaders,  Pokemon, and ThotCoin currency (mine, purchase capabilities (gamble))***
### About the File(s)/Folder(s) in the Repo
								Code Files
>**data** folder
> >Contains a storm-trooper bit-map for the boot-sequence
>
>**boot-sequence.ino**
> >Scrolling Morse code and binary sequences, followed by a storm-trooper image and menu screen
>
>**gambler.ino**
>>When selected from the menu, this allows users to bet their ThotCoin for a chance to double
>
>
>**internet.ino**
>>Utilizes the hash string from unique_identifier.ino to connect to the internet, once capabilities have been purchased using store.ino, selected from the main menu
> 
>**konami.ino**
> >
> 
>**menu.ino**
> > Menu design and button logic
>  
>**million.ino**
> >
>
>**payment.ino**
> >Logic for differentiating game purchases and game completions
>
>**pokemon.ino**
> >Allows users to control a pokemon game using the 3 button inputs on the badge
>  
>**qrcode.ino**
> > Holds 2 arrays of hex values to compose the qrcode for the boot-sequence
>  
>**space_invaders.ino**
> >Button and design logic adapted from the ccostin93 repository of Arduino Space Invaders
	> https://github.com/ccostin93/Space-Invader-Arduino
>  
>**store.ino**
> >Allows users to spend their ThotCoin on multiplier pick axes, and WiFi capabilities to download more games
>  
>**thing_dev.ino**
> >Initializes user variables and menu capabilities
>  
>**thotcoin.ino**
> >ThotCoin miner game selected through the main menu
>  
>**unique_identifier.ino**
> >Uses the MD5 algorithm to generate a badge identifier
								
								Hardware Files
>**tc0x9-proto-BoM.xlsx**
> >Excel sheet containing all hardware specifications - purchased through Mouser
> 
> **tc0x9proto.pdf**
> >Hardware schematic 
>
>
>**Thotcon0x09Outline.dxf**
>>Badge cut-lines 

### Download and Setup Arduino IDE
> Download Arduino IDE version 1.6.4 or greater
> Go to **File > Preferences**
> At the bottom of the menu paste the following URL into the "Additional Board Manager URLs" Field and click "OK" http://arduino.esp8266.com/stable/package_esp8266com_index.json
> Go to **Tools > Boards > Boards Manager**
> Click esp8266 and click "Install"
> Go to **Tools > Boards Manager** and click "SparkFun ESP8266 Thing" from the list
> Within the **Tools** sub-menu 
> >Flash Mode: DIO
> >Flash Frequency: 80MHZ
> >Upload Using: Serial
> >CPU Frequency: 80MHz
> >Flash Size: 512K (no SPIFFS)
> >Reset Method: nodemcu
