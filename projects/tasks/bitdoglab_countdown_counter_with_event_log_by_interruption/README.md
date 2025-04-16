# ⚠ Disclaimer
# THE SOFTWARE IS PROVIDED "AS IS", USE AT YOUR OWN RISK
# O SOFTWARE É FORNECIDO "COMO ESTÁ", USE POR SUA CONTA E RISCO
 
## Este código foi desenvolvido com fins educacionais como tarefa da fase 2, residência,  do programa de capacitação profissional EmbarcaTech, com objetivo de demostrar alguns pontos aprendidos durante a residência.

Este código utiliza interrupções para contar quantas bordas de descida ocorrem no botão B durante um período de 9 segundos. A contagem do tempo começa ao pressionar o botão A. O tempo restante até o final da contagem, assim como o número de bordas de descida detectadas no botão B, são exibidos tanto no display quanto via USB. 

O objetivo do programa é **observar os bounces do botão B**, já que, em alguns casos, ao pressioná-lo, a contagem de cliques ultrapassa 1 devido aos bounces. Além disso, ao soltar o botão, também podem ocorrer contagens indesejadas, o que reforça a presença dos bounces.

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
Para iniciar a contagem do tempo pressione o Botão A, e observe a contagem das bordas de descida do Botão B. Tanto o tempo restante como o número de bordas de descida são visíveis no display, bem como via USB em um terminal serial (Baud rate 115200).