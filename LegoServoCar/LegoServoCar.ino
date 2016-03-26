// ---------------------------------------------------------------------------
// Sketch for a Lego car with two servos (with continuous rotation) for left 
// and right wheel and a SR04 ultra sonic sensor for measureing distance to
// objects in front of the car
// ---------------------------------------------------------------------------
#include <NewPing.h>
#include <Servo.h>

//
// SR04 distance sensor setup
//
#define TRIGGER_PIN  6   // Arduino pin for trigger on sensor
#define ECHO_PIN     7   // Arduino pin for echo on sensor
#define MAX_DISTANCE 100 // Maximum distance (in centimeters) to detect
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
unsigned long distance = 0;

//
// On/off button setup
//
#define BUTTON_PIN 8
bool runCar = false;

//
// Servo setup
//
#define RIGHT_WHEEL_PIN 10
#define LEFT_WHEEL_PIN 9
#define RIGHT_WHEEL_STOP_POSITION 88
#define LEFT_WHEEL_STOP_POSITION 89
Servo rightWheel;
Servo leftWheel;


void setup() 
{
  pinMode(BUTTON_PIN,OUTPUT);
  
  rightWheel.attach(RIGHT_WHEEL_PIN);
  leftWheel.attach(LEFT_WHEEL_PIN);

  Stop();
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() 
{
  CheckButton();

  if (runCar)
  {
    MeasureDistance();
    OperateCar();
  }

  delay(200);
}

void OperateCar()
{
  if (distance > 0 && distance < 50)
  {
    Backwards();
  }
  else
  {
    Forward();
  }
}

void CheckButton()
{
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH)
  {
    if (!runCar)
    {
      runCar = true;
    }
    else
    {
      runCar = false;
      Stop();
    }

    delay(500);
  }
}

void MeasureDistance()
{
  int uS = sonar.ping_median(10);
  distance = uS / US_ROUNDTRIP_CM;
  Serial.println(distance);
}

void Forward()
{
  Serial.println("Forward");
  rightWheel.write(RIGHT_WHEEL_STOP_POSITION-10);
  leftWheel.write(LEFT_WHEEL_STOP_POSITION+10);
}

void Backwards()
{
  Serial.println("Backwards");
  rightWheel.write(RIGHT_WHEEL_STOP_POSITION+10);
  leftWheel.write(LEFT_WHEEL_STOP_POSITION+10);
}

void Stop()
{
  Serial.println("Stop");
  rightWheel.write(RIGHT_WHEEL_STOP_POSITION);
  leftWheel.write(LEFT_WHEEL_STOP_POSITION);
}


