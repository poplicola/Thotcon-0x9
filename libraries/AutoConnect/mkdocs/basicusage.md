## Simple usage

### <i class="fa fa-edit"></i> Embed to the sketches

How embed the AutoConnect to the sketches you have. Most simple approach to applying AutoConnect for the existing sketches, follow the below steps.

<img src="../images/BeforeAfter.svg" />

<ul class="ulsty-edit" style="list-style:none;">
  <li>Insert <code class="codehilite"><span class="cp">#include</span> <span class="cpf">&lt;AutoConnect.h&gt;</span></code> to behind of <code class="codehilite"><span class="cp">#include</span> <span class="cpf">&lt;ESP8266WebServer.h&gt;</span></code>.</li>
  <li>Insert <code class="codehilite"><span class="na">AutoConnect</span> <em>PORTAL(WEBSERVER);</em></code> to behind of <code class="codehilite"><span class="na">ESP8266WebServer</span> <em>WEBSERVER;</em></code> declaration.<sup id="fnref:1"><a class="footnote-ref" href="#fn:1" rel="footnote">1</a></sup></li>
  <li>Remove <code class="codehilite">WiFi.<span class="na">begin</span>(<em>SSID</em>,<em>PSK</em>)</code> and the subsequent logic for the connection status check.</li>
  <li>Replace <code class="codehilite"><em>WEBSERVER</em>.<span class="na">begin</span><span class="p">()</span></code> to <code class="codehilite"><em>PORTAL</em>.<span class="na">begin</span><span class="p">()</span></code>.<sup id="fnref:2"><a class="footnote-ref" href="#fn:2" rel="footnote">2</a></sup></li>
  <li>Replace <code class="codehilite"><em>WEBSERVER</em>.<span class="na">handleClient</span><span class="p">()</span></code> to <code class="codehilite"><em>PORTAL</em>.<span class="na">handleClient</span><span class="p">()</span></code>.<sup id="fnref:3"><a class="footnote-ref" href="#fn:3" rel="footnote">3</a></sup></li>
  <li>If the connection checks logic is needed, you can check the return value according to <code class="codehilite"><em>PORTAL</em>.<span class="na">begin</span><span class="p">()</span></code> with <code class="codehilite">true</code> or <code class="codehilite">false</code>.</li>
</ul>

[^1]:
Each *VARIABLE* conforms to the actual declaration in the sketches.  

[^2]:
WiFi SSID and Password can be specified AutoConnect::begin() too.

[^3]:
Replacement the **handleClient** method is not indispensable. AutoConnect can still connect with the captive portal as it is ESP8266WebServer::handleClient. But it can **not valid AutoConnect menu**.

## Basic usage

### <i class="fa fa-caret-right"></i> Basic logic sequence for the user sketches

#### 1. A typical logic sequence

!!! note ""
    1. <strong>Include headers,</strong> `ESP8266WebServer.h` and `AutoConnect.h`  
    2. <strong>Declare ESP8266WebServer variable.</strong>  
    3. <strong>Declare AutoConnect variable.</strong>  
    4. <strong>Implements the URL handler with the *function()*.</strong>  
    5. <strong>setup()</strong>  
       5.1 <strong>Sets URL handler *function()* to ESP8266WebServer by</strong>`ESP8266WebServer::on`<strong>.</strong>  
       5.2 <strong>Starts </strong>`AutoConnect::begin()`<strong>.</strong>  
       5.3 <strong>Check WiFi connection status.</strong>  
    6. <strong>loop()</strong>  
       6.1 <strong>Invokes </strong>`AutoConnect::handleClient()`<strong>, or invokes </strong>`ESP8266WebServer::handleClient()`<strong> then </strong>`AutoConnect::handleRequest()`<strong>.</strong>  
       6.2 <strong>Do the process for actual sketch.</strong>  

#### 2. Declare AutoConnect object

[Two options](#esp8266webserver-hosted-or-parasitic) are available for [AutoConnect constructor](api.md#constructors).

```arduino
AutoConnect VARIABLE(&ESP8266WebServer);
```
or

```arduino
AutoConnect VARIABLE;
```

- **The parameter with an ESP8266WebServer variable:** An ESP8266WebServer object variable must be declared. AutoConnect uses its variable to handles the [AutoConnect menu](menu.md).

- **With no parameter:** The sketch does not declare ESP8266WebServer object. In this case, AutoConnect allocates an instance of the ESP8266WebServer internally. The logic sequence of the sketch is somewhat different as the above. To register a URL handler function by *ESP8266WebServer::on* should be performed after [*AutoConnect::begin*](api.md#begin).

#### 3. No need WiFI.begin(...)

AutoConnect internally performs *WiFi.begin* to establish a WiFi connection. There is no need for a general process to establish a connection using *WiFi.begin* with a sketch code.

#### 4. Alternate ESP8266WebServer::begin()

[*AutoConnect::begin*](api.md#begin) executes *ESP8266WebServer::begin* internally too and it starts the DNS server to behave as a Captive portal. So it is not needed to call *ESP8266WebServer::begin* with the sketch.

!!! info "Why DNS Server starts"
    AutoConnect traps the detection of the captive portal and achieves a connection with the WLAN interactively by the AutoConnect menu. It responds SoftAP address to all DNS queries temporarily to trap. When the WLAN connection establishes, then stops DNS server.

#### 5. AutoConnect::begin with SSID and Password

SSID and Password can also specify by [*AutoConnect::begin*](api.me#begin). ESP8266 uses provided SSID and Password explicitly. If the connection false with specified SSID with Password then a captive portal is activated. SSID and Password are not present, ESP8266 SDK will attempt to connect using the still effectual SSID and password. Usually, it succeeds.

#### 6. Use ESP8266WebServer::on to handle URL

AutoConnect is designed to coexist with the process for handling the web pages by user sketches. The page processing function which will send an HTML to the client invoked by the "*on::ESP8266WebServer*" function is the same as when using ESP8266WebServer natively.

#### 7. Use either ESP8266WebServer::handleClient() or AutoConnect::handleClient()

Both classes member function name is the same: *handleClient*, but the behavior is different. Using the AutoConnect embedded along with ESP8266WebServer::handleClient has limitations. Refer to the below section for details. 

### <i class="fa fa-caret-right"></i> ESP8266WebServer hosted or parasitic

The interoperable process with an ESP8266WebServer depends on the parameters of the [AutoConnect constructor](api.md#constructors).

Declaration parameter for the constructor | Use ESP8266WebServer::handleClient only | Use AutoConnect::handleClient
----|----|---
[None](api.md#constructors) | AutoConnect menu not available.<br>To use AutoConnect menu, need [AutoConnect::handleRequest()](api.md#handlerequest).<br>also to use ESP8266WebServer natively, need [AutoConnect::host()](api.md#host). | AutoConnect menu available.<br>To use ESP8266WebServer natively, need [AutoConnect::host()](api.md#host).
[Reference to ESP8266WebServer](api.md#withparameter) | AutoConnect menu not available.<br>To use AutoConnect menu, need [AutoConnect::handleRequest()](api.md#handlerequest). | AutoConnect menu available.

- **By declaration for the AutoConnect variable with no parameter**: The ESP8266WebServer instance is hosted by AutoConnect automatically then the sketches use [*AutoConnect::host*](api.md#host) as API to get it after [*AutoConnect::begin*](api.md#begin) performed.

- **By declaration for the AutoConnect variable with the reference of ESP8266WebServer**: AutoConnect will use it. The sketch can use it is too.

- **In use ESP8266WebServer::handleClient()**: AutoConnect menu can be dispatched but not works normally. It is necessary to call [*AutoConnect::handleRequest*](api.md#void-handlerequest) after *ESP8255WebServer::handleClient* invoking.

- **In use [AutoConnect::handleClient()](api.md#void-handleclient)**: The handleClient() process and the AutoConnect menu is available without calling *ESP8266WebServer::handleClient*.

!!! info "Why AutoConnect::handleRequest is needed when using ESP8266::handleClient"
    The AutoConnect menu function may affect WiFi connection state. It follows that the menu process must execute outside *ESP8266WebServer::handleClient*.  
    [*AutoConnect::handleClient*](api.md#void-handleclient) is equivalent *ESP8266WebServer::handleClient* included [*AutoConnect::handleRequest*](api.md#void-handlerequest).

