#include <LiquidCrystal_I2C.h>    //Librería para la pantalla LCD
//////////////////////////// LCD ////////////////////////////
/* Objeto LCD con numero de filas y columnas */
LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {
  /****** PANTALLA ******/
  /*Inicio del módulo de pantalla.*/
  Serial.println("Iniciando Pantalla LCD");
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0); lcd.print("INICIANDO PRUEBA DE");
  lcd.setCursor(0,1); lcd.print("   PANTALLA  LCD");
  lcd.setCursor(0,2); lcd.print("     ESTADO: OK");
}

void loop() {
}
