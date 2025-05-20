#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <Wire.h>
 
// MMA8452Q I2C address is 0x1C(28)
#define Addr 0x1C
 

const char* ssid = "brisa-1390908";
const char* password = "bfldjzat";

// HTTP server will listen at port 80
ESP8266WebServer server(80);



void setup(void) {
  Serial.begin(115200); //Inicializa a comunicação serial
  delay(50); // ?Intervalo para aguardar a estabilização do sistema
  Serial.println("Conectando a Rede: "); //Imprime na serial a mensagem
  Serial.println(ssid); //Imprime na serial o nome da Rede Wi-Fi

  WiFi.begin(ssid, password); //Inicialização da comunicação Wi-Fi

  //Verificação da conexão
  while (WiFi.status() != WL_CONNECTED) { //Enquanto estiver aguardando status da conexão
    delay(1000);
    Serial.print("."); //Imprime pontos
  }
  Serial.println("");
  Serial.println("WiFi Conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP()); //Função para exibir o IP da ESP

  server.on("/", handle_OnConnect); //Servidor recebe uma solicitação HTTP - chama a função handle_OnConnect
  server.onNotFound(handle_NotFound); //Servidor recebe uma solicitação HTTP não especificada - chama a função handle_NotFound

  server.begin(); //Inicializa o servidor
  Serial.println("Servidor HTTP inicializado");

  //////////////////////// sensor
  Wire.begin();
  Wire.beginTransmission(Addr);
  Wire.write(0x2A);
  Wire.write((byte)0x00);
  Wire.endTransmission();
  Wire.beginTransmission(Addr);
  Wire.write(0x2A);
  Wire.write(0x01);
  Wire.endTransmission();
  Wire.beginTransmission(Addr);
  Wire.write(0x0E);
  Wire.write((byte)0x00);
  Wire.endTransmission();
  delay(300);
  
 int plano = 1024; 
 double cosarg = 0;
 double ang = 0;
}

void loop(void) {

 ///////////////////////////// http server

 server.handleClient(); //Chama o método handleClient()
 
}

void handle_OnConnect() {
  unsigned int data[7];
  Wire.requestFrom(Addr, 7);
  if(Wire.available() == 7) 
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
    data[6] = Wire.read();
  }
  int xAccl = ((data[1] * 256) + data[2]) / 16;
  if (xAccl > 2047)
  {
    xAccl -= 4096;
  }
 
  int yAccl = ((data[3] * 256) + data[4]) / 16;
  if (yAccl > 2047)
  {
    yAccl -= 4096;
  }
 
  int zAccl = ((data[5] * 256) + data[6]) / 16;
  if (zAccl > 2047)
  {
    zAccl -= 4096;

  }
  
 int plano = 1023; 
 double cosarg = double(zAccl)/double(plano);
 double ang = acos(cosarg)*(180/PI);
 delay(200);
 Serial.print("angulo  ");
 Serial.println(ang);
 server.send(200, "text/html", EnvioHTML(ang)); //Envia as informações usando o código 200, especifica o conteúdo como "text/html" e chama a função EnvioHTML

}

void handle_NotFound() { //Função para lidar com o erro 404
  server.send(404, "text/plain", "Não encontrado"); //Envia o código 404, especifica o conteúdo como "text/pain" e envia a mensagem "Não encontrado"

}

String EnvioHTML(double ang) { //Exibindo a página da web em HTML
  String ptr = "<!DOCTYPE html> <html>\n"; //Indica o envio do código HTML
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n"; //Torna a página da Web responsiva em qualquer navegador Web
  ptr += "<meta http-equiv='refresh' content='0.5'>";//Atualizar browser a cada 2 segundos
  ptr += "<link href=\"https://fonts.googleapis.com/css?family=Open+Sans:300,400,600\" rel=\"stylesheet\">\n";
  ptr += "<title>Monitoramento Angular de Exercicio</title>\n"; //Define o título da página

  //Configurações de fonte do título e do corpo do texto da página web
  ptr += "<style>html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #000000;}\n";
  ptr += "body{margin-top: 50px;}\n";
  ptr += "h1 {margin: 50px auto 30px;}\n";
  ptr += "h2 {margin: 40px auto 20px;}\n";
  ptr += "p {font-size: 24px;color: #000000;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>Angulo azimutal de movimento</h1>\n";


  //Exibe as informações de temperatura e umidade na página web
  ptr += "<p><b>Angulo: </b>";
  ptr += (double)ang;
  ptr += " Graus</p>";


  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;

}
