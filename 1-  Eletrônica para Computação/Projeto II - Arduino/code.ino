//Inclusão de Bibliotecas:
#include <Ultrasonic.h>
#include <VarSpeedServo.h>

//Definição de Macros para Pinagem:
#define irsensor 2 //pino de sinal do sensor de obstáculos ir
#define trig 3 //hcsr04 trig (sensor ultrassônico)
#define echo 4 //hcsr04 echo (sensor ultrasônico)
#define enA 5 //enable A da Ponte H (habilitador de controle de velocidade dos motores da direita)
#define in1 6 //pin1 A da ponte H ("positivo" dos motores da direita)
#define in2 7 //pin2 A da ponte H ("negativo" dos motores da direita)
#define in3 9 //pin1 B da ponte H ("positivo" dos motores da esquerda)
#define in4 10 //pin2 B da ponte H ("negativo" dos motores da esquerda)
#define enB 11 //enable B (habilitador de controle de velocidade dos motores da esquerda)
#define preceiver 12 //pino de sinal do receptor do sensor infraverlho (para o controle remoto)
#define pservo 8 //pino de sinal (amarelo) do servo motor

//Definição de Macros para damais Constantes:
#define CAR_SPEED 100
#define STRAIGHT_ANGLE 85
#define LEFT_ANGLE 179
#define RIGHT_ANGLE 0
#define SAFE_DISTANCE 12

//Instanciação de Objetos:
Ultrasonic mydistsensor(trig, echo);
VarSpeedServo myservo; 

//Protótipos de Funções Complementares:
void findBestAngle();
void rotate();
void turnOnMotors(char direct);
void turnOffMotors();

void setup() {
  //Definição do Modo (entrada ou saída) de Cada Pino:
  pinMode(irsensor, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(pservo, OUTPUT);

  //Determinação do posicionamento inicial do Servo Motor:
  myservo.attach(pservo);
  myservo.slowmove(STRAIGHT_ANGLE, 50);

  //Determinação da Velocidade do Carro:
  analogWrite(enA, CAR_SPEED);
  analogWrite(enB, CAR_SPEED);
  
  //Pausa para Início do Programa:  
  delay(1000);
}

//Declaração e Inicialização de Variáveis Globais:
int distance = 0;
int bestAngle = 85;
char bestDirect = 'F';

void loop(){
  //Acionamento do motor para frente, caso essa seja a melhor direção:
  if(bestDirect == 'F') turnOnMotors('F');

  //Cálculo da Distância em 'cm' lida pelo Sensor Ultrasônico:
  distance = mydistsensor.Ranging(CM); 

  //Verificaçao da possibilidade de colisão frontal:
  if(!digitalRead(irsensor) ||  distance < SAFE_DISTANCE){ //se a distância for pequena:  
    turnOnMotors('B'); //a marcha ré é acionada
    turnOffMotors(); //os motores são desligados
    
    rotate(); //o carro encontra a melhor direção e rotaciona
  } 
}

void turnOnMotors(char direct){
  switch(direct){
    case 'F': //"Front"
      //Polarização Direta de ambos os Motores:
      digitalWrite(in1, HIGH);  
      digitalWrite(in2, LOW);
      digitalWrite(in3,HIGH);  
      digitalWrite(in4, LOW);
      delay(50);      
      break;
    case 'B': //"Back"
      //Polarização Inversa de ambos os Motores:
      digitalWrite(in1, LOW);  
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);  
      digitalWrite(in4, HIGH);
      delay(600);
      break;
    case 'L': //"Left"
      //"Travamento" da Roda da Esquerda para que o carro vire em sua direção
      digitalWrite(in1, HIGH);  
      digitalWrite(in2, LOW);
      digitalWrite(in3,HIGH);  
      digitalWrite(in4, HIGH);
      delay(1500);
      break;
    case 'R': //"Right"
      //"Travamento" da Roda da Direita para que o carro vire em sua direção
      digitalWrite(in1, HIGH);  
      digitalWrite(in2, HIGH);
      digitalWrite(in3,HIGH);  
      digitalWrite(in4, LOW);
      delay(1500);
      break;
  }
}

void turnOffMotors(){
  //Travamento de todas as Rodas:
  digitalWrite(in1, HIGH);  
  digitalWrite(in2, HIGH);
  digitalWrite(in3,HIGH);  
  digitalWrite(in4, HIGH);
  delay(50);
}

void rotate(){
  //Determinação da Melhor Direção:
  findBestDirection();

  //Leitura da distância detectada pelo Sensor Ultrasônico:
  double curDistance = mydistsensor.Ranging(CM);

  switch(bestDirect){
    case 'R': //Se a melhor direção for "Right" (direita):
      turnOnMotors('R'); //o carro gira para a direita
      while(curDistance < SAFE_DISTANCE * 3 || !digitalRead(irsensor)) curDistance = mydistsensor.Ranging(CM);
      break;
    case 'L': //Se a melhor direção for "Left" (esquerda):
      turnOnMotors('L'); //o carro gira para a esquerda
      while(curDistance < SAFE_DISTANCE * 3 || !digitalRead(irsensor)) curDistance = mydistsensor.Ranging(CM);
      break;
    default:
      break;
  }

  //Após a rotação, a melhor direção volta a ser a frontal:
  bestDirect = 'F';
}

void findBestDirection(){
  //Declaração e Inicialização das variáveis que guardarão as distâncias lidas na esquerda e na direita:
  double leftDist = 0, rightDist = 0;

  //Giro do servo para a Esquerda e leitura da distância:
  myservo.slowmove(LEFT_ANGLE, 50);
  delay(2000);
  leftDist = mydistsensor.Ranging(CM); 

  //Giro do servo para a Direita e leitura da distância:
  myservo.slowmove(RIGHT_ANGLE, 50);
  delay(3000);
  rightDist = mydistsensor.Ranging(CM); 

  //Giro do servo para a posição reta (frontal):
  myservo.slowmove(STRAIGHT_ANGLE, 50);
  delay(1000);

  //Atribuição da melhor direção (a de maior distância):
  bestDirect = (leftDist > rightDist) ? 'L' : 'R';
}
