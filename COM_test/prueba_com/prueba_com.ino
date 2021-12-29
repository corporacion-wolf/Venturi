char dato = 0;

unsigned int p1 = 412;
unsigned int p2 = 313;

unsigned int f1 = 42;
unsigned int f2 = 125;

int aux = 0;

unsigned char numeros[2] = {0, 0};      // HIGH RAW - LOW RAW

void setup() 
{
  Serial.begin(9600);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() 
{
  if (Serial.available())
  {
    dato = Serial.read();

    if (dato == 'A')
    {
      convertir_format(p1);
      Serial.write(numeros, 2);
      convertir_format(p2);
      Serial.write(numeros, 2);
      convertir_format(f1);
      Serial.write(numeros, 2);
      convertir_format(f2);
      Serial.write(numeros, 2);
      
      digitalWrite(13, HIGH);
    }

    if (dato == 'B')
    {
      convertir_format(p1);
      Serial.write(numeros, 2);
      convertir_format(p2);
      Serial.write(numeros, 2);
      convertir_format(f1);
      Serial.write(numeros, 2);
      convertir_format(f2);
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
