// Vinicius junior
// @VinihJunior
// vinicius.dphelippe@gmail.com
// Referências: http://labdegaragem.org
//              http://electronicpiece.blogspot.com.br/2012/01/ldr-led-arduino.html
// ** Este software faz a comunicação com o Arduino
// colhendo dados de luminosidade (% de luz) e temperatura (Cº)
// e quando a luminosidade for baixa (<= 10%) Liga o LED
// e quando for (> 30%) Apaga o LED.**



#include <LiquidCrystal.h> //Inclui a biblioteca do LCD
#include <Thermistor.h> //Inclui a biblioteca do Thermistor

#define Luz_Fundo  7
#define led 8
#define LDR A1 //Define LDR como A1


LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Configura os pinos do Arduino para se comunicar com o LCD

Thermistor temp(0); //Configura o pino A0 para a leitura do Thermistor (0 = A0 / 1 = A1 / ...)


float luminosidade; //Variável para armazenar o valor da luminosidade
int amostra; //Variável para se guardar os valores das amostras da luminosidade
int temperatura; //Variavel para armazenar o valor da temperatura

void setup()
{
lcd.begin(16, 2); // Iniciando o objeto "lcd" de 2 linhas e 16 colunas
pinMode(Luz_Fundo,OUTPUT); //define o pino como saída
digitalWrite(Luz_Fundo,HIGH); // Liga a luz do display.

 Serial.begin(9600);
 pinMode(led, OUTPUT);
 digitalWrite(led, LOW);

}

void loop()
{

temperatura = temp.getTemp(); //Pega a temperatura do Thermistor e armazena na variável temperatura em ºC

amostra = 0; //Zera a variável amostra

//Pega 1000 amostras
for(int i=0; i < 100 ; i++)
{
luminosidade = analogRead(LDR); //Armazena o valor lido pelo LDR
luminosidade = (luminosidade / 1024) * 100; //Transforma o valor lido em porcentagem
amostra = amostra + luminosidade; //Armazena na variável amostra
}
//=================

amostra = amostra/100; //Tira a média das amostras

lcd.setCursor(0,0); //Posiciona o cursor na primeira coluna(0) e na primeira linha(0) do LCD
lcd.print("Temperatura: "); //Imprime no LCD "Temperatura: "
lcd.print(temperatura); //Imprime o valor da temperatura
lcd.print("C"); //Imprime "C" indicando que está na escala Celsius

lcd.setCursor(0,1); //Posiciona o cursor na primeira coluna(0) e na segunda linha(1) do LCD
lcd.print("Luminosida.: "); //Imprime no LCD "Luminosida.: "
lcd.print(amostra); //Imprime o valor da luminosidade
lcd.print("%"); //Imprime "%" indicando que a luminosidade está em porcentagem

//Acendendo o LED
if (amostra <= 10) { // pouca luz - quase escuro. Valor da % de luz
   digitalWrite(led, HIGH);
 }
 if (amostra > 40) { // muita luz. Valor de % de luz
 digitalWrite(led, LOW);
   }

 delay(500); // tempo de liga/desliga do LED 0,5 segundos.

}
