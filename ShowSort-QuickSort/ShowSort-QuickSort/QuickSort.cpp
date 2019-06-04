#include"QuickSort.h"

int DataMax = SCREEN_HEIGHT - 30;
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
		data[i] = sin(RegAngle)*(DataMax - DataMin) + DataMin;
	}
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
	swap(data[orderIndex], data[minIndex]);
	DrawGreen();
	if (orderIndex != DataSum)orderIndex++;
}



void DrawPoint(int x, int y, const Color color)
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
	if (step % 20 == 0)
		PutBufferToScreen();
}

void DrawGreen()
{
	for (int x = 0; x < orderIndex; x++)
	{
		for (int y = 0; y < data[x]; y++)
		{
			Color green = Color(0, 255, 0);
			DrawPoint(x, SCREEN_HEIGHT - y, green);
		}
		for (int y = SCREEN_HEIGHT; y >= data[x]; y--)
		{
			Color black = Color(0, 0, 0);
			DrawPoint(x, SCREEN_HEIGHT - y, black);
		}
	}

}

void DrawTempRed(int x)
{
	for (int y = 0; y < data[x]; y++)
	{
		Color red = Color(255, 0, 0);
		DrawPoint(x, SCREEN_HEIGHT - y, red);
	}

}
void DrawTempBlue(int x)
{
	for (int y = 0; y < data[x]; y++)
	{
		Color red = Color(0, 0, 255);
		DrawPoint(x, SCREEN_HEIGHT - y, red);
	}

}

void Draw()
{
	CleanScreen();

	for (int x = 0; x < DataSum; x++)
	{
		for (int y = 0; y < data[x]; y++)
		{
			Color color;

			DrawPoint(x, SCREEN_HEIGHT - y, color);
		}

	}

}


void swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

int Partition(int a[], int p, int r)
{

	int i = p, j = r + 1;
	int x = a[p];
	while (true) {
		while (a[++i] < x&&i < r);
		while (a[--j] > x);
		if (i >= j)break;
		swap(a[i], a[j]);
	}
	// 最后会分成 a[p,j-1] a[j] a[j+1,r] 三个部分
	// 把Partition元素从最左边换到 a[j]位置
	a[p] = a[j];
	a[j] = x;
	return j;
}

int Random(int p, int r)
{
	srand((unsigned)time(0));
	return (float)rand() / (RAND_MAX + 1)*(r - p) + p;
}


int RandomizedPartition(int a[], int p, int r)
{
	int i = Random(p, r);

	swap(a[i], a[p]);
	return Partition(a, p, r);
}

void RandomizedQuickSort(int a[], int p, int r)
{
	if (p < r) {

		int q = RandomizedPartition(a, p, r);

		Draw();
		DrawTempBlue(p);
		DrawTempBlue(r);
		DrawTempRed(q);
		orderIndex = p;
		DrawGreen();
		PutBufferToScreen();
		Sleep(20);

		RandomizedQuickSort(a, p, q - 1);
		RandomizedQuickSort(a, q + 1, r);
	}
}


void QuickSort(int a[], int p, int r)
{
	if (p < r) {
		int q = Partition(a, p, r);
		Draw();
		DrawTempBlue(p);
		DrawTempBlue(r);
		DrawTempRed(q);
		orderIndex = p;
		DrawGreen();
		PutBufferToScreen();
		Sleep(2000);

		QuickSort(a, p, q - 1);		//左半排序
		QuickSort(a, q + 1, r);		//右半排序
	}
}
