#include"ShowSort.h"

int DataMax = SCREEN_HEIGHT-30;
int DataMin = 30;
int orderIndex = 0;
int nowIndex = -1;
int data[DataSum];


void InitData()
{
	srand((unsigned)time(0));

	for (int i = 0; i < DataSum; i++)
	{
		float angle = (float)rand() / (RAND_MAX + 1) * 90;
		float RegAngle = angle / 180.0*3.1415926;
		data[i] = sin(RegAngle)*(DataMax-DataMin) + DataMin;
	}
}



void Swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}



void Sort()
{
	int min = data[orderIndex];
	int minIndex = orderIndex;
	for (nowIndex = orderIndex + 1; nowIndex < DataSum; nowIndex++)
	{
		
		if (data[nowIndex] < min)
		{
			min = data[nowIndex];
			minIndex = nowIndex;
		}
		DrawRed();

	}
	Swap(data[orderIndex], data[minIndex]);
	DrawGreen();
	if(orderIndex !=DataSum)orderIndex++;
}



void DrawPoint(int x, int y,const Color color)
{
	if (x <= 0 || x >= SCREEN_WIDTH)return;
	if (y <= 0 || y >= SCREEN_HEIGHT)return;

	buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 1] = color.r;
	buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 2] = color.g;
	buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 3] = color.b;
}


void CleanScreen()
{
	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{

			buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 1] = 0;
			buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 2] = 0;
			buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 3] = 0;
		}
	}
}

void DrawRed()
{
	static int step = 0;
	static int lastIndex = -1;
	if (lastIndex != -1)
	{
		for (int y = 0; y < data[lastIndex]; y++)
		{
			DrawPoint(lastIndex, SCREEN_HEIGHT - y);
		}
		for (int y = 0; y < data[nowIndex]; y++)
		{
			Color red = Color(255, 0, 0);
			DrawPoint(nowIndex, SCREEN_HEIGHT - y, red);
		}
	}
	lastIndex = nowIndex;
	step++;
	if(step%20==0)
		PutBufferToScreen();
}

void DrawGreen()
{
	for (int y = 0; y < data[orderIndex]; y++)
	{
		Color green = Color(0, 255, 0);
		DrawPoint(orderIndex, SCREEN_HEIGHT - y, green);
	}
	for (int y = SCREEN_HEIGHT; y >= data[orderIndex]; y--)
	{
		Color black = Color(0, 0, 0);
		DrawPoint(orderIndex, SCREEN_HEIGHT-y, black);
	}
	PutBufferToScreen();
}

void Draw()
{
	CleanScreen();

	for (int x = 0; x < DataSum; x++)
	{
		for (int y = 0; y < data[x]; y++)
		{
			Color color;

			DrawPoint(x, SCREEN_HEIGHT - y,color);
		}

	}
	PutBufferToScreen();
}