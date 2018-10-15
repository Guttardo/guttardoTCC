#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <BH1750.h>
#include "TSL2561.h"

#define ONE_WIRE_BUS 3
 
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;

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
  Serial.write("T");
  postBH1750();
  postBMP180();
  postLDR1();
  postLDR2();
  postLDR3();
  postTSL2561();
  postTEMT6000();
  postDS18B20();

  delay(5000);

}

void postBH1750(){
  media = 0;
  for(i=0; i<10; i++){
    media += lightMeter.readLightLevel();
    delay(30);
  }
  Serial.write("1");
  Serial.write(String(String(media/10).length()).c_str());
  Serial.write(String(media/10).c_str());  
  delay(100);
}

void postBMP180(){
  mediaf = 0;
  for(i=0; i<10; i++){
    mediaf += bmp180.readTemperature();
    delay(30);
  }
  Serial.write("2");
  Serial.write(String(String(mediaf/10.0).length()).c_str());
  Serial.write(String(mediaf/10.0).c_str());  
  delay(100);
}

void postLDR1(){
  media = 0;
  for(i=0; i<10; i++){
    media += analogRead(A2);
    delay(30);
  }
  Serial.write("3");
  Serial.write(String(String(media/10).length()).c_str());
  Serial.write(String(media/10).c_str());  
  delay(100);
}

void postLDR2(){
  media = 0;
  for(i=0; i<10; i++){
    media += analogRead(A1);
    delay(30);
  }
  Serial.write("4");
  Serial.write(String(String(media/10).length()).c_str());
  Serial.write(String(media/10).c_str());  
  delay(100);
}


void postLDR3(){
  media = 0;
  for(i=0; i<10; i++){
    media += analogRead(A0);
    delay(30);
  }
  Serial.write("5");
  Serial.write(String(String(media/10).length()).c_str());
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
    delay(30);
  }
  
  Serial.write("6");
  Serial.write(String(String(mediair/10).length()).c_str());
  Serial.write(String(mediair/10).c_str());
  Serial.write(String(String(mediafull/10).length()).c_str());
  Serial.print(String(mediafull/10).c_str());
  Serial.write(String(String(mediav/10).length()).c_str());
  Serial.print(String(mediav/10).c_str());   
  Serial.write(String(String(medialx/10).length()).c_str());
  Serial.write(String(medialx/10).c_str());
}

void postTEMT6000(){
  media = 0;
  for(i=0; i<10; i++){
    media += analogRead(A3);
    delay(30);
  }
  Serial.write("7");
  Serial.write(String(String(media/10).length()).c_str());
  Serial.write(String(media/10).c_str());  
  delay(100);
}

void postDS18B20(){
  /*
  mediaf = 0;
  for(i=0; i<10; i++){
    mediaf += bmp180.readTemperature();
    delay(30);
  }
  Serial.write("8");
  Serial.write(String(String(mediaf/10.0).length()).c_str());
  Serial.write(String(mediaf/10.0).c_str());  
  delay(100);*/
}


