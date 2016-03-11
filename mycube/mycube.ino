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
  }
}



void setup() {
  // put your setup code here, to run once:
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

void show_all_led_single()
{
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
  digitalWrite(LED8, LOW);
  digitalWrite(LED9, LOW);
  digitalWrite(LED1, HIGH);
  delay(100);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(100);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, HIGH);
  delay(100);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, HIGH);
  delay(100);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, HIGH);
  delay(100);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, HIGH);
  delay(100);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, HIGH);
  delay(100);
  digitalWrite(LED7, LOW);
  digitalWrite(LED8, HIGH);
  delay(100);
  digitalWrite(LED8, LOW);
  digitalWrite(LED9, HIGH);
  delay(100);
}

void show_complete_layer()
{
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, HIGH);
  digitalWrite(LED6, HIGH);
  digitalWrite(LED7, HIGH);
  digitalWrite(LED8, HIGH);
  digitalWrite(LED9, HIGH);
}

void single_movement()
{
  int i;
  // put your main code here, to run repeatedly:
  for(i=0;i<3;i++)
  {
    switch_layer(1);
    show_all_led_single();
    switch_layer(2);
    show_all_led_single();
    switch_layer(3);
    show_all_led_single();
  }
}

void show_layers_seperate()
{
  switch_layer(1);
  show_complete_layer();
  delay(200);
  switch_layer(2);
  delay(300);
  switch_layer(3);
  delay(400);
  switch_layer(2);
  delay(500);
  switch_layer(1);
}

void multiplex_show()
{
  int i;
  for(i=0;i<333;i++)
  {
    switch_layer(1);
    delay(1);
    switch_layer(0);
    delay(1);
    switch_layer(0);
    delay(1);
  }
  for(i=0;i<333;i++)
  {
    switch_layer(1);
    delay(1);
    switch_layer(2);
    delay(1);
    switch_layer(0);
    delay(1);
  }
  for(i=0;i<333;i++)
  {
    switch_layer(1);
    delay(1);
    switch_layer(2);
    delay(1);
    switch_layer(3);
    delay(1);
  }
  for(i=0;i<333;i++)
  {
    switch_layer(2);
    delay(1);
    switch_layer(3);
    delay(1);
    switch_layer(0);
    delay(1);
  }
  for(i=0;i<333;i++)
  {
    switch_layer(0);
    delay(1);
    switch_layer(3);
    delay(1);
    switch_layer(0);
    delay(1);
  }
  switch_layer(3);
  delay(1000);  
}

void loop() {
  // put your main code here, to run repeatedly:
  single_movement();
  show_layers_seperate();
  delay(1000);
  multiplex_show();
}
