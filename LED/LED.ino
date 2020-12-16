
#include <Arduino.h>

////LED MATRIX THINGS
/////////////////////
byte A[] = {
    B1111,
    B1001,
    B1001,
    B1001,
    B1111};
byte O[] = {
    B0000,
    B1111,
    B1001,
    B1111,
    B0000};
byte U[] = {
    B0000,
    B1110,
    B1010,
    B1110,
    B0000};
byte I[] = {
    B1110,
    B1010,
    B1010,
    B1010,
    B1110};
byte E[] = {
    B1110,
    B1010,
    B1010,
    B1010,
    B1110};
byte L[] = {
    B0000,
    B1110,
    B1010,
    B1010,
    B1110};
byte LL[] = {
    B0000,
    B0000,
    B1111,
    B1001,
    B1111};
byte R[] = {
    B1110,
    B1010,
    B1010,
    B1110,
    B0000};
byte RR[] = {
    B1111,
    B1001,
    B1111,
    B0000,
    B0000};
byte IDLE[] = {
    B0000,
    B0100,
    B0100,
    B0100,
    B0000};
byte MIDDLE[] = {
    B0110,
    B0110,
    B0110,
    B0110,
    B0110};
byte FLAT[] = {
    B0100,
    B0100,
    B0100,
    B0100,
    B0100};

int8_t c;
const int colPins[] = {3, 4, 5, 6};
const int rowPins[] = {7, 8, 9, 10, 11};

const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data
int mouth=20, energy = 14, prevMouth;
boolean newData = false;
int iTalking = 0;

void setup()
{
    Serial.begin(19200);
    pinMode(LED_BUILTIN, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(2), recvWithStartEndMarkers, RISING);

    for (int i = 0; i <= sizeof(colPins) / sizeof(colPins[0]); i++)
    {
        pinMode(colPins[i], OUTPUT);
        digitalWrite(colPins[i], HIGH);
    }
    for (int i = 0; i <= sizeof(rowPins) / sizeof(rowPins[0]); i++)
    {
        pinMode(rowPins[i], OUTPUT);
    }
}

void loop()
{
    if (mouth == 20)
    {
        showTalkingMouth();
    }
    else
    {
        showMouth();
    }
}

void showTalkingMouth()
{

    int fourthnthird = (millis() / 100) % 100;

    switch ((fourthnthird) % 4)
    {
    case 0:
        show(FLAT);
        break;
    case 1:
        show(E);
        break;
    case 2:
        show(A);
        break;
    case 3:
        show(E);
        break;
    }
    if (iTalking > 2)
    {
        iTalking = 0;
    }
    else
    {
        iTalking++;
    }
}

void showMouth()
{
    if (energy > 1)
    {
        switch (mouth)
        {
        case 0:
            show(LL);
            break;
        case 1:
            show(A);
            break;
        case 2:
            show(A);
            break;
        case 3:
            show(A);
            break;
        case 4:
            show(I);
            break;
        case 5:
            show(E);
            break;
        case 6:
            show(A);
            break;
        case 7:
            show(U);
            break;
        case 8:
            show(E);
            break;
        case 9:
            show(E);
            break;
        case 10:
            show(O);
            break;
        case 11:
            show(U);
            break;
        case 12:
            show(A);
            break;
        case 13:
            show(RR);
            break;
        default:
            show(IDLE);
            break;
        }
    }
    else
    {
        show(IDLE);
    }
    return;
}

void show(byte *image)
{

    //delayMicroseconds((14 - energy) * 800);
    for (int row = 0; row < 5; row++)
    {
        digitalWrite(rowPins[row], HIGH);
        for (int column = 0; column < 4; column++)
        {

            bool pixel = bitRead(image[row], column);
            if (pixel == 1)
            {
                digitalWrite(colPins[column], LOW);
            }
            delayMicroseconds(300);
            digitalWrite(colPins[column], HIGH);
        }
        digitalWrite(rowPins[row], LOW);
    }
}

void recvWithStartEndMarkers()
{
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
    digitalWrite(LED_BUILTIN, HIGH);

    // if (Serial.available() > 0) {
    while (Serial.available() > 0 && newData == false)
    { // <<== NEW - get all bytes from buffer
        rc = Serial.read();

        if (recvInProgress == true)
        {
            if (rc != endMarker)
            {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars)
                {
                    ndx = numChars - 1;
                }
            }
            else
            {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker)
        {
            recvInProgress = true;
        }
    }
    parseData();
    digitalWrite(LED_BUILTIN, LOW);
    showNewData();
}

void parseData()
{

    // split the data into its parts

    char *strtokIndx; // this is used by strtok() as an index

    //strcpy(messageFromPC, strtokIndx);       // copy it to messageFromPC

    strtokIndx = strtok(receivedChars, ","); // get the first part - the string
    mouth = atoi(strtokIndx);                // convert this part to an integer

    strtokIndx = strtok(NULL, ",");
    energy = atoi(strtokIndx);
}
void showNewData()
{
    if (newData == true)
    {
        Serial.print("\nmouth=");
        Serial.print(mouth);
        Serial.print("\tenergy=");
        Serial.print(energy);
        newData = false;
    }
}