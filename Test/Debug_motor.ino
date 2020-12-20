const int stp = 13; 
const int dir = 12;
int x = 0; 
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
void setup() {
  Serial.begin(9600);
  pinMode(stp,OUTPUT); 
  pinMode(dir,OUTPUT);
  startpoint(); // Функция для выставления в нулевую точку
}
void loop() {
  if (Serial.available() > 0) {
    int n = Serial.parseInt();
    x+=n;
    if (n < 0){
      Move(stp,n);
    } 
    else if (n > 0){
      Move(dir,n);
    }
    Serial.print("New x:");
    Serial.println(x);
    n = 0;
  }
}
