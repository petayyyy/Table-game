#define NUM_LEDS 576
#include "FastLED.h"
#define PIN 6 // pin led
CRGB leds[NUM_LEDS];

bool players = 0;
uint8_t id[9];
String str;
int pose(uint8_t x, uint8_t y){
  for (uint8_t i = 0; i < 3; i++) { 
    if (y % 2 == 0){
      id[i] = y*72 + x*3 + i*24;
      id[i+1] = y*72 + x*3 +1 + i*24;
      id[i+2] = y*72 + x*3 +2 + i*24;
    }
    else{
      id[i] = y*72 + x*3 + i*24 + 2;
      id[i+1] = y*72 + x*3 +1 + i*24;
      id[i+2] = y*72 + x*3 + i*24;
    }
  }
}
void led_move(){
  for(uint8_t i = 0; i < 9; i++) {
      leds[id[i]] = CRGB::White; 
  }
  FastLED.show(); delay(30); 
}
void led_xp(uint8_t xp){
  if (xp == 2){
    for(uint8_t i = 0; i < 9; i++) {
      leds[id[i]] = CRGB::Green; 
  }
  }
  else if (xp == 3){
    for(uint8_t i = 0; i < 9; i++) {
      if (i % 3 == 0){
        leds[id[i]] = CRGB::Red;
      }
  }
  }
  else if (xp == 4){
    for(uint8_t i = 0; i < 9; i++) {
      if (i % 3 == 1){
        leds[id[i]] = CRGB::Red;
      }
  }
  }
  else if (xp == 5){
    for(uint8_t i = 0; i < 9; i++) {
      if (i % 3 == 2){
        leds[id[i]] = CRGB::Red;
      }
  }
  }
  FastLED.show(); delay(30); 
}
//void start(){
//  for(int i = 0; i < 24; i++) {
//      if (pose[i][-1] == 2){
//        led_xp(pose[i]);
//        } 
//      }
//}

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(50);
 }

void loop() {
  if (Serial.available() > 0) {
    String n = Serial.readString();
    if (n[0] == '1'){
       //Serial.println(F("New players"));
       Serial.println(players);
       players = 1;
    }
    else if (n[0] == '2'){
      //Serial.println(F("Led"));
      str = n[2];
      int x2 = str.toFloat();
      str = n[4];
      int y2 = str.toFloat();
      pose(x2,y2);
      
      Serial.println(id[1]);

    }
    else if (n[0] == '3'){
      //Serial.println(F("Move"));
      str = n[2];
      int x1 = str.toFloat();
      str = n[4];
      int y1 = str.toFloat();
      str = n[6];
      int x2 = str.toFloat();
      str = n[8];
      int y2 = str.toFloat();
    }
    else if (n[0] == '4'){
      // Serial.println(F("Damage"));
       str = n[2];
       int x1 = str.toFloat();
       str = n[4];
       int y1 = str.toFloat();
       //led_xp(pose[24*y1+x1]);
       //pose[24*y2+x2][-1] += 1;
    }
//    Serial.println();
}
}
