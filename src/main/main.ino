static int pulsos_1 = 0;
static int pulsos_2 = 0;

int caudal_1 = 0;
int caudal_2 = 0;

int conv = 0;

int presion_1 = 0;
int presion_2 = 0;

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
}

void loop() 
{
  _delay_ms(1000);
  
  conv = analogRead(A0);
  presion_1 = (-100 + conv);
  
  conv = analogRead(A1);
  presion_2 = (-100 + conv);

  Serial.print("caudal 1: ");
  Serial.println(caudal_1);
  Serial.print("caudal 2: ");
  Serial.println(caudal_2);

  Serial.print("presion 1: ");
  Serial.println(presion_1);
  Serial.print("presion 2: ");
  Serial.println(presion_2);
}

ISR (TIMER1_COMPA_vect)
{
  caudal_1 = (-14.861 + 7.777 * pulsos_1);
  caudal_2 = (-14.861 + 7.777 * pulsos_2);

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
