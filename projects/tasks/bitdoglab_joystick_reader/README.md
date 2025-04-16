# ⚠ Disclaimer
# THE SOFTWARE IS PROVIDED "AS IS", USE AT YOUR OWN RISK
# O SOFTWARE É FORNECIDO "COMO ESTÁ", USE POR SUA CONTA E RISCO
 
## Este código foi desenvolvido com fins educacionais como tarefa da fase 2, residência,  do programa de capacitação profissional EmbarcaTech, com objetivo de demostrar alguns pontos aprendidos durante a residência.
Este código mostra as leituras dos ADs que estão conectados ao joystick da placa, tanto no display como via USB.

## Código de terceiros
- Os arquivos para o acionamento do display OLED(arquivos: ssd1306_...) que estão no diretório libs_ext, incluindo as fontes de texto foram utilizados os do repositório: https://github.com/BitDogLab/BitDogLab-C/tree/main/display_oled_logo/inc com pequenas alterações;
- O arquivo pico_sdk_import.cmake foi "gerado" automaticamente na criação do projeto pelo plugin da Raspberry pi pico;
- O arquivo CMakeLists.txt foi inicialmente "gerado" automaticamente na criação do projeto pelo plugin da Raspberry pi pico, e posteriormente editado conforme as necessidades do projeto.

## Como gerar/compilar o código
Este software foi desenvolvido para a placa BitDogLab V6.3. Essa placa utiliza a placa Raspberry pi Pico-W (que contem o microcontrolador RP2040).
Para o desenvolvimento do código foi utilizado a IDE Visual Studio Code com o plugin da Raspberry pi Pico. Foi utilizado o SDK 2.1.1.
Obs.: As configurações do CMakeList.txt são para baixar o código na RAM, portanto ao desligar a placa o programa será perdido.

## Usando o código
Basta descarregar o código na placa.
As leituras dos ADs que estão conectados ao joystick da placa (x e y) serão visíveis no display, bem como via USB em um terminal serial (Baud rate 115200)