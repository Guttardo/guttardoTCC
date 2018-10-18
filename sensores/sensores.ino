
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
long media, i, vint, aint;
float mediaf, vfloat, afloat;
bool ruido = false;
long tempo = 100;
void setup(){
  Serial.begin(9600);
  Serial.setTimeout(tempo);
  Wire.begin();
  lightMeter.begin();
  tsl.begin();
  tsl.setGain(TSL2561_GAIN_0X);
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

  delay(20000);

}

void postBH1750(){
  media = 0;
  ruido = false;
  for(i=1; i<=10; i++){
    media += lightMeter.readLightLevel();
    delay(30);
  }
  Serial.write("a");
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
  Serial.write("b");
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
  Serial.write("c");
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
  Serial.write("d");
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
  Serial.write("e");
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
    if(i==0){
      mediair += (uint32_t)ir;
      mediafull += (uint32_t)full;
      mediav += (uint32_t)(full-ir);
      medialx += (uint32_t)(tsl.calculateLux(full, ir));
    }
    if(i!=0 && abs(ir-mediair)<500 && abs(full-mediafull)<1000){
      mediair = (mediair + (uint32_t)ir)/2;
      mediafull = (mediafull + (uint32_t)full)/2;
      mediav = (mediav + (uint32_t)full - (uint32_t)ir)/2;
      medialx = (medialx + tsl.calculateLux(full, ir))/2;
    }
    delay(30);
  }
  
  Serial.write("f");
  Serial.write(String(String(mediair).length()).c_str());
  Serial.write(String(mediair).c_str());
  Serial.write(String(String(mediafull).length()).c_str());
  Serial.print(String(mediafull).c_str());
  Serial.write(String(String(mediav).length()).c_str());
  Serial.print(String(mediav).c_str());   
  Serial.write(String(String(medialx).length()).c_str());
  Serial.write(String(medialx).c_str());
}

void postTEMT6000(){
  media = 0;
  for(i=0; i<10; i++){
    media += analogRead(A3);
    delay(30);
  }
  Serial.write("g");
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


