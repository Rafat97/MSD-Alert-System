#include <LiquidCrystal.h>

int value = 0;
int lm35 = A3;

int Gas = 7;
int buzzer = 28;
int LED = 30;
int LED2 = 39;
int flame_sensor = 27;
int inf = 8;

bool isFlame = 0;
bool isGas = 0;
bool isIr = 0;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

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

void feverAlert() {
  lcd.setCursor(4, 1);
  lcd.print("ALERT!!!");
  delay(100);
}
void loop()
{

  delay(100);
  if (digitalRead(flame_sensor) == HIGH )
  {
    isFlame = 1;
    Serial.println("Flame detected...! take action immediately.");
    digitalWrite(buzzer, HIGH);
    digitalWrite(LED, HIGH);
    digitalWrite(22, HIGH);
    digitalWrite(23, LOW);
  }
  if (digitalRead(flame_sensor) == LOW )
  {
    isFlame = 0;
    Serial.println("No flame detected. stay cool");
    digitalWrite(buzzer, LOW);
    digitalWrite(LED, LOW);
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
  }

  if (digitalRead(Gas) == HIGH) {
    isGas = 1;
    Serial.println("YES GAS");
  }
  if (digitalRead(Gas) == LOW) {
    isGas = 0;
    Serial.println("NOT GAS");
  }

  if (digitalRead(inf) == HIGH) {
    Serial.println("Present");
    isIr = 1;
  }
  if (digitalRead(inf) == LOW) {
    Serial.println("Absent");
    isIr = 0;
  }

  value = analogRead(lm35);
  float milivolts = ( value / 1024.0) * 5000;
  float cel = milivolts / 10;
  float farh = (cel * 9) / 5 + 32;


  String tempFar;

  tempFar = String(farh);
  lcd.clear();
  if (isIr == 1) {

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

    if (farh > 100) {
      feverAlert();
      digitalWrite(LED2, HIGH);
    }
    else {
      digitalWrite(LED2, LOW);
      lcd.setCursor(4, 1);
      lcd.print("Fine");
    }

    lcd.clear();
  } else {
    digitalWrite(LED2, LOW);
  }
  delay(200);



}
