#include <stdio.h>
#define MAX 10
int queue[MAX];
int front = 0;
int rear = 0;

void Enqueue(int value);
int Dequeue();
int Size();
void Display();
bool IsEmpty();
bool IsFull();


int main()
{
	Display();
	Enqueue(10);
	Display();
	Enqueue(9);
	Display();
	Enqueue(8);
	Display();
	Dequeue();
	Display();
	Dequeue();
	Display();
	Enqueue(7);
	Display();
	Enqueue(6);
	Display();
	Enqueue(5);
	Display();
	Enqueue(4);
	Display();
	Enqueue(3);
	Display();
	Dequeue();
	Display();
	Dequeue();
	Display();
	Enqueue(2);
	Display();
	Enqueue(1);
	Display();
	Enqueue(101);
	Display();
	Enqueue(91);
	Display();
}

void Enqueue(int value)
{
	if (IsFull())
	{
		printf("full\r\n");
	}
	queue[rear] = value;
	rear = (rear + 1) % MAX;
}

int Dequeue()
{
	if (IsEmpty())
	{
		printf("empty\r\n");
	}
	int value = queue[front];
	queue[front] = -1;
	front = (front + 1) % MAX;
	return value;
}

int Size()
{
	if (IsEmpty())
	{
		return 0;
	}

	if (IsFull())
	{
		return MAX;
	}

	if (front < rear)
	{
		return rear - front;
	}

	return (MAX - front) + rear;
}

void Display()
{
	for (int i = 0; i < MAX; ++i)
	{
		printf("%d\t", queue[i]);
	}
	printf("\r\n");
	printf("size:%d\r\n", Size());
	printf("front:%d\r\n", front);
	printf("rear:%d\r\n", rear);

}

bool IsEmpty()
{
	return front == rear;
}

bool IsFull()
{
	return front == (rear + 1) % MAX;
}