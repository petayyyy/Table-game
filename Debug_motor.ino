const int stp = 13; 
const int dir = 12;
int x = 0; 
void startpoint(){
  digitalWrite(stp,HIGH);   // Если крутиться в неправильную сторону то закоменть эту строку и раскоменть нижнюю 
  //digitalWrite(dir,HIGH); 
  Serial.println("Wait 10 seconds");
  delay(10000);
  digitalWrite(stp,LOW);
  digitalWrite(dir,LOW);
  Serial.println("Ready");

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
      for(int i = 0; i < n; i++) {
        digitalWrite(stp,HIGH); 
        delayMicroseconds(200); 
        digitalWrite(stp,LOW); 
        delayMicroseconds(200);}
    } 
    else if (n > 0){
      for(int i = 0; i < n; i++) {
        digitalWrite(dir,HIGH); 
        delayMicroseconds(200); 
        digitalWrite(dir,LOW); 
        delayMicroseconds(200);}
    }
    Serial.print("New x:");
    Serial.println(x);
    n = 0;
  }
}
