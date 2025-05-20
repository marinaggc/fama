# FAMA - Ferramenta de Ângulos para Monitoramento de Atividade

**FAMA** é uma ferramenta baseada em ESP8266 e sensor acelerômetro MMA8452Q, destinada ao monitoramento de movimentos por meio do cálculo do ângulo azimutal em tempo real. Ideal para aplicações de análise de exercícios físicos, fisioterapia e acompanhamento de movimentações corporais.

## 📷 Visão Geral

Este projeto captura dados de aceleração usando o sensor MMA8452Q via I2C, processa os valores para calcular o ângulo de inclinação e exibe as informações em uma página web acessível por qualquer dispositivo conectado à mesma rede Wi-Fi.

## 🚀 Funcionalidades

- Conexão Wi-Fi com ESP8266
- Leitura de dados de aceleração em tempo real
- Cálculo do ângulo de inclinação (azimutal)
- Exibição dos dados em interface web atualizada automaticamente
- Interface HTML simples, responsiva e leve

## 🛠️ Tecnologias e Componentes

- **ESP8266** (NodeMCU)
- **Sensor MMA8452Q** (acelerômetro 3 eixos)
- **Linguagem C++** (Arduino)
- **Servidor Web HTTP**
- **HTML/CSS** para visualização

## 📡 Conectividade

O projeto utiliza a biblioteca `ESP8266WiFi` para conexão à rede sem fio e `ESP8266WebServer` para servir a interface web com os dados de ângulo em tempo real.

```cpp
const char* ssid = "Seu_SSID";
const char* password = "Sua_Senha";
```

## 📐 Cálculo do Ângulo

O ângulo é calculado com base na componente Z da aceleração, normalizada em relação a um valor máximo (plano de referência) e convertida para graus usando a função `acos`:

```cpp
double cosarg = double(zAccl) / plano;
double ang = acos(cosarg) * (180 / PI);
```

## 🌐 Interface Web

A página web mostra o valor do ângulo em graus e se atualiza a cada 0.5 segundo automaticamente:

```
Título: Ângulo de Movimento
Valor exibido: 35.27 Graus
```

## 📦 Instalação

### 1. Requisitos

- Arduino IDE com suporte à placa ESP8266
- Bibliotecas:
  - ESP8266WiFi
  - ESP8266WebServer
  - Wire (I2C)

### 2. Montagem

- Conecte o sensor MMA8452Q ao ESP8266 via I2C:
  - SDA: D1
  - SCL: D2
- Faça o upload do código via Arduino IDE

### 3. Acesso

- Conecte seu dispositivo à mesma rede Wi-Fi
- Acesse o IP exibido no monitor serial após a conexão

## 🧪 Exemplo de Uso

Ideal para o monitoramento de articulações durante:
- Flexões de braço
- Movimentos de joelho
- Exercícios de fisioterapia com amplitude angular

## 📁 Organização do Código

- `setup()`: Inicializa rede, sensor e servidor web
- `loop()`: Mantém o servidor rodando
- `handle_OnConnect()`: Lê dados do sensor e responde com página HTML
- `EnvioHTML()`: Gera a interface web com o valor do ângulo

## ✅ Resultados Esperados

- Interface acessível pelo navegador
- Exibição contínua e responsiva do ângulo de inclinação

## 📃 Licença

Este projeto está licenciado sob a [MIT License](LICENSE).

## 🙌 Contribuições

Contribuições são bem-vindas! Fique à vontade para abrir *issues*, propor melhorias ou enviar *pull requests*.
