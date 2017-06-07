//https://arduino.stackexchange.com/questions/36516/modbus-rtu-slave-library   
/*
 * //thanks goddland_16
 pin rs 485 
 Tx+ dan Rx+ digabung, ini menjadi pin A
 Tx- dan Rx- digabung, ini menjadi pin B
 GND

 pin A RS485=>  pin A max485  
 pin B RS485=>  pin B max485  

 pin DE dan RE di max 485 digabung dan dhubungkan ke pin 3
 pin DI di max485 ke pin 11 arduino (TX)
 pin R0 di max485 ke pin 10 arduino (RX)

 GND modbus dan arduino tersambung
  */  
    #include <SoftwareSerial.h>
    #define rxPin 10
    #define txPin 11

    #define RS485_pin 3
    SoftwareSerial mySerial(rxPin, txPin);
    //#define mySerial Serial1

    // sesuaikan kebutuhan
    byte test_data[8] = {0x02,0x03,0x00,0x00,0x00,0x15,0x84,0x36};

    int data_count = 5;
    byte rcvdata[15];
    int param_value_int[7];

    void setup() {
      // put your setup code here, to run once:
    //mySerial.begin(19200,SERIAL_8E1);
    mySerial.begin(9600);
    Serial.begin(9600);
    delay(1000);
    pinMode(RS485_pin, OUTPUT);
    digitalWrite(RS485_pin,LOW);
    delay(100);
    Serial.println("program from stack exchange");
    }
    int count = 0; 
    
    void loop() {

      if(count%10 == 0) {
        Serial.println();
        send_data();
      }

      count++;
      while(mySerial.available()>0)
      {
        byte b=mySerial.read();
        delay(1);
        Serial.print(b,HEX);
        Serial.print(" ");
        //Serial.print("myserial");
      }
      //Serial.println(count);
      /*while(Serial.available())
      {
        digitalWrite(RS485_pin,HIGH);
        byte a=Serial.read();
        delay(1);
        mySerial.print(a);
        digitalWrite(RS485_pin,LOW);
       // Serial.print(a);
       // Serial.print("Serial");
      }*/


      delay(1000);
      //while(1);
    }

    void send_data() {
      Serial.println("send data");

      digitalWrite(RS485_pin,HIGH);
      delay(1);
      for(char i=0;i<8;i++){
        mySerial.write(test_data[i]);
        delay(1);
        Serial.print(test_data[i],HEX);
        Serial.print(" ");
      }

      Serial.println();
      digitalWrite(RS485_pin,LOW);
      delay(1);
    }
