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
#define LEDPIN 38
#define en_pin 41

// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
QTRSensorsRC qtrrc((unsigned char[]) {14, 15, 16, 17, 18, 19, 44, 45},
  NUM_SENSORS, TIMEOUT, EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];
const unsigned int speed=120;



int SumLeft = 0;
int SumRight = 0;
int SumDifference = 0;
int SumLeft_i = 0;
int SumRight_i = 0;
int SumDifference_i = 0;
int Last = 0;
int BG;
unsigned int qtr[NUM_SENSORS];
unsigned int qtri[NUM_SENSORS];
unsigned int en_status;

void setup()
{
  delay(500);
   pinMode(enableA, OUTPUT);
   pinMode(enableB, OUTPUT);
   pinMode(direction1motorA, OUTPUT);
   pinMode(direction2motorA, OUTPUT);
   pinMode(direction1motorB, OUTPUT);
   pinMode(direction2motorB, OUTPUT);
   pinMode(LEDPIN, OUTPUT);
   pinMode(en_pin, INPUT);

  //pinMode(13, OUTPUT);
  //digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
   for (int i = 0; i < 100; i++)  // make the calibration take about 10 seconds
  {
   // turn();
    qtrrc.calibrate();       // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
delay(200); 
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
  for(int j=0;j<NUM_SENSORS;j++){
    if(sensorValues[j]>500){
      qtr[7-j]=1;
      qtri[7-j]=0;
    }
    else {
      qtr[7-j]=0;
      qtri[7-j]=1;
    }
  //Serial.print(qtr[j]);
    //Serial.print('\t');
  }
  //Serial.println();

  en_status=digitalRead(en_pin);
  
  if((qtr[0]==0 && qtr[7]==0) && (qtr[3]==1 && qtr[4]==1) && en_status==LOW){
    BG=0;
    }
else if((qtr[3]==0 && qtr[4]==0) && (qtr[0]==1 && qtr[7]==1) && en_status==HIGH){
    BG=1;
    }
  

  SumLeft = (qtr[1] + qtr[2] + qtr[3] );
  SumRight = (qtr[4] + qtr[5] + qtr[6] );
  SumDifference = (SumLeft - SumRight);
  Serial.print(SumDifference);
  Serial.println();

  SumLeft_i = (qtri[1] + qtri[2] + qtri[3] );
  SumRight_i = (qtri[4] + qtri[5] + qtri[6] );
  SumDifference_i = (SumLeft_i - SumRight_i);

 
  if(BG==1)

  {
      digitalWrite(LEDPIN, HIGH);
      if(abs(SumDifference) == 0){
      Forward();
      }


      else if( qtr[0]==1 && qtr[7]==0){
        motorOff();
        spotRightTurn();
        }

        else if( qtr[7]==1 && qtr[0]==0){
        motorOff();
        spotLeftTurn();
        }

      else if(SumDifference == 1){
      slightestrightTurn();
      }
      
      else if(SumDifference == 2){
      slightrightTurn();
      }

      else if(SumDifference == 3){
      spotRightTurn();
      }

      else if(SumDifference == -1){
      slightestleftTurn();
      }
      
      else if(SumDifference == -2){
      slightleftTurn();
      }

      else if(SumDifference == -3){
      spotLeftTurn();
      
      }
      
  }

  else if(BG==0)
  {
      digitalWrite(LEDPIN, LOW);
       if(abs(SumDifference_i) == 0){
      Forward();
      }


      else if( (qtri[0]==1 && qtri[7]==0)&& qtri[3]==1){
        motorOff();
        spotRightTurn();
        
        }

        else if( qtri[7]==1 && qtri[0]==0){
        motorOff();
        spotLeftTurn();
        }

      else if(SumDifference_i == 1){
      slightestrightTurn();
      }
      
      else if(SumDifference_i == 2){
      slightrightTurn();
      }

      else if(SumDifference_i == 3){
        delay(1000);
      spotRightTurn();
      }

      else if(SumDifference_i == -1){
      slightestleftTurn();
      }
      
      else if(SumDifference_i == -2){
      slightleftTurn();
      }

      else if(SumDifference_i == -3){
          delay(1000);
      spotLeftTurn();
      
      }
  }
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

void motorOff(){
    // now turn off motors
  digitalWrite(direction1motorA, LOW);
  digitalWrite(direction2motorA, LOW);  
  digitalWrite(direction1motorB, LOW);
  digitalWrite(direction2motorB, LOW);
  analogWrite(enableA, 0);
  analogWrite(enableB, 0);
}

void slightestleftTurn(){
  digitalWrite(direction1motorA, LOW);
  digitalWrite(direction2motorA, LOW);  
  digitalWrite(direction1motorB, HIGH);
  digitalWrite(direction2motorB, LOW);
  analogWrite(enableA, speed-5);
  analogWrite(enableB, speed);
}

void slightleftTurn(){
  digitalWrite(direction1motorA, LOW);
  digitalWrite(direction2motorA, LOW);  
  digitalWrite(direction1motorB, HIGH);
  digitalWrite(direction2motorB, LOW);
  analogWrite(enableA, speed-10);
  analogWrite(enableB, speed);
}

void leftTurn(){
  digitalWrite(direction1motorA, LOW);
  digitalWrite(direction2motorA, LOW);  
  digitalWrite(direction1motorB, HIGH);
  digitalWrite(direction2motorB, LOW);
  analogWrite(enableA, 0);
  analogWrite(enableB, speed);
}

void slightestrightTurn(){
  digitalWrite(direction1motorA, HIGH);
  digitalWrite(direction2motorA, LOW);  
  digitalWrite(direction1motorB, LOW);
  digitalWrite(direction2motorB, LOW);
  analogWrite(enableA, speed);
  analogWrite(enableB, speed-5);
}

void slightrightTurn(){
  digitalWrite(direction1motorA, HIGH);
  digitalWrite(direction2motorA, LOW);  
  digitalWrite(direction1motorB, LOW);
  digitalWrite(direction2motorB, LOW);
  analogWrite(enableA, speed);
  analogWrite(enableB, speed-10);
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