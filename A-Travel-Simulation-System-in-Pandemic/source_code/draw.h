#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#include<stdbool.h>
#include<float.h>
#include<conio.h>
#include<graphics.h>

#include"input.h"
#include"route.h"
#include"state.h"
#include"structure.h"

extern CITY cities[CITYNUM];
extern DPRT departureTable[DPRTNUM];
extern PSGR passengerList[100];
extern PLAN travelPlans[MAX_PSGRNUM];
extern int dayTime;
extern int hourTime;
extern int psgrNum;

typedef struct cityPoint {
	int x, y;
}CITYPOINT;

void drawCityMap();	//���Ƴ��е�ͼ
void drawPsgr();	//����״̬�����ÿ�
void drawInfo();	//������Ϣ