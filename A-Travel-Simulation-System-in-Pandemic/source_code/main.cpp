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
#include"draw.h"

CITY cities[CITYNUM];				//存储城市的数组
DPRT departureTable[DPRTNUM];		//存储车次的数组
PSGR passengerList[MAX_PSGRNUM];	//存储旅客的数组
PLAN travelPlans[MAX_PSGRNUM];		//存储旅客旅行计划的数组
int dayTime;						//以天为单位计数的时间，初始值为0，即第0天
int hourTime;						//以小时为单位计数的时间
int psgrNum;						//乘客数量

int main()
{
	dayTime = 0;
	hourTime = 5;				//从第0天5:00开始运行程序
	psgrNum = 0;				//初始化乘客数量为0
	citiesInit();				//初始化城市，航班车次，旅客，旅行计划
	departureInit();
	memset(passengerList, 0, (sizeof(PSGR)) * MAX_PSGRNUM);
	memset(travelPlans, 0, sizeof(travelPlans));

	//printDprt();
	//fPrintDprt();
	initgraph(1200, 700, SHOWCONSOLE);//初始化画布
	while (1)
	{
		drawCityMap();		//绘制城市地图
		drawInfo();			//绘制时间信息
		changeState();		//改变旅客状态
		inputDetect();		//实时检测输入
		changeState();		//改变旅客状态
		printPsgr();		//命令行打印旅客状态信息
		fPrintPsgr();		//日志文件打印旅客状态信息
		drawPsgr();			//绘制旅客
		Sleep(SLEEPTIME);	//每隔10秒左右推移一个小时
		hourTime ++;		//时间推移
		dayTime = hourTime/24;
		cleardevice();		//清屏
	}
	closegraph();			//关闭画布
	return 0;
}
