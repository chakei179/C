#include<STC15F2K60S2.h>
#include<intrins.h>
char ass_mod[]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};
void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}






void main()
	{
	P2=0xA0;P0=0x00;
	P2=0x80;P0=0xFF;
//while(1){
	//P00=0;Delay1000ms();P00=1;Delay1000ms();
//}

while(1){
	int i=0;
	for(i;i<3;i++){
	int j;	
        for (j = 0; j < 7; j=j+2)
        {
             P0=ass_mod[j];
             Delay1000ms();
        }
        for (j = 1; j < 8; j=j+2)
        {
             P0=ass_mod[j];
             Delay1000ms();
        }

    }
for(i=0;i<3;i++){
for ( i =0; i < 8; i++)
{
    P0=ass_mod[i];
    Delay1000ms();
}
}






}



}