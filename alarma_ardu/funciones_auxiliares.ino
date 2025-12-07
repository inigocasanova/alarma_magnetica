// Usamos una librería para comunicarnos con el RTC
#include "RTClib.h"

RTC_DS3231 rtc; //SDA a A4, SCL a A5
int SENSOR_PIN = A3;
int LED_PIN = 2;
int BUZZER_PIN = 3;

int umbral_intensidad = 500;
bool abierto_actualmente = false;
bool abierto_antes = false;
char estatus[2][7] = {"cerrado", "abierto"};


void setup () {
  Serial.begin(57600);
  pinMode(SENSOR_PIN, INPUT);

//Inicializar RTC
#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void loop() {
  while(1){
    int intensidad_mag = 1023 - analogRead(SENSOR_PIN);
    abierto_actualmente = intensidad_mag < umbral_intensidad;

    if(abierto_actualmente){
      mostrarAlarma(LED_PIN, 200);
      sonarAlarma(BUZZER_PIN);
    }else{
      ocultarAlarma(LED_PIN);
      callarAlarma(BUZZER_PIN);
    }

    
    if(abierto_actualmente != abierto_antes){
      abierto_antes = abierto_actualmente;
      break;
    }
  }
  
  if(abierto_actualmente) {
    Serial.print("Apertura");
    Serial.print(",");
    Serial.print("abierto");
    }else{
      Serial.print("Cierre");
      Serial.print(",");
      Serial.print("cerrado");
    }
  Serial.print(",");
  printShortDate(rtc.now());
}
