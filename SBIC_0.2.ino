#include <SPI.h>
#define CS_DAC 9

int sensor_value =0;
int output_value=0;

/*
 * O sistema de primeira ordem é tratado como um filtro RC de 1ªOrdem
 */
//int R=1000;
//int C=0.000001;
//int Ts=0.0005;
//int Vmax=5;


void setup() {

  Serial.begin(9600);

  pinMode(CS_DAC,OUTPUT);
  digitalWrite(CS_DAC,HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2);

  
  
}

void analogOut(int value) {
  byte data;
  digitalWrite(CS_DAC, LOW);
  data = highByte(value);
  data = B00001111 & data;
  data = B00110000 | data;
  SPI.transfer (data); 
  data = lowByte(value);
  SPI.transfer (data); 
  digitalWrite(CS_DAC, HIGH);
}


int x_n_1=0; //x[n-1]=0; <<valor inicial do output
int u_n; //u[n] << input
int x_n; //x[n] output
int u_n_1; // valor anterior do input

int SISO_1(int u_n_b){
  
  //mapeamento para ficar à escala
  u_n=map(u_n_b , 0 , 1023, 0, 5000);
  x_n=0.2*u_n+0.2*u_n_1+0.6*x_n_1;
  //mapeamento do output
  int x_n_b= map(x_n, 0 , 5000 , 0 , 4095);
  x_n_1=x_n;
  u_n_1=u_n;

    return x_n_b;

}


void loop() {
  
//works
  int u_n_b=analogRead(A0);
  int x_n_b=SISO_1(u_n_b);
  analogOut(x_n_b);
  delay(0.5);

  
}


