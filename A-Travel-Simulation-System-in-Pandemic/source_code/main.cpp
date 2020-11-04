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

CITY cities[CITYNUM];				//�洢���е�����
DPRT departureTable[DPRTNUM];		//�洢���ε�����
PSGR passengerList[MAX_PSGRNUM];	//�洢�ÿ͵�����
PLAN travelPlans[MAX_PSGRNUM];		//�洢�ÿ����мƻ�������
int dayTime;						//����Ϊ��λ������ʱ�䣬��ʼֵΪ0������0��
int hourTime;						//��СʱΪ��λ������ʱ��
int psgrNum;						//�˿�����

int main()
{
	dayTime = 0;
	hourTime = 5;				//�ӵ�0��5:00��ʼ���г���
	psgrNum = 0;				//��ʼ���˿�����Ϊ0
	citiesInit();				//��ʼ�����У����೵�Σ��ÿͣ����мƻ�
	departureInit();
	memset(passengerList, 0, (sizeof(PSGR)) * MAX_PSGRNUM);
	memset(travelPlans, 0, sizeof(travelPlans));

	//printDprt();
	//fPrintDprt();
	initgraph(1200, 700, SHOWCONSOLE);//��ʼ������
	while (1)
	{
		drawCityMap();		//���Ƴ��е�ͼ
		drawInfo();			//����ʱ����Ϣ
		changeState();		//�ı��ÿ�״̬
		inputDetect();		//ʵʱ�������
		changeState();		//�ı��ÿ�״̬
		printPsgr();		//�����д�ӡ�ÿ�״̬��Ϣ
		fPrintPsgr();		//��־�ļ���ӡ�ÿ�״̬��Ϣ
		drawPsgr();			//�����ÿ�
		Sleep(SLEEPTIME);	//ÿ��10����������һ��Сʱ
		hourTime ++;		//ʱ������
		dayTime = hourTime/24;
		cleardevice();		//����
	}
	closegraph();			//�رջ���
	return 0;
}
