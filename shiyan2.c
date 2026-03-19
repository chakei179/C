#include<STC15F2K60S2.h>
#include<intrins.h>
char ass_mod[]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};
void key_pressS7();
void key_pressS6();
void key_pressS5();
void key_pressS4();
typedef unsigned char u8;
void Delay(int num)
{
    int i;
    while(num--)
    for (i = 0; i < 628; i++);
    
}




void main()
{
    P2=0xA0;P0=0x00;P2=0x80;P0=0xFF;
    while (1)
    {
       key_pressS7(); 
       key_pressS6();
       key_pressS5();
       key_pressS4();
    }
    
}

void key_pressS7()
{
    if (P30==0)
    {
        Delay(10);
        if (P30==0)
        {
            P06=0;
            Delay(500);
            P06=1;
        }
        while(P30==0);

    }
    
}

void key_pressS6()
{
    if (P31==0)
    {
        Delay(10);
        if (P31==0)
        {
       u8 i, j; 
	    for(i=0;i<3;i++){
	   
        for (j = 1; j < 8; j=j+2)
        {
             P0=ass_mod[j];
             Delay(200);
        }
        for (j = 0; j < 8; j=j+2)
        {
             P0=ass_mod[j];
             Delay(200);
        }

        }
        while(P31==0);

    }
    
}
}

void key_pressS5()
{ int i=0;
  int c=0;
    if (P32==0)
    {
        Delay(10);
        if (P32==0)
        {   
        for(i=0;i<3;i++)
        {
        for ( c =0; c < 8; c++)
        {
            P0=ass_mod[c];
            Delay(200);
        }
            
        }
        while(P32==0);

    }
    
}
}

void key_pressS4()
{
    if (P33==0)
    {
        Delay(10);
        if (P33==0)
        {int i=0;
            for ( i = 0; i < 3; i++)
            {int j;
                for(j=0;j<4;j++)
		            {
			        P0=ass_mod[j] & ass_mod[7-j];
			        Delay(1000);
		            }
		        for(j=2;j>=0;j--)
		        {
			        P0=ass_mod[j] & ass_mod[7-j];
			        Delay(1000);
		        }
            }
            
           
        }
        while(P33==0);

    }
    
}