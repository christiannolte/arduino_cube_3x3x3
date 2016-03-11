#define L1 3
#define L2 2
#define L3 13

#define LED1 10
#define LED2 7
#define LED3 6
#define LED4 11
#define LED5 9 
#define LED6 5
#define LED7 12
#define LED8 8
#define LED9 4


unsigned char pwm;
unsigned char layer;
unsigned char counter;
unsigned char speed;
unsigned char updateFrame=0;

unsigned char cube[3][3][3];


// Timer 1 output compare A interrupt service routine.
// Determines when new frame is generated.
ISR(TIMER1_COMPA_vect){
  counter++;
  if(counter >= speed){        
    counter = 0;
    if (updateFrame == 0){
      updateFrame = 1;
    }
  }  
}

// Timer 2 output compare interrupt service routine.
// Controls layer multiplexing and PWM.
ISR(TIMER2_COMPA_vect){
  // PWM current layer. count 0-15 
  // Then change layer. count 0-8
  pwm++;
  if(pwm >= 15){
    pwm = 0;
     
    layer++;
    if(layer >= 3){
      layer = 0;
    }
    switch_layer(layer+1);
  }
  //Do all the hard work here
  if(cube[0][0][layer]>pwm)  
        digitalWrite(LED1, HIGH);
  else   
        digitalWrite(LED1, LOW);
        
  if(cube[1][0][layer]>pwm)  
        digitalWrite(LED2, HIGH);
  else   
        digitalWrite(LED2, LOW);
  
  if(cube[2][0][layer]>pwm)  
        digitalWrite(LED3, HIGH);
  else   
        digitalWrite(LED3, LOW);
  
  if(cube[0][1][layer]>pwm)  
        digitalWrite(LED4, HIGH);
  else   
        digitalWrite(LED4, LOW);

  if(cube[1][1][layer]>pwm)  
        digitalWrite(LED5, HIGH);
  else   
        digitalWrite(LED5, LOW);

  if(cube[2][1][layer]>pwm)  
        digitalWrite(LED6, HIGH);
  else   
        digitalWrite(LED6, LOW);

  if(cube[0][2][layer]>pwm)  
        digitalWrite(LED7, HIGH);
  else   
        digitalWrite(LED7, LOW);

  if(cube[1][2][layer]>pwm)  
        digitalWrite(LED8, HIGH);
  else   
        digitalWrite(LED8,LOW);

  if(cube[2][2][layer]>pwm)  
        digitalWrite(LED9, HIGH);
  else   
        digitalWrite(LED9, LOW);
}

void komplett(unsigned char value,int mydelay)
{
  unsigned char i,j,k;
  for(i=0;i<3;i++)
     for(j=0;j<3;j++)
        for(k=0;k<3;k++)
        {
          cube[k][j][i]=value;
          delay(mydelay);
        }
}


void fade2off(int mydelay)
{
  int i,j,k,n;
  for(n=15;n>=0;n--)
  {
     for(i=0;i<3;i++)
     {
       for(j=0;j<3;j++)
       {
        for(k=0;k<3;k++)
        {
           if(cube[i][j][k]>n)cube[i][j][k]=n;
   
        }
      }
    }
    delay(mydelay);
 }
}

void fade2on(int mydelay)
{
  int i,j,k,n;
  for(n=0;n<=15;n++)
  {
     for(i=0;i<3;i++)
     {
       for(j=0;j<3;j++)
       {
        for(k=0;k<3;k++)
        {
           if(cube[i][j][k]<n)cube[i][j][k]=n;
   
        }
      }
    }
    delay(mydelay);
 }
}

void fade(int delay)
{
  komplett(0,0);
  fade2on(delay);
  fade2off(delay);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  pinMode(LED9, OUTPUT);
  digitalWrite(L1, HIGH);
  digitalWrite(L2, HIGH);
  digitalWrite(L3, HIGH);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
  digitalWrite(LED8, LOW);
  digitalWrite(LED9, LOW);

  // Timer/Counter 1 initialization (~10 Hz)
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 1562;// = (16*10^6) / (10*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  // Timer/Counter 2 initialization (~7 kHz)
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 8khz increments
  OCR2A = 8;// = (16*10^6) / (7000*256) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS21 bit for 256 prescaler
  TCCR2B |= (1<<CS22) | (1 << CS21);   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  interrupts();
}

void switch_layer(int layer)
{
  digitalWrite(L1, HIGH);
  digitalWrite(L2, HIGH);
  digitalWrite(L3, HIGH);
  if(layer==1)   digitalWrite(L1, LOW);
  if(layer==2)   digitalWrite(L2, LOW);
  if(layer==3)   digitalWrite(L3, LOW);
}


void flash(int mydelay)
{
  komplett(15,0);
  delay(mydelay);
  komplett(0,0);
  delay(mydelay);
}

void random_behavior_soft(int duration,int mydelay)
{
  int i;
  komplett(0,0);
  for(i=0;i<duration;i++)
  {
    cube[random(0,3)][random(0,3)][random(0,3)]=random(0,15);
    delay(mydelay);
  }
}

void random_behavior_hard(int duration,int mydelay)
{
  int i;
  komplett(0,0);
  for(i=0;i<duration;i++)
  {
    cube[random(0,3)][random(0,3)][random(0,3)]=15*random(0,2);
    delay(mydelay);
  }
}

void single_led(int mydelay)
{
  unsigned char i,j,k;
  for(i=0;i<3;i++)
     for(j=0;j<3;j++)
        for(k=0;k<3;k++)
        {
          komplett(0,0);
          cube[k][j][i]=15;
          delay(mydelay);
        }
  komplett(0,0);
}

void seiten(int mydelay)
{
  komplett(0,0);
  cube[0][0][0]=15;
  cube[0][1][0]=15;
  cube[0][2][0]=15;
  cube[0][0][1]=15;
  cube[0][1][1]=15;
  cube[0][2][1]=15;
  cube[0][0][2]=15;
  cube[0][1][2]=15;
  cube[0][2][2]=15;
  delay(mydelay);
  komplett(0,0);
  cube[1][0][0]=15;
  cube[1][1][0]=15;
  cube[1][2][0]=15;
  cube[1][0][1]=15;
  cube[1][1][1]=15;
  cube[1][2][1]=15;
  cube[1][0][2]=15;
  cube[1][1][2]=15;
  cube[1][2][2]=15;
  delay(mydelay);
  komplett(0,0);
  cube[2][0][0]=15;
  cube[2][1][0]=15;
  cube[2][2][0]=15;
  cube[2][0][1]=15;
  cube[2][1][1]=15;
  cube[2][2][1]=15;
  cube[2][0][2]=15;
  cube[2][1][2]=15;
  cube[2][2][2]=15;
  delay(mydelay);
}

void etagen(int mydelay)
{
  komplett(0,0);
  cube[0][0][0]=15;
  cube[1][0][0]=15;
  cube[2][0][0]=15;
  cube[0][1][0]=15;
  cube[1][1][0]=15;
  cube[2][1][0]=15;
  cube[0][2][0]=15;
  cube[1][2][0]=15;
  cube[2][2][0]=15;
  delay(mydelay);
  komplett(0,0);
  cube[0][0][1]=15;
  cube[1][0][1]=15;
  cube[2][0][1]=15;
  cube[0][1][1]=15;
  cube[1][1][1]=15;
  cube[2][1][1]=15;
  cube[0][2][1]=15;
  cube[1][2][1]=15;
  cube[2][2][1]=15;
  delay(mydelay);
  komplett(0,0);
  cube[0][0][2]=15;
  cube[1][0][2]=15;
  cube[2][0][2]=15;
  cube[0][1][2]=15;
  cube[1][1][2]=15;
  cube[2][1][2]=15;
  cube[0][2][2]=15;
  cube[1][2][2]=15;
  cube[2][2][2]=15;
  delay(mydelay);
}

void tiefen(int mydelay)
{
  komplett(0,0);
  cube[0][2][0]=15;
  cube[1][2][0]=15;
  cube[2][2][0]=15;
  cube[0][2][1]=15;
  cube[1][2][1]=15;
  cube[2][2][1]=15;
  cube[0][2][2]=15;
  cube[1][2][2]=15;
  cube[2][2][2]=15;
  delay(mydelay);
  komplett(0,0);
  cube[0][1][0]=15;
  cube[1][1][0]=15;
  cube[2][1][0]=15;
  cube[0][1][1]=15;
  cube[1][1][1]=15;
  cube[2][1][1]=15;
  cube[0][1][2]=15;
  cube[1][1][2]=15;
  cube[2][1][2]=15;
  delay(mydelay);
  komplett(0,0);
  cube[0][0][0]=15;
  cube[1][0][0]=15;
  cube[2][0][0]=15;
  cube[0][0][1]=15;
  cube[1][0][1]=15;
  cube[2][0][1]=15;
  cube[0][0][2]=15;
  cube[1][0][2]=15;
  cube[2][0][2]=15;
  delay(mydelay);
  
}

void etage2seite(int mydelay)
{
  komplett(0,0);
  cube[0][0][2]=15;
  cube[1][0][2]=15;
  cube[2][0][2]=15;
  cube[0][1][2]=15;
  cube[1][1][2]=15;
  cube[2][1][2]=15;
  cube[0][2][2]=15;
  cube[1][2][2]=15;
  cube[2][2][2]=15;
  delay(mydelay);
  komplett(0,0);
  cube[0][0][2]=15;
  cube[0][1][2]=15;
  cube[0][2][2]=15;
  cube[1][0][1]=15;
  cube[1][1][1]=15;
  cube[1][2][1]=15;
  cube[2][0][0]=15;
  cube[2][1][0]=15;
  cube[2][2][0]=15;
  delay(mydelay);
  komplett(0,0);
  cube[0][0][0]=15;
  cube[0][1][0]=15;
  cube[0][2][0]=15;
  cube[0][0][1]=15;
  cube[0][1][1]=15;
  cube[0][2][1]=15;
  cube[0][0][2]=15;
  cube[0][1][2]=15;
  cube[0][2][2]=15;
  delay(mydelay);
}

void seiten2tiefen(int mydelay)
{
  komplett(0,0);
  cube[2][0][0]=15;
  cube[2][1][0]=15;
  cube[2][2][0]=15;
  cube[2][0][1]=15;
  cube[2][1][1]=15;
  cube[2][2][1]=15;
  cube[2][0][2]=15;
  cube[2][1][2]=15;
  cube[2][2][2]=15;
  delay(mydelay);
  komplett(0,0);
  cube[2][2][0]=15;
  cube[2][2][1]=15;
  cube[2][2][2]=15;
  cube[0][0][0]=15;
  cube[0][0][1]=15;
  cube[0][0][2]=15;
  cube[1][1][0]=15;
  cube[1][1][1]=15;
  cube[1][1][2]=15;
  delay(mydelay);
  komplett(0,0);
  cube[0][2][0]=15;
  cube[1][2][0]=15;
  cube[2][2][0]=15;
  cube[0][2][1]=15;
  cube[1][2][1]=15;
  cube[2][2][1]=15;
  cube[0][2][2]=15;
  cube[1][2][2]=15;
  cube[2][2][2]=15;
  delay(mydelay);
}

void tiefen2etage(int mydelay)
{
  komplett(0,0);
  cube[0][0][0]=15;
  cube[1][0][0]=15;
  cube[2][0][0]=15;
  cube[0][0][1]=15;
  cube[1][0][1]=15;
  cube[2][0][1]=15;
  cube[0][0][2]=15;
  cube[1][0][2]=15;
  cube[2][0][2]=15;
  delay(mydelay);
  komplett(0,0);
  cube[0][0][0]=15;
  cube[1][0][0]=15;
  cube[2][0][0]=15;
  cube[0][1][1]=15;
  cube[1][1][1]=15;
  cube[2][1][1]=15;
  cube[0][2][2]=15;
  cube[1][2][2]=15;
  cube[2][2][2]=15;
  delay(mydelay);
  komplett(0,0);
  cube[0][0][0]=15;
  cube[1][0][0]=15;
  cube[2][0][0]=15;
  cube[0][1][0]=15;
  cube[1][1][0]=15;
  cube[2][1][0]=15;
  cube[0][2][0]=15;
  cube[1][2][0]=15;
  cube[2][2][0]=15;
  delay(mydelay);
  
}

void fold(int mydelay)
{
  etagen(2*mydelay);
  etage2seite(mydelay);
  seiten(2*mydelay);
  seiten2tiefen(mydelay);
  tiefen(2*mydelay);
  tiefen2etage(mydelay);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i;
  single_led(150);
  single_led(150);
  komplett(15,150);
  komplett(0,150);
  random_behavior_hard(1000,10);
  komplett(0,0);
  fold(150);
  fold(150);
  fold(150);
  fold(150);
  for (i=0;i<10;i++)flash(100);
  fade2on(100);
  fade2off(100);
  for(i=1;i<10;i++)fade(i*10);
  fade(100);
  fade(100);
  random_behavior_soft(100,100);
  fade2off(200);
  for (i=0;i<10;i++)fade(20);
}
