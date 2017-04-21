#include <SoftwareSerial.h>
SoftwareSerial WIFI1(3, 2); // RX | TX
// IP: 192.168.43.233

String msg = "";
char c;

String ordenes[]=
  {  
     "AT+CWMODE=3",
     "AT+CWJAP=\"AndroidAp\",\"ulfp7699\"",
     "AT+CIPMUX=1",
     "AT+CIPSERVER=1,80",
     "END"                 // Para reconocer el fin de los comandos AT
  };


void setup()
  {  
     Serial.begin(115200);
     WIFI1.begin(115200);
  }

void loop() {  
    // separados ppor fin de linea??  String data.concat
    // enviar los dos numeros seguidos
     if (WIFI1.available()) { 
          c =  WIFI1.read() ;
          Serial.print(c);
          msg += c;
     }
     if (Serial.available()) {  
         char s = Serial.read();
          WIFI1.print(s);
     }   
     if (c == '\n'){
       // Drink type
       if (msg.indexOf("drink:0") > 0) {
          Serial.println("Chupito");
       } else if (msg.indexOf("drink:1") > 0) {
          Serial.println("Corto");
       } else if (msg.indexOf("drink:2") > 0) {
          Serial.println("Normal");
       } else if (msg.indexOf("drink:3") > 0) {
          Serial.println("Largo");
       }
       
       // Ice
      if (msg.indexOf("ice:1") > 0) {
        Serial.println("Con hielo");
      } else if (msg.indexOf("ice:0") > 0) {
        Serial.println("Sin hielo");
      }
    
      c = '.';
      msg = "";
    }   
}
