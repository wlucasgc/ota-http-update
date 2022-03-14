//=======================================================================================================================
//BIBLIOTECAS
//=======================================================================================================================

#include <Arduino.h>        //Biblioteca para as funções padrão do Arduino
#include <WiFi.h>           //Biblioteca para o WiFi
#include <HTTPUpdate.h>     //Biblioteca para as atualizações via HTTP
#include <SPIFFS.h>         //Biblioteca para o sistema de arquivos interno do ESP32
#include "OTAHTTPUpdate.h"  //Biblioteca para as funções de atualização via HTTP

//=======================================================================================================================
//FUNÇÃO QUE MOSTRA O PROGRESSO DA ATUALIZAÇÃO
//=======================================================================================================================

void progresso(size_t atual, size_t total) {
    int porcentagem;
    static int ultima_porcentagem = -1;

    porcentagem = (atual * 100) / total;

    if(porcentagem != ultima_porcentagem) {
        Serial.println(String(porcentagem) + "%");
        ultima_porcentagem = porcentagem;
    }
}

//=======================================================================================================================
//CONSTRUTOR
//=======================================================================================================================

OTAHTTPUpdate::OTAHTTPUpdate() {
    httpUpdate.setLedPin(2, HIGH);      //LED indicador de progresso
    Update.onProgress(progresso);       //Indica a função a ser executada para mostrar o progresso da atualização
}

//=======================================================================================================================
//CONSTRUTOR
//=======================================================================================================================

void OTAHTTPUpdate::reboot() {
    ESP.restart();                      //Reinicia o ESP
}

//=======================================================================================================================
//SETA O LINK DE ATUALIZAÇÃO DO SKETCH
//=======================================================================================================================

void OTAHTTPUpdate::setLinkSketch(String linkSketch) {
    _linkSketch = linkSketch;
}

//=======================================================================================================================
//SETA O LINK DE ATUALIZAÇÃO DO SPIFFS
//=======================================================================================================================

void OTAHTTPUpdate::setLinkSpiffs(String linkSpiffs) {
    _linkSpiffs = linkSpiffs;
}

//=======================================================================================================================
//SETA O PINO DO LED INDICADOR DE PROGRESSO
//=======================================================================================================================

void OTAHTTPUpdate::setLedProgresso(int ledProgresso) {
    httpUpdate.setLedPin(ledProgresso, HIGH);
}

//=======================================================================================================================
//ATUALIZAR SKETCH
//=======================================================================================================================

int OTAHTTPUpdate::atualizarSketch() {
    t_httpUpdate_return resultado;                              //Variável para guardar o resultado da atualização

    Serial.println("************************************");
    Serial.println("Atualizando sketch...");
    Serial.println("Link: " + _linkSketch);
    
    WiFiClientSecure client;                                    //Cria uma instância de Cliente seguro
    client.setInsecure();                                       //Instrui o Cliente a ignorar a assinatura do Servidor na conexao segura

    resultado = httpUpdate.update(client, _linkSketch);         //Inicia o processo de atualização do sketch
        
    switch (resultado) {                                        //Verifica o resultado
        case HTTP_UPDATE_OK:                                    //Se a atualização for bem sucedida, retorna 1
            return(1);
        break;
        
        case HTTP_UPDATE_FAILED:                                //Se a atualização falhar, retorna 0
            return(0);
        break;
    
        case HTTP_UPDATE_NO_UPDATES:                            //Se não encontrar nenhuma atualização, retorna -1
            return(-1);
        break;  
    }
}

//=======================================================================================================================
//ATUALIZAR SPIFFS (MODO 1)
//=======================================================================================================================

int OTAHTTPUpdate::atualizarSpiffs() {
    return(atualizarSpiffs(false));
}

//=======================================================================================================================
//ATUALIZAR SPIFFS (MODO 2)
//=======================================================================================================================

int OTAHTTPUpdate::atualizarSpiffs(bool reboot) {
    t_httpUpdate_return resultado;                              //Variável para guardar o resultado da atualização

    Serial.println("************************************");
    Serial.println("Atualizando SPIFFS...");
    Serial.println("Link: " + _linkSpiffs);
    SPIFFS.end();                                               //Encerra o SPIFFS para a atualização
    
    //httpUpdate.rebootOnUpdate(reboot);                          //Indica se deve ou não reiniciar automaticamente

    WiFiClientSecure client;                                    //Cria uma instância de Cliente seguro
    client.setInsecure();                                       //Instrui o Cliente a ignorar a assinatura do Servidor na conexao segura

    resultado = httpUpdate.updateSpiffs(client, _linkSpiffs);   //Inicia o processo de atualização da SPIFFS

    switch (resultado) {                                        //Verifica o resultado
        case HTTP_UPDATE_OK:                                    //Se a atualização for bem sucedida, retorna 1
            return(1);
        break;
        
        case HTTP_UPDATE_FAILED:                                //Se a atualização falhar, retorna 0
            return(0);
        break;
    
        case HTTP_UPDATE_NO_UPDATES:                            //Se não encontrar nenhuma atualização, retorna -1
            return(-1);
        break;  
    }
}

//=======================================================================================================================
//IMPRIME O RESULTADO DA ATUALIZAÇÃO
//=======================================================================================================================

void OTAHTTPUpdate::resultado(int codigo) {
    if(codigo == 1) {                                                   //Se a atualização foi bem sucedida
        Serial.println("Atualizado com sucesso!");    
    }

    else if(codigo == 0) {                                              //Se a atualização falhar
        Serial.println("Falha: " + httpUpdate.getLastErrorString());
    }
    
    else if(codigo == -1) {                                             //Se não encontrar nenhuma atualização
        Serial.println("Nenhuma atualização disponível!");
    }
}

//=======================================================================================================================
