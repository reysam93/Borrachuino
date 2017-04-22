///////////////////////////////////////////////////////ORDENES DE ARRANQUE///////////////////////////////////////////////
void SetUpWIFI(){  
String ordenes[]=
   {  //"AT+RST",
      "AT+CWMODE=3",
      //"AT+CWQAP", 
      //"AT"AT+CWLAP",
      "AT+CWJAP=\"AndroidAP\",\"borrachuino123\"",
      //"AT+CIFSR" ,
      "AT",
      "AT+CIPMUX=1",
      "AT+CIPSERVER=1,80",
      "END"          // Para reconocer el fin de los comandos AT
   };

  int index = 0;
  while(ordenes[index] != "END"){  
    Serial3.println(ordenes[index++]);
     while ( true)
        {   String s = GetLineWIFI();
            if ( s!= "") Serial.println(s);
            if ( s.startsWith("no change"))  
                 break;
           if ( s.startsWith("OK"))   
                 break;
           if ( s.startsWith("ready"))  
                 break;
        }
      Serial.println("....................");
    }  
}
String GetLineWIFI()
   {   String S = "" ;
       if (Serial3.available())
          {    char c = Serial3.read(); ;
                while ( c != '\n' )            //Hasta que el caracter sea intro
                  {     S = S + c ;
                        delay(25) ;
                        c = Serial3.read();
                   }
                 return( S ) ;
          }
   }
////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int motorMezcla =  9; // the number of the motor pin
const int motorAlcohol =  10; // the number of the motor pin

void setup(){  
    // initialize the motor pin as an output:
    pinMode(motorMezcla, OUTPUT);
    pinMode(motorAlcohol, OUTPUT); 
    Serial.begin(115200);
    Serial3.begin(115200);
    delay(1500);          // Para darnos tiempo a abrir la consola
    SetUpWIFI() ;         // Envia los comandos AT
}

   
String msg = "";

void loop(){
 char c =' ';
 if (Serial3.available()){
       //Llega del wifi 
       c = Serial3.read() ;
       Serial.print(c);
       msg += c;              // Vamos montando un String con lo que entra
       
       //Si Llega /n es que es una orden de bebida
       if (c == '\n'){
        
          // Ice
          if (msg.indexOf("ice:1") > 0) {
            Serial.println("Con hielo");
          } else if (msg.indexOf("ice:0") > 0) {
            Serial.println("Sin hielo");
          }
        
         // Drink type
         if (msg.indexOf("drink:0") > 0) {
            Serial.println("Chupito");
            digitalWrite(motorAlcohol, HIGH);
            delay(4000); //TIEMPO QUE LOS MOTORES ESTARÁN EN ALTO
            digitalWrite(motorAlcohol, LOW);
            Serial.println("Bebida Lista!");
            
         } else if (msg.indexOf("drink:1") > 0) {
            Serial.println("Corto");
            digitalWrite(motorMezcla, HIGH);
            delay(1000);
            digitalWrite(motorAlcohol, HIGH);
            delay(1000); //TIEMPO QUE LOS MOTORES ESTARÁN EN ALTO
            digitalWrite(motorMezcla, LOW);
            delay(1000);
            digitalWrite(motorAlcohol, LOW);
            delay(1000);
            Serial.println("Bebida Lista!");
            
         } else if (msg.indexOf("drink:2") > 0) {
            Serial.println("Normal");
            digitalWrite(motorMezcla, HIGH);
            digitalWrite(motorAlcohol, HIGH);
            delay(4000); //TIEMPO QUE LOS MOTORES ESTARÁN EN ALTO
            digitalWrite(motorMezcla, LOW);
            digitalWrite(motorAlcohol, LOW);
            Serial.println("Bebida Lista!");
            
         } else if (msg.indexOf("drink:3") > 0) {
            Serial.println("Largo");
            digitalWrite(motorMezcla, HIGH);
            digitalWrite(motorAlcohol, HIGH);
            delay(4000); //TIEMPO QUE LOS MOTORES ESTARÁN EN ALTO
            digitalWrite(motorMezcla, LOW);
            digitalWrite(motorAlcohol, LOW);
            Serial.println("Bebida Lista!");
            
         } else if (msg.indexOf("drink:4") > 0) {
            Serial.println("Solo refresco (vaso fiesta)");
            digitalWrite(motorMezcla, HIGH);
            delay(4000); //TIEMPO QUE LOS MOTORES ESTARÁN EN ALTO
            digitalWrite(motorMezcla, LOW);
            Serial.println("Bebida Lista!");
            
         } else if (msg.indexOf("drink:5") > 0) {
            Serial.println("Vaso de Sidra");
            digitalWrite(motorMezcla, HIGH);
            digitalWrite(motorAlcohol, HIGH);
            delay(4000); //TIEMPO QUE LOS MOTORES ESTARÁN EN ALTO
            digitalWrite(motorMezcla, LOW);
            digitalWrite(motorAlcohol, LOW);
            Serial.println("Bebida Lista!");
            
         } else if (msg.indexOf("drink:6") > 0) {
            Serial.println("Mini");
            digitalWrite(motorMezcla, HIGH);
            digitalWrite(motorAlcohol, HIGH);
            delay(4000); //TIEMPO QUE LOS MOTORES ESTARÁN EN ALTO
            digitalWrite(motorMezcla, LOW);
            digitalWrite(motorAlcohol, LOW);
            Serial.println("Bebida Lista!");
         }
         
        
        c = '.';
        msg = "";
      }
 }
 if (Serial.available()){  
    char c = Serial.read();
    Serial3.print(c);
 }
 
}


   
