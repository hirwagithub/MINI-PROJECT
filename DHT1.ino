  #include <SoftwareSerial.h> 
#include "DHT.h"
 
#define DHTPIN 12 
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
 
char inchar; 
 
SoftwareSerial SIM900(8, 7); 
 
String TextForSms ;
String humidity = " Humidity: %";
String temperature = "   Temperature";
String sign = " *C";
 
 
void setup() {
 
   Serial.begin(9600);
  SIM900.begin(9600); 
   dht.begin();

 delay(5000); 
randomSeed(analogRead(0));
 
  SIM900.print("AT+CMGF=1\r"); 
  delay(1000);
  SIM900.print("AT+CNMI=2,2,0,0,0\r"); 
  
  delay(1000);
     SIM900.println("AT+CMGD=1,4");
   delay(5000);
  Serial.println("Ready...");
  
}
 
 
 
 
void sendSMS(String message)
{
  SIM900.println("AT+CMGF=1\r");                
  delay(1000);
 SIM900.println("AT+CMGS = \"+250786789381\"");  
 
  delay(1000);
  SIM900.println(message);                      
  delay(1000);
  SIM900.println((char)26);                       
  delay(1000); 
  SIM900.println();
  delay(1000);                                    
                                  
}
void loop() {
 
if(SIM900.available() == 0)
{
 
  delay(2000);
 
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  int f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  int hi = dht.computeHeatIndex(f, h);
 
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
 Serial.print("Temperature: "); 
Serial.print(t);
 Serial.print(" *C ");
  
  TextForSms = TextForSms + "Humidity: ";
  TextForSms.concat(h);
  TextForSms = TextForSms + "%    Temperature: ";
  TextForSms.concat(t);
  TextForSms = TextForSms + "*C";
  Serial.println(TextForSms);
  delay(2000);
  TextForSms = " ";
  
   if ( t > 35)
   {
   Serial.println("Temperature Exceeded"); 
TextForSms = " Temperature Exceeded";
 sendSMS(TextForSms);
 delay(5000); 
 TextForSms = ""; 
   }
  
}
  if(SIM900.available() >0)
  {
 
    inchar=SIM900.read(); 
  Serial.println(inchar);
    delay(20);
    if (inchar=='v')
    {
      delay(10);
 
   Serial.println(inchar);
  delay(2000);
  int h = dht.readHumidity();
  // Read temperature as Celsius
  int t = dht.readTemperature();
  // Read temperature as Fahrenheit
  int f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
  int hi = dht.computeHeatIndex(f, h);
 
 Serial.print("Humidity: "); 
 Serial.print(h);
 Serial.print(" %\t");
 Serial.print("Temperature: "); 
  Serial.print(t);
 Serial.print(" *C ");
  
  TextForSms = TextForSms + "HUMIDITY: ";
  TextForSms.concat(h);
  TextForSms = TextForSms + "%    TEMPERATURE: ";
  TextForSms.concat(t);
  TextForSms = TextForSms + "*C";
   sendSMS(TextForSms);
  Serial.println(TextForSms);
  delay(2000);
  TextForSms = " ";
    }
 
}
 
 
}
