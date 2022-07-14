#include<stdio.h>
#define MAX 10
int stack[MAX];
int top = -1;

void push(int value);
int size();
void display();
bool isEmpty();
bool isFull();
int pop();

int main()
{
	push(1);
	push(10);
	push(100);
	push(1000);
	push(10000);
	push(100000);
	push(1000000);
	push(10000000);
	push(100000000);
	push(1000000000);
	push(10000000000);
	display();
	pop();
	display();
	pop();
	display();
	pop();
	display();
	pop();
	display();
	pop();
	display();
	pop();
	display();
	pop();
	display();
	pop();
	display();
	pop();
	display();
	pop();
	display();
	pop();
	display();
	pop();
	display();
	pop();
	display();
}

void push(int value)
{
	if (isFull())
	{ 
		printf("isFull!!\r\n");
		return;
	}

	stack[++top] = value;
}

int pop()
{
	if (isEmpty())
	{
		printf("isEmpty\r\n");
		return -99999;
	}
	return stack[--top];
}

int size()
{
	return top + 1;
}

void display()
{
	for (int i = 0; i < MAX; ++i)
	{
		printf("%d\r\n", stack[i]);
	}
	printf("size:%d\r\n", size());
}

bool isEmpty()
{
	if (top == -1)
	{
		return true;
	}

	return false;
}

bool isFull()
{
	if (top + 1 == MAX)
	{
		return true;
	}

	return false;
}

