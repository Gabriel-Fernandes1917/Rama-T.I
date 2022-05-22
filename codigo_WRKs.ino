#include <SoftwareSerial.h>

SoftwareSerial bluetooth(2,3);

double cal_NTU(double volt);

double NTU = 0.0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  int sensorValue = analogRead(A0);

  float voltage = sensorValue*(5.0/1024.0); // calcular a tensão em V

  NTU = calc_NTU(voltage);

  if(NTU > 0){
     Serial.print(voltage);
     Serial.print(" V | ");
     Serial.print(NTU);
     Serial.println(" NTU");
     bluetooth.print(NTU);
    }
     


  delay(741);

}

// converter tensao em turbidez

double calc_NTU(double volt){
  
  double NTU_val;
  NTU_val = -(1120.4*volt*volt)+(5742.3*volt)-4352.9; // calcular turbidez formula 

    return NTU_val;
  }
