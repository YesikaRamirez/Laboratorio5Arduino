/*LABORATORIO5
Autores:Yesika Ramirez - Ashley Romero
Valor Carnet: 2138
Valor de Resistencia: 534.5*/
class Modo1P
{
 private:
  //Declaración de los pines de los LED
  int i;
  byte D3=7; //D3
  byte D2=6; //D2
  byte D1=5; //D1
  byte D0=4; //D0
  //Declaración de los DIPSWTICH
  byte S3=13; 
  byte S2=12;
  byte S1=11; 
  byte S0=10;
 public:
  void AsignaSW()
  {//Configura los Pines digitales como SALIDAS
    for(i=S0;i<=S3;i++)
    {
      pinMode(i,INPUT);
    }
   pinMode(D3,OUTPUT);
   pinMode(D2,OUTPUT);
   pinMode(D1,OUTPUT);
   pinMode(D0,OUTPUT);
  }
  void Encender()
    {
    while (digitalRead(S3) == LOW)
    {
      digitalWrite(D3,LOW); //Apaga  el LED MODO1 
      if (digitalRead(S2) == LOW)
      {
        digitalWrite(D2,LOW);
      }else{
        digitalWrite(D2,HIGH);
      }
      if (digitalRead(S1) == LOW)
      {
        digitalWrite(D1,LOW);
      }else{
        digitalWrite(D1,HIGH);
      }
      if (digitalRead(S0) == LOW)
      { 
        digitalWrite(D0,LOW);
      }else{
        
        digitalWrite(D0,HIGH);
      }
      }
    }
  };//Cierro la clase
class Modo2AR
{
  private:
  //Declaración de los pines de los LED
  byte D3=7; //D3
  byte D2=6; //D2
  byte D1=5; //D1
  byte D0=4; //D0   
  //Declaración de los DIPSWTICH
  byte S3=13; 
  byte S2=12;
  byte S1=11; 
  byte S0=10;
  float poten;
  float toleran=0;
  float limsup=0;
  float liminfe=0;
  float valorefe=534.5;
  
 
  public:
  void Asignador()
  {//Configura los Pines digitales como SALIDAS
   pinMode(A1,INPUT);
  }
  float leerpoten()
  {
    while (digitalRead(S3) == HIGH) //Modo Analog Reference
  {
      digitalWrite(D3,HIGH); //ENCIENDE  el LED MODO2;
      poten=analogRead(A1); //asignacion de la variable a la entrada analogica
        tolerancia();
        comparar();
        return (poten);
        
    }
    
  }
  void tolerancia()
  { //Se concatenan los valores de s2 s1 y s0 para hallar el valor de la tolerancia
    toleran = (digitalRead(S2)<<2) + (digitalRead(S1)<<1) + (digitalRead(S0));
  }  
  void comparar()
  { //Se calculan los limites superior e inferior
    limsup= valorefe + ((valorefe*toleran)/100); 
    liminfe=valorefe -((valorefe*toleran)/100);
    //si esta dentro del rango
    if(poten < limsup && poten > liminfe)
    {
      digitalWrite(D1,HIGH);//SE ENCIENDE D1
      digitalWrite(D2,LOW);
      digitalWrite(D0,LOW);
    }
    //si supera el rango superior
    if(poten > limsup)
    {
      digitalWrite(D2,HIGH); //SE ENTIENDE D2
      digitalWrite(D1,LOW);
      digitalWrite(D0,LOW);
    }
    //si  el rango inferior
    if(poten < liminfe)
    {
      digitalWrite(D0,HIGH);//SE ENCIENDE D0
      digitalWrite(D2,LOW);
      digitalWrite(D1,LOW);
    
    }
      
  }
};
Modo1P mood1;
Modo2AR mood2;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  mood1.AsignaSW();
  mood1.Encender();
  mood2.Asignador();
  mood2.leerpoten(); 
  delay(1000);
}
