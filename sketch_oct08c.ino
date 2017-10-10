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
#define EMITTER_PIN   16     // emitter is controlled by digital pin 2
#define enableA 11 
#define enableB 10
#define direction1motorA 12
#define direction2motorA 13
#define direction1motorB 14
#define direction2motorB 15

// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
QTRSensorsRC qtrrc((unsigned char[]) {2, 3, 4, 5, 6, 7, 8, 9 },
  NUM_SENSORS, TIMEOUT, EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];

int SumLeft = 0;
int SumRight = 0;
int SumDifference = 0;
int Last = 0;

void setup()
{
  delay(500);
   pinMode(enableA, OUTPUT);
   pinMode(enableB, OUTPUT);
   pinMode(direction1motorA, OUTPUT);
   pinMode(direction2motorA, OUTPUT);
   pinMode(direction1motorB, OUTPUT);
   pinMode(direction2motorB, OUTPUT); 
 
  //pinMode(13, OUTPUT);
  //digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtrrc.calibrate();       // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
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
  //  qtrrc.read(sensorValues); instead of unsigned int position = qtrrc.readLine(sensorValues);
  unsigned int position = qtrrc.readLine(sensorValues);
 
  SumLeft =(sensorValues[0] + sensorValues[1] + sensorValues[2]+sensorValues[3]);
  SumRight = (sensorValues[3] + sensorValues[4] + sensorValues[5]+sensorValues[6]+sensorValues[7]);
  SumDifference = (SumLeft - SumRight);
  Serial.print(SumDifference); 
  Serial.print('\t');
  Serial.print(SumLeft);
  Serial.print('\t');
  Serial.print(SumRight);
  Serial.print('\t');
  
  if(abs(SumDifference) < 700){
    Forward();
    Serial.print("Forward");
  
  }
  if((SumDifference > 700) && (SumDifference < 1000)){
    SlightRight();
    Serial.print("SlightRight");
    Last = 1;
    Serial.print('\t');
    Serial.print("Last = Right");
  }
  if(SumDifference >= 1000){
    HardRight();
    Serial.print("Hard Right");
    Last = 1;
    Serial.print('\t');
    Serial.print("Last = Right");
  }
  
  if((SumDifference < -700) && (SumDifference > -1000)){
    SlightLeft();
    Serial.print("SlightLeft");
    Last = 2;
    Serial.print('\t');
    Serial.print("Last = Left");
  }
  if((SumDifference) <= -1000){
    HardLeft();
    Serial.print("Hard Left");
    Last = 2;
    Serial.print('\t');
    Serial.print("Last = Left");
  }
  if ((SumLeft < 100) && (SumRight < 100)){
    if (Last == 1){
      HardRight();
    }
    if (Last == 2){
      HardLeft();
    }
    
  }



  
  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println(); // uncomment this line if you are using raw values
 // Serial.println(position); // comment this line out if you are using raw values

 
 Serial.print(SumDifference); 
  
  delay(10);
}

void Forward(){
    digitalWrite(direction1motorA, HIGH);
    digitalWrite(direction2motorA, LOW);
    digitalWrite(direction1motorB, HIGH);
    digitalWrite(direction2motorB, LOW);
    analogWrite(enableA,175);
    analogWrite(enableB,175);
    //delay(3000);
}

void SlightRight(){
    digitalWrite(direction1motorA, HIGH);
    digitalWrite(direction2motorA, LOW);
    digitalWrite(direction1motorB, HIGH);
    digitalWrite(direction2motorB, LOW);
    analogWrite(enableA,125);
    analogWrite(enableB,175);
    //delay(3000);
}

 void HardRight(){
    digitalWrite(direction1motorA, HIGH);
    digitalWrite(direction2motorA, LOW);
    digitalWrite(direction1motorB, HIGH);
    digitalWrite(direction2motorB, LOW);
    analogWrite(enableA,0);
    analogWrite(enableB,175);
    //delay(3000);
 }

void SlightLeft(){
    digitalWrite(direction1motorA, HIGH);
    digitalWrite(direction2motorA, LOW);
    digitalWrite(direction1motorB, HIGH);
    digitalWrite(direction2motorB, LOW);
    analogWrite(enableA,175);
    analogWrite(enableB,125);
    //delay(3000);
}
void HardLeft(){
    digitalWrite(direction1motorA, HIGH);
    digitalWrite(direction2motorA, LOW);
    digitalWrite(direction1motorB, HIGH);
    digitalWrite(direction2motorB, LOW);
    analogWrite(enableA,175);
    analogWrite(enableB,0);
    //delay(3000);
}
void Stop(){
    digitalWrite(direction1motorA, HIGH);
    digitalWrite(direction2motorA, LOW);
    digitalWrite(direction1motorB, HIGH);
    digitalWrite(direction2motorB, LOW);
    analogWrite(enableA,0);
    analogWrite(enableB,0);
    //delay(3000);
}



