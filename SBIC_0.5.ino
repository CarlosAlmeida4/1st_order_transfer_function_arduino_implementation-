#include <SPI.h>
#define CS_SISO_1 9
#define CS_SISO_2 8
#define CS_SISO_3 7

//Amostragem em MiliSegundos
int Ts=1;

void setup() {


  pinMode(CS_SISO_1,OUTPUT);
  pinMode(CS_SISO_2,OUTPUT);
  pinMode(CS_SISO_3,OUTPUT);
  digitalWrite(CS_SISO_1,HIGH);
  digitalWrite(CS_SISO_2,HIGH);
  digitalWrite(CS_SISO_3,HIGH);
  
  
  SPI.begin();
  //Velocidade das comms SPI maxima é 0.125 microsegundos
  SPI.setClockDivider(SPI_CLOCK_DIV2);

  
  
}

void analogOut(int value,int CS) {
  byte data;
  digitalWrite(CS, LOW);
  data = highByte(value);
  data = B00001111 & data;
  data = B00110000 | data;
  SPI.transfer (data); 
  data = lowByte(value);
  SPI.transfer (data); 
  digitalWrite(CS, HIGH);
}

/*  
 *   Sistema 1 
 */
int x1_n_1=0; //x[n-1]=0; <<valor inicial do output
int u1_n_1; // valor anterior do input

int SISO_1(int u_n_b){

  int x_n_1=0; //x[n-1]=0; <<valor inicial do output
  int x_n; //x[n] output
  
  //mapeamento para ficar à escala
  int u_n=map(u_n_b , 0 , 1023, 0, 5000);//u[n] << input
  x_n=0.1351*u_n+0.1351*u1_n_1+0.7297*x1_n_1;
  //mapeamento do output
  int x_n_b= map(x_n, 0 , 5000 , 0 , 4095);
  x1_n_1=x_n;
  u1_n_1=u_n;

  return x_n_b;
}

/*  
 *   Sistema 2 
 */
int x2_n_1=0; //x[n-1]=0; <<valor inicial do output
int u2_n_1; // valor anterior do input

int SISO_2(int u_n_b){

  int x_n_1=0; //x[n-1]=0; <<valor inicial do output
  int x_n; //x[n] output
  
  //mapeamento para ficar à escala
  int u_n=map(u_n_b , 0 , 1023, 0, 5000);//u[n] << input
  x_n=0.09091*u_n+0.09091*u2_n_1+0.8182*x2_n_1;
  //mapeamento do output
  int x_n_b= map(x_n, 0 , 5000 , 0 , 4095);
  x2_n_1=x_n;
  u2_n_1=u_n;

  return x_n_b;
}




void loop() {
  

//works
  int u1_n_b=analogRead(A0);
  int x1_n_b=SISO_1(u1_n_b);
  analogOut(x1_n_b,CS_SISO_1);
  
  int u2_n_b=analogRead(A0);
  int x2_n_b=SISO_2(u2_n_b);
  analogOut(x2_n_b,CS_SISO_2);

  delay(Ts);
  
}


