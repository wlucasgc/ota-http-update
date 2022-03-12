//=======================================================================================================================
//BIBLIOTECAS
//=======================================================================================================================

#include <WiFi.h>
#include "OTAHTTPUpdate.h"
#include <SPIFFS.h>

//=======================================================================================================================
//VARIÁVEIS GLOBAIS
//=======================================================================================================================

const char*   SSID      = "Redmi9-WL";
const char*   PASSWORD  = "2danados";

//=======================================================================================================================
//OBJETOS
//=======================================================================================================================

OTAHTTPUpdate ota;

//=======================================================================================================================
//SETUP
//=======================================================================================================================

void setup() {
    Serial.begin(115200);

    Serial.println("");
    Serial.println("************************************");
    Serial.println("OTA HTTP Update");
    Serial.println("Esquema de particao: Minimal SPIFFS");
    
    //Inicializa SPIFFS
    Serial.println("************************************");
    if(SPIFFS.begin()) {
        Serial.println("SPIFFS Ok");
    }
    
    else {
        Serial.println("SPIFFS Falha");
    }

    //Verifica / exibe arquivo
    Serial.println("************************************");
    if(SPIFFS.exists("/Teste.txt")) {
        File f = SPIFFS.open("/Teste.txt", "r");
        
        if(f) {
            Serial.println("Conteudo do arquivo \"Teste.txt\":");
            Serial.println(f.readString());
            f.close();
        }
    }
    
    else {
        Serial.println("Arquivo não encontrado!");
    }
  
    //Conecta WiFi
    Serial.println("************************************");
    Serial.print("Conectando WiFi: " + String(SSID));
    
    WiFi.begin(SSID, PASSWORD);
    
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }
    
    ota.setLinkSketch("https://raw.githubusercontent.com/wlucasgc/OTA-HTTP-Update/main/sketch.bin");  //Link do sketch.bin
    ota.setLinkSpiffs("https://internetecoisas.com.br/download/IeC115-OTA/Blink.spiffs.esp32.bin");   //Link do SPIFFS
}

//=======================================================================================================================
//LOOP
//=======================================================================================================================

void loop() {
    int resultado;

    Serial.println("");
    Serial.println("************************************");
    Serial.print("Procurando por atualizaçoes em: ");
    for(int i = 10 ; i > 0 ; i--) {
        Serial.print(String(i) + "... ");
        delay(1000);
    }
    Serial.println("0");
    
    resultado = ota.atualizarSketch();
    
    Serial.println();
    ota.resultado(resultado);

    //if(resultado == 1) ota.reboot();
}

//=======================================================================================================================
