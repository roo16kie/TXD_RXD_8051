//實驗三 4x4 鍵盤與 RS232 串列傳輸
#include "reg51.h"
/*******************************************/
/* keyboard's infomation */
/*******************************************/
code char ser[]={0xfe,0xfd,0xfb,0xf7};
code int key[]={1,2,3,12,4,5,6,13,7,8,9,14,10,0,11,15};
code char keymsg[]={0xee,0xed,0xeb,0xe7,
 0xde,0xdd,0xdb,0xd7,
 0xbe,0xbd,0xbb,0xb7,
 0x7e,0x7d,0x7b,0x77};
code char msg[] = "0123456789abcdef";
code char startmsg[] = "Hello";
void send(char ch);
void delay (int t);
int getkey();
void main( )
{
 int x;
 int y;
 SCON=0x50;
 TMOD=0x20;
 TH1=0xe6;
 TR1=1;
 TI=0;
 for(y=0;y<5;y++){
send(startmsg[y]);
 }
 while(1){
x = getkey();
if( x>=0 && x<=15)
send(msg[x]);
 }
}
void send(char ch)
{
 SBUF=ch;
 while(TI == 0)
 ;
 TI=0;
}
int getkey()
{
 int i,k=-1;
 while(1){
 for(i=0;i<4;i++){
 P1=ser[i];
 if(P1!=ser[i]){
 if(P1==keymsg[i])
 k=key[i];
 else if(P1==keymsg[i+4])
 k=key[i+4];
 else if(P1==keymsg[i+8])
 k=key[i+8];
 else if(P1==keymsg[i+12])
 k=key[i+12];
 }
 if (k!=-1) break ;
 }
 if(k!=-1)
 while(1){
 P1=ser[i];
 if(P1==ser[i])
 return k;
 }
 }
}
void delay (int t)
{
int x;
for (x=0;x<t;x++)
;
}