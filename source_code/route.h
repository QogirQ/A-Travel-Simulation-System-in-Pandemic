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
#include"logfile.h"
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

void findRoute(PSGR *tmp);	//根据形参中旅客生成最佳旅行计划
void dfsRoute(DPRT *tempDprt, PSGR *tempPsgr, CITY *tempCity, int step);	//带剪枝的dfs函数
unsigned int countTime(unsigned int a, unsigned int b);		//根据两个时间点计算耗时的简单函数