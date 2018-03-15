#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include "RTClib.h"

Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731();
RTC_DS3231 rtc;

uint16_t X = 10;
uint8_t Color = 65535;

int8_t lastHourTens   = -1;
int8_t lastHourOnes   = -1;
int8_t lastMinuteTens = -1;
int8_t lastMinuteOnes = -1;

uint8_t _symbols[11][27] = {
  // 0
  {
    0, X, 0,
    X, 0, X,
    X, 0, X,
    X, 0, X,
    X, 0, X,
    X, 0, X,
    X, 0, X,
    X, 0, X,
    0, X, 0
  },
  // 1
  {
    0, X, 0,
    X, X, 0,
    0, X, 0,
    0, X, 0,
    0, X, 0,
    0, X, 0,
    0, X, 0,
    0, X, 0,
    X, X, X
  },
  // 2
  {
    0, X, 0,
    X, 0, X,
    0, 0, X,
    0, 0, X,
    0, X, 0,
    X, 0, 0,
    X, 0, 0,
    X, 0, 0,
    X, X, X
  },
  // 3
  {
    0, X, 0,
    X, 0, X,
    0, 0, X,
    0, 0, X,
    0, X, X,
    0, 0, X,
    0, 0, X,
    X, 0, X,
    0, X, 0
  },
  // 4
  {
    0, 0, X,
    X, 0, X,
    X, 0, X,
    X, 0, X,
    X, X, X,
    0, 0, X,
    0, 0, X,
    0, 0, X,
    0, 0, X
  },
  // 5
  {
    X, X, X,
    X, 0, 0,
    X, 0, 0,
    X, 0, 0,
    X, X, 0,
    0, 0, X,
    0, 0, X,
    X, 0, X,
    0, X, 0
  },
  // 6
  {
    0, X, 0,
    X, 0, X,
    X, 0, 0,
    X, 0, 0,
    X, X, 0,
    X, 0, X,
    X, 0, X,
    X, 0, X,
    0, X, 0
  },
  // 7
  {
    X, X, X,
    0, 0, X,
    0, 0, X,
    0, 0, X,
    0, X, 0,
    0, X, 0,
    0, X, 0,
    0, X, 0,
    0, X, 0
  },
  // 8
  {
    0, X, 0,
    X, 0, X,
    X, 0, X,
    X, 0, X,
    0, X, 0,
    X, 0, X,
    X, 0, X,
    X, 0, X,
    0, X, 0
  },
  // 9
  {
    0, X, 0,
    X, 0, X,
    X, 0, X,
    X, 0, X,
    X, X, X,
    0, 0, X,
    0, 0, X,
    X, 0, X,
    0, X, 0
  },
  // : (10)
  {
    0,
    0,
    0,
    X,
    0,
    X,
    0,
    0,
    0
  }
};

void myDrawBitmap(Adafruit_GFX &gfx, int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color) {
  for (int cy = 0; cy < h; cy++) {
    for (int cx = 0; cx < w; cx++) {
      uint8_t pixel = bitmap[cy * w + cx];
      if (pixel == 0) {
        gfx.drawPixel(x + cx, y + cy, pixel);
      } else {
        gfx.drawPixel(x + cx, y + cy, color);
      }
    }
  }
}

void myClearScreen(Adafruit_GFX &gfx) {
  for (int y = 0; y < 9; y++) {
    for (int x = 0; x < 16; x++) {
      gfx.drawPixel(x, y, 0);
    }
  }
}

/**
 * Initializer.
 */
void setup() {
  Serial.begin(9600);

  if (! ledmatrix.begin()) {
    Serial.println("IS31FL3731 not found");
    while (1);
  }
  Serial.println("IS31FL3731 found");

  if (! rtc.begin()) {
    Serial.println("DS3231 not found");
    while (1);
  }
  Serial.println("DS3231 found");

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  myClearScreen(ledmatrix);
}

/**
 * Loop function.
 */
void loop() {
  DateTime now = rtc.now();

  uint8_t hour, minute;

  hour = now.hour();
  if (hour > 12) {
    hour -= 12;
  }
  minute = now.minute();

  int hourTens = hour / 10;
  int hourOnes = hour - hourTens;
  int minuteTens = minute / 10;
  int minuteOnes = minute - (minuteTens * 10);

  if (hourTens > 0) {
    myDrawBitmap(ledmatrix, 0, 0, _symbols[hourTens],  3, 9, Color);
  }

  myDrawBitmap(ledmatrix, 4, 0, _symbols[hourOnes],  3, 9, Color);

  myDrawBitmap(ledmatrix, 7, 0, _symbols[10], 1, 9, Color);
  
  myDrawBitmap(ledmatrix, 8, 0, _symbols[minuteTens],  3, 9, Color);

  myDrawBitmap(ledmatrix, 12, 0, _symbols[minuteOnes], 3, 9, Color);

  delay(1000);
}

