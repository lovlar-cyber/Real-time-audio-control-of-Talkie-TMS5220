// Talkie library
// Copyright 2011 Peter Knight
// This code is released under GPLv2 license.
//
// Armin Joachimsmeyer 11/2018 converted to .c and .h files
//
// Here's a demo of the output of my work-in-progress custom speech compressor.
//
// Tom's Diner by Suzanne Vega, over two minutes of it, in 24 kilobytes of data.
//
// It does sound a little bit compressed though...
//
// Buy the original - it's stunning.
//     http://www.amazon.com/Solitude-Standing-Suzanne-Vega/dp/B000002GHB
//     http://www.amazon.co.uk/Solitude-Standing-Suzanne-Vega/dp/B000026GZQ
//
//     or look for 'Solitude Standing' on your preferred music store.
//            (Only this album contains the original a capella version)
//
// Sound is output on digital pin 3 and/or 11. It can drive headphones directly, or add a simple audio amplifier to drive a loudspeaker.

#include <Arduino.h>
#include "Talkie.h"
#include "Vocab_US_Acorn.h"
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
int pin = 3;
int sensorValue = 0;
int phoneme = 0;
int pitch = 0;

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

// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO

// uncomment "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit
// binary, one right after the other. This is very fast (as fast as possible
// without compression or data loss), and easy to parse, but impossible to read
// for a human.
//#define OUTPUT_BINARY_ACCELGYRO

#define LED_PIN 13
bool blinkState = false;

void setup()
{

    //TALKIE things
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
#if defined(__AVR_ATmega32U4__)
    while (!Serial)
        ; //delay for Leonardo, but this loops forever for Maple Serial
#endif
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_TALKIE));

//    voice.doNotUseUseInvertedOutput();
#if defined(TEENSYDUINO)
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH); //Enable Amplified PROP shield
#endif

#if !defined(__AVR_ATmega32U4__)

    //voice.say(spMMKF45);
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

    // use the code below to change accel/gyro offset values
    accelgyro.CalibrateGyro();
    accelgyro.CalibrateAccel();
    accelgyro.PrintActiveOffsets();

/*
    Serial.println("Updating internal sensor offsets...");
    int16_t cali[6] = {-3399,-1865,-1992, 15, -44, -30 };
    accelgyro.setXAccelOffset(cali[0]);
    accelgyro.setXAccelOffset(cali[1]);
    accelgyro.setXAccelOffset(cali[2]);
    accelgyro.setXGyroOffset(cali[3]);
    accelgyro.setYGyroOffset(cali[4]);
    accelgyro.setZGyroOffset(cali[5]);
    Serial.print(accelgyro.getXAccelOffset());
    Serial.print("\t");∏
    Serial.print(accelgyro.getYAccelOffset());
    Serial.print("\t");
    Serial.print(accelgyro.getZAccelOffset());
    Serial.print("\t");
    Serial.print(accelgyro.getXGyroOffset());
    Serial.print("\t");
    Serial.print(accelgyro.getYGyroOffset());
    Serial.print("\t");
    Serial.print(accelgyro.getZGyroOffset());
    Serial.print("\t");
    Serial.print("\n");
*/
    // configure Arduino LED pin for output
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    phoneme = map(analogRead(0), 0, 1023, 0, 22);
    pitch = map(analogRead(1), 0, 1023, 0, 62);
    voice.sayQ(ehmat[phoneme][pitch]);

    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    Serial.print("a/g:\t");
    Serial.print(ax);
    Serial.print("\t");
    Serial.print(ay);
    Serial.print("\t");
    Serial.print(az);
    Serial.print("\t");
    Serial.print(gx);
    Serial.print("\t");
    Serial.print(gy);
    Serial.print("\t");
    Serial.println(gz);

    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}

void initLPC()
{
    return;
}
