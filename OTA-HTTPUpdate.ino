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
    Serial.println("\nIniciando");

    //Inicializa SPIFFS
    if(SPIFFS.begin()) {
        Serial.println("SPIFFS Ok");
    }
    
    else {
        Serial.println("SPIFFS Falha");
    }

    //Verifica / exibe arquivo
    if(SPIFFS.exists("/Teste.txt")) {
        File f = SPIFFS.open("/Teste.txt", "r");
        
        if(f) {
            Serial.println("Lendo arquivo:");
            Serial.println(f.readString());
            f.close();
        }
    }
    
    else {
        Serial.println("Arquivo não encontrado");
    }
  
    //Conecta WiFi
    WiFi.begin(SSID, PASSWORD);
    Serial.println("\nConectando WiFi " + String(SSID));
    
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    
    Serial.println();

    ota.setLinkSketch("https://mega.nz/file/uZ5VkQbS#kJpgeaMH8XZuhpV-UppAutb3CxsQuVmTr78G-xXZLaM");     //Link do sketch.bin
    
    //ota.setLinkSpiffs("https://mega.nz/file/vcQEBb7A#hZ6jFkSICq6_abfaukW8JGz8LdSAsSJWOo1bkkW9zh0");   //SPIFFS vazio
    //ota.setLinkSpiffs("https://mega.nz/file/CZBBFaSY#xlf40xMF7UCvfgw54fX_Jry3nbTdOP4Tl5iKmPXKDG0");   //SPIFFS /Teste.txt
        
    /*
    //LED indicador de progresso
    httpUpdate.setLedPin(2, HIGH);

    //Callback - Progresso
    Update.onProgress([](size_t progresso, size_t total) {
        Serial.print(progresso * 100 / total);
        Serial.print(" ");
    });

    //Não reiniciar automaticamente
    httpUpdate.rebootOnUpdate(false);

    //Cria instância de Cliente seguro
    WiFiClientSecure client;

    //Instrui Cliente a ignorar assinatura do Servidor na conexao segura
    client.setInsecure();

    //Atualização SPIFFS ---------------------------------
    Serial.println("\n*** Atualização da SPIFFS ***");
    
    for (byte b = 5; b > 0; b--) {
        Serial.print(b);
        Serial.println("... ");
        delay(1000);
    }
  
    //Encerra SPIFFS
    SPIFFS.end();

    t_httpUpdate_return resultado = httpUpdate.updateSpiffs(client, "https://internetecoisas.com.br/download/IeC115-OTA/Blink.spiffs.esp32.bin");
    
    //Verifica resultado
    switch (resultado) {
        case HTTP_UPDATE_FAILED: {
            String s = httpUpdate.getLastErrorString();
            Serial.println("\nFalha: " + s);
        }
        break;
    
        case HTTP_UPDATE_NO_UPDATES: {
            Serial.println("\nNenhuma atualização disponível!");
        }
        break;
    
        case HTTP_UPDATE_OK: {
            Serial.println("\nAtualizado com sucesso!");
        }
        break;
    }

    //Inicializa SPIFFS
    if(SPIFFS.begin()) {
        Serial.println("SPIFFS Ok");
    }
    
    else {
        Serial.println("SPIFFS Falha");
    }

    //Verifica / exibe arquivo
    if (SPIFFS.exists("/Teste.txt")) {
        File f = SPIFFS.open("/Teste.txt", "r");
        
        if(f) {
            Serial.println("Lendo arquivo:");
            Serial.println(f.readString());
            f.close();
        }
    }
    
    else {
        Serial.println("Arquivo não encontrado!");
    }

    //Atualização do Sketch
    Serial.println("\n*** Atualização do sketch ***");
    for (byte b = 5; b > 0; b--) {
        Serial.print(b);
        Serial.println("... ");
        delay(1000);
    }

    resultado = httpUpdate.update(client, "https://internetecoisas.com.br/download/IeC115-OTA/Blink.ino.esp32.bin");

    //Verifica resultado
    switch (resultado) {
        case HTTP_UPDATE_FAILED: {
            String s = httpUpdate.getLastErrorString();
            Serial.println("\nFalha: " + s);
        }
        break;
    
        case HTTP_UPDATE_NO_UPDATES:
            Serial.println("\nNenhuma atualização disponível");
        break;
        
        case HTTP_UPDATE_OK: {
            Serial.println("\nSucesso, reiniciando...");
            ESP.restart();
        }
        break;
    }
    */
}

//=======================================================================================================================
//LOOP
//=======================================================================================================================

void loop() {
    int resultado;
    
    delay(10 * 1000);
    
    resultado = ota.atualizarSketch();
    
    Serial.println();
    ota.resultado(resultado);

    if(resultado == 1) ESP.restart();
}

//=======================================================================================================================
