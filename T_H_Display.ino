#include "LiquidCrystal.h"
#include "dht_nonblocking.h"

#define DHT_SENSOR_TYPE DHT_TYPE_11

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {  
  //set up the LCD's number of columns and rows:
  lcd.begin(16,2);  
}

//poll for a measurement, keeping the state machine alive. Returns true if a measurement is available
static bool measure_environment(float *temperature, float *humidity) {
  static unsigned long measurement_timestamp = millis( ); 

  //measure once every four seconds
  if( millis( ) - measurement_timestamp > 3000ul ) {
    if (dht_sensor.measure( temperature, humidity) == true ) {
      measurement_timestamp = millis( );
      return(true);
    }
  }
  return(false);
}

void loop() {
  float temperature;
  float humidity;

  //measure temp and humidity. if the function returns true, then a measurement is available
  if( measure_environment ( &temperature, &humidity) == true ) {
    lcd.setCursor(0,0);
    //display T and H on LCD
    lcd.print("T = " );
    lcd.print(temperature, 1);
    lcd.print(" deg. F");
    lcd.setCursor(0,1);
    lcd.print("H = ");
    lcd.print(humidity, 1);
    lcd.print("%");
  }
}
