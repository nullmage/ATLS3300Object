/*
 * 
 * 
#include <NewPing.h>

#define TRIGGER_PIN  11  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     10  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
}
 */




#include <Servo.h>

Servo left;
Servo right;

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

float ti;

float tx;
float ty;

int leftVal;
int rightVal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  left.attach(5);
  right.attach(6);
  ti = 0;
  leftVal = 70;
  rightVal = 40;
  right.write(rightVal);
}

void loop() {
  // put your main code here, to run repeatedly:
  ti += 0.0001;

  tx = 4*sin(11*PI*ti) + 6;
  ty = 9*cos(10*PI*ti) + 14;
  
  leftVal = LeftTurnTo(tx, ty);
  rightVal = RightTurnTo(tx, ty);
  left.write(leftVal);
  right.write(rightVal);

  delay(15);
  //Serial.println();
}

float LeftTurnTo(float x, float y){
  float dy = y - 33.0;
  float dx = x - 4.0;
  
  float D = sqrt(dy*dy + dx*dx);
  float alpha = 0 ;
  alpha = (atan(dx / dy) * RAD_TO_DEG)+90;
  
  float beta = acos(D/31.0)* RAD_TO_DEG;

  float angle = alpha + beta;
  //Serial.println(alpha);
  //Serial.print("\t Left Angle: ");
  //Serial.print(alpha);
  float Servo_Angle = map(angle, 90.0, 180.0, 154.0, 50.0); // left vals 154.0, 50.0
  return Servo_Angle;
}

float RightTurnTo(float x, float y){
  float dy = y - 33.0;
  float dx = x - 8.0;

  float D = sqrt(dy*dy + dx*dx);
  float alpha = 0 ;
  alpha = (atan(dx / dy) * RAD_TO_DEG) + 90;
  
  float beta = acos(D/31.0)* RAD_TO_DEG;

  float angle = alpha - beta;
  //Serial.print("\t Right Angle: ");
  //Serial.println(angle);
  
  float Servo_Angle = map(angle, 0.0, 90.0, 124.0, 21.0); //right vals 127.0, 23.0
  return Servo_Angle;
}
