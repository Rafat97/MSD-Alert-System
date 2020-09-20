#include <LiquidCrystal.h> //this is for servo motor header file

/******************** initialize all pin value  **********************/

/**

   rs pin                 =====>   12
   en pin                 =====>   11
   d4 pin                 =====>   5
   d5 pin                 =====>   4
   d6 pin                 =====>   3
   d7 pin                 =====>   2
   buzzer pin             =====>   28
   LED pin                =====>   30
   LED2 pin               =====>   39
   flame_sensor pin       =====>   27
   inf sensor pin         =====>   8
   gas sensor pin         =====>   7

*/

//lm35(temperature) sensor pin number
int lm35 = A3;

//Gas sensor pin number
int Gas = 7;

//buzzer pin number
int buzzer = 28;

//LED pin number
int LED = 30;
int LED2 = 39;

//flame sensor pin number
int flame_sensor = 27;

//infrared sensor display pin number
int inf = 8;

//LCD display pin number
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
/******************** ending all pin value  **********************/


/******************** initialize all variables  **********************/
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
bool isFlame = 0;
bool isGas = 0;
bool isIr = 0;
int value = 0;
/********************  ending all variables  **********************/


/******************** setup function for arduino  **********************/
void setup()
{
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(flame_sensor, INPUT);
  pinMode (Gas , INPUT);
  pinMode (inf , INPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Initializing..");
  delay(500);
  lcd.clear();
}
/******************** ending setup function for arduino  **********************/


/******************** fever detection function **********************/
void feverAlert() {
  lcd.setCursor(4, 1);
  lcd.print("ALERT!!!");
  delay(500);
}


/******************** loop function for arduino **********************/
void loop()
{
  delay(100);
  if (digitalRead(flame_sensor) == HIGH ) //digitalRead for flame sensor is HIGH
  {
    isFlame = 1;
    Serial.println("Flame detected...! take action immediately.");
    digitalWrite(buzzer, HIGH);
    digitalWrite(LED, HIGH);
    digitalWrite(22, HIGH);
    digitalWrite(23, LOW);
  }
  if (digitalRead(flame_sensor) == LOW ) //digitalRead for flame sensor LOW
  {
    isFlame = 0;
    Serial.println("No flame detected. stay cool");
    digitalWrite(buzzer, LOW);
    digitalWrite(LED, LOW);
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
  }

  if (digitalRead(Gas) == HIGH) {  //digitalRead for Gas sensor HIGH
    isGas = 1;
    Serial.println("YES GAS");
    digitalWrite(LED2, HIGH); // Blink LED 2
  }
  if (digitalRead(Gas) == LOW) { //digitalRead for Gas sensor LOW
    isGas = 0;
    Serial.println("NOT GAS");
    digitalWrite(LED2, LOW); // Blink LED 2
  }

  if (digitalRead(inf) == HIGH) {  //digitalRead for infrared sensor HIGH
    Serial.println("Present");
    isIr = 1;
  }
  if (digitalRead(inf) == LOW) {  //digitalRead for infrared sensor LOW
    Serial.println("Absent");
    isIr = 0;
  }

  //analogRead for lm35(temperature) sensor
  value = analogRead(lm35);

  //calculate temperature values
  float milivolts = ( value / 1024.0) * 5000;
  float cel = milivolts / 10;
  float farh = (cel * 9) / 5 + 32;


  String tempFar;
  tempFar = String(farh);
  lcd.clear();
  if (isIr == 1) { //when infrared true

    Serial.print("TEMPRATURE = ");
    Serial.print(cel);
    Serial.print("*C");
    Serial.println();

    Serial.print("TEMPRATURE = ");
    Serial.print(farh);
    Serial.print("*F");
    Serial.println();

    lcd.setCursor(4, 0);

    lcd.print(tempFar + " *F");

    if (farh > 100) { //when body temperature in greater then 100
      feverAlert();
      
    }
    else {
      //digitalWrite(LED2, LOW); // Unblinking LED 2
      lcd.setCursor(4, 1);
      lcd.print("Fine");
      delay(500);
    }

    lcd.clear();
  } else {
    digitalWrite(LED2, LOW);
  }
  delay(200);

}

/******************** ending loop detection function **********************/
