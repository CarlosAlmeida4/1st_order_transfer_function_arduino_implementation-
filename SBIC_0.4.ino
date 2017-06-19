#include <SPI.h>
#define CS_DAC 9

int sensor_value =0;
int output_value=0;

/*
 * O sistema de primeira ordem é tratado como um filtro RC de 1ªOrdem
 */
//int R=1600;
//int C=0.000002;
//int Ts=0.0005;
//int Vmax=5;


void setup() {

  Serial.begin(9600);


//Inicialização Timer 2 8 bits
//  noInterrupts();
//  TCCR2A= 0;
//  TCCR2B=0; 
//  TCNT2=6; // Carregar o temporizador  com o offset 
//  TCCR2B = (0<<CS22) | (1<<CS20)| (1<<CS21);
//  TIMSK2 |= (1 << TOIE2);
//  interrupts(); 

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

/*  
 *   Sistema 1 
 */
int x_n_1=0; //x[n-1]=0; <<valor inicial do output
int u_n; //u[n] << input
int x_n; //x[n] output
int u_n_1; // valor anterior do input
/*  
 *   Sistema 2 
 */
int x_n_1b=0; //x[n-1]=0; <<valor inicial do output
int u_nb; //u[n] << input
int x_nb; //x[n] output
int u_n_1b; // valor anterior do input


int SISO_1(int u_n_b){
  
  //mapeamento para ficar à escala
  u_n=map(u_n_b , 0 , 1023, 0, 5000);
  x_n=0.2*u_n+0.2*u_n_1+0.6*x_n_1;
  //mapeamento do output
  int x_n_b= map(x_n, 0 , 5000 , 0 , 4095);
  x_n_1=x_n;
  u_n_1=u_n;

return x_n_b;

int SISO_2(int u_n_b2){
  
  //mapeamento para ficar à escala
  5u_nb=map(u_n_b2 , 0 , 1023, 0, 5000);
  x_nb=0.07246*u_nb+0.07246*u_n_1b+0.8551*x_n_1b;
  //mapeamento do output
  int x_n_b2= map(x_nb, 0 , 5000 , 0 , 4095);
  x_n_1b=x_n;
  u_n_1b=u_n;

return x_n_b2;

//  Serial.print("\n Entrada Analogica = ");
//  Serial.print(u_n_b);
//  Serial.print("\t Entrada mapeada = ");
//  Serial.print(u_n);
//  Serial.print("\t Output = ");
//  Serial.print(x_n);
//  Serial.print("\t output mapeada = ");
//  Serial.print(x_n_b);
  
}


void loop() {
  
//  sensor_value=analogRead(A0);
//  output_value=map(sensor_value, 0 , 1023, 0, 4095);
//  analogOut(output_value);
//  Serial.print("\n Entrada Analogica= ");
//  Serial.print(sensor_value);
//  Serial.print("\t Ouptput PWM=  ");
//  Serial.print(output_value);

//works
  int u_n_b=analogRead(A0);
  int u_n_b2=analogRead(A1);
  int x_n_b=SISO_1(u_n_b);
  int x_n_b2=SISO_2(u_n_b2);
  analogOut(x_n_b);
  analogOut(x_n_b2);
  delay(0.5);

//  TCNT2=6;
//  u_n_1=analogRead(A0);
//  while(1){
//    
//  }

  
}


