#include <iostream.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
union REGS i,o;
class screen
{
	public:
	int x,y;
	char *s;
	screen()
	{
		s = "Screen";
	}
}s[10];
int n = 1;
void concat(char a[],char b[])
{
	for (int i = strlen(a), j=0; b[j]!='\0';j++,i++)
	{
		a[i] = b[j];
	}
	a[i] = '\0';
}
void screen_allocate()
{
	char *a;
	for (int i=0;i<n;i++)
	{
		itoa(i+1,a,10);
		concat(s[i].s,a);
	}
}
void draw()
{
	rectangle(s[0].x-100,s[0].y-200,s[0].x+100,s[0].y+200);
	outtextxy(s[0].x-100,s[0].y+210,s[0].s);
}
void init()
{
	i.x.ax = 0;
	int86(0x33,&i,&o);
}
void show()
{
	i.x.ax = 1;
	int86(0x33,&i,&o);
}
void main()
{
	clrscr();
	int gd = DETECT,gm;
	initgraph(&gd,&gm,"..\\bgi");
	s[0].x = (getmaxx()+1)/2;
	s[0].y = (getmaxy()+1)/2;
	init();
	show();
	screen_allocate();
	while (!kbhit())
	{
		i.x.ax = 3;
		int86(0x33,&i,&o);
		if (o.x.bx==1)
		n++;
		draw();
	}
}
