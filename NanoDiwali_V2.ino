#include <FastLED.h>


#define NUM_LEDS 432

#define LED_PIN     2
#define COLOR_ORDER GRB
#define CHIPSET     WS2812

#define BRIGHTNESS  80
#define FRAMES_PER_SECOND 30


CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette ;
TBlendType    currentBlending;

CRGBPalette16 gPal;

void setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
  gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White); 
}

void loop()
{ 
  random16_add_entropy( random());
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; 
  Fire2012WithPalette(startIndex); 
  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}

#define COOLING  70
#define SPARKING 200


void Fire2012WithPalette( uint8_t colorIndex)
{
  uint8_t secondHand = (millis() / 1000) % 60;
  static uint8_t lastSecond = 99;

  if ( lastSecond != secondHand) {
    lastSecond = secondHand;
    if ( secondHand ==  0)  {
      currentPalette = RainbowColors_p;
      currentBlending = LINEARBLEND;
    }
    if ( secondHand == 7)  {
      currentPalette = RainbowStripeColors_p;
      currentBlending = NOBLEND;
    }
    if ( secondHand == 14)  {
      currentPalette = RainbowStripeColors_p;
      currentBlending = LINEARBLEND;
    }
    if ( secondHand == 21)  {
      CRGB purple = CHSV( HUE_PURPLE, 255, 255);
      CRGB green  = CHSV( HUE_GREEN, 255, 255);
      CRGB black  = CRGB::Black;

      currentPalette = CRGBPalette16(
                         green,  green,  black,  black,
                         purple, purple, black,  black,
                         green,  green,  black,  black,
                         purple, purple, black,  black );
      currentBlending = LINEARBLEND;
    }
    if ( secondHand == 27)  {
      for ( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
      }             currentBlending = LINEARBLEND;
    }
    if ( secondHand == 35)  {
      fill_solid( currentPalette, 16, CRGB::Black);
      // and set every fourth one to white.
      currentPalette[0] = CRGB::White;
      currentPalette[4] = CRGB::White;
      currentPalette[8] = CRGB::White;
      currentPalette[12] = CRGB::White;
      currentBlending = NOBLEND;
    }
    if ( secondHand == 42)  {
      currentPalette = RainbowStripeColors_p;
                       currentBlending = LINEARBLEND;
    }
    if ( secondHand == 49)  {
      currentPalette = CloudColors_p;
      currentBlending = LINEARBLEND;
    }
    if ( secondHand == 52)  {
      currentPalette = PartyColors_p;
      currentBlending = LINEARBLEND;
    }
    if ( secondHand == 54)  {
      currentPalette = OceanColors_p;
      currentBlending = LINEARBLEND;
    }
    if ( secondHand == 57)  {
      currentPalette = ForestColors_p;
      currentBlending = LINEARBLEND;
    }
  } 
  static byte heat[72];
 
 for( int i = 0; i < 72; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / 72) + 2));
    }
  
   for( int k= 72 - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
 
  if ( random8() < SPARKING ) {
    int y = random8(7);
    heat[y] = qadd8( heat[y], random8(160, 255) );
  }
 
  for ( int j = 0; j < 72; j++) { 
    byte colorindex = scale8( heat[72-j], 240);
    CRGB color = ColorFromPalette( gPal, colorindex);
    int pixel1 =    j ;
    int pixel2 =    431 - j;
    leds[pixel1] = color;
    leds[pixel2] = color;
  }  
  for (int x = 0; x < NUM_LEDS; x++)
  {
    if (x > 71 && x < 360)
    {
      leds[x] = ColorFromPalette( currentPalette, colorIndex, 255, currentBlending);
      colorIndex += 3;
    }
  }
}
