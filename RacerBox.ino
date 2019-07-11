#include <Keyboard.h>
#include <Keypad.h>
#include <Encoder.h>

const byte ROWS = 5;
const byte COLS = 5;

char keys[ROWS][COLS] = {
  {'1','2','3','4','5'},
  {'6','7','8','9','0'},
  {'a','b','c','d','e'},
  {'f','g','h','i','j'},
  {'k','l','m','n','o'}
};
// Row pinouts.
byte rowPins[ROWS] = {8, 9, A1, A2, A3};
// Column pinouts.
byte colPins[COLS] = {A0, 15, 14, 16, 10};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );;

Encoder knobs[3] = {
  // First encoder is connected to pin 2 and 3.
  Encoder(2, 3),
  Encoder(4, 5),
  Encoder(6, 7),
};

byte knobPosition[3] = {-99, -99, -99};

void pressKey(char key) {
    Keyboard.write(key);
    Serial.println(key + " sent");
}


char knobKeys[3][2] = {
  {'p', 'q'},
  {'r', 's'},
  {'t', 'u'},
};

void setup(){
  delay(500);
  Serial.begin(9600);
  Keyboard.begin();
  Serial.println("init");
}

void loop(){
  char key = keypad.getKey();
  if (key != NO_KEY){
    pressKey(key);
  }


  for (int i = 0; i < sizeof(knobs); i++) {
    long newKnobPosition;
    newKnobPosition = knobs[i].read();
    if (newKnobPosition != knobPosition[i]) {
      pressKey(knobKeys[i][newKnobPosition > knobPosition[i] ? 1 : 0]);
      knobPosition[i] = newKnobPosition;
    }
  }
}
