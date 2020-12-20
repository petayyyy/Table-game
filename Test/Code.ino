const int stp_x = 13; 
const int dir_x = 12;
const int stp_y = 11; 
const int dir_y = 10;
String str = "";
int x1 = 0; int x2 = 0; int y1 = 0; int y2 = 0;
bool players = 0;
int x_dist = 2;
int y_dist = 3;
int x_last = 0;
int y_last = 0;

void startpoint(){
  Move(stp, 1000);   // Если крутиться в неправильную сторону то закоменть эту строку и раскоменть нижнюю 
  //Move(dir, 1000); 
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
    }
    Serial.println();}
}
