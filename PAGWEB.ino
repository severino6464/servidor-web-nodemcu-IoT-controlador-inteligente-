#include <ESP8266WiFi.h> //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO
#include <Wire.h> 
#include "SH1106Wire.h"
#include <brzo_i2c.h>
#include "SH1106Brzo.h"
const char* ssid = "AREX"; //VARIÁVEL QUE ARMAZENA O NOME DA REDE SEM FIO EM QUE VAI CONECTAR
const char* password = "12345678"; //VARIÁVEL QUE ARMAZENA A SENHA DA REDE SEM FIO EM QUE VAI CONECTAR
SH1106Brzo  display(0x3c, D3, D5);

int ledPin = 13; // GPIO13 do ESP8266 e D7 do NodeMCU
int ledPin1 = 2; // GPIO2 do ESP8266 e D4 do NodeMCU
int counter = 1;
int x = 1;
WiFiServer server(80); //CASO OCORRA PROBLEMAS COM A PORTA 80, UTILIZE OUTRA (EX:8082,8089) E A CHAMADA DA URL FICARÁ IP:PORTA(EX: 192.168.0.15:8082)
 
#define DEMO_DURATION 3000
void setup() {
pinMode(LED_BUILTIN, OUTPUT);
Serial.begin(115200); //INICIALIZA A SERIAL
delay(10); //INTERVALO DE 10 MILISEGUNDOS
  display.init(); //  iniciar display oled

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

   

  

  
  // draw the progress bar
  while(x < 100){
     int progress = x;
  display.drawProgressBar(0, 32, 120, 10, progress);
  // draw the percentage as String
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, String(progress) + "%");
  display.display();
  counter++;
  x++;
  delay(50);
  display.clear();//limpando oled
  }
   display.setFont(ArialMT_Plain_10);
    display.drawString(22, 32, "AREX BEM-VINDO");
      display.display();
      delay(200);
  display.clear();//limpando oled
   display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "AREX");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "10.0.1.117");
    display.display();
  
pinMode(ledPin, OUTPUT); // Define o D7 como saída
digitalWrite(ledPin, HIGH); // O LED começa desligado
pinMode(ledPin1, OUTPUT); // Define o D7 como saída
digitalWrite(ledPin1, HIGH); // O LED começa desligado


Serial.println(""); //PULA UMA LINHA NA JANELA SERIAL
Serial.println(""); //PULA UMA LINHA NA JANELA SERIAL
Serial.print("Conectando a "); //ESCREVE O TEXTO NA SERIAL
Serial.print(ssid); //ESCREVE O NOME DA REDE NA SERIAL
 
WiFi.begin(ssid, password); //PASSA OS PARÂMETROS PARA A FUNÇÃO QUE VAI FAZER A CONEXÃO COM A REDE SEM FIO
 
while (WiFi.status() != WL_CONNECTED) { //ENQUANTO STATUS FOR DIFERENTE DE CONECTADO
delay(500); //INTERVALO DE 500 MILISEGUNDOS
Serial.print("."); //ESCREVE O CARACTER NA SERIAL
}
Serial.println(""); //PULA UMA LINHA NA JANELA SERIAL
Serial.print("Conectado a rede sem fio "); //ESCREVE O TEXTO NA SERIAL
Serial.println(ssid); //ESCREVE O NOME DA REDE NA SERIAL
server.begin(); //INICIA O SERVIDOR PARA RECEBER DADOS NA PORTA DEFINIDA EM "WiFiServer server(porta);"
Serial.println("Servidor iniciado"); //ESCREVE O TEXTO NA SERIAL
 
Serial.print("IP para se conectar ao NodeMCU: "); //ESCREVE O TEXTO NA SERIAL
Serial.print("http://"); //ESCREVE O TEXTO NA SERIAL
Serial.println(WiFi.localIP()); //ESCREVE NA SERIAL O IP RECEBIDO DENTRO DA REDE SEM FIO (O IP NESSA PRÁTICA É RECEBIDO DE FORMA AUTOMÁTICA)



}



void loop() {
   

    

  
WiFiClient client = server.available(); //VERIFICA SE ALGUM CLIENTE ESTÁ CONECTADO NO SERVIDOR
if (!client) { //SE NÃO EXISTIR CLIENTE CONECTADO, FAZ
return; //REEXECUTA O PROCESSO ATÉ QUE ALGUM CLIENTE SE CONECTE AO SERVIDOR
}




Serial.println("Novo cliente se conectou!"); //ESCREVE O TEXTO NA SERIAL
while(!client.available()){ //ENQUANTO CLIENTE ESTIVER CONECTADO
delay(1); //INTERVALO DE 1 MILISEGUNDO
}


String request = client.readStringUntil('\r'); //FAZ A LEITURA DA PRIMEIRA LINHA DA REQUISIÇÃO
Serial.println(request); //ESCREVE A REQUISIÇÃO NA SERIAL
client.flush(); //AGUARDA ATÉ QUE TODOS OS DADOS DE SAÍDA SEJAM ENVIADOS AO CLIENTE

// Operação do pedido
int porta1 = 0;
int porta2 = 0;
if (request.indexOf("/LED=ON") != -1)  {
digitalWrite(ledPin, LOW); // Se o pedido no LedPin for LED=ON, acende o LED
display.clear();//limpando oled
 display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "AREX");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "10.0.1.117");
display.setFont(ArialMT_Plain_24);
    display.drawString(0, 26, "porta 1 = on");
      display.display();
porta1 = 0;
}
if (request.indexOf("/LED=OFF") != -1)  {
digitalWrite(ledPin, HIGH); // Se o pedido no LedPin for LED=OFF, apaga o LED
display.clear();//limpando oled
 display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "AREX");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "10.0.1.117");
display.setFont(ArialMT_Plain_24);
    display.drawString(0, 26, "porta 1 = off");
      display.display();
porta1 = 1;
}
if (request.indexOf("/LED1=ON") != -1)  {
digitalWrite(ledPin1, LOW); // Se o pedido no LedPin1 for LED=ON, acende o LED
display.clear();//limpando oled
 display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "AREX");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "10.0.1.117");
display.setFont(ArialMT_Plain_24);
    display.drawString(0, 26, "porta 2 = on");
      display.display();
porta2 = 0;
}
if (request.indexOf("/LED1=OFF") != -1)  {
digitalWrite(ledPin1, HIGH); // Se o pedido no LedPin1 for LED=OFF, apaga o LED
display.clear();//limpando oled
 display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "AREX");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "10.0.1.117");
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 26, "porta 2 = off");
      display.display();
porta2 = 1;
}

 // Inicialização da página HTML
// Retorno do resposta
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); //  do not forget this one
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<head>");
client.println("<h1><center>SERVIDOR AREX</center></h1>"); //ESCREVE "SERVIDOR AREX" NA PÁGINA
client.println("<center><font size='5'>Seja bem vindo!</center>");

client.println("<style> .button {border: none;color: white;padding: 70px 70px;text-align: center;text-decoration: none;display: inline-block; font-size: 32px;margin: 4px 2px;cursor: pointer;}.button1 {background-color: #4CAF50;}.button2 {background-color: #008CBA;}.button3 {background-color: #4CAF50;}.button4 {background-color: #008CBA;}</style>");

client.println("</head>");
client.println("<body>");
client.println("Estado do RAPTOR 1: ");


if(porta1 == 1) { // Se está ligado apresenta “on”
client.print("ligado");
} else {
client.print("desligado");// Se está desligado apresenta “Off”
}
client.println("<br><br>");
client.println("Estado do RAPTOR 2: ");
if(porta2 == 1) { // Se está ligado apresenta “on”
client.print("ligado");
} else {
client.print("desligado");// Se está desligado apresenta “Off”
}


client.println("<br><br>");
 client.println("<center><font size='7'>PORTA 1</center>");

client.println("<center><a href=\"/LED=ON\"\"><button class=\"button button1\">ON </button></a>");// Ligar o LED corresponde Turn On
client.println("<a href=\"/LED=OFF\"\"><button class=\"button button2\">OFF</button></a><br /></center>");  // Desligar o LED corresponde Turn Off
client.println("<br><br>");
 client.println("<center><center><font size='7'>PORTA 2</center>");

client.println("<center><a href=\"/LED1=ON\"\"><button class=\"button button3\">ON</button></a> ");
client.println("<a href=\"/LED1=OFF\"\"><button class=\"button button4\">OFF</button></a><br /></center>");
client.println("</body>");
client.println("</html>");

delay(1);
Serial.println("");
}
