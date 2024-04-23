#include <AccelStepper.h>

#define IN1 D5
#define IN2 D6
#define IN3 D7
#define IN4 D8

AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);

const long stepsPerRevolution = 2048;

#define ROTATIONS 15 //total rotations 
#define ROTATIONS_IN_ONE_DIRECTION ROTATIONS/2 //half of the rotations in each direction
const int TimeSleepS = 3600; //3600 = 1 hour , 1800 = 30min 

void setup()
{
    Serial.begin(9600);     // 9600 bps
    Serial.println("");
    Serial.println("pluciorx@gmail.com Watch Rotor Programm v1.01 ");
    stepper.setMaxSpeed(1650);
    stepper.setAcceleration(500);
    stepper.moveTo(stepsPerRevolution * ROTATIONS_IN_ONE_DIRECTION); 
}

void loop()
{
    int counter = 0;

    while (counter < ROTATIONS)
    {
        stepper.setMinPulseWidth(15);

        stepper.runToPosition();
        counter++;
        Serial.print("Revolution:"); Serial.println(counter);
        if (counter >= ROTATIONS / 2)
        {
            stepper.move(-1 * (stepsPerRevolution * ROTATIONS_IN_ONE_DIRECTION));
        }
        else
        {
            stepper.move(stepsPerRevolution * ROTATIONS_IN_ONE_DIRECTION);
        }
    }
    Serial.print("Pause for :"); Serial.print(TimeSleepS); Serial.println("s");
    stepper.disableOutputs();
    delay(TimeSleepS * 1000);
    stepper.enableOutputs();
    Serial.println("Pause finished");
}
