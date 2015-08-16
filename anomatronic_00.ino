
#include <Servo.h> 

Servo nodder;
Servo twister;

const int nodPin = 8;
const int twistPin = 7;
const int buttonPin = 3;
const int ledPin = 10;
const int potPin = A1;

const int WAITING = 0;
const int SAYING = 1;
volatile int Optimism = 60; //percents
volatile int headState = WAITING;

 
 
void setup()
{
  
nodder.attach(nodPin);
twister.attach(twistPin);
nodder.write(120);
//twister.write(70);
delay(1200);
nodder.write(120);
//twister.write(90);
//delay(1000);
nodder.write(90);
//twister.write(90);
delay(200);
digitalWrite(ledPin, HIGH);

pinMode(buttonPin, INPUT);
//digitalWrite(buttonPin, HIGH);
attachInterrupt(1,bpress, RISING);
Serial.begin(9600);
nodder.detach();
twister.detach();
randomSeed (analogRead(0));
 

}

void loop()
{

delay(100);
if (headState == SAYING){
  int pv = analogRead(potPin);
  Optimism = map(pv, 0, 1023, 0, 100);
  Serial.print("Pot value: ");
  Serial.println(pv);
  Serial.print("Optimism: ");
  Serial.println(Optimism, DEC);
  
  nodder.attach(nodPin);
  twister.attach(twistPin);
  digitalWrite(ledPin, LOW);
  
  //twister.write(random(70,110));
  nodder.write(120);
  delay(500);
  //twister.write(90);
  //delay(300);
  nodder.write(90);
  delay(200);
  
  Serial.println("Button pressed");
  
  int Answer = random(0,100);
  int Emotion = random(1,4);
  
  if (Answer<Optimism){
    //YES
    Serial.println("Answer YES");
    for (int i=1; i<=Emotion ; i++){ 
//      for(int pos=1500 ; pos>=1100 ; pos--){
//        nodder.writeMicroseconds(pos);
//        delay(5);
//      }
//       for(int pos=1100 ; pos<=1500 ; pos+=2){
//        nodder.write(pos);
//        delay(20);
//      }
//
      nodder.write(140);
      delay(500);
      nodder.write(90);
      delay(500);
    }
    
    
  }else{
    //NOT YES
    Serial.println("Answer NO");
    for (int i=1; i<=Emotion ; i++){
      for (int e=1500; e>=1300;e=e-6){
      twister.writeMicroseconds(e);
      //float dt = sin((1500-e)/1500);
      delay(20);
      }
      delay(200);
      for (int e=1300; e<=1700;e=e+6){
      twister.writeMicroseconds(e);
      //float dt = sin((1600-e)/1600);
      delay(20);
      }
      delay(200);
      for (int e=1700; e>=1500;e=e-6){
      twister.writeMicroseconds(e);
      //float dt = sin((e-1500)/1500);
      delay(20);
      }  
      delay(200);
      twister.write(90);    
      //twister.write(70);
      delay(100);
      //twister.write(110);
      //delay(500);
      //delay(200);
    }
    twister.write(90);
    delay(200);  
  }
  twister.detach();
  nodder.detach(); 
  headState = WAITING;
  digitalWrite(ledPin, HIGH);
  
}

 
}

//Generally one is recommended to keep ISR routines as simple 
//and short as possible, calling other functions from inside 
//a ISR is not recommended practice. Just test or input for some 
//condition and set a global volatile variable or flag and let 
//the main loop check that variable or flag and do the actual 
//action you require.

void bpress(){
headState = SAYING;
}

void nod(){
  //noInterrupts();
  Serial.println("press");
  nodder.write(90);
  delayMicroseconds(1000);
  nodder.write(130);
  delayMicroseconds(200);
  nodder.write(90);
  headState = WAITING;
  //interrupts();


}
