// VARIABLES GLOBALES
static unsigned int pulsos_1 = 0;
static unsigned int pulsos_2 = 0;

unsigned int caudal_1 = 0;
unsigned int caudal_2 = 0;

unsigned int v1 = 0;
unsigned int v2 = 0;
unsigned int presion_1 = 0;
unsigned int presion_2 = 0;

// VARIABLES AUXILIARES
char dato = 0;
int conv = 0;
unsigned char numeros[2] = {0, 0};      // HIGH RAW - LOW RAW

// MODO PRUEBA 
unsigned int presion_1t = 412;
unsigned int presion_2t = 313;
unsigned int v1t = 15;
unsigned int v2t = 30;
unsigned int caudal_1t = 120;
unsigned int caudal_2t = 600;

void setup() 
{
  pinMode(13, OUTPUT);
  TCCR1A = 0B00000000;    // MODO CTC 
  OCR1A = 62499;          // PARA BASETIME DE 1HZ
  TCCR1B = 0B00001100;    

  TIMSK1 = 0B00000010;

  EICRA = 0B00001010;
  EIMSK = 0B00000011;

  sei();

  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() 
{ 
  conv = analogRead(A0);
  presion_1 = (-100 + conv);
  
  conv = analogRead(A1);
  presion_2 = (-100 + conv);

  if (Serial.available())
  {
    dato = Serial.read();

    if (dato == 'A')
    {
      convertir_format(presion_1t);
      Serial.write(numeros, 2);
      convertir_format(presion_2t);
      Serial.write(numeros, 2);
      convertir_format(caudal_1t);
      Serial.write(numeros, 2);
      convertir_format(caudal_2t);
      Serial.write(numeros, 2);
      
      digitalWrite(13, HIGH);
    }

    if (dato == 'B')
    {
      convertir_format(presion_1t);
      Serial.write(numeros, 2);
      convertir_format(presion_2t);
      Serial.write(numeros, 2);
      convertir_format(caudal_1t);
      Serial.write(numeros, 2);
      convertir_format(caudal_2t);
      Serial.write(numeros, 2);
      
      digitalWrite(13, LOW);
    }
  }
}

void convertir_format(int a)
{
   numeros[0] = (unsigned char) (a >> 8);               // HIGH RAW
   numeros[1] = (unsigned char) (a - (numeros[0] << 8));  // LOW RAW
}

ISR (TIMER1_COMPA_vect)
{
  //caudal_1 = (-14.861 + 7.777 * pulsos_1);    // Ec. de regresion lineal sensor yf-s201
  caudal_1 = (7.5 * pulsos_1);    // Ec. de datasheet lineal sensor yf-s201
  caudal_2 = (pulsos_2 * 0.6122);             // Ec. de datasheet sensor yf-s401 en l/h

  v1 = pulsos_1;
  v2 = pulsos_2;
  
  pulsos_1 = 0;
  pulsos_2 = 0;
}

ISR (INT0_vect)
{
  pulsos_1++;
}

ISR (INT1_vect)
{
  pulsos_2++;
}
