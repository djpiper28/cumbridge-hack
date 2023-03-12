/*******************************************************************
This code is partically based off of the ArduinoSpotify example
 *******************************************************************/

// ----------------------------
// Internal Helper Functions
// ----------------------------
#include <Arduino.h>
#include <GxEPD.h>
#include <GxGDE0213B72B/GxGDE0213B72B.h> // 2.13" b/w
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#define MAX_LENGTH_PER_LINE 22 // max length of a line on the display

void showLines(String text, int maxLines, int y, GxEPD_Class* display);

int rumbleMotorPin = 32;
int buttonPin = 39;

char buff[1024];

bool isButtonPressed = true;

GxIO_Class io(SPI, /*CS=5*/ SS, /*DC=*/17, /*RST=*/16);
GxEPD_Class display(io, /*RST=*/16, /*BUSY=*/4);

void setup()
{
  Serial.begin(115200);
  // Initialising the display
  display.init(115200);
  display.setRotation(1);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextSize(1);
  display.setTextWrap(true);

  // printing hello world to the display
  display.setCursor(0, 20);
  display.println("Hello World!");
  display.setCursor(0, 40);
  display.println("Hack Cambridge?");

  Serial.println("Updating display");
  display.update();
  pinMode(rumbleMotorPin, OUTPUT);
  digitalWrite(rumbleMotorPin, LOW);
  pinMode(buttonPin, INPUT);

}

void loop() {
  // Check if serial data is available, if so, add to buffer
  if (Serial.available() > 0) {
    Serial.readString().toCharArray(buff, 1024);

        // Turn on rumble motor
    if(strcmp(buff, "1") == 0) {
      Serial.println("Turning on pin 32");
      digitalWrite(rumbleMotorPin, HIGH);
    } else if (strcmp(buff, "0") == 0) {
      Serial.println("Turning off pin 32");
      digitalWrite(rumbleMotorPin, LOW);
    } else {
      display.fillScreen(GxEPD_WHITE);
      display.setCursor(0, 0);

      // Remove all newlines from the buffer
      for (int i = 0; i < 1024; i++) {
        if (buff[i] == '\n') {
          buff[i] = ' ';
        }
      }
      showLines(buff, 6, 20, &display);
      display.update();

    }
  }
  // Check if button is pressed, if so, send a 1 to the serial port
  if (digitalRead(buttonPin) == HIGH) {
    if (!isButtonPressed) {
      Serial.println("not pressed");
      isButtonPressed = true;
    }
  } else {
    if(isButtonPressed) {
      Serial.println("pressed");
    }
    isButtonPressed = false;
  }
}


void showLines(String text, int maxLines, int y, GxEPD_Class* display)
{ // this function displays words whole on the display and limits the lines they use
  if (y > 0)
  { // if a Y is given, set the cursor to it
    display->setCursor(0, y);
  }
  if (text.length() > MAX_LENGTH_PER_LINE)
  {
    for (int i = 0; i < maxLines; i++)
    {
      if (text.length() > 0)
      {
        if (text.length() > 21)
        {
          if (i == maxLines - 1)
          {
            text = text.substring(0, 18);
            text.concat("...");
            // display->setCursor(0, y);
            display->println(text.c_str());
          }
          else
          {
            int endOfLastWord = text.lastIndexOf(" ", 21);
            String temp = text.substring(0, endOfLastWord);
            text = text.substring(endOfLastWord + 1);
            // display->setCursor(0, y);
            display->println(temp.c_str());
            y += 15;
          }
        }
        else
        {
          display->println(text.c_str());
          text = "";
        }
      }
    }
  }
  else
  {
    display->println(text.c_str());
  }
}