				
#line 1 "Traffic light.c" /0
  
#line 1 "C:\KEIL\C51\INC\ATMEL\REG51.H" /0
 //#include<89c51rd2.h>
 
 sfr P0   = 0x80;
 sfr P1   = 0x90;
 sfr P2   = 0xA0;
 sfr P3   = 0xB0;
 sfr PSW  = 0xD0;
 sfr ACC  = 0xE0;
 sfr B    = 0xF0;
 sfr SP   = 0x81;
 sfr DPL  = 0x82;
 sfr DPH  = 0x83;
 sfr PCON = 0x87;
 sfr TCON = 0x88;
 sfr TMOD = 0x89;
 sfr TL0  = 0x8A;
 sfr TL1  = 0x8B;
 sfr TH0  = 0x8C;
 sfr TH1  = 0x8D;
 sfr IE   = 0xA8;
 sfr IP   = 0xB8;
 sfr SCON = 0x98;
 sfr SBUF = 0x99;
 
 
 
 
 sbit CY   = 0xD7;
 sbit AC   = 0xD6;
 sbit F0   = 0xD5;
 sbit RS1  = 0xD4;
 sbit RS0  = 0xD3;
 sbit OV   = 0xD2;
 sbit P    = 0xD0;
 
 
 sbit TF1  = 0x8F;
 sbit TR1  = 0x8E;
 sbit TF0  = 0x8D;
 sbit TR0  = 0x8C;
 sbit IE1  = 0x8B;
 sbit IT1  = 0x8A;
 sbit IE0  = 0x89;
 sbit IT0  = 0x88;
 
 
 sbit EA   = 0xAF;
 sbit ES   = 0xAC;
 sbit ET1  = 0xAB;
 sbit EX1  = 0xAA;
 sbit ET0  = 0xA9;
 sbit EX0  = 0xA8;
 
 
 sbit PS   = 0xBC;
 sbit PT1  = 0xBB;
 sbit PX1  = 0xBA;
 sbit PT0  = 0xB9;
 sbit PX0  = 0xB8;
 
 
 sbit RD   = 0xB7;
 sbit WR   = 0xB6;
 sbit T1   = 0xB5;
 sbit T0   = 0xB4;
 sbit INT1 = 0xB3;
 sbit INT0 = 0xB2;
 sbit TXD  = 0xB1;
 sbit RXD  = 0xB0;
 
 
 sbit SM0  = 0x9F;
 sbit SM1  = 0x9E;
 sbit SM2  = 0x9D;
 sbit REN  = 0x9C;
 sbit TB8  = 0x9B;
 sbit RB8  = 0x9A;
 sbit TI   = 0x99;
 sbit RI   = 0x98;
 
 
#line 1 "Traffic light.c" /0
 
 sbit R1=P1^0;
 sbit Y1=P1^1;
 sbit G1=P1^2;
 sbit R2=P1^3;
 sbit Y2=P1^4;
 sbit G2=P1^5;
 sbit R3=P2^0;
 sbit Y3=P2^1;
 sbit G3=P2^2;
 sbit R4=P2^3;
 sbit Y4=P2^4;
 sbit G4=P2^5;

 sbit C1=P0^0;
 sbit C2=P0^1;
 
 unsigned int timeA =25,timeB=25;
 unsigned int countA =1,countB=1;
 unsigned int i,c;
 void seconddelay (unsigned  int b)
 { 

	TMOD=0x01;
	for(c=0;c<=b;c++){
     for(i=0;i<20;i++)
       {
         TH0=500000/255;
         TL0=-500000%256;
         TF0=0;
         TR0=1;
         while (TF0==0);
       }
     }
  }

 void clear()
 {
 R1=0;
 R2=0;
 R3=0;
 R4=0;
 Y1=0;
 Y2=0;
 Y3=0;
 Y4=0;
 G1=0;
 G2=0;
 G3=0;
 G4=0;
 } 

 void phase1(unsigned  int t)
 {
 R1=1;
 G2=1;
 R3=1;
 G4=1;
 seconddelay(t);
 Y2=1;
 Y4=1;
 seconddelay(5);
 }

 void phase2(unsigned  int t)
 {
 G1=1;
 R2=1;
 G3=1;
 R4=1;
 seconddelay(t);
 Y1=1;
 Y3=1;
 Y4=1;
 seconddelay(5);
 }
 void incountA() interrupt 0 using 1
{
countA=countA+1;;
}
 void incountB() interrupt 2 using 1
{
countB=countB+1;
}
void generateTime()
{
  unsigned int rate =60/(countA+countB);
	timeA=rate*countA;
	timeB=rate*countB;
	countA=1;
	countB=1;
}
 void main( void )
 {
 P1=0x00;
 P2=0x00;
 P0=0xFF;
 IE=0x85; // interrupt generate
 
 EX0=1;
 IT0=1;

 while(1)
 {
 phase1(timeA);
 clear();
 //generateTime();//time colculation 
 phase2(timeB);
 clear();
 generateTime();//time colculation 
 } 
 
 }
