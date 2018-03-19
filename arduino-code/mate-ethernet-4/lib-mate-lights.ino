#include <FastLED.h>

#define STRIP_NUM_LEDS 150

int TOTAL_NUM_LEDS = STRIP_NUM_LEDS;

// Define the array of leds
CRGB leds[STRIP_NUM_LEDS];
CRGB leds2[STRIP_NUM_LEDS];

void setupLeds(int totalNumLeds) {
  TOTAL_NUM_LEDS = totalNumLeds;

  // Uncomment/edit one of the following lines for your leds arrangement.
  FastLED.addLeds<WS2812B, 5, GRB>(leds, STRIP_NUM_LEDS);
  FastLED.addLeds<WS2812B, 6, GRB>(leds2, STRIP_NUM_LEDS);

//  FastLED.setBrightness( BRIGHTNESS );
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);

  for (int i = 0; i < TOTAL_NUM_LEDS; i++) {
    writeLeds(i,0,0,0);
  }

  for(int i=0;i<3;i++){
    writeLeds(0+i*STRIP_NUM_LEDS, 0, 0, 0); // Black
    writeLeds(1+i*STRIP_NUM_LEDS, 255, 0, 0); // Red
    writeLeds(2+i*STRIP_NUM_LEDS, 0, 255, 0); // Green
    writeLeds(3+i*STRIP_NUM_LEDS, 0, 0, 255); // Blue
  }

  FastLED.show();
}

byte ENCODING_POS_RGB = 1;
byte ENCODING_POS_VGA = 2;
byte ENCODING_VGA = 3;
byte ENCODING_RGB = 4;

void writeLeds(int pos, byte r, byte g, byte  b) {
  if (pos < 150) {
    leds[pos].red = r;
    leds[pos].green = g;
    leds[pos].blue = b;
    leds[pos].maximizeBrightness();
  } else {
    leds2[pos-150].red = r;
    leds2[pos-150].green = g;
    leds2[pos-150].blue = b;
    leds2[pos-150].maximizeBrightness();
  }
}

void writeLedFrame(char data[], int offset) {
  int encoding = data[0+offset];
  if(encoding == ENCODING_RGB) {
    for (int i = 0; i < TOTAL_NUM_LEDS; i++) {
      writeLeds(i, data[1+i * 3 + offset], data[1+1 + i * 3 + offset], data[1+2 + i * 3+offset]);
      //writeLeds(i, i, 0, 0);
    }
  } else {
    Serial.println(F("Unexpected encoding byte"));
  }
  FastLED.show();
}

