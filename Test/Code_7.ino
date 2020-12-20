#define NUM_LEDS 576
#include "FastLED.h"
#define PIN 13 // pin led
CRGB leds[NUM_LEDS];

bool players = 0;
int id[9];
String str;
void pose_out(){
  for(uint8_t i = 0; i < 9; i++) {
    Serial.println(id[i]);
  }
}
int pose(uint8_t x, uint8_t y){
  if (y % 2 == 0){
      id[0] = y*72 + x*3;id[1] = y*72 + x*3 +1;id[2] = y*72 + x*3 +2;
      id[3] = y*72  + 24 + (23-3*x); id[4] = y*72 + 24 + (23-3*x-1); id[5] = y*72  + 24 +(23-3*x-2);
      id[6] = y*72 + x*3 + 24*2;id[7] = y*72 + x*3 +1 + 24*2;id[8] = y*72 + x*3 +2 + 24*2;
  }
  else{
      id[0] = y*72 + (23-3*x);id[1] = y*72 + (23-3*x-1);id[2] = y*72 + (23-3*x-2);
      id[3] = y*72 + x*3 + 24; id[4] = y*72 + x*3 + 1 + 24; id[5] = y*72 + x*3 +24 + 2;
      id[6] = y*72 + 24*2 + (23-3*x);id[7] = y*72 + (23-3*x-1) + 24*2;id[8] = y*72 + 24*2 +(23-3*x-2);
  }
}
void led_move(int f){
  if (f == 1){
  for(int i = 0; i < 9; i++) {
      leds[id[i]] = CRGB::White; 
  }}
  else{
    for(int i = 0; i < 9; i++) {
      leds[id[i]] = CRGB::Black; 
  }
  }
  FastLED.show(); delay(30); 
}
void led_xp(uint8_t xp){
  if (xp == 0){
    for(uint8_t i = 0; i < 9; i++) {
      leds[id[i]] = CRGB::Black;     }
  }
  else if (xp == 1){
    for(uint8_t i = 0; i < 9; i++) {
      leds[id[i]] = CRGB::Green;     }
  }
  else if (xp == 2){
    for(uint8_t i = 0; i < 9; i++) {
      if (i % 3 == 0){
        leds[id[i]] = CRGB::Red;
      }
    }
  }
  else if (xp == 3){
    for(uint8_t i = 0; i < 9; i++) {
      if (i % 3 == 1){
        Serial.print(id[i]);
        leds[id[i]] = CRGB::Red;
      }
    }
  }
  else if (xp == 4){
    for(uint8_t i = 0; i < 9; i++) {
      if (i % 3 == 2){
        leds[id[i]] = CRGB::Red;
      }
  }
  }
  FastLED.show(); delay(30); 

}
void start(){
  if (players == 0){
    pose(1,0);
    led_xp(1);
    pose(3,0);
    led_xp(1);
    pose(5,0);
    led_xp(1);
    pose(7,0);
    led_xp(1);
    pose(6,1);
    led_xp(1);
    pose(4,1);
    led_xp(1);
    pose(2,1);
    led_xp(1);
    pose(0,1);
    led_xp(1);
  } 
  else{
    pose(0,6);
    led_xp(1);
    pose(2,6);
    led_xp(1);
    pose(4,6);
    led_xp(1);
    pose(6,6);
    led_xp(1);
    pose(7,7);
    led_xp(1);
    pose(5,7);
    led_xp(1);
    pose(3,7);
    led_xp(1);
    pose(1,7);
    led_xp(1);
  }
}

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(50);
 }

void loop() {
  if (Serial.available() > 0) {
    String n = Serial.readString();
    if (n[0] == '1'){ // Если введено "1", то введено это то инициализируется новый пользователь(0,1).
       Serial.println(F("New players"));
       Serial.println(players);
       start();
       players = 1;
    }
    else if (n[0] == '2'){ // Если введено "2 1 1 1", то введено загориться путь до точки 1 1 при 1 или выключиться при 0.
      Serial.println(F("Led"));
      str = n[2];
      int x2 = str.toFloat();
      str = n[4];
      int y2 = str.toFloat();
      str = n[6];
      int f = str.toFloat();
      pose(x2,y2);
      //pose_out();
      led_move(f);
}
    else if (n[0] == '3'){ // Если введено "3 1 1 2 2 2", то введено произойдет движение от 1 1 до 2 2 с состоянием здоровья 2. 
      Serial.println(F("Move"));
      str = n[2];
      int x1 = str.toFloat();
      str = n[4];
      int y1 = str.toFloat();
      str = n[6];
      int x2 = str.toFloat();
      str = n[8];
      int y2 = str.toFloat();
      str = n[10];
      int xp = str.toFloat();
      pose(x1,y1);
      led_xp(0);
      pose(x2,y2);
      led_xp(xp);
    }
    else if (n[0] == '4'){ // Если введено "4 1 1 2", то введено произойдет инициализация здоровья персонажа.
       Serial.println(F("Damage"));
       str = n[2];
       int x1 = str.toFloat();
       str = n[4];
       int y1 = str.toFloat();
       str = n[6];
       int xp = str.toFloat();
       pose(x1,y1);
       Serial.print(xp);
       led_xp(xp); // 2, 3 , 4
    }
    Serial.println();
}
}
