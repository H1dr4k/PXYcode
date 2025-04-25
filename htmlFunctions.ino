///////////////////////////////////////////////////////////////////////////////////////////
//               HTML FUNCTIONS                   /////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void handleRoot() {                               //                                     //
  server.send(200, "text/html", controlWebpage);  // Takes you to the control interface  //
}  ////////////////////////////////////////////////////////////////////////////////////////
void patternPlus() {                              //                                     //
  patternNumber++;                                // Increases the pattern number by 1   //
  startingTime = millis();                        // Updates the time                    //
  server.send(200, "text/html", controlWebpage);  // Takes you to the control interface  //
}  ////////////////////////////////////////////////////////////////////////////////////////
void patternMinus() {                             //                                     //
  if (1 == patternNumber) {                       //                                     //
    patternNumber = numberOfPatterns;             // Jumps to the last pattern           //
    startingTime = millis();                      // Updates the time                    //
  } else {                                        //                                     //
    patternNumber--;                              // Decreases the pattern number by 1   //
    startingTime = millis();                      // Updates the time                    //
  }                                               //                                     //
  server.send(200, "text/html", controlWebpage);  // Takes you to the control interface  //
}  ////////////////////////////////////////////////////////////////////////////////////////
void groupPlus() {                                //                                     //
  groupNumber++;                                  // Increases the group number by 1     //
  patternNumber = 1;                              // Resets the pattern number to 1      //
  numberOfPatterns = 1;                           // Resets the number of patterns  to 1 //
  startingTime = millis();                        // Updates the time                    //
  server.send(200, "text/html", controlWebpage);  // Takes you to the control interface  //
}  ////////////////////////////////////////////////////////////////////////////////////////
void groupMinus() {                               //                                     //
  if (1 == groupNumber) {                         //                                     //
    groupNumber = numberOfGroups;                 // Jumps to the last pattern           //
    startingTime = millis();                      // Updates the time                    //
  } else {                                        //                                     //
    groupNumber--;                                // Decreases the pattern number by 1   //
    startingTime = millis();                      // Updates the time                    //
  }                                               //                                     //
  server.send(200, "text/html", controlWebpage);  // Takes you to the control interface  //
}  ////////////////////////////////////////////////////////////////////////////////////////
void brightPlus() {                               //                                     //
  if (10 > brightness) {                          //                                     //
    brightness++;                                 // Increases the group number by 1     //
  }                                               //                                     //
  server.send(200, "text/html", controlWebpage);  // Takes you to the control interface  //
}  ////////////////////////////////////////////////////////////////////////////////////////
void brightMinus() {                              //                                     //
  if (1 < brightness) {                           //                                     //
    brightness--;                                 // Increases the group number by 1     //
  }                                               //                                     //
  server.send(200, "text/html", controlWebpage);  // Takes you to the control interface  //
}  ////////////////////////////////////////////////////////////////////////////////////////
void batteryCheck() {                             //                                     //
  strip.show();                                   //                                     //
  batteryDisplay();                               // Shows the battery charge            //
  server.send(200, "text/html", controlWebpage);  // Takes you to the control interface  //
}  ////////////////////////////////////////////////////////////////////////////////////////
void standBy() {                                  //                                     //
  patternNumber = 0;                              // Resets to stand-by pattern          //
  startingTime = millis();                        // Updates the time                    //
  server.send(200, "text/html", controlWebpage);  // Takes you to the control interface  //
}  ////////////////////////////////////////////////////////////////////////////////////////
void autoCycleSwitch() {                          //                                     //
  autoCycle = !autoCycle;                         // activates or deactivates auto cycle //
  startingTime = millis();                        // Updates the time                    //
  server.send(200, "text/html", controlWebpage);  // Takes you to the control interface  //
}  ////////////////////////////////////////////////////////////////////////////////////////
void wifiSyncSwitch() {                           //                                     //
  allowSync = !allowSync;                         // activates or deactivates ESPnow Sync//
  server.send(200, "text/html", controlWebpage);  // Takes you to the control interface  //
}  ////////////////////////////////////////////////////////////////////////////////////////
