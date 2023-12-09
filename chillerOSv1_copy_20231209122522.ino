//
//    FILE: DS18B20_minimum.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: most minimal sketch
//     URL: https://github.com/RobTillaart/DS18B20_INT
//
// WARNING: this sketch does not wait for isConversionComplete()
//          and therefore temperature read is probably incorrect
//          but it is fast and maybe accurate enough...

//#include <SoftPWM.h>

#include <OneWire.h>
#include <DS18B20_INT.h>


#define ONE_WIRE_BUS            A2

OneWire     oneWire(ONE_WIRE_BUS);
DS18B20_INT sensor(&oneWire);
 

void setup(void)

{
  
  analogReadResolution(12);
//SoftPWMBegin();
  
  //SoftPWMSet(D4, 0);

 // SoftPWMSetFadeTime(D4, 100, 100);
 // pwmFrequency(D5, 100);
 pinMode(A3,INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A4,INPUT_PULLUP);
  pinMode(A5,INPUT_PULLUP);
pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
pinMode(D5, ANALOG); 
  digitalWrite(D2,LOW);
//  pwmMode(D5, PWM_MODE_SOLO, PWM_FREQ_FAST);
 Serial.begin(9600);
  Serial.println(__FILE__);
  Serial.print("DS18B20_INT_LIB_VERSION: ");
  Serial.println(DS18B20_INT_LIB_VERSION);
  int val = 0;
 sensor.begin();
 sensor.setResolution(8);
 analogReference(INTERNAL4V096);
}
void loop(void)
{
  int val = map(sensor.getTempCentiC(), 2500, 3300, 50, 77);
   val = constrain(val, 50, 77);
  Serial.print("val");
Serial.print("\t");  
Serial.println(val);
analogWrite(D5, val);
Serial.print("temp");
Serial.print("\t");  
sensor.requestTemperatures();
Serial.println(sensor.getTempCentiC());
Serial.print("Air");
Serial.print("\t"); 
Serial.println(analogRead(A3));
Serial.print("laser");
Serial.print("\t"); 
Serial.println(analogRead(A4));
Serial.print("GUN");
Serial.print("\t");  
Serial.println(analogRead(A5));
   if (analogRead(A5) > 1500  || analogRead(A5) < 800 ){
    digitalWrite(D2,LOW);
    Serial.print("LASEROFF"); 
      Serial.print("GUN"); 
   }
  if (analogRead(A5) < 1500  && analogRead(A5) > 650 ){
   // digitalWrite(D2,HIGH);
     Serial.print("gunok"); 
}
if (analogRead(A4) > 950  || analogRead(A4) < 400 || analogRead(A3) < 350){
    digitalWrite(D2,LOW);
    Serial.print("LASEROFF2"); 
  }
  if (analogRead(A4) < 900  && analogRead(A4) > 100 && analogRead(A3) > 330  && analogRead(A3) < 2100 && analogRead(A5) < 1500  && analogRead(A5) > 650 ){
    digitalWrite(D2,HIGH);
Serial.println("laserONma");
  } 
if (analogRead(A3) > 800   ){
    digitalWrite(D3,LOW);
    Serial.print("PUMPOFF"); 
  
  }
  if (analogRead(A3) < 400)  {
    digitalWrite(D3,HIGH);
    Serial.print("PUMPON");
}
delay(350);
}
// -- END OF FILE --

