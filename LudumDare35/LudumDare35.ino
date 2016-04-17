#include "WS2812.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

//Variables
//byte RGB[768];//take your number of LEDs and multiply by 3
byte RGB[768] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte A[126] = {0,0,0,0,0,0,0,25,0,0,25,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,25,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,25,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,0,0,25,0,0,25,0,0,25,0,0,25,0,0,0,0,0,25,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,25,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0};
int count = 0;
int count2 = 0;
Color color;
Player player;
Player player2;
Bullet testBullet, b2, b3,b4;

//Initialization
void setup() 
{  
  byte player1Mask[25] =  {0, 0, 1, 0, 0, 
                           0, 1, 1, 1, 0,
                           1, 1, 0, 1, 1,
                           0, 1, 1, 1, 0,
                           0, 0, 1, 0, 0};
  byte player2Mask[25] =  {0, 0, 1, 0, 0, 
                           0, 1, 1, 1, 0,
                           1, 1, 0, 1, 1,
                           0, 1, 1, 1, 0,
                           0, 0, 1, 0, 0};
                           
  pinMode(WS2812_pin, OUTPUT);
  
  Serial.begin(9600);
  // initialize Timer1
  cli();          // disable global interrupts
  TCCR1A = 0;     // set entire TCCR1A register to 0
  TCCR1B = 0;     // same for TCCR1B

  // set compare match register to desired timer count:
  OCR1A = 261;//651;
  // turn on CTC mode:
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler:
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);
  // enable timer compare interrupt:
  TIMSK1 |= (1 << OCIE1A);
  // enable global interrupts:
  sei();
  color.longColor = 0x00100000;
  player.x = 10;
  player.y = 7;
  player.color = color;
  player.coreColor.longColor = 0x10101010;
  player.bulletList = NULL;

  player2.x = 7;
  player2.y = 7;
  player2.coreColor.longColor = 0x10101010;
  player2.color.longColor = 0x10000000;
  player2.bulletList = NULL;
  
  memcpy(player.mask, player1Mask, 25);
  memcpy(player2.mask, player2Mask, 25);
  
  for(int i = 0; i < 25; i++)
  {
    //Serial.println(player.mask[i]);
  }
  testBullet.x.subShort = 0x0100;
  testBullet.y.subShort = 0x0100;
  testBullet.dX = 255;
  testBullet.dY = 127;
  color.longColor = 0x00101000;
  testBullet.color = color;
  drawBullet(&testBullet);
}//setup


void loop() 
{
  
  count++;
  count2++;
  if (count == 10)
  {
    updateBullet(&testBullet);
    updatePlayer(&player);
    color.longColor = 0x22222002;
    fillScreen(color);
    drawPlayers(&player, &player2);
    drawBullet(&testBullet);
    color.longColor = 0x0f000000;
    RGB_update(-1,0,0,0);//LED#, RED, GREEN, BLUE
    
    
    count = 0;
  }
  if (count2 == 30)
  {
    rotatePlayer(&player2);
    count2 = 0;
  }
  delay(20);
}//loop

ISR(TIMER1_COMPA_vect)
{ 
}
