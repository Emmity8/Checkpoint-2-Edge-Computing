#include <Adafruit_Sensor.h>                       
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDR 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2
#define DHTTYPE    DHT22                                              
#define DHTPIN 11                                   
DHT_Unified dht(DHTPIN, DHTTYPE);                  
uint32_t delayMS;                                  

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLUMNS, LCD_ROWS);

const unsigned int ldrPin = A0;
const unsigned int ledVerde = 8;
const unsigned int ledAmarelo = 9;
const unsigned int ledVermelho = 10;
const unsigned int buzzer = 5;

const unsigned int LIMITE_ALERTA = 700;
const unsigned int LIMITE_OK = 400;

void setup() {

  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(5,0);
  lcd.print("Iniciando...");
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  dht.begin();                                  
  Serial.println("Usando o Sensor DHT");
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);           
  Serial.println("------------------------------------");
  Serial.println("Temperatura");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Valor max:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Valor min:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolucao:   "); Serial.print(sensor.resolution); Serial.println(" *C");
  Serial.println("------------------------------------");
  dht.humidity().getSensor(&sensor);            
  Serial.println("------------------------------------");
  Serial.println("Umidade");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Valor max:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Valor min:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolucao:   "); Serial.print(sensor.resolution); Serial.println("%");
  Serial.println("------------------------------------");
  delayMS = sensor.min_delay / 1000;           
}

void loop() {
  int valorLuz = analogRead(ldrPin);
  Serial.println(valorLuz);

  
  if (valorLuz < LIMITE_OK) {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(buzzer, LOW);
  } 
  else if (valorLuz < LIMITE_ALERTA) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(buzzer, HIGH);
    delay(3000);
    digitalWrite(buzzer, LOW);
  } 
  else {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(buzzer, LOW);
  }

  
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  float temperatura = 0.0;
  if (isnan(event.temperature)) {
    Serial.println("Erro na leitura da Temperatura!");
  } else {
    temperatura = event.temperature;
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" *C");
  }

  
  dht.humidity().getEvent(&event);
  float umidade = 0.0;
  if (isnan(event.relative_humidity)) {
    Serial.println("Erro na leitura da Umidade!");
  } else {
    umidade = event.relative_humidity;
    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println("%");
  }

  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatura, 1);  
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Umid: ");
  lcd.print(umidade, 1);
  lcd.print(" %");

  delay(3000);

  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Luminosidade:");
  lcd.setCursor(0, 1);
  lcd.print(valorLuz);

  delay(3000);
}