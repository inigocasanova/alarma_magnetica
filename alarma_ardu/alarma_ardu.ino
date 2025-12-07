#include "RTClib.h"

char daysOfTheWeek[7][12] = {"Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};

void printDate(DateTime given_time){
    Serial.print(given_time.year(), DEC);
    Serial.print('/');
    Serial.print(given_time.month(), DEC);
    Serial.print('/');
    Serial.print(given_time.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[given_time.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(given_time.hour(), DEC);
    Serial.print(':');
    Serial.print(given_time.minute(), DEC);
    Serial.print(':');
    Serial.print(given_time.second(), DEC);
    Serial.println();
}

void printShortDate(DateTime given_time){
    Serial.print(given_time.day(), DEC);
    Serial.print('/');
    Serial.print(given_time.month(), DEC);
    Serial.print('/');
    Serial.print(given_time.year(), DEC);
    Serial.print(',');
    Serial.print(given_time.hour(), DEC);
    Serial.print(':');
    Serial.print(given_time.minute(), DEC);
    Serial.print(':');
    Serial.print(given_time.second(), DEC);
    Serial.println();
    
}

void sonarAlarma(int buzzer_pin){
  tone(buzzer_pin, 400);
}

void callarAlarma(int buzzer_pin){
  noTone(buzzer_pin);
}

void mostrarAlarma(int led_pin, int T){
  if(millis() % (2 * T) > T){
    digitalWrite(led_pin, HIGH);
  }else{
    digitalWrite(led_pin, LOW);
  }
}

void ocultarAlarma(int led_pin){
  digitalWrite(led_pin, LOW); 
}
