#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include <addons/TokenHelper.h>

/* 1. Definición de credenciales de wifi */
#define WIFI_SSID "Galaxy" //Ingresar SSID de la red con la que se desea conectar
#define WIFI_PASSWORD "cris1234" //Ingresar Contraseña de la red con la que se desea conectar

/* 2. Definición del API Key */
#define API_KEY "AIzaSyCv2KOp4wX-OSVe1uJ8LgX_by0m7dKa1vw"

/* 3. Definición del project ID */
#define FIREBASE_PROJECT_ID "sca-cdici"

/* 4. Definición del email y contraseña para la autenticación de usuario */
#define USER_EMAIL "cristhian.xavier4@gmail.com"
#define USER_PASSWORD "cris12345"

//Definición de Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

bool taskCompleted = false;

unsigned long dataMillis = 0;

void setup()
{

    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Conectando a red Wi-Fi:");
    while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(1000);
    }
    Serial.println();
    Serial.print("Conectado con IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Cliente Firebase version: %s\n\n", FIREBASE_CLIENT_VERSION);

    config.api_key = API_KEY;

    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

    Firebase.begin(&config, &auth);
    
    Firebase.reconnectWiFi(true);
}

void loop()
{

    String documentPath = "prueba/1";
    if (Firebase.ready() && (millis() - dataMillis > 60000 || dataMillis == 0))
    {
        dataMillis = millis();

        if (!taskCompleted)
        {
            taskCompleted = true;
            FirebaseJson content;

            //mensaje
            content.set("fields/Resultado/stringValue", "Operación Correcta");
    
            Serial.print("Creando documento... ");

            if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), content.raw()))
                Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
            else
                Serial.println(fbdo.errorReason());
        }

        Serial.print("Obteniendo documento... ");

        if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), ""))
            Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
        else
            Serial.println(fbdo.errorReason());
    }
}
