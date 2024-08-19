/* The source Code from : https://github.com/riyadhasan24
 * By Md. Riyad Hasan
 */

// I Used Only Atmega328p Microcontroler for this project......

/*
 * I used "25 in 1 small TV Remote / 50J2 Remote"
 */

#include <EEPROM.h>
#include <IRremote.h>
#include <TimerOne.h>

//     Arduino Pin... IC Pin.... Light & Fan
#define Light_1  10   // 16
#define Light_2  11   // 17
#define Light_3  12   // 18
#define Light_4  13   // 19
#define Traic_Pin 8   // 14

//     Arduino Pin... IC Pin.... For seven-segment...
#define Pin_A A3       // 26
#define Pin_B A2       // 25
#define Pin_C 3        //  5
#define Pin_D A0       // 23
#define Pin_E A1       // 24
#define Pin_F A4       // 27
#define Pin_G A5       // 28

int State_1 = LOW;
int State_2 = LOW;
int State_3 = LOW;
int State_4 = LOW;

byte Valu_1;
byte Valu_2;
byte Valu_3;
byte Valu_4;


int Receive_PIN = 4;            // IC Pin 6
IRrecv IR_Receive(Receive_PIN);
decode_results Results;

int Dim = 0;
int Dim_Value;  
int Freq_Step = 75;                         // This Freq_Step for 50Hz AC Power
volatile int ZC = 0;
volatile boolean Zero_Cross = 0;

void setup()
{
  IR_Receive.enableIRIn();

  pinMode(Light_1, OUTPUT);
  pinMode(Light_2, OUTPUT);
  pinMode(Light_3, OUTPUT);
  pinMode(Light_4, OUTPUT);
  pinMode(Traic_Pin, OUTPUT);

  pinMode(Pin_A, OUTPUT);
  pinMode(Pin_B, OUTPUT);
  pinMode(Pin_C, OUTPUT);
  pinMode(Pin_D, OUTPUT);
  pinMode(Pin_E, OUTPUT);
  pinMode(Pin_F, OUTPUT);
  pinMode(Pin_G, OUTPUT);

  Timer1.initialize(Freq_Step);
  Timer1.attachInterrupt(Dim_Check, Freq_Step);
  
  attachInterrupt(0, Zero_Cross_Detect, RISING);
}

void Zero_Cross_Detect()
{
  Zero_Cross = true;
  ZC = 0;
  digitalWrite(Traic_Pin, LOW);
}

void Dim_Check()
{
  if(Zero_Cross == true)
  {
    if(ZC >= Dim)
    {
      digitalWrite(Traic_Pin, HIGH);
      ZC = 0;
      Zero_Cross = false;
    }
    else
    {
      ZC++;
    }
  }
}


void loop()
{
  if(IR_Receive.decode(&Results)) 
    {    
        IR_Receive.resume();

        // This is Light Section......
        // Light 1
        if(Results.value == 0x38863BF2)
          {
            digitalWrite(Light_1, State_1);
            EEPROM.write(1, State_1);
            State_1 = !State_1; 
          }
        
        // Light 2
        if(Results.value == 0x38863BC2)  
          {
            digitalWrite(Light_2, State_2);
            EEPROM.write(2, State_2);
            State_2 = !State_2; 
          }

        // Light 3
        if(Results.value == 0x38863BFA)  
          {
            digitalWrite(Light_3, State_3);
            EEPROM.write(3, State_3);
            State_3 = !State_3; 
          }

        // Light 4
        if(Results.value == 0x38863BCA)  
          {
            digitalWrite(Light_4, State_4);
            EEPROM.write(4, State_4);
            State_4 = !State_4; 
          }


        // This is Light Section......
        // Remote Button 0      || Fan Off
        if(Results.value == 0x38863BC0)
          {
            Dim = 128;
            Digit_Zero();
            EEPROM.write(0, Dim);
          }

        // Remote Button 1
        if(Results.value == 0x38863BE0)  
          {
            Dim = 110;
            Digit_One();
            EEPROM.write(0, Dim);
          }

        // Remote Button 2
        if(Results.value == 0x38863BD0)
          {
            Dim = 95;
            Digit_Two();
            EEPROM.write(0, Dim);
          }
        // Remote Button 3
        if(Results.value == 0x38863BF0)
          {
            Dim = 81;
            Digit_Three();
            EEPROM.write(0, Dim);
          }

        // Remote Button 4
        if(Results.value == 0x38863BC8)
          {
            Dim = 67;
            Digit_Four();
            EEPROM.write(0, Dim);
          }

        // Remote Button 5
        if(Results.value == 0x38863BE8)
          {
            Dim = 53;
            Digit_Five();
            EEPROM.write(0, Dim);
          }

        // Remote Button 6
        if(Results.value == 0x38863BD8)
          {
            Dim = 39;
            Digit_Six();
            EEPROM.write(0, Dim);
          }

        // Remote Button 7
        if(Results.value == 0x38863BF8)
          {
            Dim = 28;
            Digit_Seven();
            EEPROM.write(0, Dim);
          }// Remote Button 4

        // Remote Button 8
        if(Results.value == 0x38863BC4)
          {
            Dim = 14;
            Digit_Eight();
            EEPROM.write(0, Dim);
          }

        // Remote Button 9      || Fan Full-Speed
        if(Results.value == 0x38863BE4)
          {
            Dim = 0;
            Digit_Nine();
            EEPROM.write(0, Dim);
          }  
    }
        else
            {
              // This is Light Section......
              Valu_1 = EEPROM.read(1);
              digitalWrite(Light_1, Valu_1);

              Valu_2 = EEPROM.read(2);
              digitalWrite(Light_2, Valu_2);

              Valu_3 = EEPROM.read(3);
              digitalWrite(Light_3, Valu_3);

              Valu_4 = EEPROM.read(4);
              digitalWrite(Light_4, Valu_4);

              // This is Fan Section......
              Dim_Value = EEPROM.read(0);
              Dim = Dim_Value;

              // Remote Button 0      || Fan Off
              if (Dim == 128)
                {
                  Digit_Zero();
                }

              // Remote Button 1
              if (Dim == 110)
                {
                  Digit_One();
                }

              // Remote Button 2
              if (Dim == 95)
                {
                  Digit_Two();
                }

              // Remote Button 3
              if (Dim == 81)
                {
                  Digit_Three();
                }

              // Remote Button 4
              if (Dim == 67)
                {
                  Digit_Four();
                }

              // Remote Button 5
              if (Dim == 53)
                {
                  Digit_Five();
                }

              // Remote Button 6
              if (Dim == 39)
                {
                  Digit_Six();
                }

              // Remote Button 7
              if (Dim == 28)
                {
                  Digit_Seven();
                }

              // Remote Button 8
              if (Dim == 14)
                {
                  Digit_Eight();
                }

              // Remote Button 9
              if (Dim == 0)
                {
                  Digit_Nine();
                }
            }
}

void Digit_Zero()
{
  digitalWrite(Pin_A, HIGH);
  digitalWrite(Pin_B, HIGH);
  digitalWrite(Pin_C, HIGH);
  digitalWrite(Pin_D, HIGH);
  digitalWrite(Pin_E, HIGH);
  digitalWrite(Pin_F, HIGH);
  digitalWrite(Pin_G, LOW);
}

void Digit_One()
{
  digitalWrite(Pin_A, LOW);
  digitalWrite(Pin_B, HIGH);
  digitalWrite(Pin_C, HIGH);
  digitalWrite(Pin_D, LOW);
  digitalWrite(Pin_E, LOW);
  digitalWrite(Pin_F, LOW);
  digitalWrite(Pin_G, LOW);
}

void Digit_Two()
{
  digitalWrite(Pin_A, HIGH);
  digitalWrite(Pin_B, HIGH);
  digitalWrite(Pin_C, LOW);
  digitalWrite(Pin_D, HIGH);
  digitalWrite(Pin_E, HIGH);
  digitalWrite(Pin_F, LOW);
  digitalWrite(Pin_G, HIGH);
}

void Digit_Three()
{
  digitalWrite(Pin_A, HIGH);
  digitalWrite(Pin_B, HIGH);
  digitalWrite(Pin_C, HIGH);
  digitalWrite(Pin_D, HIGH);
  digitalWrite(Pin_E, LOW);
  digitalWrite(Pin_F, LOW);
  digitalWrite(Pin_G, HIGH);
}

void Digit_Four()
{
  digitalWrite(Pin_A, LOW);
  digitalWrite(Pin_B, HIGH);
  digitalWrite(Pin_C, HIGH);
  digitalWrite(Pin_D, LOW);
  digitalWrite(Pin_E, LOW);
  digitalWrite(Pin_F, HIGH);
  digitalWrite(Pin_G, HIGH);
}

void Digit_Five()
{
  digitalWrite(Pin_A, HIGH);
  digitalWrite(Pin_B, LOW);
  digitalWrite(Pin_C, HIGH);
  digitalWrite(Pin_D, HIGH);
  digitalWrite(Pin_E, LOW);
  digitalWrite(Pin_F, HIGH);
  digitalWrite(Pin_G, HIGH);
}

void Digit_Six()
{
  digitalWrite(Pin_A, HIGH);
  digitalWrite(Pin_B, LOW);
  digitalWrite(Pin_C, HIGH);
  digitalWrite(Pin_D, HIGH);
  digitalWrite(Pin_E, HIGH);
  digitalWrite(Pin_F, HIGH);
  digitalWrite(Pin_G, HIGH);
}

void Digit_Seven()
{
  digitalWrite(Pin_A, HIGH);
  digitalWrite(Pin_B, HIGH);
  digitalWrite(Pin_C, HIGH);
  digitalWrite(Pin_D, LOW);
  digitalWrite(Pin_E, LOW);
  digitalWrite(Pin_F, LOW);
  digitalWrite(Pin_G, LOW);
}

void Digit_Eight()
{
  digitalWrite(Pin_A, HIGH);
  digitalWrite(Pin_B, HIGH);
  digitalWrite(Pin_C, HIGH);
  digitalWrite(Pin_D, HIGH);
  digitalWrite(Pin_E, HIGH);
  digitalWrite(Pin_F, HIGH);
  digitalWrite(Pin_G, HIGH);
}

void Digit_Nine()
{
  digitalWrite(Pin_A, HIGH);
  digitalWrite(Pin_B, HIGH);
  digitalWrite(Pin_C, HIGH);
  digitalWrite(Pin_D, HIGH);
  digitalWrite(Pin_E, LOW);
  digitalWrite(Pin_F, HIGH);
  digitalWrite(Pin_G, HIGH);
}
