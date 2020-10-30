#include"draw.h"

CITYPOINT cp[11];

void drawInfo()
{
	settextcolor(BLACK);
	settextstyle(25, 0, _T("宋体"));
	setbkmode(TRANSPARENT);

	TCHAR s[100];
	_stprintf(s, "当前时间为第%d天%d:00", dayTime, hourTime % 24);
	outtextxy(900, 50, s);
}

void drawCityMap()
{
	setbkcolor(WHITE);
	cleardevice();
	IMAGE mapImage;
	loadimage(&mapImage, _T("map.jpg"), 850, 650);
	putimage(0, 0, &mapImage);

	setlinecolor(RED);
	settextcolor(BLUE);
	settextstyle(15, 0, _T("宋体"));
	setbkmode(TRANSPARENT);
	cp[0] = {630, 420 }; cp[1] = {635, 245 }; cp[3] = {740,400 }; cp[2] = {630, 570 }; 
	cp[4] = {650, 455 }; cp[5] = {710, 500 }; cp[6] = {595, 470 }; cp[7] = {500, 450 };
	cp[8] = {720, 255 }; cp[9] = {625, 295 }; cp[10] = {445, 330 };

	for (int i = 0; i < CITYNUM; i++)//输出城市名字
	{
		outtextxy(cp[i].x, cp[i].y, cities[i].name);
	}
	
}

void drawPsgr()//绘制乘客
{
	settextcolor(RED);
	settextstyle(15, 0, _T("宋体"));
	setbkmode(TRANSPARENT);
	setlinecolor(MAGENTA);

	int psgrInCity[CITYNUM];
	memset(psgrInCity, 0, sizeof(psgrInCity));
	for (int i = 0; i < psgrNum; i++)
	{
		TCHAR s[100];
		PSGR *p = &passengerList[i];
		if (p->isInDeparture == false) //旅客在城市中
		{
			//此城市每有一个乘客，输出的名字位置就向下调一点
			psgrInCity[p->inCity->ID]++;
			_stprintf(s, _T("以下旅客在%s:"), p->inCity->name);
			outtextxy(cp[p->inCity->ID].x, cp[p->inCity->ID].y + 15, s);
			outtextxy(cp[p->inCity->ID].x, cp[p->inCity->ID].y + 15*( psgrInCity[p->inCity->ID]+1 ), p->name);
		}
		else //旅客在航班中
		{
			//在航班的起点和终点之前画一条直线
			int startX, startY, destX, destY;
			startX = cp[p->inDeparture->start->ID].x;
			startY = cp[p->inDeparture->start->ID].y;
			destX = cp[p->inDeparture->dest->ID].x;
			destY = cp[p->inDeparture->dest->ID].y;
			line(startX, startY, destX, destY);
			switch (p->inDeparture->vehicle)
			{
			case 0: _stprintf(s, _T("以下乘客在C%d中:"), p->inDeparture->ID);	break;
			case 1: _stprintf(s, _T("以下乘客在T%d中:"), p->inDeparture->ID); break;
			case 2: _stprintf(s, _T("以下乘客在A%d中:"), p->inDeparture->ID); break;
			default:	break;
			}
			outtextxy((startX + destX) / 2, (startY + destY) / 2, s);
			outtextxy((startX+destX)/2, (startY+destY)/2 + 15, p->name);
		}
	}
}