#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#define MAX 9
struct cell
{
	char char_value;
	int value;
	int cant_have[MAX];
	int count;
	void convert_to_char()
	{
		if (value == 0)
			char_value = ' ';
		else
			char_value = (char)(value + 48);
	}
	void print_cant_have()
	{
		int i = 0;
		printf("\nCan't have array - ");
		for (i=0;i<MAX;i++)
		{
			printf("%d ", cant_have[i]);
		}
		printf("\n");
	}
	void count_cant_have()
	{
		int i = 0;
		count = 0;
		for (i=0;i<MAX;i++)
		{
			if(cant_have[i] == 1) count++;
		}
	}
};
struct cell sudoku[MAX][MAX];

//EASY
//char SudokuQ[MAX][MAX]={/*R1*/{'1',' ',' ',     '3','4','9',    '5',' ',' '},
//			/*R2*/{' ','9',' ',     ' ','5','1',    ' ',' ','6'},
// 			/*R3*/{'5','2',' ',     ' ','6','7',    ' ',' ',' '},

//			/*R4*/{' ','7','4',     ' ',' ','5',    ' ','6','3'},
//			/*R5*/{'2','1',' ',     '6',' ','8',    '7',' ','9'},
//			/*R6*/{' ',' ','6',     ' ','9','4',    ' ',' ',' '},

//			/*R7*/{'3',' ','2',     '5','1',' ',    ' ','7','8'},
//			/*R8*/{'6','8',' ',     ' ',' ',' ',    '4',' ','5'},
//			/*R9*/{' ',' ','9',     ' ','8',' ',    ' ',' ','2'}};

//MEDIUM
char SudokuQ[MAX][MAX]={/*R1*/{'1','2',' ',     ' ',' ','8',    '7',' ',' '},
			/*R2*/{' ','5',' ',     ' ',' ','9',    '1','4',' '},
			/*R3*/{' ',' ','9',     ' ','4',' ',    '3',' ',' '},

			/*R4*/{' ',' ','1',     ' ','8','4',    ' ','2',' '},
			/*R5*/{'5',' ',' ',     ' ','1',' ',    ' ',' ','3'},
			/*R6*/{' ','8','7',     ' ',' ',' ',    ' ','1',' '},

			/*R7*/{' ','7',' ',     ' ',' ','2',    '5','9',' '},
			/*R8*/{' ',' ',' ',     ' ',' ','6',    '2',' ',' '},
			/*R9*/{' ','9','3',     '4',' ','1',    ' ',' ',' '}};

//DIFFICULT
//char SudokuQ[MAX][MAX]={/*R1*/{'1',' ',' ',     ' ',' ',' ',    ' ',' ','7'},
//			/*R2*/{' ','6','5',     ' ',' ',' ',    '3',' ',' '},
//			/*R3*/{'7',' ',' ',     ' ',' ',' ',    ' ','2','4'},
//
//			/*R4*/{' ',' ',' ',     ' ','2','7',    ' ',' ',' '},
//			/*R5*/{' ',' ','7',     ' ',' ',' ',    ' ',' ',' '},
//			/*R6*/{' ',' ',' ',     '8',' ',' ',    ' ',' ','5'},
//
//			/*R7*/{' ',' ','2',     ' ','5',' ',    ' ','1',' '},
//			/*R8*/{'9','5',' ',     ' ',' ','8',    ' ','7','2'},
//			/*R9*/{' ',' ',' ',     '3',' ','2',    ' ','8',' '}};



void update_char_value()
{
	int i,j;
	for (i=0;i<MAX;i++)
	{
		for (j=0;j<MAX;j++)
		{
			sudoku[i][j].convert_to_char();
		}
	}
}

void copyq()
{
	int i,j;
	for (i=0;i<MAX;i++)
	{
		for (j=0;j<MAX;j++)
		{
			sudoku[i][j].value = ((SudokuQ[i][j] == ' ')? 0 : SudokuQ[i][j] - 48);

		}
	}
	update_char_value();
}

void update_cant_have(int r, int c)
{
	int a,b,i,j,k;
	for (k=0;k<MAX;k++)
	{
		if(sudoku[k][c].value != 0)
		{
			sudoku[r][c].cant_have[sudoku[k][c].value - 1] = 1;
		}
		if(sudoku[r][k].value != 0)
		{
			sudoku[r][c].cant_have[sudoku[r][k].value - 1] = 1;
		}
	}
	a = (r/3) * 3;
	b = (c/3) * 3;
	for (i=a;i<a+3;i++)
	{
		for (j=b;j<b+3;j++)
		{
			if(sudoku[i][j].value!=0)
			{
				sudoku[r][c].cant_have[sudoku[i][j].value-1] = 1;
			}
		}
	}
	sudoku[r][c].count_cant_have();
}

void update_cant_have1(int r, int c)
{
	int a,b,i,j,k;
	for (k=0;k<MAX;k++)
	{
		if(k!=c)
		{
			sudoku[r][k].cant_have[sudoku[r][c].value - 1] = 1;
			sudoku[r][k].count_cant_have();
		}
		if(k!=r)
		{
			sudoku[k][c].cant_have[sudoku[r][c].value - 1] = 1;
			sudoku[k][c].count_cant_have();
		}
	}
	a = (r/3) * 3;
	b = (c/3) * 3;
	for (i=a;i<a+3;i++)
	{
		for (j=b;j<b+3;j++)
		{
			if(i!=r && j!=c)
			{
				sudoku[i][j].cant_have[sudoku[r][c].value-1] = 1;
			}
			sudoku[i][j].count_cant_have();
		}
	}
}

void find()
{
	int i,j,k;
	for (i=0;i<MAX;i++)
	{
		for (j=0;j<MAX;j++)
		{
			if (sudoku[i][j].value==0)
			{
				update_cant_have(i, j);
			}
			else
			{
				update_cant_have1(i, j);
			}
		}
	}
}

void input_sudoku()
{
	int i,j;
	for (i=0;i<MAX;i++)
	{
		for (j=0;j<MAX;j++)
		{
			scanf("%d", &sudoku[i][j].value);
		}
	}
	update_char_value();
}

void fill()
{
	int i,j,k;
	for (i=0;i<MAX;i++)
	{
		for (j=0;j<MAX;j++)
		{
			if (sudoku[i][j].count == MAX-1)
			{
				for (k=0;k<MAX;k++)
				{
					if(sudoku[i][j].cant_have[k] == 0)
					{
						sudoku[i][j].value = k+1;
						break;
					}
				}
			}
		}
	}
	update_char_value();
}

void check_filled()
{
	int filled = 0,i,j;
	for (i=0;i<MAX;i++)
	{
		for (j=0;j<MAX;j++)
		{
			if (sudoku[i][j].value!=0)
			filled++;
		}
	}
	if (filled==81)
	{
		printf("\nFILLED\n");
		getch();
		exit(0);
	}
}

void print_sudoku()
{
	int i,j;
	for (i=0;i<MAX;i++)
	{
		for (j=0;j<MAX;j++)
		{
			printf("%c", sudoku[i][j].char_value);
			if ((j+1)%3==0 && j!=MAX-1) printf("|");
			else printf(" ");
		}
		printf("\n");
		if ((i+1)%3==0 && i!=MAX-1)
		printf("---------------------\n");
	}
}

void solve()
{
	char c;
	static int i = 1;
	c = getch();
	if (c == 'q') exit(0);
	clrscr();
	check_filled();
	find();
	fill();
	print_sudoku();
	printf("Step: %d", i++);
	//printf("%d", sudoku[4][0].count);
	//sudoku[4][0].print_cant_have();
	solve();
}

void main()
{
	int i,j;
	clrscr();
	//input_sudoku();
	copyq();
	print_sudoku();
	solve();
	getch();
}
