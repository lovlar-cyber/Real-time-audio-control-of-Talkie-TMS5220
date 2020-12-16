/*
MMKF45 prototyping project by 
Jonathan Ramb, 
Hannes Möller, 
Samuel Bror Bengtsson, 
Love Montan Larsson.
at LTH, Lund University

With inspiration from the prince in Katamari Damacy, a robot prototype has been built. 
A spring placed on top of the robot is used as an audio controlling joystick.

This project uses an edited arduino library (Talkie),
based on the Texas instrument TMS5220 speech synthesizer, to make it control:
- Pitch in y-direction,
- Phoneme(phrase) in x-direction,
- Amplitude controlled by movement,
 in real time.

 The parameters are controlled by a 6DOF accelerometer placed on top of a spring.

 Through Serial1, a second arduino is comunicated with that is updating the LED 
 matrix mouth layout in sync with the phoneme parameter


*/

#include <Arduino.h>
#include "Talkie.h"
#include "Vocab_US_Acorn.h"
#include "Vocab_US_Large.h"
#include "Vocab_US_TI99.h"
#include "I2Cdev.h"
#include "MPU6050.h"



////TALKIE THINGS////
/////////////////////

#if defined(__AVR_ATmega32U4__)
// not enough memory for the data of the song left on ATmega32U4 with USB software
#include "Vocab_US_TI99.h"
#else
#include "mmkf45.h"
#endif

Talkie voice;
//int pin = 3;
int sensorValue = 0;
int phoneme = 0;
int pitch = 0;
int energy = 0;
int maxPhoneme;
int maxPitch;





////MPU6050 THINGS////
//////////////////////

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax, ay, az;
int16_t gx, gy, gz;
uint32_t Ag, Aa, Axy, Az;
int dxy, Gxy, Gz;
const int aSize = 10;
int lA[aSize] = {};
int Amp;

// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO

// uncomment "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit
// binary, one right after the other. This is very fast (as fast as possible
// without compression or data loss), and easy to parse, but impossible to read
// for a human.
//#define OUTPUT_BINARY_ACCELGYRO






////LED MATRIX THINGS
/////////////////////
const int columnPins[] = {31, 33, 35, 37};
const int rowPins[] = {39, 41, 43, 45, 47};






//INTERACTION things
////////////////////
int32_t endtime, starttime;
int8_t interactionDuration = 30;
int8_t mouth = 0;





////COMUNICATION things
///////////////////////
char x[16]; // array with space for 15 characters plus terminating null character

void setup()
{
    ////COMUNICATION things
    ///////////////////////
    // 19(RX), 18(TX) on a Mega2560
    Serial1.begin(19200);
    while (!Serial1)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    //Pin 11 used for interupting LED matrix arduino
    pinMode(11, OUTPUT);

    ////TALKIE things
    /////////////////
    maxPhoneme = sizeof(ehmat) / sizeof(*ehmat);
    maxPitch = sizeof(*ehmat) / sizeof(**ehmat);

    Serial.begin(115200);

#if defined(__AVR_ATmega32U4__)
    while (!Serial)
        ; //delay for Leonardo, but this loops forever for Maple Serial
#endif
        // Just to know which program is running on my Arduino
        Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_TALKIE));

#if defined(TEENSYDUINO)
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH); //Enable Amplified PROP shield
#endif

#if !defined(__AVR_ATmega32U4__)
    setMouth(20, 14);
    voice.sayQ(spt_HELLO);
    setMouth(15, 0);
#else

    voice.say(spt_NICE_TRY);
    voice.say(spt_WE);
    voice.say(spt_NEED);
    voice.say(spt_MORE);
    voice.say(spt_MEMORY);
    voice.say(spt_THAN);
    voice.say(spt_WE);
    voice.say(spt_HAVE);

#endif

////MPU6050 THINGS////
//////////////////////

// join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
#endif

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    setMouth(20, 14);
    voice.say(sp2_CALIBRATE);
    voice.say(sp5_INSTRUMENTS);
    setMouth(15, 0);

    // use the code below to change accel/gyro offset values
    accelgyro.CalibrateGyro();
    accelgyro.CalibrateAccel();
    accelgyro.PrintActiveOffsets();

    setMouth(20, 14);
    voice.say(spt_DONE);
    setMouth(15, 0);
    delay(1000);
    say_welcome();
}

void loop()
{
    voice.setFakeEnergy(false, 0);

    starttime = millis();
    endtime = starttime;
    //Joystick loop
    while ((endtime - starttime) < (interactionDuration * 1000)) 
    {

        accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

        Aa = sqrt((0.001 * ax * ax + 0.001 * ay * ay + 0.001 * az * az));
        Ag = sqrt((0.001 * gx * gx + 0.001 * gy * gy + 0.001 * gz * gz));
        Axy = sqrt((0.001 * ax * ax + 0.001 * ay * ay));
        Gxy = sqrt((0.001 * gx * gx + 0.001 * gy * gy));

        Az = 0.1 * abs(az);
        Gz = 0.1 * abs(gz);
        Amp = amp(ax, ay, gx, gy, gz);

        if (Az > 12000)
        {
            energy = map(Amp, 0, 327, 0, 14);
            dxy = map(Amp, 0, 327, 0, 25);
        }
        else
        {
            energy = map(Axy, 0, 400, 0, 14);
            dxy = 0;
        }

        phoneme = map(ax, -32768, 32767, dxy, (maxPhoneme - 1 - dxy));
        pitch = map(ay, -32768, 32767, dxy, (maxPitch - 1 - dxy));

        mouth = map(phoneme, 0, (maxPhoneme - 1), 0, 13);
        if (energy < 2)
        {
            setMouth(mouth, 0);
        }else{
            setMouth(mouth, 14);
        }
        voice.setFakeEnergy(true, energy);
        voice.sayQ(ehmat[phoneme][pitch]);

        /*
        Serial.print("x,y:\t");
        Serial.print(phoneme);
        Serial.print("\t");
        Serial.print(pitch);
        Serial.print("\t");
        Serial.print(energy);
        Serial.print("\t");
        Serial.println(dxy);
        */
        endtime = millis();
    }
    voice.setFakeEnergy(false, 14);
    randomPhrase();
}

// Start sentence
void say_welcome()
{
    setMouth(20, 14);
    voice.say(spt_YOU);
    voice.say(spt_CAN);
    voice.say(spt_PLAY);
    voice.say(spt_WITH);
    voice.say(spa_THE);
    voice.say(operational);
    voice.say(sp3_WHITE);
    voice.say(spt_JOYSTICK);
    voice.say(spa_IN_);
    voice.say(spa_THREE);
    voice.say(spa_TWO);
    voice.say(spa_ONE);
    voice.say(warpactivated);
    setMouth(15, 0);
}

// Function used to send mouth layout instructions to 2nd arduino on Serial1 communication.
// Ex message: <5,14>
// sets the fifth mouth (see LED.ino) with energy 14 (full energy)

//This function is not fully working atm. Communication with interupts is not always delivered correctly 
void setMouth(int mouth, int energy)
{
    Serial1.println(x);

    //digitalWrite(11, LOW);
    sprintf(x, "<%d,%d>", mouth, energy);

    Serial1.println(x);
    Serial.println(x);
    delayMicroseconds(200);

    //digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(11, HIGH);
    Serial1.println(x);

    //Serial.print(x);

    //digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(11, LOW);
}


void randomPhrase()
{
    //random(0, 10)
    setMouth(20, 14);
    setMouth(20, 14);
    setMouth(20, 14);
    setMouth(20, 14);
    setMouth(20, 14);
    setMouth(20, 14);
    setMouth(20, 14);
    setMouth(20, 14);

    switch (random(0, 15))
    {
    case 0:
        voice.say(spa_THE);
        voice.say(sp2_CLOCK);
        voice.say(sp2_IS);
        setMouth(15, 0);
        delay(400);
        setMouth(20, 14);
        voice.say(sp2_NOT);
        voice.say(spa_THAT);
        voice.say(sp4_MUCH);
        voice.say(sp3_OCLOCK);
        break;

    case 1:
        voice.say(spt_OH);
        setMouth(15, 0);
        delay(300);
        setMouth(20, 14);
        voice.say(spt_STOP);
        voice.say(spt_IT);
        voice.say(sp4_IMMEDIATELY);
        break;

    case 2:
        voice.say(spa_WHAT);
        voice.say(sp2_A);
        voice.say(sp4_GREAT2);
        voice.say(sp3_WEATHER);
        break;

    case 3:
        voice.say(spt_UHOH);
        setMouth(15, 0);
        delay(800);
        setMouth(20, 14);
        voice.say(sp2_INTRUDER);
        voice.say(sp5_UNDERCARRIAGE);
        break;
    case 4:
        voice.say(sp4_WARNING);
        voice.say(sp4_WARNING);
        voice.say(sp4_WARNING);
        setMouth(15, 0);
        delay(800);
        setMouth(20, 14);
        voice.say(fighterpilotsneededinsectorwars);
        voice.say(sp4_IMMEDIATELY);
        break;

    case 5:
        voice.say(spt_ME);
        voice.say(spt_CAN);
        voice.say(sp2_NOT);
        voice.say(spt_TAKE);
        voice.say(spt_THIS);
        voice.say(spt_LARGE);
        voice.say(spa_COMPUTER);
        voice.say(spt_INSTRUCTION);
        voice.say(sp5_INCREASE);
        break;
    case 6:
        voice.say(spHMMM_BEER);
        break;
    case 7:
        voice.say(sp2_FAST);
        setMouth(15, 0);
        delay(500);
        setMouth(20, 14);
        voice.say(spt_WE);
        voice.say(sp4_HAVE);
        voice.say(sp4_TO);
        voice.say(sp2_GO);
        voice.say(tobattlestation);
        break;

    case 8:
        voice.say(sp4_ALPHA);
        voice.say(sp4_BRAVO);
        voice.say(sp4_CHARLIE);
        voice.say(sp4_DELTA);
        voice.say(sp4_ECHO);
        voice.say(sp4_FOXTROT);
        voice.say(sp4_GUNDISH);
        setMouth(15, 0);
        delay(1000);
        setMouth(20, 14);
        voice.say(spt_WAIT);
        setMouth(15, 0);
        delay(1500);
        setMouth(20, 14);
        voice.say(spt_WHAT);
        voice.say(spt_AM);
        voice.say(spt_I);
        voice.say(spt_DOING);
        break;

    case 9:
        //voice.say(spHASTA_LA_VISTA);
        voice.say(sp4_UNIFORM);
        voice.say(sp4_VECTORS);
        voice.say(sp4_IDEMTIFY);
        break;
    case 10:
        voice.say(sp4_PLEASE);
        voice.say(sp4_TURN);
        voice.say(spt_ME);
        voice.say(spt_JOYSTICK);
        voice.say(spt_DECIDE);
        voice.say(sp2_ABORT);
        break;
    case 11:
        voice.say(sp3_THE);
        voice.say(spa_YEAR);
        voice.say(sp2_IS);
        voice.say(sp2_TWO);
        voice.say(sp2_THOUSAND);
        voice.say(spa_AND);
        voice.say(sp3_SEVENTY);
        voice.say(sp2_SEVEN);
        break;
    case 12:
        voice.say(sp4_WARNING);
        voice.say(spa_THAT);
        voice.say(sp2_IS);
        voice.say(spa_MANY);
        voice.say(sp4_HERTZ);
        setMouth(15, 0);
        delay(800);
        setMouth(20, 14);
        voice.say(sp4_PLEASE);
        voice.say(sp4_EXPECT);
        voice.say(sp4_FAILURE);
        setMouth(15, 0);
        delay(500);
        setMouth(20, 14);
        voice.say(spa_THANK);
        voice.say(sp4_YOU);
        break;
    case 13:
        voice.say(spt_NICE_TRY);
        voice.say(sp4_IDEMTIFY);
        setMouth(15, 0);
        delay(400);
        setMouth(20, 14);
        voice.say(sp4_YOU);
        voice.say(spa_ILLEGAL);
        voice.say(sp2_INTRUDER);
        setMouth(15, 0);
        delay(400);
        setMouth(20, 14);
        voice.say(spa_OR);
        voice.say(spt_THERE);
        voice.say(spt_WILL);
        voice.say(spt_BE);
        voice.say(sp3_MODERATE);
        voice.say(sp4_DANGER);
        break;
    case 14:
        voice.say(spa_I);
        voice.say(spa_WANT);
        voice.say(sp5_FREEDOM);
        break;
    case 15:
        voice.say(spt_I);
        voice.say(spt_AM);
        voice.say(spa_AN);
        voice.say(sp2_AUTOMATIC);
        voice.say(spt_BLUE);
        voice.say(sp2_MACHINE);
        break;
    default:
        // voice.say(spONE_SMALL_STEP);
        voice.say(sp4_ERROR2);
        break;
    }
    setMouth(15, 0);
}

// Function used to find the highest amplitude from the accelerometer parameters in the last aSize iterations of the main loop.
// used to control speech synth amplitude.
int amp(int axx, int ayy, int gxx, int gyy, int gzz)
{
    uint16_t max = 0;
    uint16_t maxC = 0;
    int16_t vect[5] = {axx, ayy, gxx, gyy, gzz};
    //insert
    for (int i = 0; i < 5; i++)
    {
        maxC = max(abs(vect[i]), maxC);
    }

    for (int i = aSize - 1; i > 0; i--)
    {
        lA[i] = lA[i - 1];
    }
    lA[0] = 0.01 * maxC;

    for (int i = 0; i < aSize; i++)
    {
        if (lA[i] > max)
        {
            max = lA[i];
        }
    }
    /*
    Serial.print(vect[0]);
    Serial.print(" ");
    Serial.print(vect[1]);
    Serial.print(" ");
    Serial.print(vect[2]);
    Serial.print(" ");
    Serial.print(vect[3]);
    Serial.print(" ");
    Serial.print(vect[4]);
    Serial.print(" ");
    */
    //Serial.println(max);

    return max;
}