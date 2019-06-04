#pragma once
#pragma once
#include<Windows.h>
#include<iostream>
#include<time.h>


//用于显示窗体的全局变量
//----------------------------------
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int bits = 24;
extern BYTE buffer[SCREEN_WIDTH*SCREEN_HEIGHT*bits / 8];


//-----------------------------------

//用于处理排序数据的全局变量
//-----------------------------------
const int DataSum = SCREEN_WIDTH;
extern int DataMax;
extern int DataMin;
extern int data[DataSum];
extern int nowIndex;

//-----------------------------------


class Color
{
public:
	Color(int R, int G, int B) :r(R), g(G), b(B) {};
	Color() :r(255), g(255), b(255) {};
	int r, g, b;
};


void InitData();
void CleanScreen();
void Draw();
void DrawRed();
void DrawGreen();
void DrawPoint(int x, int y, Color color = Color(255, 255, 255));
void Sort();
void PutBufferToScreen();

//排序函数
int Random(int p, int r);
int RandomizedPartition(int a[], int p, int r);
void RandomizedQuickSort(int a[], int p, int r);
void QuickSort(int a[], int p, int r);
int Partition(int a[], int p, int r);
void swap(int &a, int &b);