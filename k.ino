#include <QTRSensors.h>

// This example is designed for use with eight QTR-1RC sensors or the eight sensors of a
// QTR-8RC module.  These reflectance sensors should be connected to digital inputs 3 to 10.
// The QTR-8RC's emitter control pin (LEDON) can optionally be connected to digital pin 2, 
// or you can leave it disconnected and change the EMITTER_PIN #define below from 2 to 
// QTR_NO_EMITTER_PIN.

// The setup phase of this example calibrates the sensor for ten seconds and turns on
// the LED built in to the Arduino on pin 13 while calibration is going on.
// During this phase, you should expose each reflectance sensor to the lightest and 
// darkest readings they will encounter.
// For example, if you are making a line follower, you should slide the sensors across the
// line during the calibration phase so that each sensor can get a reading of how dark the
// line is and how light the ground is.  Improper calibration will result in poor readings.
// If you want to skip the calibration phase, you can get the raw sensor readings
// (pulse times from 0 to 2500 us) by calling qtrrc.read(sensorValues) instead of
// qtrrc.readLine(sensorValues).

// The main loop of the example reads the calibrated sensor values and uses them to
// estimate the position of a line.  You can test this by taping a piece of 3/4" black
// electrical tape to a piece of white paper and sliding the sensor across it.  It
// prints the sensor values to the serial monitor as numbers from 0 (maximum reflectance) 
// to 1000 (minimum reflectance) followed by the estimated location of the line as a number
// from 0 to 5000.  1000 means the line is directly under sensor 1, 2000 means directly
// under sensor 2, etc.  0 means the line is directly under sensor 0 or was last seen by
// sensor 0 before being lost.  5000 means the line is directly under sensor 5 or was
// last seen by sensor 5 before being lost.


#define NUM_SENSORS   8    // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   2     // emitter is controlled by digital pin 2
#define enableA 5 
#define enableB 11
#define direction1motorA 3
#define direction2motorA 4
#define direction1motorB 12
#define direction2motorB 13

// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
QTRSensorsRC qtrrc((unsigned char[]) {14, 15, 16, 17, 18, 19, 44, 45},
  NUM_SENSORS, TIMEOUT, EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];
<<<<<<< HEAD
const unsigned int speed=170;



int SumLeft = 0;
int SumRight = 0;
int SumDifference = 0;
int Last = 0;
int BG;
unsigned int qtr[NUM_SENSORS];

=======
const unsigned int speed=200;
>>>>>>> b10fa968628df44a84bb4d6c6e059508fef1e49d

void setup()
{
  delay(500);
   pinMode(enableA, OUTPUT);
   pinMode(enableB, OUTPUT);
   pinMode(direction1motorA, OUTPUT);
   pinMode(direction2motorA, OUTPUT);
   pinMode(direction1motorB, OUTPUT);
<<<<<<< HEAD
   pinMode(direction2motorB, OUTPUT);


  //pinMode(13, OUTPUT);
  //digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
   for (int i = 0; i < 100; i++)  // make the calibration take about 10 seconds
  {
   // turn();
    qtrrc.calibrate();       // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
delay(200); 
=======
   pinMode(direction2motorB, OUTPUT); 
 
  //pinMode(13, OUTPUT);
  //digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
   for (int i = 0; i < 4; i++)  // make the calibration take about 10 seconds
  {
  
    qtrrc.calibrate();       // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
  delay(200); 
>>>>>>> b10fa968628df44a84bb4d6c6e059508fef1e49d
 // digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  
  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
}

void loop()
{
  // read calibrated sensor values and obtain a measure of the line position from 0 to 5000
  // To get raw sensor values, call:

  unsigned int position = qtrrc.readLine(sensorValues);
<<<<<<< HEAD
  for(int j=0;j<NUM_SENSORS;j++){
    if(sensorValues[j]>500){
      qtr[7-j]=1;
    }
    else {
      qtr[7-j]=0;
    }
  //Serial.print(qtr[j]);
    //Serial.print('\t');
  }
  //Serial.println();
  
  if((qtr[0]==0 && qtr[7]==0) && (qtr[3]==1 && qtr[4]==1)){
    BG=0;
    }
  if((qtr[3]==0 && qtr[4]==0) && (qtr[0]==1 && qtr[7]==1)){
    BG=1;
    }
  

  SumLeft = (qtr[1] + qtr[2] + qtr[3] );
  SumRight = (qtr[4] + qtr[5] + qtr[6] );
  SumDifference = (SumLeft - SumRight);
  Serial.print(SumDifference);
 Serial.println();

 /*
  if(BG==1)
  {
    
      if(abs(SumDifference) < 112){
      Forward();
      }

      else if(SumDifference > 112){
      rightTurn();
      }
      
      else if(SumDifference < -112){
      leftTurn;
      }

  }
*/
  if(BG==0)
  {
    
      if(abs(SumDifference) < 1){
      Forward();
      }

      else if(SumDifference > 0){
      leftTurn;
      }
      
      else if(SumDifference < 0){
      rightTurn;
      }

  }

  
//commented
/*

    if(abs(SumDifference) < 700){
    Forward();
  }
  if((SumDifference > 700) && (SumDifference < 1000)){
    leftTurn();
//    Serial.print("SlightRight");
    Last = 1;
//    Serial.print('\t');
//    Serial.print("Last = Right");
  }
  if(SumDifference >= 1000){
    leftTurn();
//    Serial.print("Hard Right");
    Last = 1;
//    Serial.print('\t');
//    Serial.print("Last = Right");
  }
  
  if((SumDifference < -700) && (SumDifference > -1000)){
    rightTurn();
//    Serial.print("SlightLeft");
    Last = 2;
//    Serial.print('\t');
//    Serial.print("Last = Left");
  }
  if((SumDifference) <= -1000){
    rightTurn();
//    Serial.print("Hard Left");
    Last = 2;
//    Serial.print('\t');
//    Serial.print("Last = Left");
  }
  if ((SumLeft < 100) && (SumRight < 100)){
    if (Last == 1){
      leftTurn();
    }
    if (Last == 2){
     rightTurn();
    }
    
  }
   */ 

   //end comment
  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position

  /*
=======

   
  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
>>>>>>> b10fa968628df44a84bb4d6c6e059508fef1e49d
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
<<<<<<< HEAD
   }
     Serial.println(); // uncomment this line if you are using raw values
*/
  }


  void Forward(){
=======

    if(sensorValues[1,6]<=500 && sensorValues[4,3]>=500){
        Forward();
    }
    else if((sensorValues[1]<=500&& sensorValues[6]>=500)&&(sensorValues[4,3]>=500)){
        leftTurn();
    }
    else if((sensorValues[1]>=500&& sensorValues[6]<=500)&&(sensorValues[4,3]>=500)){
      rightTurn();
    }
    else{
      motorOff();
    }
  }
     Serial.println(); // uncomment this line if you are using raw values

  }

//Move bot forward 
void Forward(){
>>>>>>> b10fa968628df44a84bb4d6c6e059508fef1e49d
    digitalWrite(direction1motorA, HIGH);
    digitalWrite(direction2motorA, LOW);
    digitalWrite(direction1motorB, HIGH);
    digitalWrite(direction2motorB, LOW);
    analogWrite(enableA,speed);
    analogWrite(enableB,speed);
    //delay(3000);
}

<<<<<<< HEAD
=======
//Move bot backward 
>>>>>>> b10fa968628df44a84bb4d6c6e059508fef1e49d
void Backward(){
    digitalWrite(direction1motorA, LOW);
    digitalWrite(direction2motorA, HIGH);
    digitalWrite(direction1motorB, LOW);
    digitalWrite(direction2motorB, HIGH);
    analogWrite(enableA,speed);
    analogWrite(enableB,speed);
    //delay(3000);
}

<<<<<<< HEAD
=======
//Turn off the motor
>>>>>>> b10fa968628df44a84bb4d6c6e059508fef1e49d
void motorOff(){
    // now turn off motors
  digitalWrite(direction1motorA, LOW);
  digitalWrite(direction2motorA, LOW);  
  digitalWrite(direction1motorB, LOW);
  digitalWrite(direction2motorB, LOW);
  analogWrite(enableA, 0);
  analogWrite(enableB, 0);
}

<<<<<<< HEAD
=======
//90 degree turn based on array response
>>>>>>> b10fa968628df44a84bb4d6c6e059508fef1e49d
void leftTurn(){
  digitalWrite(direction1motorA, LOW);
  digitalWrite(direction2motorA, LOW);  
  digitalWrite(direction1motorB, HIGH);
  digitalWrite(direction2motorB, LOW);
  analogWrite(enableA, 0);
  analogWrite(enableB, speed);
}

<<<<<<< HEAD
=======
//90 degree turn based on array response
>>>>>>> b10fa968628df44a84bb4d6c6e059508fef1e49d
void rightTurn(){
  digitalWrite(direction1motorA, HIGH);
  digitalWrite(direction2motorA, LOW);  
  digitalWrite(direction1motorB, LOW);
  digitalWrite(direction2motorB, LOW);
  analogWrite(enableA, speed);
  analogWrite(enableB, 0);
}

<<<<<<< HEAD
=======
//turn based on array response
>>>>>>> b10fa968628df44a84bb4d6c6e059508fef1e49d
void spotLeftTurn(){
  digitalWrite(direction1motorA, LOW);
  digitalWrite(direction2motorA, HIGH);  
  digitalWrite(direction1motorB, HIGH);
  digitalWrite(direction2motorB, LOW);
  analogWrite(enableA, speed);
  analogWrite(enableB, speed);
}

<<<<<<< HEAD
=======
//turn based on array response
>>>>>>> b10fa968628df44a84bb4d6c6e059508fef1e49d
void spotRightTurn(){
  digitalWrite(direction1motorA, HIGH);
  digitalWrite(direction2motorA, LOW);  
  digitalWrite(direction1motorB, LOW);
  digitalWrite(direction2motorB, HIGH);
  analogWrite(enableA, speed);
  analogWrite(enableB, speed);
<<<<<<< HEAD
}
=======
}
>>>>>>> b10fa968628df44a84bb4d6c6e059508fef1e49d
