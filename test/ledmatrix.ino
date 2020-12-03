byte A[] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000
};
byte B[] = {
  B01000,
  B01000,
  B01000,
  B01000,
  B01000
};
byte C[] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};
byte D[] = {
  B00010,
  B00010,
  B00010,
  B00010,
  B00010
};
byte E[] = {
  B00001,
  B00001,
  B00001,
  B00001,
  B00001
};

//const int columnPins[] = {6, 7, 8, 9, 10};
const int columnPins[] = {2, 3, 4, 5};
//const int rowPins[] = {2, 3, 4, 5};
const int rowPins[] = {6, 7, 8, 9, 10};
int incomingByte = 1;
  
void setup() {
  for (int i=0; i < 6; i++) {
    pinMode(rowPins[i], OUTPUT);
    pinMode(columnPins[i], OUTPUT);
    digitalWrite(columnPins[i], HIGH);
  }
}
void loop() {

  if (incomingByte == 1) {

    show(A, 200);
    show(B, 200);
    show(C, 200);
    show(D, 200);
    show(E, 200);
  }
}

void show( byte * image, unsigned long duration)
{
  unsigned long start = millis();
  while (start + duration > millis())
  {
    for(int row = 0; row < 5; row++){
      digitalWrite(rowPins[row], HIGH);
      for(int column = 0; column < 4; column++){
        
        boolean pixel = bitRead(image[row], column);
        if(pixel == 1){
        digitalWrite(columnPins[column], LOW);
        }
        delayMicroseconds(300);
        digitalWrite(columnPins[column], HIGH);
      }
      digitalWrite(rowPins[row], LOW);
   }
}
}