///////////////////////////////////////////////////////////////////////////////////////////
//                   BASIC FUNCTIONS                     //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void batteryDisplay() {                                  // Future feature :P            //
  unsigned const int batteryDisplayTime = 757;           // <= Time in milliseconds for the battery charge to display
  for (int i = 1; i < LED_COUNT; i++) {                  // Sets all but the first LED   //
    strip.setPixelColor(i, 0, 0, 0);                     // ...to off                    //
  }                                                      // ¿Read battery level?         //
  int batteryCharge = 77;                                // Variable for future battery charge display feature, right now it's fixed as if batery was 77% charged
  strip.setPixelColor(0, 50 - (77 * 0.5), 77 * 0.5, 0);  // Sets the color of the first LED according to the "battery charge"
  strip.show();                                          // Displays the "battery charge"//
  //Serial.println("Battery Charge: :P ");               // USB serial report            //
  delay(batteryDisplayTime);                             // Delays to have time to see it//
}  ////////////////////////////////////////////////////////////////////////////////////////
void cycle() {                                              //                           //
  unsigned const int patternScoutingTime = 11;              // <= Time in milliseconds to allow looking for new patterns before looping back to the first
  unsigned const int groupScoutingTime = 11;                // <= Time in milliseconds to allow looking for new groups before looping back to the first
  if ((groupNumber > numberOfGroups)                        // Checks if the group number has exceeded the number of groups, if so, it jumps back to group 1
      && ((millis() - startingTime) > groupScoutingTime)    //                           //
      && (digitalRead(BUTTON_PIN) == HIGH)) {               //                           //
    groupNumber = 1;                                        //                           //
  }                                                         //                           //
  if ((patternNumber > numberOfPatterns)                    // Checks if the pattern number has exceeded the number of patterns, if so, it jumps back to pattern 1
      && ((millis() - startingTime) > patternScoutingTime)  //                           //
      && (digitalRead(BUTTON_PIN) == HIGH)) {               //                           //
    patternNumber = 1;                                      //                           //
  }                                                         //                           //
}  ////////////////////////////////////////////////////////////////////////////////////////
void buttonCheck() {                                             //                      //
  unsigned const int buttonDelay = 7;                            // <= Time in milliseconds for button rebounce prevention (buttonDelay should be used every time there's a change in the button oldState), high values cause latency
  unsigned const int LongPressTimer = 757;                       // <= Time in milliseconds to account for a long press of the button
  if ((digitalRead(BUTTON_PIN) == LOW) && (oldState == HIGH)) {  // Checks if the button has just been pressed, if so...
    oldState = LOW;                                              // Updates button state
    delay(buttonDelay);                                          // Delays to prevent button rebounce
    startingTime = millis();                                     // Updates the time
    for (int i = 0; i < LED_COUNT; i++) {                        // Uses index i to keep track of each LED beyond the first
      strip.setPixelColor(i, 0, 0, 0);                           // Sets every LED on the stip to off
      strip.show();                                              // Turns off LED strip  //
    }                                                            //                      //
  }                                                              //                      //
  /////////////////////////////////////////////////////////////////////////////////////////
  if ((oldState == LOW) && ((millis() - startingTime) > LongPressTimer)) {  // Checks if the button has been pressed long enough to be considered a long press (this should be the only thing happenning while the button is being pressed), if so...
    if (groupNumber < LED_COUNT) {                                         // Checks if the group number can be displayed on the LED strip, if so...
      strip.setPixelColor(groupNumber, 0, 0, 69);                           // Sets to blue the LED corresponding to the group number
      strip.show();                                                         // Shows the number of the next group to be displayed on the LED strip
    }                                                                       //           //
    //if (numberOfGroups <= groupNumber) {                                    // Checks if the number of groups can be displayed on the LED strip, if so...
    //  strip.setPixelColor(0, 0, 0, 69);                                     // Sets to blue the LED corresponding to the number of groups
    //  strip.show();                                                         // Shows the number of the next group to be displayed on the LED strip
    //}                                                                       //           //
  }  //           //
  /////////////////////////////////////////////////////////////////////////////////////////
  if ((digitalRead(BUTTON_PIN) == HIGH) && (oldState == LOW)) {  // Checks if the button has just been depressed, if so...
    if ((millis() - startingTime) < LongPressTimer) {            // If it was short pressed...
      patternNumber++;                                           // Increase the pattern number by 1
    } else {                                                     // If it was long pressed...
      groupNumber++;                                             // Increase the group number by 1
      patternNumber = 1;                                         // Resets the pattern number for the new group, use 0 to begin new groups on stand-by pattern or 1 to begin on first pattern
      numberOfPatterns = 1;                                      // Resets the number of patterns to 1 for the new group
    }                                                            //                      //
    oldState = HIGH;                                             // Updates button state //
    delay(buttonDelay);                                          // Delays to prevent button rebounce
    startingTime = millis();                                     // Updates the time     //
  }                                                              //                      //
}  ////////////////////////////////////////////////////////////////////////////////////////
void StandBy() {                                                    //                   //
  if ((patternNumber == 0) && (digitalRead(BUTTON_PIN) == HIGH)) {  // This pattern number 0 is the stand-by pattern
    for (int i = 1; i < LED_COUNT; i++) {                           // Uses index i to keep track of each LED beyond the first
      strip.setPixelColor(i, 0, 0, 0);                              // Turns off each LED beyond the first
    }                                                               //                   //
    strip.setPixelColor(0, 0, 0, 1);                                // Sets the color of the first LED to the dimmest blue
    strip.show();                                                   // Displays the stand-by pattern
  }                                                                 //                   //
}  ////////////////////////////////////////////////////////////////////////////////////////
