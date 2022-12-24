# include<stdio.h>
# include<ctype.h>
# define MAX 20

typedef struct stack
{
	char arr[MAX];
	int top;
}STACK;

void init(STACK* ps);
void push(STACK* ps,int ele);
char pop(STACK* ps);
char stackTop(STACK* ps);
void infixToPostfix(char infix[],char postfix[]);
int precedence(char st,char in);

int main()
{
	char par[20];
	char iar[20];
	printf("Enter valid infix expression\n");
	scanf("%s",iar);
	infixToPostfix(iar,par);
	printf("postfix expression = %s\n",par);
	return 0;
}

void init(STACK* ps)
{
	ps->top = -1;
}
int isEmpty(STACK* ps)
{
	return ps->top == -1;
}
void push(STACK* ps,int ele)
{
	++ps->top;
	ps->arr[ps->top] = ele;
}
char pop(STACK* ps)
{
	char popE = ps->arr[ps->top];
	ps->top--;
	return popE;
}
char stackTop(STACK* ps)
{
	return ps->arr[ps->top];
}
void infixToPostfix(char infix[],char postfix[])
{	
	STACK s;
	init(&s);
	
	int j=0;
	for(int i=0;infix[i]!='\0';i++)
	{
		if(isdigit(infix[i]))
			postfix[j++]=infix[i];
		else
		{
			while(!isEmpty(&s) && precedence(stackTop(&s),infix[i]))
				postfix[j++]=pop(&s);
			
			if(infix[i]==')')
				pop(&s);
			else
				push(&s,infix[i]);
		}
	}
	while(!isEmpty(&s))
		postfix[j++]=pop(&s);
	postfix[j]='\0';
}
int precedence(char st,char in)
{
	switch(in)
	{
		case '+':
		case '-': if(st=='(')
					return 0;  //PUSH 
				else
					return 1;   // POP
				
		case '*':
		case '/': if(st=='+' || st=='-' || st=='(') // higher the precedence the op must be ABOVE lower precedence op, NO two op of same precedence be in stack together
						return 0;  //PUSH
					else
						return 1;   //POP
		case '(':return 0;      // Always PUSH
		case ')':if(st=='(')
					return 0;     // PUSH
				else
					return 1;    // POP
	}
	return 0;
}

