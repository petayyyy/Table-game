#define NUM_LEDS 576
#include "FastLED.h"
#define PIN 6 // pin led
CRGB leds[NUM_LEDS];

const int stp_x = 13;const int dir_x = 12;const int stp_y = 11;const int dir_y = 10;
String str = "";
int x1 = 0; int x2 = 0; int y1 = 0; int y2 = 0;
bool players = 0;
int x_dist = 2; int y_dist = 3;int x_last = 0;int y_last = 0;

int pose[64][10] = {{ 0 , 1 , 2 , 24 , 25 , 26 , 48 , 49 , 50 , 0},
{ 3 , 4 , 5 , 27 , 28 , 29 , 51 , 52 , 53 , 0},
{ 6 , 7 , 8 , 30 , 31 , 32 , 54 , 55 , 56 , 0},
{ 9 , 10 , 11 , 33 , 34 , 35 , 57 , 58 , 59 , 0},
{ 12 , 13 , 14 , 36 , 37 , 38 , 60 , 61 , 62 , 0},
{ 15 , 16 , 17 , 39 , 40 , 41 , 63 , 64 , 65 , 0},
{ 18 , 19 , 20 , 42 , 43 , 44 , 66 , 67 , 68 , 0},
{ 21 , 22 , 23 , 45 , 46 , 47 , 69 , 70 , 71 , 0},
{ 72 , 73 , 74 , 96 , 97 , 98 , 120 , 121 , 122 , 0},
{ 75 , 76 , 77 , 99 , 100 , 101 , 123 , 124 , 125 , 0},
{ 78 , 79 , 80 , 102 , 103 , 104 , 126 , 127 , 128 , 0},
{ 81 , 82 , 83 , 105 , 106 , 107 , 129 , 130 , 131 , 0},
{ 84 , 85 , 86 , 108 , 109 , 110 , 132 , 133 , 134 , 0},
{ 87 , 88 , 89 , 111 , 112 , 113 , 135 , 136 , 137 , 0},
{ 90 , 91 , 92 , 114 , 115 , 116 , 138 , 139 , 140 , 0},
{ 93 , 94 , 95 , 117 , 118 , 119 , 141 , 142 , 143 , 0},
{ 144 , 145 , 146 , 168 , 169 , 170 , 192 , 193 , 194 , 0},
{ 147 , 148 , 149 , 171 , 172 , 173 , 195 , 196 , 197 , 0},
{ 150 , 151 , 152 , 174 , 175 , 176 , 198 , 199 , 200 , 0},
{ 153 , 154 , 155 , 177 , 178 , 179 , 201 , 202 , 203 , 0},
{ 156 , 157 , 158 , 180 , 181 , 182 , 204 , 205 , 206 , 0},
{ 159 , 160 , 161 , 183 , 184 , 185 , 207 , 208 , 209 , 0},
{ 162 , 163 , 164 , 186 , 187 , 188 , 210 , 211 , 212 , 0},
{ 165 , 166 , 167 , 189 , 190 , 191 , 213 , 214 , 215 , 0},
{ 216 , 217 , 218 , 240 , 241 , 242 , 264 , 265 , 266 , 0},
{ 219 , 220 , 221 , 243 , 244 , 245 , 267 , 268 , 269 , 0},
{ 222 , 223 , 224 , 246 , 247 , 248 , 270 , 271 , 272 , 0},
{ 225 , 226 , 227 , 249 , 250 , 251 , 273 , 274 , 275 , 0},
{ 228 , 229 , 230 , 252 , 253 , 254 , 276 , 277 , 278 , 0},
{ 231 , 232 , 233 , 255 , 256 , 257 , 279 , 280 , 281 , 0},
{ 234 , 235 , 236 , 258 , 259 , 260 , 282 , 283 , 284 , 0},
{ 237 , 238 , 239 , 261 , 262 , 263 , 285 , 286 , 287 , 0},
{ 288 , 289 , 290 , 312 , 313 , 314 , 336 , 337 , 338 , 0},
{ 291 , 292 , 293 , 315 , 316 , 317 , 339 , 340 , 341 , 0},
{ 294 , 295 , 296 , 318 , 319 , 320 , 342 , 343 , 344 , 0},
{ 297 , 298 , 299 , 321 , 322 , 323 , 345 , 346 , 347 , 0},
{ 300 , 301 , 302 , 324 , 325 , 326 , 348 , 349 , 350 , 0},
{ 303 , 304 , 305 , 327 , 328 , 329 , 351 , 352 , 353 , 0},
{ 306 , 307 , 308 , 330 , 331 , 332 , 354 , 355 , 356 , 0},
{ 309 , 310 , 311 , 333 , 334 , 335 , 357 , 358 , 359 , 0},
{ 360 , 361 , 362 , 384 , 385 , 386 , 408 , 409 , 410 , 0},
{ 363 , 364 , 365 , 387 , 388 , 389 , 411 , 412 , 413 , 0},
{ 366 , 367 , 368 , 390 , 391 , 392 , 414 , 415 , 416 , 0},
{ 369 , 370 , 371 , 393 , 394 , 395 , 417 , 418 , 419 , 0},
{ 372 , 373 , 374 , 396 , 397 , 398 , 420 , 421 , 422 , 0},
{ 375 , 376 , 377 , 399 , 400 , 401 , 423 , 424 , 425 , 0},
{ 378 , 379 , 380 , 402 , 403 , 404 , 426 , 427 , 428 , 0},
{ 381 , 382 , 383 , 405 , 406 , 407 , 429 , 430 , 431 , 0},
{ 432 , 433 , 434 , 456 , 457 , 458 , 480 , 481 , 482 , 0},
{ 435 , 436 , 437 , 459 , 460 , 461 , 483 , 484 , 485 , 0},
{ 438 , 439 , 440 , 462 , 463 , 464 , 486 , 487 , 488 , 0},
{ 441 , 442 , 443 , 465 , 466 , 467 , 489 , 490 , 491 , 0},
{ 444 , 445 , 446 , 468 , 469 , 470 , 492 , 493 , 494 , 0},
{ 447 , 448 , 449 , 471 , 472 , 473 , 495 , 496 , 497 , 0},
{ 450 , 451 , 452 , 474 , 475 , 476 , 498 , 499 , 500 , 0},
{ 453 , 454 , 455 , 477 , 478 , 479 , 501 , 502 , 503 , 0},
{ 504 , 505 , 506 , 528 , 529 , 530 , 552 , 553 , 554 , 0},
{ 507 , 508 , 509 , 531 , 532 , 533 , 555 , 556 , 557 , 0},
{ 510 , 511 , 512 , 534 , 535 , 536 , 558 , 559 , 560 , 0},
{ 513 , 514 , 515 , 537 , 538 , 539 , 561 , 562 , 563 , 0},
{ 516 , 517 , 518 , 540 , 541 , 542 , 564 , 565 , 566 , 0},
{ 519 , 520 , 521 , 543 , 544 , 545 , 567 , 568 , 569 , 0},
{ 522 , 523 , 524 , 546 , 547 , 548 , 570 , 571 , 572 , 0},
{ 525 , 526 , 527 , 549 , 550 , 551 , 573 , 574 , 575 , 0}};


void led_move(int c[10]){
  for(int i = 0; i < 9; i++) {
      leds[c[i]] = CRGB::White; 
  }
  FastLED.show(); delay(30); 
}
void led_xp(int c[10]){
  if (c[-1] == 2){
    for(int i = 0; i < 9; i++) {
      leds[c[i]] = CRGB::Green; 
  }
  }
  else if (c[-1] == 3){
    for(int i = 0; i < 9; i++) {
      if (i % 3 == 0){
        leds[c[i]] = CRGB::Red;
      }
  }
  }
  else if (c[-1] == 4){
    for(int i = 0; i < 9; i++) {
      if (i % 3 == 1){
        leds[c[i]] = CRGB::Red;
      }
  }
  }
  else if (c[-1] == 5){
    for(int i = 0; i < 9; i++) {
      if (i % 3 == 2){
        leds[c[i]] = CRGB::Red;
      }
  }
  }
  FastLED.show(); delay(30); 
}
void start(){
  for(int i = 0; i < 24; i++) {
      if (pose[i][-1] == 2){
        led_xp(pose[i],pose[i][-1]);
        } 
      }
}
// массив 24 на 10,  9 pix + индекс xp
void startpoint(){
  Move(stp_x, 1000);   // Если крутиться в неправильную сторону то закоменть эту строку и раскоменть нижнюю 
  //Move(dir_x, 1000); 
  Serial.println("Wait 10 seconds");
  Serial.println("Ready");

}
void Move(int flag, int dist){
  for(int i = 0; i < dist; i++) {
      digitalWrite(flag,HIGH); 
      delayMicroseconds(200); 
      digitalWrite(flag,LOW); 
      delayMicroseconds(200);}
}
void moveto(int x1,int x2, int y1,int y2){
  if (x1-x_last > 0){
    Move(stp_x,(x1-x_last)*x_dist);
  }else{
    Move(dir_x,-(x1-x_last)*x_dist);
  }
  if (y1-y_last > 0){
    Move(stp_y,(y1-y_last)*y_dist);
  }else{
    Move(dir_y,-(y1-y_last)*y_dist);
  }
  // Включение магнита
  if (x2-x1 > 0){
    Move(stp_x,(x2-x1)*x_dist);
  }else{
    Move(dir_x,-(x2-x1)*x_dist);
  }
  if (y2-y1 > 0){
    Move(stp_y,(y2-y1)*y_dist);
  }else{
    Move(dir_y,-(y2-y1)*y_dist);
  }
  // Выключение магнита
}
void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(50);
  pinMode(stp_x,OUTPUT); 
  pinMode(dir_x,OUTPUT);
  pinMode(stp_y,OUTPUT); 
  pinMode(dir_y,OUTPUT);
  }

void loop() {
  if (Serial.available() > 0) {
    String n = Serial.readString();
    Serial.println(n);
    
    if (n[0] == '1'){
       Serial.println("New players");
       Serial.println(players);
       players = 1;
    }
    else if (n[0] == '2'){
      Serial.println("Led");
      str = n[2];
      x2 = str.toFloat();
      str = n[4];
      y2 = str.toFloat();
      led_move(pose[24*y2+x2])
    }
    else if (n[0] == '3'){
      Serial.println("Move");
      str = n[2];
      x1 = str.toFloat();
      str = n[4];
      y1 = str.toFloat();
      str = n[6];
      x2 = str.toFloat();
      str = n[8];
      y2 = str.toFloat();
      moveto(x1,x2,y1,y2);    
    }
    else if (n[0] == '4'){
       Serial.println("Damage");
       str = n[2];
       x1 = str.toFloat();
       str = n[4];
       y1 = str.toFloat();
       led_xp(pose[24*y1+x1])
    }
    Serial.println();}
}
