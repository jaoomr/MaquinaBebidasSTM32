# MaquinaBebidasSTM32
Projeto de máquina de bebidas para a matéria de Automação I da UPF

Pinagem:

Parte superior da pinagem

PC14 = P1 - Pressostato de filtro de água saturado.

PC15 = P2 - Pressostato de cilindro de CO2 vazio.

PB10 = Y1 - Válvula de água quente

PB11 = Y2 - Válvula de água gelada

PB1  = Y3 - Válvula de água natural

PB0  = Y4 - Válvula de alimentação de CO2

PA0 = B1 - Bomba de alimentação de água (PWM)

PA1 = R1 - Aquecimento resistivo (PWM)

PA2 = CP1 - Compressor de saída (PWM)

PA3 = T1 - Sensor de temperatura do Heater

PA4 = T2 - Sensor de temperatura do Cooler


Parte inferior da pinagem
PA7, PA8, PA9, PA10 = Bn1 - Leitor óptico para detecção da cápsula (usado 3 digitais para emular, e o PA7 para dar trigger na leitura)


PA11,PA12,PA15,PB3,PB4,PB5,PB6,PB7,PB8,PB9 - Pinos para o LCD (PB8 e PB9 = RS e E, respectivamente. PA11 - PB7 = B0 - B7, em ordem)


PB12,PB13,PB14,PB15 - Teclado (Cancela, Adiciona, Subtrai e Confirma, respectivamente)

Montagem:

![Montagem](https://github.com/jaoomr/MaquinaBebidasSTM32/Images/montagem.jpg)

Leitura:

Pinos (A8, A9, A10):

000 - Água (Quente, Gelada e Natural)

001 - Água com Gás

010 - Chá Gelado

011 - Chá Quente

100 - Refrigerante


Qualquer outro código - "Erro na Leitura!" aparece no LCD.

Estrutura da máquina:

![Diagrama](https://github.com/jaoomr/MaquinaBebidasSTM32/blob/master/Images/montagem.jpg)

Módulos:
Core.c - Possui o leitor de tipo de bebida e o preparador de cada tipo de bebida

Modules.c - Possui os módulos de aquecimento, resfriamento, adição de CO2, etc.

LCD.c - Possui a biblioteca para escrita no LCD, com alguns caracteres especiais para português.


Documentação:

[Documentação](https://github.com/jaoomr/MaquinaBebidasSTM32/blob/master/ProjetoFinal/html/index.html)
