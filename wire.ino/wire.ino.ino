#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <BH1750.h>
#include "TSL2561.h"

BH1750 lightMeter;
Adafruit_BMP085 bmp180;
TSL2561 tsl(TSL2561_ADDR_FLOAT); 
int media, i;
float mediaf;
long tempo = 100;
void setup(){
  Serial.begin(115200);
  Serial.setTimeout(tempo);
  Wire.begin();
  lightMeter.begin();
  tsl.begin();
  tsl.setTiming(TSL2561_INTEGRATIONTIME_13MS);
  bmp180.begin();
}

void loop() {

  postBH1750();
  postBMP180();
  postLDR1();
  postLDR2();
  postLDR3();
  postLDR4();
  postTSL2561();

  delay(5000);

}

void postBH1750(){
  media = 0;
  for(i=0; i<10; i++){
    media += lightMeter.readLightLevel();
    delay(10);
  }
  Serial.write("1 ");
  Serial.write(String(media/10).c_str());  
  delay(100);
}

void postBMP180(){
  mediaf = 0;
  for(i=0; i<10; i++){
    mediaf += bmp180.readTemperature();
    delay(10);
  }
  Serial.write("2 ");
  Serial.write(String(mediaf/10.0).c_str());  
  delay(100);
}

void postLDR1(){
  media = 0;
  for(i=0; i<10; i++){
    media += analogRead(A2);
    delay(10);
  }
  Serial.write("3 ");
  Serial.write(String(media/10).c_str());  
  delay(100);
}

void postLDR2(){
  media = 0;
  for(i=0; i<10; i++){
    media += analogRead(A1);
    delay(10);
  }
  Serial.write("4 ");
  Serial.write(String(media/10).c_str());  
  delay(100);
}

void postLDR3(){
  media = 0;
  for(i=0; i<10; i++){
    media += analogRead(A3);
    delay(10);
  }
  Serial.write("5 ");
  Serial.write(String(media/10).c_str());  
  delay(100);
}

void postLDR4(){
  media = 0;
  for(i=0; i<10; i++){
    media += analogRead(A0);
    delay(10);
  }
  Serial.write("6 ");
  Serial.write(String(media/10).c_str());  
  delay(100);
}

void postTSL2561(){
  uint32_t mediair=0, mediafull=0, mediav=0, medialx=0;
  uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir, full;
  for(i=0; i<10; i++){
    lum = tsl.getFullLuminosity();
    ir = lum >> 16;
    full = lum & 0xFFFF;
    mediair += ir;
    mediafull += full;
    mediav += full-ir;
    medialx += tsl.calculateLux(full, ir);
  }
  
  Serial.write("7 ");
  Serial.write(String(mediair/10).c_str());
  Serial.write("/");
  Serial.print(String(mediafull/10).c_str());
  Serial.write("/");
  Serial.print(String(mediav/10).c_str());   
  Serial.write("/");
  Serial.write(String(medialx/10).c_str());
}


