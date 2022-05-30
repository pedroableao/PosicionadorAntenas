
/*
   Modified by Navaneeth Krishnan, For Elementz Engineers Guild Pvt Ltd
*/
#include <SPI.h>
#include "epd2in9.h"
#include "epdpaint.h"
#include "imagedata.h"

#define COLORED     1
#define UNCOLORED   0

int k = 0;


// defines pins numbers

const int stepPin = 2;

const int dirPin  = 3;

const int enPin  = 4;

// Button

const int b1 = A0; // se for alto, ativa modo automatico. se for baixo, ativa modo manual
const int b2 = A1; // botao de start do modo automatico
const int b3 = A2; // botao de reset do modo automatico
const int b4 = A3; // Incrementa 1 grau
const int b5 = A4; // Decrementa 1 grau
const int b6 = A5; // Incrementa 5 grau
const int b7 = 12; // Decrementa 5 grau
const int b8 = 5; // Incrementa 45 grau
const int b9 = 6; // Decrementa 45 grau


int currentAngle = 0;
int angle = 0;
int auxangle = 0;
float stepPerAngle = 0.009; // full step = 1.8
int   numstep;
float temp1 = 0;
float temp2 = 0;
float temp3 = 0;




int x = 5;
unsigned long y = 0;
//String myString;
unsigned char image[1024];//[1024];
Paint paint(image, 0, 0);
Epd epd;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);

  digitalWrite(enPin, LOW);
  digitalWrite(dirPin, HIGH);

  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  pinMode(b5, INPUT);
  pinMode(b6, INPUT);
  pinMode(b7, INPUT);
  pinMode(b8, INPUT);
  pinMode(b9, INPUT);




  if (epd.Init(lut_full_update) != 0) {
    Serial.print("e-Paper init failed");
    return;
  }
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();

  //epd.SetFrameMemory(IMAGE_DATA);
  //epd.DisplayFrame();
  //epd.SetFrameMemory(IMAGE_DATA);
  //epd.DisplayFrame();


  paint.SetRotate(ROTATE_90);
  paint.SetWidth(20);
  paint.SetHeight(250);

  paint.Clear(COLORED);
  paint.DrawStringAt(0, 0, "POSICIONADOR DE ANTENAS", &Font16, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 75, 20, paint.GetWidth(), paint.GetHeight()); //75 e 250
  epd.DisplayFrame();


}
void loop() {


  int n;

  int xx = 0;
  Serial.println(xx);

  if (digitalRead(b1) == HIGH ) {


    if (digitalRead(b3) == HIGH) { //melhorar a volta para o zero
      angle = 0;
      auxangle = 0;


      String stringOne = "Automatico - Angulo:" +  String(auxangle);
      char Bolinha[50];
      stringOne.toCharArray(Bolinha, 50);

      paint.SetRotate(ROTATE_90);
      paint.SetWidth(20);
      paint.SetHeight(300);

      paint.Clear(COLORED);
      paint.DrawStringAt(0, 0, Bolinha, &Font16, UNCOLORED);
      epd.SetFrameMemory(paint.GetImage(), 40, 15, paint.GetWidth(), paint.GetHeight()); //75 e 250
      epd.DisplayFrame();
      
      digitalWrite(dirPin, LOW);
      n = angle + currentAngle;
      numstep = n / stepPerAngle;
      for (int x = 0; x < numstep; x++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000);

      }

    }


    if ( digitalRead(b2) == HIGH ) {

      xx = 1;
      Serial.println(xx);
      temp1 = millis();
              String stringOne = "Automatico - Angulo:" +  String(auxangle);
        char Bolinha[50];
        stringOne.toCharArray(Bolinha, 50);


        paint.SetRotate(ROTATE_90);
        paint.SetWidth(20);
        paint.SetHeight(300);

        if (k == 0) {
          epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
          epd.DisplayFrame();
          epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
          epd.DisplayFrame();

          k = k + 1;
        }
        paint.Clear(COLORED);
        paint.DrawStringAt(0, 0, Bolinha, &Font16, UNCOLORED);
        epd.SetFrameMemory(paint.GetImage(), 40, 15, paint.GetWidth(), paint.GetHeight()); //75 e 250
        epd.DisplayFrame();
        
      delay(14000); //tempo para print na posição zero     
      temp2 = millis();
      temp3 = temp2 - temp1;
      Serial.println(temp3);


      for (int y = 0; y < 359; y++) {   // o for vai até 359 porque a primeira iteração é no angulo 1.
        temp1 = millis();



        if (digitalRead(b3) == HIGH) { //melhorar a volta para o zero
          angle = 0;
          auxangle = 0;


      String stringOne = "Automatico - Angulo:" +  String(auxangle);
      char Bolinha[50];
      stringOne.toCharArray(Bolinha, 50);

      paint.SetRotate(ROTATE_90);
      paint.SetWidth(20);
      paint.SetHeight(300);

      paint.Clear(COLORED);
      paint.DrawStringAt(0, 0, Bolinha, &Font16, UNCOLORED);
      epd.SetFrameMemory(paint.GetImage(), 40, 15, paint.GetWidth(), paint.GetHeight()); //75 e 250
      epd.DisplayFrame();
          
          digitalWrite(dirPin, LOW);
          n = angle + currentAngle;
          numstep = n / stepPerAngle;
          for (int x = 0; x < numstep; x++) {
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(1000);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(1000);
            y = 358;

          }

          currentAngle = angle;

        } else {
          angle = angle + 1;
          digitalWrite(dirPin, HIGH);
          n = angle - currentAngle;
          numstep = n / stepPerAngle;
          auxangle = auxangle + 1;
          for (int x = 0; x < numstep; x++) {
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(1000);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(1000);

          }

          currentAngle = angle;
        }



        if (auxangle >= 360) {
          auxangle = auxangle - 360;
        }
        if (auxangle < 0) {
          auxangle = (360) + auxangle;
        }
        if (auxangle == 0) {
          auxangle = 0;

        }

        String stringOne = "Automatico - Angulo:" +  String(auxangle);
        char Bolinha[50];
        stringOne.toCharArray(Bolinha, 50);


        paint.SetRotate(ROTATE_90);
        paint.SetWidth(20);
        paint.SetHeight(300);

        if (k == 0) {
          epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
          epd.DisplayFrame();
          epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
          epd.DisplayFrame();

          k = k + 1;
        }
        paint.Clear(COLORED);
        paint.DrawStringAt(0, 0, Bolinha, &Font16, UNCOLORED);
        epd.SetFrameMemory(paint.GetImage(), 40, 15, paint.GetWidth(), paint.GetHeight()); //75 e 250
        epd.DisplayFrame();

        delay(12500);
        temp2 = millis();
        temp3 = temp2 - temp1;
        Serial.println(temp3);
      }
    }
  }


  else if (digitalRead(b1) == LOW ) {



    if (digitalRead(b4) == HIGH) {

      angle = angle + 1;
      auxangle = auxangle + 1;
      if (auxangle >= 360) {

        auxangle = auxangle - 360;
      }
      if (auxangle < 0) {
        auxangle = (360) + auxangle;
      }
      if (auxangle == 0) {
        auxangle = 0;
      }
      String stringOne = "Manual - Angulo:" +  String(auxangle);
      char Bolinha[50];
      stringOne.toCharArray(Bolinha, 50);

      if (k == 0) {
        epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
        epd.DisplayFrame();
        epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
        epd.DisplayFrame();
        k = k + 1;
      }
      paint.SetRotate(ROTATE_90);
      paint.SetWidth(20);
      paint.SetHeight(300);

      paint.Clear(COLORED);
      paint.DrawStringAt(0, 0, Bolinha, &Font16, UNCOLORED);
      epd.SetFrameMemory(paint.GetImage(), 40, 15, paint.GetWidth(), paint.GetHeight()); //75 e 250
      epd.DisplayFrame();

    }

    else if ( digitalRead(b5) == HIGH) {

      angle = angle - 1;
      auxangle = auxangle - 1;
      if (auxangle >= 360) {

        auxangle = auxangle - 360;
      }
      if (auxangle < 0) {
        auxangle = (360) + auxangle;
      }
      if (auxangle == 0) {
        auxangle = 0;
      }
      String stringOne = "Manual - Angulo:" +  String(auxangle);
      char Bolinha[50];
      stringOne.toCharArray(Bolinha, 50);
      if (k == 0) {
        epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
        epd.DisplayFrame();
        epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
        epd.DisplayFrame();

        k = k + 1;
      }
      paint.SetRotate(ROTATE_90);
      paint.SetWidth(20);
      paint.SetHeight(300);

      paint.Clear(COLORED);
      paint.DrawStringAt(0, 0, Bolinha, &Font16, UNCOLORED);
      epd.SetFrameMemory(paint.GetImage(), 40, 15, paint.GetWidth(), paint.GetHeight()); //75 e 250
      epd.DisplayFrame();

    }

    else if ( digitalRead(b6) == HIGH) {

      angle = angle + 5;
      auxangle = auxangle + 5;
      if (auxangle >= 360) {

        auxangle = auxangle - 360;
      }
      if (auxangle < 0) {
        auxangle = (360) + auxangle;
      }
      if (auxangle == 0) {
        auxangle = 0;
      }
      String stringOne = "Manual - Angulo:" +  String(auxangle);
      char Bolinha[50];
      stringOne.toCharArray(Bolinha, 50);
      if (k == 0) {
        epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
        epd.DisplayFrame();
        epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
        epd.DisplayFrame();

        k = k + 1;
      }
      paint.SetRotate(ROTATE_90);
      paint.SetWidth(20);
      paint.SetHeight(300);

      paint.Clear(COLORED);
      paint.DrawStringAt(0, 0, Bolinha, &Font16, UNCOLORED);
      epd.SetFrameMemory(paint.GetImage(), 40, 15, paint.GetWidth(), paint.GetHeight()); //75 e 250
      epd.DisplayFrame();

    }

    else if ( digitalRead(b7) == HIGH) {

      angle = angle - 5;
      auxangle = auxangle - 5;
      if (auxangle >= 360) {

        auxangle = auxangle - 360;
      }
      if (auxangle < 0) {
        auxangle = (360) + auxangle;
      }
      if (auxangle == 0) {
        auxangle = 0;
      }
      String stringOne = "Manual - Angulo:" +  String(auxangle);
      char Bolinha[50];
      stringOne.toCharArray(Bolinha, 50);
      if (k == 0) {
        epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
        epd.DisplayFrame();
        epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
        epd.DisplayFrame();

        k = k + 1;
      }
      paint.SetRotate(ROTATE_90);
      paint.SetWidth(20);
      paint.SetHeight(300);

      paint.Clear(COLORED);
      paint.DrawStringAt(0, 0, Bolinha, &Font16, UNCOLORED);
      epd.SetFrameMemory(paint.GetImage(), 40, 15, paint.GetWidth(), paint.GetHeight()); //75 e 250
      epd.DisplayFrame();

    }

    else if ( digitalRead(b8) == HIGH) {

      angle = angle + 45;
      auxangle = auxangle + 45;
      if (auxangle >= 360) {

        auxangle = auxangle - 360;
      }
      if (auxangle < 0) {
        auxangle = (360) + auxangle;
      }
      if (auxangle == 0) {
        auxangle = 0;
      }
      String stringOne = "Manual - Angulo:" +  String(auxangle);
      char Bolinha[50];
      stringOne.toCharArray(Bolinha, 50);
      if (k == 0) {
        epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
        epd.DisplayFrame();
        epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
        epd.DisplayFrame();

        k = k + 1;
      }
      paint.SetRotate(ROTATE_90);
      paint.SetWidth(20);
      paint.SetHeight(300);

      paint.Clear(COLORED);
      paint.DrawStringAt(0, 0, Bolinha, &Font16, UNCOLORED);
      epd.SetFrameMemory(paint.GetImage(), 40, 15, paint.GetWidth(), paint.GetHeight()); //75 e 250
      epd.DisplayFrame();

    }

    else if ( digitalRead(b9) == HIGH) {

      angle = angle - 45;
      auxangle = auxangle - 45;
      if (auxangle >= 360) {

        auxangle = auxangle - 360;
      }
      if (auxangle < 0) {
        auxangle = (360) + auxangle;
      }
      if (auxangle == 0) {
        auxangle = 0;
      }
      String stringOne = "Manual - Angulo:" +  String(auxangle);
      char Bolinha[50];
      stringOne.toCharArray(Bolinha, 50);
      if (k == 0) {
        epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
        epd.DisplayFrame();
        epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
        epd.DisplayFrame();

        k = k + 1;
      }
      paint.SetRotate(ROTATE_90);
      paint.SetWidth(20);
      paint.SetHeight(300);

      paint.Clear(COLORED);
      paint.DrawStringAt(0, 0, Bolinha, &Font16, UNCOLORED);
      epd.SetFrameMemory(paint.GetImage(), 40, 15, paint.GetWidth(), paint.GetHeight()); //75 e 250
      epd.DisplayFrame();

    }

    if ( currentAngle != angle ) {

      if ( currentAngle < angle) {

        digitalWrite(dirPin, HIGH);
        n = angle - currentAngle;
        numstep = n / stepPerAngle;

      }

      else if ( currentAngle > angle) {

        digitalWrite(dirPin, LOW);
        n = currentAngle - angle;

        if ( angle == 0) {
          n = currentAngle;
        }
        numstep = n / stepPerAngle;
      }



      for (int x = 0; x < numstep; x++) {

        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000);

      }
      currentAngle = angle;
    }

  }

  delay(500);
}
