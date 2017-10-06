*************************************************

******************************************************

//Developed By Krishnasagar Subhedarpage

//thish is code in c style for grid navigation with five sensors on ATMEGA 16 platform with specified

//pin configuration in <main()>

//submited to techfest-11 IITB at dated 30/11/2010 with abstract

//OPEN gnu LICENSE

//optional camera integration code is required which is with file camera.c

//optional genetic module is in file genetic.c

******************************************************************************************************

#define F_CPU 8000000UL  /* 1 MHz CPU clock */

#define USART_BAUDRATE 9600

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#include <util/delay.h>

#include <inttypes.h>

#include <avr/io.h>

#include <avr/wdt.h>

#include <avr/interrupt.h>

include "camera.c"

include "genetic.c"

unsigned int a[6][6],i,j,x,y,d;

void Drive_Motor(unsigned char LEFT,unsigned char RGHT)

{

        if(RGHT==0)//if right == 0 then right motor will stop

        {

        PORTB&=~_BV(5);

        PORTB&=~_BV(4);

        }

        if(RGHT==1)//if right == 1 then right motor will go forward

        {

        PORTB&=~_BV(5);

        PORTB|=_BV(4);

        }

        if(RGHT==2)//if right == 2 then right motor will go backward

        {

             PORTB|=_BV(5);

         PORTB&=~_BV(4);

        }

        if(LEFT==0)//if left == 0 then left motor will stop

        {

        PORTB&=~_BV(6);

        PORTB&=~_BV(7);

        }

        if(LEFT==1)//if left == 1 then left motor will go forward

        {

        PORTB&=~_BV(6);

        PORTB|=_BV(7);

        }

        if(LEFT==2)//if left == 2 then right motor will go backward

        {

         PORTB|=_BV(6);

         PORTB&=~_BV(7);

        }

}

void line_follow()

{

while((bit_is_clear(PINA, 0))||(bit_is_clear(PINA, 4))) //while node is not found do line following

                        {

                           

                                 

        // if((bit_is_set(PINA, 0)) && (bit_is_set(PINA, 4))&&(bit_is_set(PINA, 3))  && (bit_is_set(PINA,1))&&(bit_is_set(PINA, 2)))

                         //     {

                                                 //while((bit_is_set(PINA, 0)) && (bit_is_set(PINA, 4)))  // wait till the node is passed

                        //     {

                          //    }

                            //   i++;            

 

                                //  }

                                if((bit_is_set(PINA, 3))  && (bit_is_set(PINA, 1))&&(bit_is_set(PINA, 2)))        // if middle 3 on line go straight

                                  {

                                   Drive_Motor(1,1);

                                  }

                                  elseif((bit_is_set(PINA, 3))  && (bit_is_clear(PINA, 1))&&(bit_is_set(PINA, 2)))  

                                  {

                                   Drive_Motor(1,0);

                                  }

                                  elseif((bit_is_clear(PINA, 3))  && (bit_is_set(PINA, 1))&&(bit_is_set(PINA, 2)))

                                  {

                                   Drive_Motor(0,1);

                                  }

                                  elseif((bit_is_set(PINA, 0))&&(bit_is_clear(PINA, 4)))

                                  {

                                   Drive_Motor(0,1);

                                  }

                                  else      

                                  if((bit_is_clear(PINA, 0))&&(bit_is_set(PINA, 4)))  

     

                                  {

                                   Drive_Motor(1,0);

                                  }      

                         }

Drive_Motor(1,1);

_delay_ms(250);

Drive_Motor(0,0);

}

void turn(int angle, int direction)

{

 if(angle==90)

 {

  if(direction==0)

  {

   Drive_Motor(2,1);

   //_delay_ms(700);

   while((bit_is_set(PINA, 1))||(bit_is_set(PINA, 2))||(bit_is_set(PINA,3)))

   {

   }

   while((bit_is_clear(PINA, 1))&&(bit_is_clear(PINA, 2))&&(bit_is_clear(PINA, 3)))

   {

   }

   Drive_Motor(0,0);

  }

  if(direction==1)

  {

   Drive_Motor(1,2);

   //_delay_ms(700);

   while((bit_is_set(PINA, 1))||(bit_is_set(PINA, 2))||(bit_is_set(PINA,3)))

   {

   }

   while((bit_is_clear(PINA, 1))&&(bit_is_clear(PINA, 2))&&(bit_is_clear(PINA, 3)))

   {

   }

   Drive_Motor(0,0);

  }  

 }

 if(angle==180)

 {

  Drive_Motor(2,1);

   //_delay_ms(700);

while((bit_is_set(PINA, 1))||(bit_is_set(PINA, 2))||(bit_is_set(PINA,3)))

   {

   }

   while((bit_is_clear(PINA, 1))&&(bit_is_clear(PINA, 2))&&(bit_is_clear(PINA, 3)))

   {

   }

   Drive_Motor(0,0);

   Drive_Motor(2,1);

   //_delay_ms(250);

   while((bit_is_set(PINA, 1))||(bit_is_set(PINA, 2))||(bit_is_set(PINA,3)))

   {

   }

   while((bit_is_clear(PINA, 1))&&(bit_is_clear(PINA, 2))&&(bit_is_clear(PINA, 3)))

   {

   }

   Drive_Motor(0,0);

 }

 

}

/*void search_at_node()

{

if((bit_is_set(PINA, 6))&&(bit_is_set(PINA, 7)))

Drive_Motor(0,0);

else

{

  Drive_Motor(2,1);

  _delay_ms(250);

 

   

 if(bit_is_set(PINA ,4))

    {

     Drive_Motor(0,0);

    }

while(bit_is_clear(PINA, 4))

{

 

if((bit_is_set(PINA, 6))&&(bit_is_set(PINA, 7)))

  {

     while((bit_is_clear(PINA, 1))&&(bit_is_clear(PINA, 2))&&(bit_is_clear(PINA, 3)))

     {

      //Drive_Motor(2,1);

     }

      Drive_Motor(0,0);

   

      line_follow();

       

      Drive_Motor(1,0);

     if((bit_is_set(PINA, 3))  && (bit_is_set(PINA, 1))&&(bit_is_set(PINA, 2))&&(bit_is_clear(PINA, 0))&&(bit_is_clear(PINA, 4)))

     {

      Drive_Motor(0,0);

     }

      line_follow();

   }

}

  Drive_Motor(0,0);

 

   //_delay_ms(500);

   Drive_Motor(1,2);

   if((bit_is_clear(PINA, 3))  && (bit_is_clear(PINA, 1))&&(bit_is_clear(PINA, 2)))

   {

    //Drive_Motor(1,2);

   }

   

   Drive_Motor(1,2);

   

   

while(bit_is_set(PINA, 4))

 {

 if((bit_is_set(PINA, 6))&&(bit_is_set(PINA, 7)))

   {

    while((bit_is_clear(PINA, 3))  && (bit_is_clear(PINA, 1))&&(bit_is_clear(PINA, 2)))

    {

     Drive_Motor(1,2);

    }

    Drive_Motor(0,0);

    line_follow();

    if((bit_is_set(PINA, 0)) && (bit_is_set(PINA, 4))&&(bit_is_set(PINA, 3))  && (bit_is_set(PINA, 1))&&(bit_is_set(PINA, 2)))

    {

       Drive_Motor(0,1);    

    }

    line_follow();

   }

   else

   {

    if(bit_is_set(PINA, 4))

    {

     //_delay_ms(500);

     Drive_Motor(0,0);

    }

     

    while((bit_is_set(PINA, 1))&&(bit_is_set(PINA, 2))&&(bit_is_set(PINA, 3)))

    {

    Drive_Motor(2,1);

    }

    Drive_Motor(0,0);

    line_follow();

   }

  }

 

 

 }

}

*/

void turndirn(int fd, int sd)

{

 //_delay_ms(1000);

 

 

 if((fd==0)&&(sd==1))

 {

  turn(90,0);

  d=sd;

  x+=1;

  line_follow();

  a[x][y]=0;

 }

 else if((fd==0)&&(sd==2))

 {

  turn(180,0);

  d=sd;

  y-=1;

  line_follow();

 a[x][y]=0;

 }

 else if((fd==0)&&(sd==3))

 {

  turn(90, 1);

  d=sd;

  x-=1;

  line_follow();

  a[x][y]=0;

 }

 else if((fd==1)&&(sd==0))

 {

  turn(90,1);

  y+=1;

  d=sd;

  line_follow();

  a[x][y]=0;

 }

 else if((fd==1)&&(sd==2))

 {

  turn(90,0);

  y-=1;

  line_follow();

  d=sd;

  a[x][y]=0;

 }

 else if((fd==1)&&(sd==3))

 {

   turn(180,0);

   x-=1;

   d=sd;

   line_follow();

   a[x][y]=0;

 }

 else if((fd==2)&&(sd==1))

 {

  turn(90,1);      

  d=sd;

  x+=1;

  line_follow();

  a[x][y]=0;

 }

 else if((fd==2)&&(sd==0))  

 {

  turn(180,0);

  y+=1;

  d=sd;

  line_follow();

  a[x][y]=0;

 }

 else if((fd=2)&&(sd=3))

 {

  turn(90,0);

  x-=1;

  d=sd;

  line_follow();

  a[x][y]=0;

 }  

 else if((fd==3)&&(sd==0))

 {

  turn(90,0);

  y+=1;

  d=sd;

  line_follow();

  a[x][y]=0;

 }

 else if((fd==3)&&(sd==1))

 {

  turn(180,0);

  d=sd;

  x+=1;

  line_follow();

  a[x][y]=0;

 }

 else if((fd==3)&&(sd==2))

 {

  turn(90,1);

  d=sd;

  y-=1;

  line_follow();

  a[x][y]=0;

 }

 else if((fd==1)&&(sd==1))

 {

  line_follow();

  x+=1;

  a[x][y]=0;

 }

 else if((fd==2)&&(sd==2))

 {

  y-=1;

 

  line_follow();

  a[x][y]=0;

 }

 else if((fd==3)&&(sd==3))

 {

  x-=1;

  line_follow();

  a[x][y]=0;

 }

 else if((fd==0)&&(sd==0))

 {

  y+=1;

  line_follow();

  a[x][y]=0;

 }

   

}

void scanbox()

{

if((bit_is_set(PINA, 6))&&(bit_is_clear(PINA, 7)))

  {

  turndirn(d,d);

  PORTC|=_BV(1);

  PORTC&=~_BV(0);

  _delay_ms(4000);

PORTC&=~_BV(1);

  PORTC&=~_BV(0);

}

}

void derivepath()

{

 int sd;

 if(a[x+1][y]==1)

 {

 

  sd=1;

  turndirn(d,sd);

 }

 if(a[x-1][y]==1)

 {

 

  sd=3;

  turndirn(d,sd);

 }

 if(a[x][y+1]==1)

 {

 

  sd=0;

  turndirn(d,sd);

 }

 if(a[x][y-1]==1)

 {

 

  sd=2;

  turndirn(d,sd);

 }

scanbox();

}

void createpath()

{

 for(i=1;i<=5;i++)

 for(j=0;j<=5;j++)

 a[i][j]=0;

 for(i=0,j=0;i<3;i++)

 a[i][j]=1;

}

void homepath()

{

unsigned int k;

for(i=0;i<=5;i++)

{

for(j=0;j<=5;j++)

{

a[i][j]=0;

}

}

for(k=x;k>=0;k--)

a[y][k]=1;

for(k=j;k>=0;k--)

a[k][x]=1;

derivepath();

//line_follow();

//line_follow();

}

/*

void avoidbox()

{

 if((bit_is_set(PINA, 6))&&(bit_is_set(PINA, 7)))

 {

 a[x][y]=7;

 a[x+1][y]=1;

 a[x][y+1]=1;

 a[x][y-1]=1;

 a[x-1][y]=1;

}

*/

int main(void)

{

        //unsigned char

temp='l',node=0x30,a=0x30;

//        unsigned int i=0x00;

        unsigned int k;

           

        DDRA=0x00;

        DDRD=0xff;

        DDRB=0xff;

        PORTA=0xff;

        PORTD=0xff;

        PORTB=0x00;

        //search_at_node();

    //createpath();

    //derivepath();

        

//line_follow();

//line_follow();

d=0;

x=0;

y=0;

for(i=0;i<=5;i++)

{

for(j=0;j<=5;j++)

{

a[i][j]=0;

}

}

for(k=1;k<=5;k++)

{

for(i=0,j=k;i<=k;i++)

{

 a[i][j]=1;

 derivepath();

}

for(j=0,i=k;j<k;j++)

{

a[i][j]=1;

derivepath();

}

//for(l=1;l<=(2k+1);l++)

//derivepath();

}

}

