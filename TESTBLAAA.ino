#define enableA 5
#define enableB 11
#define direction1motorA 3
#define direction2motorA 4
#define direction1motorB 12
#define direction2motorB 13


void setup() {
  // put your setup code here, to run once:
   pinMode(enableA, OUTPUT);
   pinMode(enableB, OUTPUT);
   pinMode(direction1motorA, OUTPUT);
   pinMode(direction2motorA, OUTPUT);
   pinMode(direction1motorB, OUTPUT);
   pinMode(direction2motorB, OUTPUT);
}

void loop() {
    Forward();
}

void motoroff(){
    // now turn off motors
  digitalWrite(direction1motorA, LOW);
  digitalWrite(direction2motorA, LOW);  
  digitalWrite(direction1motorB, LOW);
  digitalWrite(direction2motorB, LOW);
  analogWrite(enableA, 0);
  analogWrite(enableB, 0);
}

 void Forward(){
    digitalWrite(direction1motorA, HIGH);
    digitalWrite(direction2motorA, LOW);
    digitalWrite(direction1motorB, HIGH);
    digitalWrite(direction2motorB, LOW);
    analogWrite(enableA,speed);
    analogWrite(enableB,speed);
    //delay(3000);
}

void Backward(){
    digitalWrite(direction1motorA, LOW);
    digitalWrite(direction2motorA, HIGH);
    digitalWrite(direction1motorB, LOW);
    digitalWrite(direction2motorB, HIGH);
    analogWrite(enableA,speed);
    analogWrite(enableB,speed);
    //delay(3000);
}



void leftTurn(){
  digitalWrite(direction1motorA, LOW);
  digitalWrite(direction2motorA, LOW);  
  digitalWrite(direction1motorB, HIGH);
  digitalWrite(direction2motorB, LOW);
  analogWrite(enableA, 0);
  analogWrite(enableB, speed);
}

void rightTurn(){
  digitalWrite(direction1motorA, HIGH);
  digitalWrite(direction2motorA, LOW);  
  digitalWrite(direction1motorB, LOW);
  digitalWrite(direction2motorB, LOW);
  analogWrite(enableA, speed);
  analogWrite(enableB, 0);
}

void spotLeftTurn(){
  digitalWrite(direction1motorA, LOW);
  digitalWrite(direction2motorA, HIGH);  
  digitalWrite(direction1motorB, HIGH);
  digitalWrite(direction2motorB, LOW);
  analogWrite(enableA, speed);
  analogWrite(enableB, speed);
}

void spotRightTurn(){
  digitalWrite(direction1motorA, HIGH);
  digitalWrite(direction2motorA, LOW);  
  digitalWrite(direction1motorB, LOW);
  digitalWrite(direction2motorB, HIGH);
  analogWrite(enableA, speed);
  analogWrite(enableB, speed);
}