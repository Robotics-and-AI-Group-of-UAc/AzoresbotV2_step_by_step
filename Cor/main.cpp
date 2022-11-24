#include <Arduino.h>

// Pinos Sensor de cor
#define SENSOR_COR_S0 19
#define SENSOR_COR_S1 21
#define SENSOR_COR_S2 4
#define SENSOR_COR_S3 16
#define SENSOR_COR_OUT 5
int data;

void GetData(){
   data=pulseIn(SENSOR_COR_OUT,LOW);       
   Serial.print(data);          
   Serial.print("\t");         
   delay(20);
}

void setup()
{
  pinMode(SENSOR_COR_OUT, INPUT);
  pinMode(SENSOR_COR_S2, OUTPUT);
  pinMode(SENSOR_COR_S3, OUTPUT);
  pinMode(SENSOR_COR_S0, OUTPUT);
  pinMode(SENSOR_COR_S1, OUTPUT);
   // Na função serial o baudrate funciona melhor em 115200
  // Para isso necessitamos alterar o ficheiro platformio.ini
  // Acrescentando a seguinte linha:
  // monitor_speed = 115200 
  Serial.begin(115200);
  
}

void loop()
{
 
   digitalWrite(SENSOR_COR_S2,LOW);        
   digitalWrite(SENSOR_COR_S3,LOW);
   Serial.print("Red value= "); 
   GetData();                   

   digitalWrite(SENSOR_COR_S2,LOW);
   digitalWrite(SENSOR_COR_S3,HIGH);
   Serial.print("Blue value= ");
   GetData();

   digitalWrite(SENSOR_COR_S2,HIGH);
   digitalWrite(SENSOR_COR_S3,HIGH);
   Serial.print("Green value= ");
   GetData();

   Serial.println();

   delay(2000);

}
