int flagPin = 8;
int flag = 0;
int motor1 = 5;
int motor2 = 4;
int led = 12;
int RLed = 9;
int GLed = 10;
int BLed = 11;
int rgb[3] = {0, 100, 200};
int r = 1;
int g = 1;
int b = 1;
int cnt = 0;

void setup() {
  pinMode(flagPin, INPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(RLed, OUTPUT);
  pinMode(GLed, OUTPUT);
  pinMode(BLed, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  //delay(10000);
  flag = digitalRead(flagPin);
  Serial.println(flag);
  if(flag){
    analogWrite(motor1, 70);
    digitalWrite(motor2, 0);
    digitalWrite(led, HIGH);
    analogWrite(RLed, 0);
    analogWrite(GLed, 200);
    analogWrite(BLed, 200);
    while(cnt != 1000){
      rgb[0] += r;
      rgb[1] += g;
      rgb[2] += b;
      if(rgb[0] == 255)
        r = -1;
      else if(rgb[0] == 0)
        r = 1;
      if(rgb[1] == 255)
        g = -1;
      else if(rgb[1] == 0)
        g = 1;
      if(rgb[2] == 255)
        b = -1;
      else if(rgb[2] == 0)
        b = 1;
      delay(20);
      cnt++;
    }
    cnt = 0;
  }
  analogWrite(motor1, 0);
  digitalWrite(motor2, 0);
  digitalWrite(led, LOW);
  analogWrite(RLed, rgb[0]);
  analogWrite(GLed, rgb[1]);
  analogWrite(BLed, rgb[2]);
}
