// Toll pass Access Project
#include<Servo.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd1(0x3F,16,2);
LiquidCrystal_I2C lcd2(0x27,16,2);

int Ir_1=3;
int Ir_2=4;

int Button_1=5;
int Button_2=6;

String RFIDCard_1 = "53009332C436"; //  Replace with your RFID card number
String RFIDCard_2 = "2100884CE80D"; //  Replace with your RFID card number

int Accountbalance  =1000;
int car=300;
int bus=200;

int count=0;
Servo myservo1;
Servo myservo2;

void setup(){
  Serial.begin(9600);

  myservo1.attach(9);
  myservo2.attach(10);
  myservo1.write(90);
  myservo2.write(0);

  pinMode(Ir_1,INPUT);
  pinMode(Ir_2,INPUT);
  pinMode(Button_1,INPUT);
  pinMode(Button_2,INPUT);
  
  lcd2.init();
  lcd1.init();
  lcd2.backlight();
  lcd1.backlight();
  lcd1.setCursor(0,0);
  lcd2.setCursor(0,0);
  lcd1.print ("RFID Toll Gate");
  lcd2.print ("RFID Toll Gate");
  lcd1.setCursor(0,1);
  lcd2.setCursor(0,1);
  lcd1.print("Access System");
  lcd2.print("Access System");
  delay(3000);
  lcd1.clear();
  lcd2.clear();

}
 void loop(){
  int Ir_1Value=digitalRead(Ir_1);
  int Ir_2Value=digitalRead(Ir_2);
  int button_1Value=digitalRead(Button_1);
  int button_2Value=digitalRead(Button_2);
  
  int ir1=Ir_1Value;
  int ir2=Ir_2Value;
  
  if(Ir_1Value==0){
    myservo1.write(0);
    lcd1.setCursor(0,0);
    lcd1.print("car entered");
    lcd1.setCursor(0,1);
    lcd1.print("Gate closed");
    delay(1000);
    lcd1.clear();
  }
  if(Ir_2Value==0){
    myservo2.write(90);
    lcd2.setCursor(0,0);
    lcd2.print("car entered");
    lcd2.setCursor(0,1);
    lcd2.print("Gate closed");
    delay(1000);
    lcd2.clear();
  }
   if(button_1Value==0){
            Serial.println("but value1: " +String(button_1Value));
            lcd1.clear();
            delay(1000);
            lcd1.setCursor(0,0);
            lcd1.print("Amount received");
            lcd1.setCursor(0,1);
            lcd1.print("Gate open");
            myservo1.write(90);
          }
         
  if(button_2Value==0){
            Serial.println("but value2: " +String(button_2Value));
            lcd2.clear();
            delay(1000);
            lcd2.setCursor(0,0);
            lcd2.print("Amount received");
            lcd2.setCursor(0,1);
            lcd2.print("Gate open");
            myservo2.write(0);
        }
          
  if (Serial.available() > 0) {
    String rfidData = Serial.readStringUntil('\n'); // Read the RFID data

     if((rfidData == RFIDCard_1) && (ir1==1)) {                 // card 1
       Serial.println("Scanned RFID card: " + rfidData); 
        lcd1.setCursor(0,0);
        lcd1.print("card valid");
        lcd1.setCursor(0,1);
        lcd1.print("Ac\B: ");
        lcd1.print(Accountbalance);      
        delay(2000);
        lcd1.clear();

       if (Accountbalance >= car) {
        Accountbalance -= car;
        Serial.print("Toll paid. Remaining balance: $");
        Serial.println(Accountbalance);
        lcd1.setCursor(0,0);
        lcd1.print("Toll Amount paid");
        lcd1.setCursor(0,1);
        lcd1.print("Ac\B: $");
        lcd1.print(Accountbalance);
        delay(2000);
        lcd1.clear();
        lcd1.setCursor(0,0);
        lcd1.print("Gate open");
        myservo1.write(90);

       }else if(Accountbalance < car) {
        Serial.println("Insufficient balance.");
         myservo1.write(0);
          lcd1.clear();
          lcd1.setCursor(0,0);
          lcd1.print("balance low");
          lcd1.setCursor(0,1);
          lcd1.print("Ac\B: ");
          lcd1.print(Accountbalance);
          delay(3000);// adjust delay value    
          lcd1.clear();
          delay(1000);
          lcd1.setCursor(0,0);
          lcd1.print("Pay Your Amount");    
        }
      }
     else if((rfidData == RFIDCard_2) && (ir2==1)) {               // card 2
       Serial.println("Scanned RFID card: " +rfidData); 
        lcd2.setCursor(0,0);
        lcd2.print("card valid");
        lcd2.setCursor(0,1);
        lcd2.print("Ac\B: ");
        lcd2.print(Accountbalance);
        delay(2000);
        lcd2.clear();

      if (Accountbalance >= bus) {
        Accountbalance -= bus;
        Serial.print("Toll paid. Remaining balance: $");
        Serial.println(Accountbalance);
        lcd2.setCursor(0,0);
        lcd2.print("Toll Amount paid");
        lcd2.setCursor(0,1);
        lcd2.print("Ac\B: $");
        lcd2.print(Accountbalance);
        delay(2000);
        lcd2.clear();
        lcd2.setCursor(0,0);
        lcd2.print("Gate open");
        myservo2.write(0);

       }else if(Accountbalance < bus) {
        Serial.println("Insufficient balance.");
         myservo2.write(90);
          lcd2.clear();
          lcd2.setCursor(0,0);
          lcd2.print("balance low");
          lcd2.setCursor(0,1);
          lcd2.print("Ac\B: ");
          lcd2.print(Accountbalance);
          delay(3000); // adjust delay value
           lcd2.clear();
           delay(1000);
           lcd2.setCursor(0,0);
           lcd2.print("Pay Your Amount"); 
        }
     }
      else{                                              // commen else
        if(rfidData != RFIDCard_1){
        Serial.println("invalid card");
            myservo1.write(0);
            lcd1.clear();
            lcd1.setCursor(0,0);
            lcd1.print("card invalid");
            delay(3000);     
            myservo1.write(0);
            lcd1.clear();
            delay(1000);
            lcd1.setCursor(0,0);
            lcd1.print("Card invaild");
            lcd1.setCursor(0,1);
            lcd1.print("Pay Your Amount");
          }

        if( rfidData !=RFIDCard_2){
        Serial.println("invalid card");
            myservo2.write(90);
            lcd2.clear();
            lcd2.setCursor(0,0);
            lcd2.print("card invalid");
            delay(3000);
            myservo2.write(90);
            lcd2.clear();
            delay(1000);
            lcd2.setCursor(0,0);
            lcd2.print("Card invaild");
            lcd2.setCursor(0,1);
            lcd2.print("Pay Your Amount");
           }
        }      
   }
 }

  
 
