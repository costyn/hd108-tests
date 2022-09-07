#include <Arduino.h>
#include <FastLED.h>

#define CLOCK_PIN 26
#define NUM_LEDS_PER_STRIP 15
#define NUM_STRIPS 1
#define PIXEL_TYPE HD108
#define USE_FASTLED

#define FULL_DMA_BUFFER //this will enable the full dma buffer
#include "I2SClockBasedLedDriver.h"
//here we have 4 colors per pixel
uint8_t leds[NUM_LEDS_PER_STRIP*NUM_STRIPS*4];

int pins[16]={25};

I2SClockBasedLedDriver driver;

void setup() {
    Serial.begin(115200);
    driver.initled((uint8_t*)leds,pins,CLOCK_PIN,NUM_STRIPS,NUM_LEDS_PER_STRIP);
    driver.setGlobalBrightness(50);
}

int off=0;
long time1,time2,time3;
void loop() {
    time1=ESP.getCycleCount();
    for(int j=0;j<NUM_STRIPS;j++)
    {
        for(int i=0;i<NUM_LEDS_PER_STRIP;i++)
        {   
            driver.setPixel(i,128,0,128,255);    
            // driver.setPixel((i+off)%NUM_LEDS_PER_STRIP+NUM_LEDS_PER_STRIP*j,(NUM_LEDS_PER_STRIP-i)*255/NUM_LEDS_PER_STRIP,i*255/NUM_LEDS_PER_STRIP,(((128-i)+255)%255)*255/NUM_LEDS_PER_STRIP);
            
        }
        for(int i=0;i<(j+1);i++)
        {
         // driver.setPixel(i+j*NUM_LEDS_PER_STRIP,255,0,0);
        }
    }
    time2=ESP.getCycleCount();
    driver.showPixels();
    time3=ESP.getCycleCount();
    Serial.printf("Calcul pixel fps:%.2f   showPixels fps:%.2f   Total fps:%.2f \n",(float)240000000/(time2-time1),(float)240000000/(time3-time2),(float)240000000/(time3-time1));
    off++;
    
}