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




// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(42, 41, 25, 24, 23, 22);

const int motorMezcla =  9; // the number of the motor pin
const int motorAlcohol =  10; // the number of the motor pin

//////////////////////////////////Metodo pintar en la pantalla////////////////////////////////////////////

void loadLCDDrink(int tiempo, String tipo){
    lcd.display();
    lcd.clear();
    String foo = "";
    String am = "Echando " + tipo;
    lcd.print(am);
    lcd.setCursor(0,1);
    for(int x = 0; x < tiempo; x = x + tiempo/16){
      foo = foo + "X";
      lcd.print("X");
      delay(tiempo/16);
    }
    lcd.clear();
    lcd.setCursor(0,0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup(){  
    // initialize the motor pin as an output:
    lcd.begin(16, 2);
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
            //120 segundos el chupito
            int y = 0;
            while(true){
              loadLCDDrink(10000, "alcohol");
              y = y + 10;
              if(y==120){
                break;
              }
            }
            lcd.clear();
            lcd.print("Chupito listo!");
            digitalWrite(motorAlcohol, LOW);
            Serial.println("Bebida Lista!");
            
         } else if (msg.indexOf("drink:1") > 0) {
            Serial.println("Corto");
            
            digitalWrite(motorAlcohol, HIGH);
            //80 segundos de alcochol para el corto
            int y = 0;
            while(true){
              loadLCDDrink(10000, "alcohol");
              y = y + 10;
              if(y==20){
                break;
              }
            }
            lcd.clear();
            digitalWrite(motorAlcohol, LOW);

            
            digitalWrite(motorMezcla, HIGH);
            //280 segundos de mezcla para el corto
            int z = 0;
            while(true){
              Serial.println(z);
              loadLCDDrink(10000, "mezcla");
              z = z + 10;
              if(z==280){
                break;
              }
            }
            digitalWrite(motorMezcla, LOW);

            
            lcd.clear();
            lcd.print("Corto listo!");
            Serial.println("Bebida Lista!");
            
         } else if (msg.indexOf("drink:2") > 0) {
            Serial.println("Normal");
                        digitalWrite(motorAlcohol, HIGH);
            //120 segundos de alcochol para el medio
            int y = 0;
            while(true){
 
              loadLCDDrink(10000, "alcohol");
              y = y + 10;
              if(y==120){
                break;
              }
            }
            lcd.clear();
            digitalWrite(motorAlcohol, LOW);

            
            digitalWrite(motorMezcla, HIGH);
            //240 segundos de mezcla para el medio
            int z = 0;
            while(true){
              loadLCDDrink(10000, "mezcla");
              z = z + 10;
              if(z==240){
                break;
              }
            }
            digitalWrite(motorMezcla, LOW);

            
            lcd.clear();
            lcd.print("Normal listo!");
            Serial.println("Bebida Lista!");
            
         } else if (msg.indexOf("drink:3") > 0) {
            Serial.println("Largo");
            digitalWrite(motorAlcohol, HIGH);
            //240 segundos de alcochol para el largo
            int y = 0;
            while(true){
              loadLCDDrink(10000, "alcohol");
              y = y + 10;
              if(y==240){
                break;
              }
            }
            lcd.clear();
            digitalWrite(motorAlcohol, LOW);

            
            digitalWrite(motorMezcla, HIGH);
            //120 segundos de mezcla para el largo
            int z = 0;
            while(true){
              loadLCDDrink(10000, "mezcla");
              z = z + 10;
              if(z==120){
                break;
              }
            }
            digitalWrite(motorMezcla, LOW);

            
            lcd.clear();
            lcd.print("Largo listo!");
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


   
