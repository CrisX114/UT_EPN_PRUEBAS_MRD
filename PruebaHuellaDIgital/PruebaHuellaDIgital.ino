#include <Adafruit_Fingerprint.h> //Librería lector huella
#include <SoftwareSerial.h>       //Librería para acceder a la comunicación serial en pines digitales
#include <LiquidCrystal_I2C.h>    //Librería para la pantalla LCD


//////////////////////////// LCD ////////////////////////////
/* Objeto LCD con numero de filas y columnas */
LiquidCrystal_I2C lcd(0x27,20,4);
/* variable para controlar el numero de página en lcd */
int numPagLCD = 0;

//////////////////////// FingerPrint ////////////////////////
/* pines de comunicación */
SoftwareSerial mySerial(16, 17); //tx = 16, rx = 17//
/* Objeto de lector de huella */
Adafruit_Fingerprint finger =  Adafruit_Fingerprint(&mySerial);

void setup() {
  // put your setup code here, to run once:
  ////////// comunicacion serial //////////
  /* inicio de la comunicacion serial */
  Serial.begin(9600);
  delay(1000);
  mySerial.begin(57600);
  delay(1000);
  while (!Serial);
  /*Inicio de comunicación serial de sensor de huella digital*/
  delay(1000);
  finger.begin(57600);
  delay(1000);
  /****** PANTALLA ******/
  /*Inicio del módulo de pantalla.*/
  Serial.println("Iniciando Pantalla LCD");
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0); lcd.print("INICIANDO PRUEBA DE ");
  lcd.setCursor(0,1); lcd.print("   HUELLA DIGITAL   ");
  
  /****** HUELLA DIGITAL ******/
  /*Inicio del sensor de huella digital. Verifica su funcionamiento*/
  Serial.print("Iniciando Sensor de Huella Digital: ");
  if (!finger.verifyPassword()){
    lcd.clear();
    lcd.setCursor(0,1); lcd.print("Error en sensor");
    lcd.setCursor(0,2); lcd.print("huella digital");
    Serial.println("Inicio Fallido!");
  }
  Serial.println("OK");
}

void loop() {
  getIDHuella();
}


void getIDHuella() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return;
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Error en leer huella");
    delay(3000);
    lcd.clear();
    numPagLCD = 0;
    return;
  }
  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  {
    Serial.println("El usuario no existe");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ERROR en leer huella");
    lcd.setCursor(0,2);
    lcd.print("EL USUARIO NO EXISTE");
    delay(3000);
    lcd.clear();
    return;
  }
  lcd.setCursor(0,2);
  lcd.print("ID Huella: ");
  lcd.print(finger.fingerID);
  Serial.println("ID Huella: ");
  Serial.println(finger.fingerID);
  delay(3000);
}
