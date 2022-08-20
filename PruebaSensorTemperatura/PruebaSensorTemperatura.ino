#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>    //Librería para la pantalla LCD

const int SENSOR_PROX = 25;    //Pin de sensor de proximidad


//////////////////////////// LCD ////////////////////////////
/* Objeto LCD con numero de filas y columnas */
LiquidCrystal_I2C lcd(0x27,20,4);

///////////////////// SENSOR TEMPERATURA /////////////////////
/* Objeto para acceder al sensor de temperatura */
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
  while (!Serial);


  /****** PANTALLA ******/
  /*Inicio del módulo de pantalla.*/
  Serial.println("Iniciando Pantalla LCD");
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0); lcd.print("INICIANDO PRUEBA DE ");
  lcd.setCursor(0,1); lcd.print(" SENSOR TEMPERATURA ");
  
/****** SENSOR DE TEMPERATURA ******/
  /*Inicio del sensor. Se verifica su funcionamiento*/
  Serial.print("Iniciando Sensor de temperatura: ");
  if (!mlx.begin()) {
    lcd.clear();
    lcd.setCursor(0,1); lcd.print("Error en sensor de");
    lcd.setCursor(0,2); lcd.print("temperatura");
    Serial.println("Inicio Fallido!");
  };
  Serial.println("OK");
  Serial.println("================================================");

  pinMode(SENSOR_PROX, INPUT);
}

void loop() {
  if(digitalRead(SENSOR_PROX) == HIGH){
    Serial.println("Midiendo Temperatura...");
    leerTemperatura();
  } 
}

void leerTemperatura(){
  String ambiente = String(mlx.readAmbientTempC());
  String objeto = String(mlx.readObjectTempC());
  lcd.setCursor(0,2);
  lcd.print("Ambiente");
  lcd.print(ambiente);
  lcd.print("*C");
  lcd.setCursor(0,3);
  lcd.print("Objeto");
  lcd.print(objeto);
  lcd.print("*C");
  Serial.print("Ambiente = "); Serial.println(ambiente);
  Serial.print("Objeto = "); Serial.print(objeto); Serial.println("*C");

  Serial.println();
  delay(5000);
  lcd.setCursor(0,2);
  lcd.print("                    ");
  lcd.setCursor(0,3);
  lcd.print("                    ");
}
