///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!////////////////
//////////>                             Wi-Fi                              <///////////////
//////////> Choose a Name:                                                 <///////////////
//////////>                                                                <///////////////
const char *Name = "Test_Controler";
//////////>                                                                <///////////////
//////////>                                                                <///////////////
//////////> Choose a Password:                                             <///////////////
//////////>                                                                <///////////////
const char *Password = "1234567890";
//////////>                                                                <///////////////
//////////>                                                                <///////////////
//////////> Choose a Channel:                                              <///////////////
//////////>                                                                <///////////////
uint8_t wifiChannel = 3;
//////////>                                                                <///////////////
///////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!////////////////
////////>   v  v  v  v  v    PATTERNS GO BELOW THIS LINE    v  v  v  v  v    </////////////
// _____________________________________________________________________________________ //



// _____________________________________________________________________________________ //
////////>   ^  ^  ^  ^  ^    PATTERNS GO ABOVE THIS LINE    ^  ^  ^  ^  ^    </////////////
///////////////////////////////////////////////////////////////////////////////////////////
//         LIBRARIES            ///////////////////////////////////////////////////////////
#include <Adafruit_NeoPixel.h>  ////                                           ////////////
#include <WiFi.h>               ////                                           ////////////
#include <WiFiClient.h>         ////       <<<    SOFTWARE LIBRARIES           ////////////
#include <WebServer.h>          ////                                           ////////////
#include <ESPmDNS.h>            ////                                           ////////////
// include: basic, draw, setup, and html functions ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//   HARDWARE CONFIG  /////////////////////////////////////////////////////////////////////
#define LED_PIN 4    // LED data pin, recommended: 2 (D4) on NodeMCUESP8266, 10 (D10) on XIAOesp32C3, 4 on SuperMini
#define LED_COUNT 18 // Number of LEDs to be controlled on the strip (hight of the pixel resolution)
#define BUTTON_PIN 9  // Buttnon pin, use 0 for NodeMCUESP8266 buit-in button, 9 for XIAOESP32C3
///////////////////////////////////////////////////////////////////////////////////////////
/////////       NETWORK CONFIG       //////////////////////////////////////////////////////
WebServer server(80);                // Select server port, default: 80                  //
IPAddress IPaddr(10, 1, 1, 1);       // Select IP address to access user network interface, default: 10, 1, 1, 1
IPAddress IPmask(255, 255, 255, 0);  // Select IP mask for the network, default: 255, 255, 255, 0
///////////////////////////////////////////////////////////////////////////////////////////
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);  ///
///////////////////////////////////////////////////////////////////////////////////////////
///////     GLOBAL VARIABLES     //////////////////////////////////////////////////////////
uint8_t brightness = 5;          // <= Variable to keep track of the brightness level, shpuld only go from 1 to 10, brightness % = (n*n/100), updates by user request (network only)
uint8_t numberOfPatterns = 0;    // <= Variable to keep track of the number of patterns, auto updates, starts at 0
uint8_t patternNumber = 1;       // <= Variable to keep track of the current pattern number, starts at 0 to begin on stand-by or at 1 to begin with the first pattern, updates by user request (button short press or network)
uint8_t numberOfGroups = 1;      // <= Variable to keep track of the number of groups, auto updates, starts at 1
uint8_t groupNumber = 1;         // <= Variable to keep track of the current group number, starts at 1, updates by user request (button long press or network)
bool allowSync = 1;              // <= Unused for now                                    //
bool autoCycle = 1;              // <= variable to keep track of auto cycle state (1 = auto cycle on, 0 = auto cycle off)
bool oldState = HIGH;            // <= variable to keep track of the button last state, starts at HIGH = depressed (oldState should be updated every time the button is pressed or unpressed)
unsigned long startingTime = 0;  // <= Variable to keep track of the time on timed patterns, starts at 0 (startingTime should be updated every time there's a change in the pattern number)
///////////////////////////////////////////////////////////////////////////////////////////
//                               USER INTERFACE IN HTML                                  //
String controlWebpage = R"***(<!DOCTYPE html><html><head><title>    WiFi Control  
</title><style>body{background-color:#000000;color:#555666;}  </style></head><body>
<h1 style="background-color:#300323;font-family:Arial;font-size:89px;color:#C0C0FE;
text-align:center;">WiFi Control</h1><h3 style="background-color:#300323;font-family:
Arial; font-size: 29px; text-align: right;margin-top:-43px;">       by Haa Kuh 
&nbsp;</h3> <div style= "font-size: 59px;text-align:center;
  background:linear-gradient(to top,black 0%,#300323 100%);">                      
  <a href="/PM"><button style= "border:none ;border-radius:100px; background-color:
  #223322;font-family:Arial Black;font-size:31px;color: #FFFFFF;width:200px;height:
  200px;"> <h1> < </h1> </button></a>
  <button style="border-radius : 66px ; border : none ; background-color : #191119;
  color:#C0FFEE;font-size:31px;width:300px;height:200px;"> <h1>PATRON</h1></button>
  <a href="/PP"><button style= "border:none ;border-radius:100px; background-color:
  #223322;font-family:Arial Black;font-size:31px;color: #FFFFFF;width:200px;height:
  200px;"> <h1> > </h1> </button></a>                                      <br><br>
  <a href="/GM"><button style= "border:none ;border-radius:100px; background-color:
  #223322;font-family:Arial Black;font-size:31px;color: #FFFFFF;width:200px;height:
  200px;"> <h1> < </h1> </button></a>
  <button style="border-radius : 66px ; border : none ; background-color : #191119;
  color:#C0FFEE;font-size:31px;width:300px;height:200px;"> <h1>GRUPO</h1> </button>
  <a href="/GP"><button style= "border:none ;border-radius:100px; background-color:
  #223322;font-family:Arial Black;font-size:31px;color: #FFFFFF;width:200px;height:
  200px;"> <h1> > </h1> </button></a>                                      <br><br>
  <a href="/BM"><button style= "border:none ;border-radius:100px; background-color:
  #233723;font-family:Arial Black;font-size:31px;color: #FFFFFF;width:200px;height:
  200px;"> <h1> - </h1> </button></a>
  <button style="border-radius : 66px ; border : none ; background-color : #191119;
  color:#C0FFEE;font-size:31px;width:300px;height:200px;"> <h1>BRILLO</h1></button>
  <a href="/BP"><button style= "border:none ;border-radius:100px; background-color:
  #223322;font-family:Arial Black;font-size:31px;color: #FFFFFF;width:200px;height:
  200px;"> <h1> + </h1> </button></a>                                      <br><br>
  <a href="/AC"><button style= "border-radius:100px; border: none;background-color:
  #192919;font-family:Arial;font-size:23px;color:#C0C0FE;width:200px;height:200px;">
  <h1>PLAY</h1></button></a>
  <a href="/SB"><button style= "border-radius:100px; border: none;background-color:
  #192919;font-family:Arial;font-size:23px;color:#C0C0FE;width:280px;height:200px;">
  <h1>STANDBY</h1></button></a>
  <a href="/WS"><button style= "border-radius:100px; border: none;background-color:
  #192919;font-family:Arial;font-size:23px;color:#C0C0FE;width:200px;height:200px;">
  <h1>SYNC</h1></button></a></div></body></html>)***"; ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//      SETUP        //////////////////////////////////////////////////////////////////////
void setup() {       //                                                                  //
  basicSetup();      // Define button pin input method, initializes the LEDs and serials //
  serverSetup();     // Initializes HTML server                                          //
  batteryDisplay();  // Displays the battery charge                                      //
}  ////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//      MAIN LOOP         /////////////////////////////////////////////////////////////////
void loop() {             //                                                             //
  server.handleClient();  // Listens for network requests                                //
  cycle();                // Cycles through patterns and groups                          //
  buttonCheck();          // Checks and respond to button press                          //
  StandBy();              // Stands by                                                   //
  drawPatterns();         // Draw selected patterns                                      //
}  ///////////////////////////////////////! THE END !//////////////////////////////////////