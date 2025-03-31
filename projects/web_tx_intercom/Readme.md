# ⚠ Disclaimer
# THE SOFTWARE IS PROVIDED "AS IS", USE AT YOUR OWN RISK
# O SOFTWARE É FORNECIDO "COMO ESTÁ", USE POR SUA CONTA E RISCO
 
## Este código foi desenvolvido com fins educacionais como tarefa final da fase 1 do programa de capacitação profissional EmbarcaTech, com objetivo de demostrar alguns pontos aprendidos durante o curso. Este código transmite mensagens em http SEM qualquer criptografia, podendo ser monitoradas facilmente. Não é validado para produção nem auditado quanto às melhores práticas de codificação e segurança.

## Código de terceiros
- Os arquivos para o acionamento do display OLED(arquivos: ssd1306_...) que estão no diretório libs_ext, incluindo as fontes de texto foram utilizados os do repositório: https://github.com/BitDogLab/BitDogLab-C/tree/main/display_oled_logo/inc com pequenas alterações;
- O arquivo lwipopts.h foi utilizado o do repositório: https://github.com/BitDogLab/BitDogLab-C/blob/main/wifi_led/lwipopts.h com a adição de alguns parâmetros para melhor estabilidade do WiFi;
- O arquivo pico_sdk_import.cmake foi "gerado" automaticamente na criação do projeto pelo plugin da Raspberry pi pico;
- O arquivo CMakeLists.txt foi inicialmente "gerado" automaticamente na criação do projeto pelo plugin da Raspberry pi pico, e posteriormente editado conforme as necessidades do projeto.


## Como gerar/compilar o código

Este software foi desenvolvido para a placa BitDogLab V6.3. Essa placa utiliza a placa Raspberry pi Pico-W (que contem o microcontrolador RP2040)  
Para o desenvolvimento do código foi utilizado a IDE Visual Studio Code com o plugin da Raspberry pi Pico. Foi utilizado o SDK 2.1.0

#### Edite o arquivo Config.h e substitua os valores abaixo
- #define WIFI_SSID  "MinhaRedeWiFi"  // Insira o nome  da sua rede Wi-Fi
- #define WIFI_PASS  "MinhaSenha123"  // Insira a senha da sua rede Wi-Fi


Após a compilação, sem erros, ele poderá ser instalado na BitDogLab.

## Usando a BitDogLab com o código instalado

Supondo que você está com seu roteador ligado e devidamente configurado com nome e senha da rede, o mesmo da compilação do código.
- Ligue a placa BitDogLab, no display OLED irá aparecer o nome do Código, , título, versão, build e data.
- Após 10 segundos o LED vermelho começará a piscar e o display OLED reportará que a placa esta tentando se conectar ao roteador
- Quando a conexão com o roteador WiFi for bem-sucedida, o LED piscará em amarelo(Vermelho e Verde piscando juntos), no display aparece o IP alocado a BitDogLab pelo roteador, exemplo: **192.168.25.3**
- De posse deste IP, em um dispositivo que esteja logado nesta rede WiFi abra um navegador WEB (browser), e digite http://o_ip_da_bitdoglab,  exemplo: **http://192.168.25.3**
- Feito isso, o navegador deverá ter aberto a página gerada pelo BitDogLab, e o LED da BitDogLab deve estar verde indicando que um navegador esta acessando-a, caso o navegador pare de acessar a placa o LED voltará para amarelo piscando, e caso caia a conexão com o roteador WiFi o LED voltará para vermelho piscando.

### Interface BitDogLab

#### Botões
Os botões tem como função enviar mensagens já pré programadas no código, sem necessidade de entrar no editor de mensagens. As mensagens pré programadas são:
- Para o botão A: "Tudo tranquilo por aqui." tipo: Low (mensagem de prioridade normal)
- Para o botão B: "Venha Logo preciso de sua ajuda!" tipo: High (mensagem de alta prioridade)

Obs.: As mensagens dos botões são editáveis no arquivo Config.h

#### LED RGB
- O LED RGB indica o estado da conexão com a rede WiFi e comunicação com Navegador, bem como se há mensagens não lidas. Obs.: A intensidade pode ser configurada no arquivo Config.h  

- O LED Azul piscando, independente dos demais LEDs indica que há mensagem recebida e não lida.

- Os LEDs Vermelho e Verde indicam:

| LED  | | WiFi  |
| ------------ | - | ------------ |
| Vermelho piscando  | => | Não conectado ao WiFi, tentando conectar.  |
| Amarelo piscando  | => | Conectado ao WiFi, sem requisição recente de algum navegador |
| Verde Continuo  | => | Conectado ao WiFi e há navegador acessando constantemente a placa |

#### Joystick
As funções do Joystick são:  
- Tornar uma mensagem recebida como lida, clicando no Joystick
- Navegar entre as telas dos display OLED, clicando no Joystick
- Permitir "digitar" a mensagem a ser enviada, clicando e movendo o Joystick

Quando o BitDogLab receber uma mensagem o LED azul vai piscar, o Display vai ficar piscando com a mensagem e caso seja uma mensagem High o buzzer vai fazer beeps. Clicando no Joystick nesta situação a mensagem é interpretada com lida, o LED azul apaga, o buzzer se beepando para de beepar e a mensagem no display para de piscar e no rodapé aparece a palavra LIDA

#### Display
Principal interface com o usuário, há diversas telas, para navegar entre as telas sequencialmente basta clicar no Joystick.
Obs.:Há eventos que fazem com que determinada tela seja ativada independente da interação do usuário, exemplo quando há falha na conexão ou se conecta a rede WiFi, vai para tela de WiFi, quando recebe uma mensagem vai para a tela MSG RECEBIDA, quando envia uma mensagem vai para tela MSG ENVIADA

- **MSG Recebida:** mostra a mensagem recebida, é a tela default do sistema, as demais telas retornam para essa tela após um timeout de 10 segundos. A primeira linha é o título da tela e informa o tipo de mensagem recebida:
	- "MSG RECEBIDA - L" para mensagem do tipo Low
	- "MSG RECEBIDA - H" para mensagem do tipo High

	logo abaixo, a mensagem recebida será exibida, e na última linha a esquerda tem a indicação de a quanto tempo a mensagem foi recebida em segundos, no outro lado se ha mensagem já foi lida.
	Obs.1: Enquanto a mensagem não for lida esta tela fica piscando.
	Obs.2: Para classificar esta mensagem como lida, basta um click com o Joystick
	
- **MSG Enviada:** Indica o tipo de mensagem que foi enviada Low ou High com o título: "MSG ENVIADA - LO":"MSG ENVIADA - HI" respectivamente. A mensagem a quanto tempo a mensagem foi enviada e se já foi lida
Obs.1: Enquanto a mensagem não for lida pelo destinatário a tela fica piscando.

- **MSG a enviar:** Esta tela permite que se edite a mensagem mensagem a ser enviada. A tela possui um cursor, bloco maciço, que é movido pelo joystick.
Ao clicar no joystick será efetuada uma ação dependendo de onde está este cursor.
	- se for em cima da mensagem a ser enviada, linhas 2, 3 e 4, o ponteiro de edição da mensagem ira para o ponto do cursor.
	- se for em cima do teclado, linhas 6, 7 e 8 a tecla que está no cursor ira para a mensagem a ser enviada.
	- se estivar na linha 5 executara as açoes correspondentes:
		- LO: enviar mensagem low
		- HI: enviar mensagem high
		- CLEAR: limpa a mensagem
		- NEXT: vai para a próxima tela do display

- **WiFi:** indica o nome da rede WiFi utilizada(que é definida no código) e se esta tentando conectar ou se está conectada, mostrando o IP
- **Versão:** mostra: nome, título, versão build e data do código
 

### Interface WEB

#### Mensagem recebida
Contem mensagem que a BitDogLab lhe enviou. se estiver com o fundo amarelo é uma mensagem normal Low, se estiver com o fundo vermelho piscando é uma mensagem High.
Ao marcar o CkeckBox "Mensagem lida", o fundo da mensagem volta para a cor da página, e a BitDolLab é avisada que você leu a mensagem.

#### Mensagem enviada/enviar
Contem o que foi enviado para a BitDogLab ou se pretende enviar(está editando). Apos se editar a mensagem a ser enviada para enviá-la basta clicar em um dos dois botões [Enviar Low] e [Enviar High], a mensagem será enviada a BitDogLab e enquanto não for lida, na BitDogLab, o fundo da mensagem ficará amarela para a mensagem Low e Vermelho para a mensagem High, o Checkbox de mensagem lida estará desmarcado. Após a leitura da mensagem na BitDogLab o fundo da mensagem volta para a cor da página e o Checkbox de mensagem lida é assinalado

#### Rodapé
A esquerda encontra-se dados da versão do código
No centro quantas requisições de página inteira foram feitas
A direita quantas requisições de atualização da página foram feitas desde a última requisição de página inteira.