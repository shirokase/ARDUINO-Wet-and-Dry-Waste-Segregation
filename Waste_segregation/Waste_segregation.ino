#include <LiquidCrystal.h>

#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
Servo myservo; 

int irsensor = 2;
int pos = 0;    
int value = A0;
#define trigPin 4
#define echoPin 3
#define trigPin1 6
#define echoPin1 7
#define buzz 5
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(buzz, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("WASTE SORTING");
  lcd.setCursor(0, 1);
  lcd.print("WET & DRY WASTE");
  Serial.begin(9600);
  myservo.attach(9);  
  myservo.write(90);
  delay(600);
  pinMode (irsensor, INPUT);
  pinMode (value, INPUT);
}

void loop() {
  value = analogRead(A0);
  if (digitalRead(2) == LOW && value > 800)
  {
    myservo.write(25);
    delay(900);
    myservo.write(84);
    delay(2000);
    lcd.setCursor(0, 0);
    lcd.print("DRY WASTE");
    lcd.setCursor(0, 1);
    lcd.print("MATERIAL");
    delay (3000);
  }
  else
  {
  
  }
  lcd.clear();
  value = analogRead(A0);
  if (value < 900) {
    Serial.println(value);
    myservo.write(140);
    delay(900);
    myservo.write(84);
    delay(2000);
    lcd.setCursor(0, 0);
    lcd.print("WET WASTE ");
    lcd.setCursor(0, 1);
    lcd.print("MATERIAL");
    delay (3000);
  }
  else
  {
   
  }
  lcd.clear();
 long duration, inches, cm;

  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

 
  duration = pulseIn(echoPin, HIGH);


  
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  if (inches <3) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WASTE FULL!");
    digitalWrite(buzz, HIGH);
    

    delay(500);
  } else {
    lcd.clear();
    Serial.println("no hand");
    digitalWrite(buzz, LOW);
    
    delay(500);
    
  }
  delay(100);
}
  
long microsecondsToInches(long microseconds)
{

  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  
  return microseconds / 29 / 2;
}
