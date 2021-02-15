#include <iostream.h>
#include <conio.h>
#include <dos.h>
#include <process.h>
char sq[9];
void board()
{
 gotoxy (30,2);
 cout << "TIC - TAC - TOE";
 gotoxy(30,8);
 cout << sq[0] << " " << sq[1] << " " << sq[2] << "\n";
 gotoxy(30,9);
 cout << sq[3] << " " << sq[4] << " " << sq[5] << "\n";
 gotoxy(30,10);
 cout << sq[6] << " " << sq[7] << " " << sq[8] << "\n";
}
int win()
{
 if (sq[0]==sq[1]&&sq[1]==sq[2])
 return 1;
 else if (sq[3]==sq[4]&&sq[4]==sq[5])
 return 1;
 else if (sq[6]==sq[7]&&sq[7]==sq[8])
 return 1;
 else if (sq[0]==sq[3]&&sq[3]==sq[6])
 return 1;
 else if (sq[1]==sq[4]&&sq[4]==sq[7])
 return 1;
 else if (sq[2]==sq[5]&&sq[5]==sq[8])
 return 1;
 else if (sq[0]==sq[4]&&sq[4]==sq[8])
 return 1;
 else if (sq[2]==sq[4]&&sq[4]==sq[6])
 return 1;
 else if (sq[0]!='1'&& sq[1]!='2'&& sq[2]!='3'&&sq[3]!='4'&&sq[4]!='5'&&sq[5]!='6'&&
 sq[6]!='7'&&sq[7]!='8'&&sq[8]!='9')
 return 0;
 else return 2;
}
void main()
{
 int i,a,p,n;
 char mark;
 clrscr();
 a = '1';
 for (i=0;i<9;i++,a++)
 sq[i] = a;
 gotoxy (30,2);
 cout << "TIC - TAC - TOE";
 board();
 i = 2;
 p = 1;
 do
 {
  if (p%2!=0) p=1;
  else p=2;
  s:gotoxy (26,11);
  cout << "Player " << p << " turn =" ;cin >> n;
  if (p==1) mark = 'x';
  else mark = 'o';
  if (sq[n-1]=='x'||sq[n-1]=='o')
  {
   gotoxy (26,12);
   cout << "INVALID MOVE";
   delay(400);
   clrscr();
   board();
   goto s;
  }
  else if(n==100) break;
  else
  sq[n-1] = mark;
  clrscr();
  board();
  p++;
  i = win();
 }
 while (i==2);
 if (i==1)
 {
  gotoxy(26,11);
  if (p==2) cout << "Player " << p-1 << " wins!!!!!!!";
  if (p==3) cout << "Player " << p-1 << " wins!!!!!!!";
 }
 else if (i==0)
 cout << "DRAW";
 else
 exit(0);
 getch();
}
