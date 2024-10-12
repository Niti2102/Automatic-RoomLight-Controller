#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define in 8
#define out 9
#define bulb 10

int count = 0;
int inState = HIGH;  // Store the previous state of the in sensor
int outState = HIGH; // Store the previous state of the out sensor

void setup() {
  lcd.begin(16, 2);
  lcd.print("Visitor Counter");
  delay(2000);
  pinMode(in, INPUT);
  pinMode(out, INPUT);
  pinMode(bulb, OUTPUT);
  lcd.clear();
  lcd.print("Person In Room:");
  lcd.setCursor(0, 1);
  lcd.print(count);
}

void loop() {
  int inValue = digitalRead(in);
  int outValue = digitalRead(out);
  
  // Check for entry
  if (inValue != inState) {
    if (inValue == LOW) {
      count++;
      updateDisplay();
      delay(1000); // Delay to stabilize the count
    }
    inState = inValue;
  }
  
  // Check for exit
  if (outValue != outState) {
    if (outValue == LOW && count > 0) {
      count--;
      updateDisplay();
      delay(1000); // Delay to stabilize the count
    }
    outState = outValue;
  }
  
  controlBulb();
}

// Function to update the LCD displa
void updateDisplay() {
  lcd.clear();
  lcd.print("Person In Room:");
  lcd.setCursor(0, 1);
  lcd.print(count);
}
// Function to control the bulb based on count
void controlBulb() {
  if (count == 0) {
    digitalWrite(bulb, LOW);
    lcd.clear();
    lcd.print("Nobody In Room");
    lcd.setCursor(0, 1);
    lcd.print("Light is Off");
  } else {
    digitalWrite(bulb, HIGH);
  }
}
