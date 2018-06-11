## Include headers

### <i class="fa fa-code"></i> AutoConnect.h

```cpp
#include <AutoConnect.h>
```

#### Define macros

```cpp
#define AC_DEBUG                                // Monitor message output activation
#define AC_DEBUG_PORT           Serial          // Default message output device
#define AUTOCONNECT_AP_IP       0x01F4A8C0      // Default SoftAP IP
#define AUTOCONNECT_AP_GW       0x01F4A8C0      // Default SoftAP Gateway IP
#define AUTOCONNECT_AP_NM       0x00FFFFFF      // Default subnet mask
#define AUTOCONNECT_DNSPORT     53              // Default DNS port at captive portal
#define AUTOCONNECT_HTTPPORT    80              // Default HTTP
#define AUTOCONNECT_MENU_TITLE  "AutoConnect"   // Default AutoConnect menu title
#define AUTOCONNECT_STARTUPTIME 10              // Default waiting time[s] for after reset
#define AUTOCONNECT_URI         "/_ac"          // Default AutoConnect root path
#define AUTOCONNECT_TIMEOUT     30000           // Default connection timeout[ms]
```

## AutoConnect API

### <i class="fa fa-code"></i> Constructors

#### AutoConnect

```cpp
AutoConnect()
```

<a id="withparameter"></a>

AutoConnect default constructor. This entry activates WebServer internally and the web server is allocated internal.

```cpp
AutoConnect(ESP8266WebServer& webServer)
```

Run the AutoConnect site using the externally ensured ESP 8266 WebServer. User's added URI handler response can be included in handleClient method.
<dl class="apidl">
    <dt>**Parameters**</dt>
    <dd><span class="apidef">webServer</span>A reference of ESP8266WebServer instance.</dd>
</dl>

### <i class="fa fa-code"></i> Public member functions

#### begin

```cpp
bool begin()
```  
```cpp
bool begin(const char* ssid, const char* passphraase)
```  
```cpp
bool begin(const char* ssid, const char* passphraase, unsinged long timeout)
```

Starts establishing WiFi connection. Before establishing, start the Web server and DNS server for the captive portal. Then begins connection establishment in WIFI_STA mode. If connection can not established with the specified SSID and password, switch to WIFI_AP_STA mode and activate SoftAP.
<dl class="apidl">
    <dt>**Parameters**</dt>
    <dd><span class="apidef">ssid</span>SSID to be connected.</dd>
    <dd><span class="apidef">passphrase</span>Password for connection.</dd>
    <dd><span class="apidef">timeout</span>A time out value in milliseconds for waiting connection.</dd>
    <dt>**Return value**</dt>
    <dd><span class="apidef">true</span>Connection established, AutoConnect service started with WIFI_STA mode.</dd>
    <dd><span class="apidef">false</span>Could not connected, Captive portal started with WIFI_AP_STA mode.</dd>
</dl>

#### config

```cpp
bool config(AutoConnectConfig& config)
```  
```cpp
bool config(const char* ap, const char* password = nullptr)
```

Sets SoftAP's WiFi configuration. 
<dl class="apidl">
    <dt>**Parameters**</dt>
    <dd><span class="apidef">config</span>Reference to AutoConnectConfig containing SoftAP's parameters.</dd>
    <dd><span class="apidef">ap</span>SSID for SoftAP. The default value is **esp8266ap**.</dd>
    <dd><span class="apidef">password</span>Password for SodtAP. The default value is **12345678**.</dd>
    <dt>**Return value**</dt>
    <dd><span class="apidef">true</span>Successfully configured.</dd>
    <dd><span class="apidef">false</span>Configuration parameter is invalid, some values out of range.</dd>
</dl>

#### end

```cpp
void end()
```

Stops AutoConnect captive portal service. Release ESP8266WebServer and DNSServer. 

!!! warning "Attention to end"
    The end function releases the instance of ESP8266WebServer and DNSServer. It can not process them after the end function.

#### handleClient

```cpp
void handleClient()
```

Handling for the AutoConnect web interface. Invoke the handleClient of the parent web server to process client request of the AutoConnect WEB interface. No effects when the web server is not available.

#### handleRequest

```cpp
void handleRequest()
```

Handling for the AutoConnect menu request.

!!! warning "About used in combination with handleClient"
    The handleRequest function is not supposed to use with AutoConnect::handleClient. It should be used with ESP8266::handleClient.

#### home

```cpp
void home(String uri)
```

Put a user site's home URI. The URI specified by home is linked from "HOME" in the AutoConnect portal menu.
<dl class="apidl">
    <dt>**Parameters**</dt>
    <dd><span class="apidef">uri</span> A URI string of user site's home path.</dd>
</dl>

#### host

Returns the reference of the ESP8266WebServer which is allocated in AutoConnect automatically.

```cpp
ESP8266WebServer& host()
```
<dl class="apidl">
    <dt>**Return value**</dt>
    <dd>A reference of the ESP8266WebServer.</dd>
</dl>

!!! note "&reference is not a pointer"
    A reference cannot be re-assigned, and must be assigned at initialization. It's like as bind as alias.      
    ```cpp
    ESP8266WebServer& server = portal.host();
    server.handleClient();
    ```
    or  
    ```cpp
    portal.host().handleClient();
    ```

#### onDetect

```cpp
void onDetect(DetectExit_ft fn)
```
Register the function which will call from AutoConnect at the start of the captive portal.
<dl class="apidl">
    <dt>**Parameters**</dt>
    <dd><span class="apidef">fn</span>Function called at the captive portal start.</dd>

</dl>

An *fn* specifies the function called when the captive portal starts. Its prototype declaration is defined as "*DetectExit_ft*".

```cpp
typedef std::function<bool(IPAddress softapIP)>  DetectExit_ft
```
<dl class="apidl">
    <dt>**Parameters**</dt>
    <dd><span class="apidef">softapIP</span>An IP address of SoftAP for the captive portal.</dd>
    <dt>**Retuen value**</dt>
    <dd><span class="apidef">true</span>Continues captive portal handling.</dd>
    <dd><span class="apidef">false</span>Cancel the captive portal. AutoConnect::begin function will return with a false.</dd>
</dl>

#### onNotFound

```cpp
void onNotFound(ESP8266WebServer::THandlerFunction fn)
```
Register the handler function for undefined URL request detected.
<dl class="apidl">
    <dt>**Parameters**</dt>
    <dd><span class="apidef">fn</span>A function of the "not found" handler.</dd>
</dl>

## AutoConnectConfig API

### <i class="fa fa-code"></i> Constructor

#### AutoConnectConfig

```cpp
AutoConnectConfig();
```  
```cpp
AutoConnectConfig(const char* ap, const char* password);
```
<dl class="apidl">
    <dt>**Parameters**</dt>
    <dd><span class="apidef">ap</span>SSID for SoftAP. The length should be up to 31. The default value is **esp8266ap**.</dd>
    <dd><span class="apidef">password</span>Password for SodtAP. The length should be from 8 to up to 63. The default value is **12345678**.</dd>
</dl>

### <i class="fa fa-code"></i> Public member variables

#### apid
SoftAP's SSID.
<dl class="apidl">
    <dt>**Type**</dt>
    <dd>String</dd>
</dl>

#### apip

Sets IP address for Soft AP in captive portal. When AutoConnect fails the initial WiFi.begin, it starts the captive portal with the IP address specified this.
<dl class="apidl">
    <dt>**Type**</dt>
    <dd><span class="apidef" style="width:230px;">IPAddress</span>The default value is **192.168.244.1**</dd>
</dl>

#### autoReset

Reset ESP8266 module automatically after WLAN disconnected.
<dl class="apidl">
    <dt>**Type**</dt>
    <dd>bool</dd>
    <dt>**Value**</dt>
    <dd><span class="apidef" style="width:230px;">true</span>Reset after WiFi disconnected automatically.</dd>
    <dd><span class="apidef" style="width:230px;">false</span>No reset.</dd>
</dl>

#### autoRise

Captive portal activation switch. False for disabling the captive portal. It prevents starting the captive portal even if the connection at the first *WiFi.begin* fails.
<dl class="apidl">
    <dt>**Type**</dt>
    <dd>bool</dd>
    <dt>**Value**</dt>
    <dd><span class="apidef" style="width:230px;">true</span>Enable the captive portal. This is the default.</dd>
    <dd><span class="apidef" style="width:230px;">false</span>Disable the captive portal.</dd>
</dl>

#### autoSave

The credential saved automatically at the connection establishment.
<dl class="apidl">
    <dt>**Type**</dt>
    <dd>AC_SAVECREDENTIAL_t</dd>
    <dt>**Value**</dt>
    <dd><span class="apidef" style="width:230px;">AC_SAVECREDENTIAL_AUTO</span>The credential saved automatically. This is the default.</dd>
    <dd><span class="apidef" style="width:230px;">AC_SAVECREDENTIAL_NEVER</span>The credential no saved.</dd>
</dl>

#### boundaryOffset

Sets the offset address of the credential storage area for EEPROM. This value must be between greater than 4 and less than flash sector size. (4096 by SDK)  
The default value is 0.
<dl class="apidl">
    <dt>**Type**</dt>
    <dd>uint16_t</dd>
</dl>

!!! warning "It will conflict with user data."
    If the sketch leaves this offset at zero, it will conflict the storage area of credentials with the user sketch owned data. It needs to use the behind of credential area.

#### channel

The channel number of WIFi when SoftAP starts.
<dl class="apidl">
    <dt>**Type**</dt>
    <dd>uint8_t</dd>
    <dt>**Value**</dt>
    <dd>1 ~ 14. The default value is 1.</dd>
</dl>

!!! info "How do I choose Channel"
    Espressif Systems had announced the [application note](https://www.espressif.com/sites/default/files/esp8266_wi-fi_channel_selection_guidelines.pdf) about Wi-Fi channel selection.

#### gateway

Sets gateway address for Soft AP in captive portal. When AutoConnect fails the initial WiFi.begin, it starts the captive portal with the IP address specified this.
<dl class="apidl">
    <dt>**Type**</dt>
    <dd><span class="apidef" style="width:230px;">IPAddress</span>The default value is **192.168.244.1**</dd>
</dl>

#### hidden

Sets SoftAP to hidden SSID.
<dl class="apidl">
    <dt>**Type**</dt>
    <dd>uint8_t</dd>
    <dt>**Value**</dt>
    <dd><span class="apidef" style="width:230px;">0</span>SSID will be appeared. This is the default.</dd>
    <dd><span class="apidef" style="width:230px;">1</span>SSID will be hidden.</dd>
</dl>

#### homeUri

Sets the home path of user sketch. This path would be linked from 'HOME' in the AutoConnect menu.
<dl class="apidl">
    <dt>**Type**</dt>
    <dd>String</dd>
</dl>

#### netmask

Sets subnet mask for Soft AP in captive portal. When AutoConnect fails the initial WiFi.begin, it starts the captive portal with the IP address specified this.
<dl class="apidl">
    <dt>**Type**</dt>
    <dd><span class="apidef" style="width:230px;">IPAddress</span>The default value is **255.255.255.0**</dd>
</dl>

#### psk

Sets password for SoftAP. The length should be from 8 to up to 63. The default value is **12345678**.
<dl class="apidl">
    <dt>**Type**</dt>
    <dd>String</dd>
</dl>

### <i class="fa fa-code"></i> AutoConnectConfig example

```arduino
AutoConenct        Portal;
AutoConenctConfig  Config("", "passpass");    // SoftAp name is determined at runtime
Config.apid = ESP.hostname();                 // Retrieve host name to SotAp identification
Config.apip = IPAddress(192,168,10,101);      // Sets SoftAP IP address
Config.gateway = IPAddress(192,168,10,1);     // Sets WLAN router IP address
Config.netmask = IPAddress(255,255,255,0);    // Sets WLAN scope
Config.autoSave = AC_SAVECREDENTIAL_NEVER;    // No save credential
COnfig.boundaryOffet = 64;                    // Reserve 64 bytes for the user data in EEPROM. 
Config.homeUri = "/index.html"				  // Sets home path of the sketch application
Portal.config(Config);                        // Configure AutoConnect
Portal.begin();                               // Starts and behaves captive portal
```

## <i class="fa fa-gift"></i> Something extra

The library presents two PNG icons which can be used to embed a hyperlink to the AutoConnect menu.

- Bar type <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAApklEQVRYR2NkGGDAOMD2M4w6YDQEkEMgEJggZwCxGI0T5mug+alAvBFkD7IDXtLBcpjfXgEZ4ugOeAETpHEIgIwHeVYC3QH+0CgAS9AQgCwHRcFmdAfQ0E7cRo9mw0EVAqPlAKhwEKVTVsBZDsyiQ2k4Wg6gxPKgyoZ0Sn+o1iCHQBBQaiYQi9DYJTjbAyAJWluOtz0wWg7QOOqxGz+aDUdDYMBDAACA0x4hs/MPrwAAAABJRU5ErkJggg==" title="AutoConnect menu" alt="AutoConnect menu" />
- Cog type <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAC2klEQVRIS61VvWsUQRSfmU2pon9BUIkQUaKFaCBKgooSb2d3NSSFKbQR/KrEIiIKBiGF2CgRxEpjQNHs7mwOUcghwUQ7g58IsbGxEBWsb2f8zR177s3t3S2cA8ftzPu993vzvoaSnMu2vRKlaqgKp74Q/tE8qjQPyHGcrUrRjwlWShmDbFMURd/a6TcQwNiYUmpFCPElUebcuQ2vz6aNATMVReHEPwzfSSntDcNwNo2rI+DcvQzhpAbA40VKyV0p1Q9snzBG1qYVcYufXV1sREraDcxpyHdXgkfpRBj6Uwm2RsC5dxxmZ9pdOY9cKTISRcHTCmGiUCh4fYyplTwG2mAUbtMTBMHXOgK9QfyXEZr+TkgQ1oUwDA40hEgfIAfj+HuQRaBzAs9eKyUZ5Htx+T3ZODKG8DzOJMANhmGomJVMXPll+hx9UUAlzZrJJ4QNCDG3VEfguu7mcpmcB/gkBOtShhQhchAlu5jlLUgc9ENgyP5gf9+y6LTv+58p5zySkgwzLNOIGc8sEoT1Lc53NMlbCQQuvMxeCME1NNPVVkmH/i3IzzXDtCSA0qQQwZWOCJDY50jsQRjJmkslEOxvTcDRO6zPxOh5xZglKkYLhWM9jMVnkIsTyMT6NBj7IbOCEjm6HxNVVTo2WXqEWJZ1T8rytB6GxizyDkPhWVpBqfiXUtbo/HywYJSpA9kMamNNPZ71R9Hcm+TMHHZNGw3EuraXEUldbfvw25UdOjqOt+JhMwJd7+jSTpZaEiIcaCDwPK83jtWnTkwnunFMtxeL/ge9r4XItt1RNNaj/0GAcV2bR3U5sG3nEh6M61US+Qrfd9Bs31GGulI2GOS/8dgcQZV1w+ApjIxB7TDwF9GcNzJzoA+rD0/8HvPnXQJCt2qFCwbBTfRI7UyXumWVt+HJ9NO4XI++bdsb0YyrqXmlh+AWOLHaLqS5CLQR5EggR3YlcVS9gKeH2hnX8r8Kmi1CAsl36QAAAABJRU5ErkJggg==" title="AutoConnect menu" alt="AutoConnect menu" />

To reference the icon, use the **AUTOCONNECT_LINK** macro in the sketch. It expands into the string literal as an HTML ```<a></a>``` tag with PNG embedded of the AutoConnect menu hyperlinks. Icon type is specified by the parameter of the macro.

<dl class="apidl">
    <dd><span class="apidef">BAR_24</span>Bars icon, 24x24.</dd>
    <dd><span class="apidef">BAR_32</span>Bars icon, 32x32.</dd>
    <dd><span class="apidef">BAR_48</span>Bars icon, 48x48.</dd>
    <dd><span class="apidef">COG_24</span>Cog icon, 24x24.</dd>
    <dd><span class="apidef">COG_32</span>Cog icon, 32x32.</dd>
</dl>

!!! note "Usage"
    ```arduino
    String html = "<html>";
    html += AUTOCONNECT_LINK(BAR_32);
    html += "</html>";
    server.send(200, "text/html", html);
    ```

