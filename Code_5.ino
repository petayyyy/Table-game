#include <Adafruit_NeoPixel.h>
#define PIN 6 // номер порта к которому подключен модуль
#define count_led 576 // количество светодиодов 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(count_led, PIN, NEO_GRB + NEO_KHZ800); //first number change does distance between colors


bool players = 0;
int id[9];
String str;
int pose(uint8_t x, uint8_t y){
  if (y % 2 == 0){
      id[0] = y*72 + x*3;id[1] = y*72 + x*3 +1;id[2] = y*72 + x*3 +2;
      id[3] = y*72 + x*3 + 24 + (23-3*x); id[4] = y*72 + x*3 + 24 + (23-3*x-1); id[5] = y*72 + x*3 + 24 +(23-3*x-2);
      id[6] = y*72 + x*3 + 24*2;id[7] = y*72 + x*3 +1 + 24*2;id[8] = y*72 + x*3 +2 + 24*2;
  }
  else{
      id[0] = y*72 + x*3 + (23-3*x);id[1] = y*72 + x*3 + (23-3*x-1);id[2] = y*72 + x*3 +(23-3*x-2);
      id[3] = y*72 + x*3 + 24; id[4] = y*72 + x*3 + 1 + 24; id[5] = y*72 + x*3 +24 + 2;
      id[6] = y*72 + x*3 + 24*2 + (23-3*x);id[7] = y*72 + x*3 + (23-3*x-1) + 24*2;id[8] = y*72 + x*3 + 24*2 +(23-3*x-2);
  }
}
void led_move(){
  for(uint8_t i = 0; i < 9; i++) {
    pixels.setPixelColor(id[i], pixels.Color(255,255,255)); //цвет "White"
  }
  pixels.show();
}
void led_xp(uint8_t xp){
  if (xp == 1){
    for(uint8_t i = 0; i < 9; i++) {
     pixels.setPixelColor(id[i], pixels.Color(0,255,0)); //цвет "Green" 
    }
  }
  else if (xp == 2){
    for(uint8_t i = 0; i < 9; i++) {
      if (i % 3 == 0){
          pixels.setPixelColor(id[i], pixels.Color(255,0,0)); //цвет "Red"
      }
    }
  }
  else if (xp == 3){
    for(uint8_t i = 0; i < 9; i++) {
      if (i % 3 == 1){
          pixels.setPixelColor(id[i], pixels.Color(255,0,0)); //цвет "Red"
      }
    }
  }
  else if (xp == 4){
    for(uint8_t i = 0; i < 9; i++) {
      if (i % 3 == 2){
          pixels.setPixelColor(id[i], pixels.Color(255,0,0)); //цвет "Red"
      }
  }
  }
  pixels.show();
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
  pixels.begin();
  pixels.show(); // Устанавливаем все светодиоды в состояние "Выключено"
 }

void loop() {
  if (Serial.available() > 0) {
    String n = Serial.readString();
    if (n[0] == '1'){
       Serial.println(F("New players"));
       Serial.println(players);
       start();
       players = 1;
    }
    else if (n[0] == '2'){
      Serial.println(F("Led"));
      str = n[2];
      int x2 = str.toFloat();
      str = n[4];
      int y2 = str.toFloat();
      pose(x2,y2);
      led_move();
}
    else if (n[0] == '3'){
      Serial.println(F("Move"));
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
       Serial.println(F("Damage"));
       str = n[2];
       int x1 = str.toFloat();
       str = n[4];
       int y1 = str.toFloat();
       str = n[4];
       int xp = str.toFloat();
       led_xp(xp); // 2, 3 , 4
    }
    Serial.println();
}
}
