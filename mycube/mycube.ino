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
}

void layer(int layer)
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
    layer(1);
    show_all_led_single();
    layer(2);
    show_all_led_single();
    layer(3);
    show_all_led_single();
  }
}

void show_layers_seperate()
{
  layer(1);
  show_complete_layer();
  delay(200);
  layer(2);
  delay(300);
  layer(3);
  delay(400);
  layer(2);
  delay(500);
  layer(1);
}

void multiplex_show()
{
  int i;
  for(i=0;i<333;i++)
  {
    layer(1);
    delay(1);
    layer(0);
    delay(1);
    layer(0);
    delay(1);
  }
  for(i=0;i<333;i++)
  {
    layer(1);
    delay(1);
    layer(2);
    delay(1);
    layer(0);
    delay(1);
  }
  for(i=0;i<333;i++)
  {
    layer(1);
    delay(1);
    layer(2);
    delay(1);
    layer(3);
    delay(1);
  }
  for(i=0;i<333;i++)
  {
    layer(2);
    delay(1);
    layer(3);
    delay(1);
    layer(0);
    delay(1);
  }
  for(i=0;i<333;i++)
  {
    layer(0);
    delay(1);
    layer(3);
    delay(1);
    layer(0);
    delay(1);
  }
  layer(3);
  delay(1000);  
}

void loop() {
  // put your main code here, to run repeatedly:
  single_movement();
  show_layers_seperate();
  delay(1000);
  multiplex_show();
}
