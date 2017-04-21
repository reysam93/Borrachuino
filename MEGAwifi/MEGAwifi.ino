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

void setup()
{   Serial.begin(115200);
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
 if (Serial.available()){  
    char c = Serial.read();
    Serial3.print(c);
 }
 
}


   
