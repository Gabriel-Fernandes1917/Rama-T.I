
#include <ESP8266WiFi.h>
 
String apiKey = "YFS22E2ONFCKD0QV";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  ".";     // replace with your wifi ssid and wpa2 key
const char *pass =  "LULA2018";
const char* server = "api.thingspeak.com";
 
   float NTU_val;
   int volt;

  double calc_NTU(){
   volt = analogRead(A0)*(3.3/ 978); // calcular turbidez formula 
   NTU_val = (-(1120.4*volt*volt)+(5742.3*volt))-4352.9; // calcular turbidez formula 
//    Serial.println(A0);
    return NTU_val;
  }
 
WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
       delay(10);

 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{
  
      float turbidez =  calc_NTU();
    
      
              if (isnan(turbidez) )
                 {
                     Serial.println("Failed to read turbidez sensor!");
                      return;
                 }
 
                         if (client.connect(server, 80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(turbidez);  
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("turbidez: ");
                             Serial.print(turbidez);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
