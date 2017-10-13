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
  // put your main code here, to run repeatedly:
//   Forward();
//   delay(2000);
  BackwardLeft();
  motoroff();
  BackwardRight();
  motoroff();

//   delay(2000);
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

// void Forward(){
//     digitalWrite(direction1motorA, HIGH);
//     digitalWrite(direction2motorA, LOW);
//     digitalWrite(direction1motorB, HIGH);
//     digitalWrite(direction2motorB, LOW);
//     analogWrite(enableA,175);
//     analogWrite(enableB,175);
//     delay(3000);
// }

void BackwardLeft(){
    digitalWrite(direction1motorA, LOW);
    digitalWrite(direction2motorA, HIGH);
    analogWrite(enableA,175);
     delay(3000);
}

void BackwardRight(){
    //delay(2000);
    digitalWrite(direction1motorB, LOW);
    digitalWrite(direction2motorB, HIGH);
    analogWrite(enableB,175);
    delay(3000);
}

