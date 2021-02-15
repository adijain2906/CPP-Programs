#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define size 30
char stack[size];
int TOP = -1;
void check(char[]);
float evaluate(char[]);
void calc(float ans[],int &pos,char c)
{
	switch(c)
	{
		case '+':
			ans[pos-1] = ans[pos-1] + ans[pos];break;
		case '-':
			ans[pos-1] = ans[pos-1] - ans[pos];break;
		case '*':
			ans[pos-1] = ans[pos-1] * ans[pos];break;
		case '/':
			ans[pos-1] = ans[pos-1] / ans[pos];break;
		case '^':
			ans[pos-1] = pow(ans[pos-1],ans[pos]);break;
	}
       pos--;
}
int presidence_check()
{
	if (stack[TOP] == '(' || stack[TOP] == '+' || stack[TOP] == '-')
	return 1;
	else
	return 0;
}
void push(char ch)
{
	if(TOP == size-1)
	{
		return;
	}
	stack[++TOP] = ch;
}
char pop()
{
	if (TOP==-1)
	{
		return -1;
	}
	return stack[TOP--];
}
char *add_bracket(char expression[])
{
	if (expression[0]=='(' && expression[strlen(expression)-1] == ')')
	return NULL;
	char *exp = new char[strlen(expression)+2];
	exp[0] = '(';
	int i;
	for (i=0;expression[i]!='\0';i++)
	{
		exp[i+1] = expression[i];
	}
	exp[i+1] = ')';
	exp[i+2] = '\0';
	return exp;
}
float evaluate(char expression[])
{
	float ans[30];
	check(expression);
	char *exp = add_bracket(expression);
	if (exp==NULL)
	{
		exp = new char[strlen(expression)];
		strcpy(exp,expression);
	}
	char number[20],p=0;
	int i,pos=-1;
	char c;
	for (i=0;exp[i]!='\0';i++)
	{
		if (isalpha(exp[i]))
		{
			cout << "Invalid Expression";
			getch();
			exit(0);
		}
	}
	for (i=0;exp[i]!='\0';i++)
	{
		if (exp[i]=='(')
		{
			push(exp[i]);
		}
		else if(exp[i] == '+' || exp[i] == '-' || exp[i] == '/' || exp[i] == '*' || exp[i] == '^')
		{
			if (presidence_check()==0)
			{
				calc(ans,pos,pop());
			}
			push(exp[i]);
		}
		else if (isdigit(exp[i]))
		{
			for(p=0;isdigit(exp[i])||exp[i]=='.';p++,i++)
			{
				number[p] = exp[i];
			}
			i--;
			number[p] = '\0';
			ans[++pos] = atof(number);
		}
		else if (exp[i]==')')
		{
			while (1)
			{
				c = pop();
				if (c=='(') break;
				if (c!=')')
				calc(ans,pos,c);
			}
		}
		else
		{
			cout << "Invalid expression";
			getch();
			exit(0);
		}
	}
	return ans[0];
}
void check(char expression[])
{
	int bracket_check = 0;
	int counter_of_brackets = 0;
	int i;
	for (i=0;expression[i] != '\0';i++)
	{
		if (bracket_check < 0) break;
		if (expression[i] == '(')
		{
			bracket_check++;
		}
		if (expression[i] == ')')
		{
			bracket_check--;
		}
	}
	if (bracket_check != 0)
	{
		cout << "Invalid Expression";
		getch();
		exit(0);
	}
}
void main()
{
	clrscr();
	float answer;
	char string[30];
	cin >> string;
	answer = evaluate(string);
	cout << answer;
	getch();
}
