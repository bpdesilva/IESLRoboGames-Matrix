int D1;//Green,2
int D2;//Brown,3
int D3;//Red,4
int D4;//Orange,5
int D5;//Yellow,6
int D6;//White,7
int D7;//Ash,8
int D8;//Purple,9

//Vcc = blue, Ground = black
#define enableA 11 
#define enableB 10
#define direction1motorA 12
#define direction2motorA 13
#define direction1motorB 14
#define direction2motorB 15

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   pinMode(A0,INPUT);
   pinMode(A1,INPUT);
   pinMode(A2,INPUT);
   pinMode(A3,INPUT);
   pinMode(A4,INPUT);
   pinMode(A5,INPUT);
   pinMode(A6,INPUT);
   pinMode(A7,INPUT);
   delay(100);
   pinMode(enableA, OUTPUT);
   pinMode(enableB, OUTPUT);
   pinMode(direction1motorA, OUTPUT);
   pinMode(direction2motorA, OUTPUT);
   pinMode(direction1motorB, OUTPUT);
   pinMode(direction2motorB, OUTPUT); 
}

void readSensorData(){
  D1 = analogRead(A0);
  D2 = analogRead(A1);
  D3 = analogRead(A2);
  D4 = analogRead(A3);
  D5 = analogRead(A4);
  D6 = analogRead(A5);
  D7 = analogRead(A6);
  D8 = analogRead(A7);
  int arr[]={D1,D2,D3,D4,D5,D6,D7,D8};
  for(int i=0;i<8;i++){
      Serial.print(" ");
      Serial.print(arr[i]);
  }
  Serial.println("");
  if (D4 && D5 <700){
    Forward();
  }
 //Fill in the condition to turn the bot
 else if(){
        Right();
 }
  //Fill in the condition to turn the bot
 else if(){
        Left();
 }
 else if (D4 && D5 > 700){
      Stop();
  }
 else{

 }
}

//Move Foward
void Forward(){
    digitalWrite(direction1motorA, HIGH);
    digitalWrite(direction2motorA, LOW);
    digitalWrite(direction1motorB, HIGH);
    digitalWrite(direction2motorB, LOW);
    analogWrite(enableA,175);
    analogWrite(enableB,175);
}

//Stop movining
void Stop(){
    digitalWrite(direction1motorA, HIGH);
    digitalWrite(direction2motorA, LOW);
    digitalWrite(direction1motorB, HIGH);
    digitalWrite(direction2motorB, LOW);
    analogWrite(enableA,0);
    analogWrite(enableB,0);
}

//Turning Bot 
void Right(){
    digitalWrite(direction1motorA, HIGH);
    digitalWrite(direction2motorA, LOW);
    digitalWrite(direction1motorB, HIGH);
    digitalWrite(direction2motorB, LOW);
    analogWrite(enableA,125);
    analogWrite(enableB,175);
    delay(1000);
}

//Turning Bot 
void Left(){
    digitalWrite(direction1motorA, HIGH);
    digitalWrite(direction2motorA, LOW);
    digitalWrite(direction1motorB, HIGH);
    digitalWrite(direction2motorB, LOW);
    analogWrite(enableA,175);
    analogWrite(enableB,125);
    delay(1000);
}

void loop() {
readSensorData();
}
