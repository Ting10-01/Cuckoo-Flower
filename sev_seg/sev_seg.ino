#include <DS1302.h>
/*#include <IRremote.h>
#define change 0xFF629D
#define ok 0xFFC23D
#define zero 0xFF6897
#define one 0xFF30CF
#define two 0xFF18E7
#define three 0xFF7A85
#define four 0xFF10EF
#define five 0xFF38C7
#define six 0xFF5AA5
#define seven 0xFF42BD
#define eight 0xFF4AB5
#define nine 0xFF52AD*/

DS1302 clock1(11, 12, 13);
/*IRrecv IR1(A5);
decode_results results;*/
Time t;

int digPin[4] = {A3, A1, A2, A0};
int segPin[7] = {7, 8, 4, 2, 3, 6, 5};
int flagPin = 10;
bool flag = false;
/*int alarm = 0;
int alarm_h = 100;
int alarm_m = 100;*/
    
void setup() {
  Serial.begin(9600);
  clock1.writeProtect(false);
  clock1.halt(false);
  clock1.setTime(20, 59, 55);
  for(int i=0; i<4; i++)
    pinMode(digPin[i], OUTPUT);
  for(int i=0; i<7; i++)
    pinMode(segPin[i], OUTPUT);
  //IR1.enableIRIn();
  pinMode(flagPin, OUTPUT);
}

void Seg(int num){
  switch(num){
    case 0:
      digitalWrite(segPin[0], HIGH);   
      digitalWrite(segPin[1], HIGH);   
      digitalWrite(segPin[2], HIGH);   
      digitalWrite(segPin[3], HIGH);   
      digitalWrite(segPin[4], HIGH);   
      digitalWrite(segPin[5], HIGH);   
      digitalWrite(segPin[6], LOW);
      break;
    case 1:
      digitalWrite(segPin[0], LOW);   
      digitalWrite(segPin[1], HIGH);   
      digitalWrite(segPin[2], HIGH);   
      digitalWrite(segPin[3], LOW);   
      digitalWrite(segPin[4], LOW);   
      digitalWrite(segPin[5], LOW);   
      digitalWrite(segPin[6], LOW);     
      break;
    case 2:
      digitalWrite(segPin[0], HIGH);   
      digitalWrite(segPin[1], HIGH);   
      digitalWrite(segPin[2], LOW);   
      digitalWrite(segPin[3], HIGH);   
      digitalWrite(segPin[4], HIGH);   
      digitalWrite(segPin[5], LOW);   
      digitalWrite(segPin[6], HIGH);     
      break;
    case 3:
      digitalWrite(segPin[0], HIGH);   
      digitalWrite(segPin[1], HIGH);   
      digitalWrite(segPin[2], HIGH);   
      digitalWrite(segPin[3], HIGH);   
      digitalWrite(segPin[4], LOW);   
      digitalWrite(segPin[5], LOW);   
      digitalWrite(segPin[6], HIGH);     
      break;
    case 4:
      digitalWrite(segPin[0], LOW);   
      digitalWrite(segPin[1], HIGH);   
      digitalWrite(segPin[2], HIGH);   
      digitalWrite(segPin[3], LOW);   
      digitalWrite(segPin[4], LOW);   
      digitalWrite(segPin[5], HIGH);   
      digitalWrite(segPin[6], HIGH);     
      break;
    case 5:
      digitalWrite(segPin[0], HIGH);   
      digitalWrite(segPin[1], LOW);   
      digitalWrite(segPin[2], HIGH);   
      digitalWrite(segPin[3], HIGH);   
      digitalWrite(segPin[4], LOW);   
      digitalWrite(segPin[5], HIGH);   
      digitalWrite(segPin[6], HIGH);     
      break;
    case 6:
      digitalWrite(segPin[0], HIGH);   
      digitalWrite(segPin[1], LOW);   
      digitalWrite(segPin[2], HIGH);   
      digitalWrite(segPin[3], HIGH);   
      digitalWrite(segPin[4], HIGH);   
      digitalWrite(segPin[5], HIGH);   
      digitalWrite(segPin[6], HIGH);     
      break;
    case 7:
      digitalWrite(segPin[0], HIGH);   
      digitalWrite(segPin[1], HIGH);   
      digitalWrite(segPin[2], HIGH);   
      digitalWrite(segPin[3], LOW);   
      digitalWrite(segPin[4], LOW);   
      digitalWrite(segPin[5], HIGH);   
      digitalWrite(segPin[6], LOW);     
      break;
    case 8:
      digitalWrite(segPin[0], HIGH);   
      digitalWrite(segPin[1], HIGH);   
      digitalWrite(segPin[2], HIGH);   
      digitalWrite(segPin[3], HIGH);   
      digitalWrite(segPin[4], HIGH);   
      digitalWrite(segPin[5], HIGH);   
      digitalWrite(segPin[6], HIGH);     
      break;
    case 9:
      digitalWrite(segPin[0], HIGH);   
      digitalWrite(segPin[1], HIGH);   
      digitalWrite(segPin[2], HIGH);   
      digitalWrite(segPin[3], HIGH);   
      digitalWrite(segPin[4], LOW);   
      digitalWrite(segPin[5], HIGH);   
      digitalWrite(segPin[6], HIGH);     
      break;
    default:
      digitalWrite(segPin[0], LOW);   
      digitalWrite(segPin[1], LOW);   
      digitalWrite(segPin[2], LOW);   
      digitalWrite(segPin[3], LOW);   
      digitalWrite(segPin[4], LOW);   
      digitalWrite(segPin[5], LOW);   
      digitalWrite(segPin[6], LOW);     
      break;
  }
}

/*void Dis(int digit){
  for(int i=0; i<4; i++){
    if(i == digit)
      digitalWrite(digPin[i], LOW);
    else
      digitalWrite(digPin[i], HIGH);
  }
  if(digit == 0)
    Seg(alarm%10000/1000);
  else if(digit == 1)
    Seg(alarm%1000/100);
  else if(digit == 2)
    Seg(alarm%100/10);
  else
    Seg(alarm%10);
}*/

void Display(int digit){
  for(int i=0; i<4; i++){
    if(i == digit)
      digitalWrite(digPin[i], LOW);
    else
      digitalWrite(digPin[i], HIGH);
  }
  if(digit == 0)
    Seg(t.hour/10);
  else if(digit == 1)
    Seg(t.hour%10);
  else if(digit == 2)
    Seg(t.min/10);
  else
    Seg(t.min%10);
}

void loop() {
  /*if(IR1.decode(&results)){
    Serial.println(results.value, HEX);
    if(results.value == change){
      IR1.resume();
      while(1){
        alarm = alarm%100000;
        if(IR1.decode(&results)){
          if(results.value == ok){
            alarm_h = alarm%10000/100;
            alarm_m = alarm%100;  
            break;
          }
          else if(results.value == zero)
            alarm = alarm*10+0;
          else if(results.value == one)
            alarm = alarm*10+1;
          else if(results.value == two)
            alarm = alarm*10+2;
          else if(results.value == three)
            alarm = alarm*10+3;
          else if(results.value == four)
            alarm = alarm*10+4;
          else if(results.value == five)
            alarm = alarm*10+5;
          else if(results.value == six)
            alarm = alarm*10+6;
          else if(results.value == seven)
            alarm = alarm*10+7;
          else if(results.value == eight)
            alarm = alarm*10+8;
          else if(results.value == nine)
            alarm = alarm*10+9;
          IR1.resume();
        }
        else{
          for(int i=0; i<4; i++){
            Dis(i);
            delay(5);
          }
        }
      }
    }
    else
      IR1.resume();
  }*/
  t = clock1.getTime();
  for(int i=0; i<4; i++){
    Display(i);
    delay(5);
  }
  if(t.min==0 && t.sec==0)
    //digitalWrite(flagPin, HIGH);
    flag = true;
  else
    flag = false;
  //if(alarm_h==t.hour && alarm_m==t.min)
    //flag = true;
  digitalWrite(flagPin, flag);
  
}
