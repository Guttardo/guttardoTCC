#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define ID_MQTT  "q1w2e3rtghnjmk"
const char* BROKER_MQTT = "iot.eclipse.org"; 
int BROKER_PORT = 1883;

const char* ssid     = "Rep Arapuca";
const char* password = "naovoupassarnao";

WiFiClient espClient; 
PubSubClient MQTT(espClient);
long tempo = 100;
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(tempo);
  delay(1000);
  
  initWiFi();
  initMQTT();
}

void loop() {
  VerificaConexoesWiFIEMQTT();
  if(Serial.available()){
    String dado = Serial.readString();
    Serial.println(dado);
    if(dado.substring(0,1)=="1"){
      postMQTT(dado.substring(2),"tcc/postBH1750");
    }
    else if(dado.substring(0,1)=="2"){
      postMQTT(dado.substring(2),"tcc/postBMP180");
    }
    else if(dado.substring(0,1)=="3"){
      postMQTT(dado.substring(2),"tcc/postLDR1");
    }
    else if(dado.substring(0,1)=="4"){
      postMQTT(dado.substring(2),"tcc/postLDR2");
    }
    else if(dado.substring(0,1)=="5"){
      postMQTT(dado.substring(2),"tcc/postLDR3");
    }
    else if(dado.substring(0,1)=="6"){
      postMQTT(dado.substring(2),"tcc/postLDR4");
    }
    else if(dado.substring(0,1)=="7"){
      postMQTT(dado.substring(2),"tcc/postTSL2561");
    }
  }
  MQTT.loop();
}

void postMQTT(String dado, const char* instrucao){
  MQTT.publish(instrucao, dado.c_str());
}

void initMQTT() 
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   
             
}

void reconnectMQTT() 
{
    while (!MQTT.connected()) 
    {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) 
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
        } 
        else 
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 2s");
            delay(2000);
        }
    }
}

void initWiFi() 
{
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(ssid);
    Serial.println("Aguarde");
    
    reconectWiFi();
}

void reconectWiFi() 
{
    //se já está conectado a rede WI-FI, nada é feito. 
    //Caso contrário, são efetuadas tentativas de conexão
    if (WiFi.status() == WL_CONNECTED)
        return;
        
    WiFi.begin(ssid, password); // Conecta na rede WI-FI
    
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(100);
        Serial.print(".");
    }
  
    Serial.println();
    Serial.print("Conectado com sucesso na rede ");
    Serial.print(ssid);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}

void VerificaConexoesWiFIEMQTT(void)
{
    if (!MQTT.connected()) 
        reconnectMQTT(); //se não há conexão com o Broker, a conexão é refeita
    
     reconectWiFi(); //se não há conexão com o WiFI, a conexão é refeita
}

