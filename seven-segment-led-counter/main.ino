#include <MsTimer2.h>

// 1 2 4 6 7 9 10
const int SEVEN_SEG_PINS[] = {13, 12, 11, 10, 9, 8, 7};
const int ONES_PLACE_PIN = 6;
const int TENS_PLACE_PIN = 5;

// output pattern of 7-segment LED
boolean OUTPUT_PATTERN[10][7]={
  {0, 0, 0, 0, 0, 0, 1}, {1, 1, 0, 0, 1, 1, 1}, {0, 0, 1, 0, 0, 1, 0}, {1, 0, 0, 0, 0, 1, 0},
  {1, 1, 0, 0, 1, 0, 0}, {1, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0}
};

int counter = 1;

void countUp() {
  counter += 1;
}

void setup() {
  // setup pins
  for (int i = 0; i < 7; i++) {
    pinMode(SEVEN_SEG_PINS[i], OUTPUT);
  }
  pinMode(ONES_PLACE_PIN, OUTPUT);
  pinMode(TENS_PLACE_PIN, OUTPUT);

  // setup timer
  MsTimer2::set(1000, countUp); // 1000ms period
  MsTimer2::start();
}

void turnOn(boolean number[]) {
  for (int i = 0; i <= 6; i++){
    digitalWrite(SEVEN_SEG_PINS[i], number[i]);
  } 
}

void loop() {
  if (counter > 60) {
    counter = 1;
    return;
  }
  
  char digit[2];
  sprintf(digit, "%02d", counter);

  // turn on ones place digit
  digitalWrite(ONES_PLACE_PIN, HIGH);
  digitalWrite(TENS_PLACE_PIN, LOW);
  turnOn(OUTPUT_PATTERN[digit[0] - '0']);
  delay(8);

  // turn on tens place digit
  digitalWrite(ONES_PLACE_PIN, LOW);
  digitalWrite(TENS_PLACE_PIN, HIGH);
  turnOn(OUTPUT_PATTERN[digit[1] - '0']);
  delay(8);
}
