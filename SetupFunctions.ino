///////////////////////////////////////////////////////////////////////////////////////////
//                   SETUP FUNCTIONS                     //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void basicSetup() {                   //                                                 //
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Define button pin input method                  //
  strip.begin();                      // Initializes the LED strip                       //
  Serial.begin(9600);                 // Initializes USB serial communication            //
  Serial.begin(115200);               // Initializes Wi-Fi serial communication          //
}  ////////////////////////////////////////////////////////////////////////////////////////
void serverSetup() {                          //                                         //
  WiFi.mode(WIFI_AP_STA);                     // Set access point and station            //
  WiFi.softAP(Name, Password, wifiChannel);   // Network's Name, Password and Channel    //
  WiFi.softAPConfig(IPaddr, IPaddr, IPmask);  // IP address and IP mask go here          //
  Serial.println();                           // Message                                 //
  Serial.print("Go to this link for App: ");  // Message                                 //
  Serial.println();                           // Message                                 //
  Serial.print("http://");                    // Message (Local URL should go here)      //
  Serial.println(WiFi.softAPIP());            // Message                                 //
  /////////////////////////////////////////////////////////////////////////////////////////
  server.on("/", handleRoot);         // User interface                                  //
  server.on("/PP", patternPlus);      // Next Pattern html function                      //
  server.on("/PM", patternMinus);     // Previous Pattern html function                  //
  server.on("/GP", groupPlus);        // Next Group html function                        //
  server.on("/GM", groupMinus);       // Previous Group html function                    //
  server.on("/BP", brightPlus);       // Brightness Increase html function               //
  server.on("/BM", brightMinus);      // Brightness Decrease html function               //
  server.on("/SB", standBy);          // Stand-by html function                          //
  server.on("/BC", batteryCheck);     // Battery Check html function (Not enabled)       //
  server.on("/AC", autoCycleSwitch);  // Auto cycle switch function                      //
  server.on("/WS", wifiSyncSwitch);   // WiFi Sync switch function                       //
  server.begin();                     // Initializes Server                              //
}  ////////////////////////////////////////////////////////////////////////////////////////
