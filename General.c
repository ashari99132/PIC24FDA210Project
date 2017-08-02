/**
general.c
**/

#include "General.h"
#include "HardwareProfile.h"
char charBuff[10];

void  stringCopy (char *buffer, char *string)
{
  while (*string !='\0')
  	{
	  *buffer=*string;
	   buffer++;
	   string++;
  	}
}
void stringCat(char *string1, char *string2)
{
	while (*string1 !='\0')string1++;
	while (*string2 !='\0')
		{
	 *string1=*string2;	
	 string1++;
	 string2++;
	}	
}

char *WordToString(unsigned int Number)
{
 unsigned int temp,c,d;
 temp=Number/10000;
 charBuff[0]='0'+temp%10;
 temp=Number/1000;
 charBuff[1]='0'+temp%10;
 temp=Number/100;
 charBuff[2]='0'+temp%10;
 temp=Number/10;
 charBuff[3]='0'+temp%10;
 temp=Number;
 charBuff[4]='0'+temp%10;
 charBuff[5]='\0';
 
 temp=Number/10;
 if (temp<1)d=4;
 else if (temp<10)d=3;
 else if (temp<100)d=2;
 else if (temp<1000)d=1;
 for(temp=0;temp<d;temp++)
   for(c=0;c<6;c++)
 	charBuff[c]=charBuff[c+1];
  
 return &charBuff[0];	
}


char *FloatToString_4Pt2Dec(float Number)
{
 signed long lNumber=Number*100;	
 signed long temp;
 unsigned char c=0,d,i,neg=0;
 if(lNumber<0){
	 lNumber*=(-1);
	 neg=1; 	
 }

 if(neg)
	{
  charBuff[c]='-';c++;	
 } 
 temp=lNumber/1000000;
 charBuff[c]='0'+temp%10;
 c++;
 temp=lNumber/100000;
 charBuff[c]='0'+temp%10;
 c++;
 temp=lNumber/10000;
 charBuff[c]='0'+temp%10;
 c++;
 temp=lNumber/1000;
 charBuff[c]='0'+temp%10;
 c++;
 temp=lNumber/100;
 charBuff[c]='0'+temp%10;
 c++;
 charBuff[c]='.';
 c++;
 temp=lNumber/10;
 charBuff[c]='0'+temp%10;
 c++;
 temp=lNumber;
 charBuff[c]='0'+temp%10;
 c++;
 charBuff[c]='\0';
 if(neg)c=1;
 else c=0;
 for(;c<8;)
 	{
	  if(charBuff[c]=='0')c++;
	  else break;	
	}

 for (d=0;d<c;d++)
	{
	 if(neg)i=1;
	 else i=0;
	 for (;i<8;i++)charBuff[i]=charBuff[i+1];
	} 	
	

  
 return &charBuff[0];	
}

void Delay_uS(unsigned int Delay )  
{
 //---for 4 MHz Tcy----	
//  while(Delay>0)
//  {
//	Nop();
//	Nop();
//	Nop();
//	Nop();  
//   	Delay--;
//  } 
//---for 16MHz Tcy----
    while (Delay>0)
    { 
	 Nop();Nop();Nop();Nop();
     Nop();Nop();Nop();Nop();
     Nop();Nop();Nop();Nop();
     Nop();Nop();Nop();Nop();
     Delay--;
    }
}

unsigned int CalcCRC16(unsigned char *chpData, char chDataLength)

{
  unsigned int CRC16Reg=0xffff;
  char i=0,j=0;
  char LSB;
  for(i=0;i<chDataLength;i++)
  {
    
    CRC16Reg^=*(chpData+i);
    for(j=0;j<8;j++)
    {
      LSB=CRC16Reg&1;
      CRC16Reg>>=1;
       if(LSB==1)CRC16Reg^=POLY_CRC16;
         
    }
  }
  return CRC16Reg;
  
} 






char strLen(char *String)
{
 char c=0;
 while (*String !='\0')
 {
 c++;
 String++;
 }
 return c;
}

unsigned long Power(unsigned int base, int Size)
{
 unsigned long val=1;
 while(Size--)
 {
 val*=base; 
 }
return val;
}
unsigned int StringToWord(char *String)
{
 unsigned int val=0,temp;
 char Size=strLen(String);
 	while(Size--)
 	{
  		temp= *String-'0';
  		temp=temp*Power(10,Size); 	 
  		val =val+temp;
		String++;
 	}
 return val;
}
unsigned long StringToLONG(char *String)
{
 unsigned long val=0,temp;
 char Size=strLen(String);
 	while(Size--)
 	{
  		temp= *String-'0';
  		temp=temp*Power(10,Size); 	 
  		val =val+temp;
		String++;
 	}
 return val;
}
void SortWordBufferAsc(unsigned int *BuffData, unsigned int nData)
{
	WORD i=0;
	WORD Temp;
	for (i=0;i<nData;)
	{
	 if(BuffData[i]>BuffData[i+1] && i<(nData-1))
	 {
	   Temp=BuffData[i+1];
	   BuffData[i+1]=BuffData[i];
	   BuffData[i]=Temp;
	 }
	 if(BuffData[i]==BuffData[i+1] && i<(nData-1))BuffData[i+1]=0xff;
	 else if(BuffData[i]==BuffData[i-1] && i>0)BuffData[i]=0xff;
	 if(i>0 && BuffData[i]<BuffData[i-1])i=0;
	 else i++;
	}
}
