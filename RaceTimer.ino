// include the library code:
#include <LiquidCrystal.h>

const int sensorPin = 0;
const int ledPin = 9;
int lightLevel, high = 0, low = 1023;
int minutes;
int seconds;
int milliseconds;
float startTime;
float endTime;
float elapsedTime;
//initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  //lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  int start = 0;
  //Serial.println(lightLevel);
  light();
  do
  {
    light();
    if (lightLevel > 200 && start == 0)
    {
      startTime = millis();
      start = 1;
      //lcd.clear();
      //lcd.print("Timer Started");
      digitalWrite(13, HIGH); //LED Timing light on
      delay(10000);
    }
    light();

    if (lightLevel > 200 && start == 1)
    {
      endTime = millis();
      start = 2;
      //lcd.clear();
      digitalWrite(13, LOW);   // LED Timing light off
      //lcd.print("Timer Stopped");
      delay(3000);
    }

    if (start == 2)
    {
      elapsedTime = endTime - startTime;
      minutes = elapsedTime / 60000;
      elapsedTime = (minutes * 60000) - elapsedTime;
      seconds = -(elapsedTime / 1000);
      elapsedTime = (seconds * 1000) - elapsedTime;
      milliseconds = elapsedTime / 1000;
      start = 3;
    }

    //Next line of LCD
    //lcd.setCursor(0, 1);   //LCD screen pint
    //lcd.print(millis());

    if (start == 3)
    {
      Serial.print("Time:");
      Serial.print(minutes);
      Serial.print(':');
      Serial.print(seconds);
      Serial.print('.');
      Serial.print(milliseconds);
      Serial.println("");
      Serial.println("");
      start = -1;
    }
  } while (start != -1);
  delay(5000);
}
void light()
{
  lightLevel = analogRead(sensorPin);
  autoTune(); // calls autoTune function
  analogWrite(ledPin, 255 - lightLevel);
}
void autoTune()
{
  if (lightLevel < low)
  {
    low = lightLevel;
  }
  if (lightLevel > high)
  {
    high = lightLevel;
  }
  lightLevel = map(lightLevel, low + 30, high - 30, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);
}
