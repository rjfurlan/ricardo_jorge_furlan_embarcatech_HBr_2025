# Projetos de Sistemas Embarcados - EmbarcaTech 2025

Autor: **Ricardo Jorge Furlan**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Campinas, 09 de maio de 2025

---

# ⚠ Disclaimer
# THE SOFTWARE IS PROVIDED "AS IS", USE AT YOUR OWN RISK
# O SOFTWARE É FORNECIDO "COMO ESTÁ", USE POR SUA CONTA E RISCO


## This code was developed for educational purposes as an assignment for Phase 2 of the residency program in the **EmbarcaTech professional training program**, with the goal of demonstrating some of the concepts learned during the residency.

## Third-Party Code

- The files for controlling the **OLED display** (`ssd1306_...` files) located in the `libs_ext` directory, including the text fonts, were based on the repository:  
  https://github.com/BitDogLab/BitDogLab-C/tree/main/display_oled_logo/inc with minor modifications.
- The `pico_sdk_import.cmake` file was **automatically generated** during project creation by the **Raspberry Pi Pico plugin**.
- The `CMakeLists.txt` file was initially **automatically generated** during project creation by the **Raspberry Pi Pico plugin**, and later edited as needed for the project.

## How to Build/Compile the Code

This software was developed for the **BitDogLab V6.3** board. This board uses the **Raspberry Pi Pico-W** board (which contains the **RP2040 microcontroller**).

For development, the **Visual Studio Code IDE** was used along with the **Raspberry Pi Pico plugin**. The SDK version used was **2.1.1**.

**Note:** The `CMakeLists.txt` configuration is set to load the code into **RAM**; therefore, the program will be lost when the board is powered off.

---

# Using the Galton Board

This project is a **Galton Board simulator** developed for the **BigDogLab** board.

The board's display has **low resolution** and **only two colors**, which imposes some limitations on the project.

The main goal was to create a **flexible solution**, allowing the user to configure various parameters through an interactive menu.

## Menu Parameters

Below are the parameters available in the configuration menu:

---

### 1. Ball Size

Allows you to adjust the ball size between **1, 3, 5, and 7 pixels**. It is also possible to add **extra spacing around the ball**, indicated in the menu by the `+` symbol after the number.  
Available options:

- 1
- 1+
- 1++
- 3
- 3+
- 3++
- 5
- 5+
- 5++
- 7
- 7+

**Note:** When changing the ball size, if the configured depth does not fit the display, the program will **automatically adjust the depth** to ensure everything fits properly.

---

### 2. Number of Balls on the Board

Defines how the balls will be released:

- `ONLY-ONE`: One ball at a time
- `3-SPACE`: Multiple balls, with **3-position spacing** between them
- `1-SPACE`: Multiple balls, with **1-position spacing**
- `BURST`: Releases **5 balls in sequence**
- `MAX`: Releases multiple balls **with no spacing** (one right after the other)

---

### 3. Deep (Depth)

Defines the number of **pin rows** on the Galton Board.  
The minimum value is **1**, and the maximum depends on the **ball size** to ensure it fits on the display.

The table below shows the maximum depth limits:

| Ball Size | Max Depth | Pixels |
|-----------|-----------|--------|
| 1         | 30        | 1      |
| 1+        | 14        | 3      |
| 1++       | 9         | 5      |
| 3         | 14        | 3      |
| 3+        | 9         | 5      |
| 5         | 9         | 5      |
| 5+        | 6         | 7      |
| 7         | 6         | 7      |
| 7+        | 5         | 9      |

---

### 4. Speed

Defines the speed of each ball step:

- `500ms`
- `200ms`
- `100ms`
- `50ms`
- `MAX` → maximum speed (~25ms, the minimum time needed to update the display)

---

### 5. Histo Bars

Defines how the **separator bars of the bins** will be displayed:

- `NO`: No bars
- `LINE`: Continuous lines separating the bins
- `DOT`: Dots separating the bins
- `DOT L`: Dots with wider spacing
- `TOP D`: Small lines at the top, middle, and bottom of each bin

---

### 6. Histo Bell

Defines how the **bell (Gaussian distribution)** will be displayed:

- `NO`: No display
- `DOT`: A dot at the center of the column corresponding to the value
- `BAR`: A horizontal bar at the column corresponding to the value
- `LINE`: Lines connecting the dots (DOT mode)

---

### 7. Random

Defines the **bias** of the random number generator (probability of going left or right).  
The value ranges from **0 to 16**:

- `0:16`: 100% chance of going **right**
- `8:8`: 50% chance to each side
- `16:0`: 100% chance of going **left**

**Note:** There is also the `Dynamic` option, where the value is dynamically set based on the **mouse position**.

---

### 8. Search (Combination Search)

Allows you to **scan all possible combinations** of **ball size** and **depth** graphically, to select the best one.  
Use the **Left** and **Right** buttons (via USB or Joystick) to navigate through the combinations. Press **Click** to select and return to the main menu.

---

### 9. Play

Selecting this option will open a **sub-menu** with the following options:

#### 9.1 Play Normal-Way
Starts the traditional Galton Board execution with the configured parameters.

#### 9.2 Play Hypersonic
Runs the Galton Board **without pins** and **without ball movement**; only the ball counter and histogram are updated.  
Ideal for running a large number of balls quickly.

#### 9.3 Clear Data
Clears the histogram data.  
> **Important:** Data is not automatically cleared when entering or exiting the display. You must use this option to clear it.

#### 9.4 Histogram Data
Opens a menu that **shows the number of balls in each column** of the histogram.

#### 9.5 Return
Returns to the main menu.

---

## Final Notes

This simulator aims to balance **simplicity**, **hardware limitations**, and **configuration flexibility**.




---


---

# Utilizando o Galton Board

Este projeto é um **simulador da Galton Board** desenvolvido para a placa **BigDogLab**.

O display da placa possui **baixa resolução** e **apenas duas cores**, o que impõe algumas limitações ao projeto.

Como premissa, buscou-se criar uma solução **flexível**, permitindo ao usuário configurar diversos parâmetros por meio de um menu interativo.

## Parâmetros do Menu

Abaixo estão descritos os parâmetros disponíveis no menu de configuração:

---

### 1. Tamanho da Bola

Permite ajustar o tamanho da bola entre **1, 3, 5 e 7 pixels**. Também é possível adicionar um **espaço extra ao redor da bola**, indicado no menu pelo símbolo `+` após o número.  
As opções disponíveis são:
- 1
- 1+
- 1++
- 3
- 3+
- 3++
- 5
- 5+
- 5++
- 7
- 7+


**Obs.:** Ao alterar o tamanho da bola, caso a profundidade configurada não caiba no display, o programa **ajusta automaticamente a profundidade** para garantir que tudo seja exibido corretamente.  

---

### 2. Número de Bolas na Board

Define como as bolas serão lançadas:

- `ONLY-ONE`: Uma bola por vez
- `3-SPACE`: Múltiplas bolas, com espaçamento de **3 posições** entre elas
- `1-SPACE`: Múltiplas bolas, com espaçamento de **1 posição**
- `BURST`: Lança **5 bolas em sequência**
- `MAX`: Lança múltiplas bolas **sem espaçamento** (uma atrás da outra)

---

### 3. Deep (Profundidade)

Define o número de **linhas de pinos** da Galton Board.  
O valor mínimo é **1** e o máximo depende do **tamanho da bola**, para que tudo caiba no display.

A tabela abaixo mostra os limites máximos de profundidade:

| Tamanho da Bola | Profundidade Máxima | Pixels |
|-----------------|---------------------|-------|
| 1               | 30                  | 1      |
| 1+              | 14                  | 3      |
| 1++             | 9                   | 5      |
| 3               | 14                  | 3      |
| 3+              | 9                   | 5      |
| 5               | 9                   | 5      |
| 5+              | 6                   | 7      |
| 7               | 6                   | 7      |
| 7+              | 5                   | 9      |

---

### 4. Speed (Velocidade)

Define a velocidade de cada passo da bola:

- `500ms`
- `200ms`
- `100ms`
- `50ms`
- `MAX` → velocidade máxima (~25ms, tempo mínimo necessário para atualizar o display)

---

### 5. Histo Bars (Barras do Histograma)

Define como as **barras separadoras das canaletas** serão exibidas:

- `NO`: Sem barras
- `LINE`: Linhas contínuas separando as canaletas
- `DOT`: Pontos separando as canaletas
- `DOT L`: Pontos mais espaçados
- `TOP D`: Pequenas linhas no topo, meio e base de cada canaleta

---

### 6. Histo Bell (Sino da Gaussiana)

Define como será exibido o **sino (distribuição Gaussiana)**:

- `NO`: Não exibe
- `DOT`: Um ponto no centro da coluna correspondente ao valor
- `BAR`: Uma barra horizontal na coluna correspondente ao valor
- `LINE`: Linhas interligando os pontos (modo DOT)

---

### 7. Random (Aleatoriedade)

Define a **tendência** do gerador de números aleatórios (probabilidade de ir para a esquerda ou direita).  
O valor varia de **0 a 16**:

- `0:16`: 100% chance de ir para a **direita**
- `8:8`: 50% de chance para cada lado
- `16:0`: 100% chance de ir para a **esquerda**

**Obs.:** Há também a opção `Dynamic`, onde o valor é definido dinamicamente conforme a posição do **mouse**.

---

### 8. Search (Busca de Combinações)

Permite **varrer todas as combinações possíveis** de **tamanho da bola** e **profundidade** de forma gráfica, para selecionar a melhor.  
Use os botões **Left** e **Right** (via USB ou Joystick) para navegar pelas combinações. Pressione **Click** para selecionar e retornar ao menu principal.

---

### 9. Play (Executar)

Selecionando esta opção, será exibido um **sub-menu** com as seguintes opções:

#### 9.1 Play Normal-Way
Inicia a execução tradicional da Galton Board com os parâmetros configurados.

#### 9.2 Play Hypersonic
Executa o Galton Board **sem os pinos** e **sem o movimento das bolas**; apenas o contador de bolas e o histograma são atualizados.  
Ideal para rodar um grande número de bolas rapidamente.

#### 9.3 Clear Data
Limpa os dados do histograma.  
> **Importante:** Os dados não são apagados automaticamente ao entrar ou sair do display. É necessário usar esta opção para limpar.

#### 9.4 Histogram Data
Exibe um menu que **mostra o número de bolas em cada coluna** do histograma.

#### 9.5 Return
Retorna ao menu principal.

---

## Observações Finais

Este simulador busca balancear **simplicidade**, **limitações do hardware** e **flexibilidade de configuração**.  


---

## 📜 Licença
MIT License - MIT GPL-3.0.