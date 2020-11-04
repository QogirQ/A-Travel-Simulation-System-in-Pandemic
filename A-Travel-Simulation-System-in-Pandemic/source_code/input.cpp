#include"input.h"

void inputDetect()
{
	FILE *OutF;
	if ((OutF = fopen("LogFile.txt", "a+")) == NULL)
	{
		printf("can not open file!\n");
		exit(0);
	}
	printf("-------------------------------------------------\n");
	fprintf(OutF, "-------------------------------------------------\n");
	printf("当前时间为第%d天%d:00\n", dayTime, hourTime % 24);
	fprintf(OutF,"当前时间为第%d天%d:00\n", dayTime, hourTime % 24);
	PSGR t;
	char tName[20];
	printf("若要添加乘客或查询信息请按任意键\n");
	if ( _kbhit() )
	{
		int tmp;
		while (1) 
		{
			printf("添加乘客请按0，查询乘客请按1，按2结束输入\n");
			scanf("%d", &tmp);
			if (tmp == 0)
			{
				fprintf(OutF, "已输入0，开始添加乘客\n");
				t.ID = psgrNum;
				printf("请输入乘客姓名:\n");
				scanf("%s", t.name);
				fprintf(OutF, "已输入乘客姓名为%s\n", t.name);

				printf("请输入乘客出发地:\n");
				scanf("%s", tName);
				fprintf(OutF, "已输入乘客出发地为%s\n", tName);
				for (int i = 0; i < CITYNUM; i++)
				{
					if (strcmp(tName, cities[i].name) == 0)
						t.start = &cities[i];
				}
				printf("请输入乘客目的地:\n");
				scanf("%s", tName);
				fprintf(OutF, "已输入乘客目的地为%s\n", tName);
				for (int i = 0; i < CITYNUM; i++)
				{
					if (strcmp(tName, cities[i].name) == 0)
						t.dest = &cities[i];
				}
				printf("请输入乘客限制时间:\n");
				scanf("%u", &t.timeLimit);
				fprintf(OutF, "已输入乘客限制时间为%u\n", t.timeLimit);

				t.startTime = hourTime;
				t.inCity = t.start;
				t.isInDeparture = false;
				passengerList[psgrNum] = t;
				psgrNum++;
				findRoute(&passengerList[psgrNum - 1]);
				while (travelPlans[psgrNum - 1].route[0] == NULL)
				{
					printf("找不到符合限时要求的旅行计划！\n");
					fprintf(OutF, "找不到符合限时要求的旅行计划！\n");

					printf("请重新输入乘客限制时间：\n");
					scanf("%u", &passengerList[psgrNum - 1].timeLimit);
					fprintf(OutF, "重新输入乘客限制时间为%u\n", passengerList[psgrNum - 1].timeLimit);
					findRoute(&passengerList[psgrNum - 1]);
				}
				printPlan(&passengerList[psgrNum - 1]);
				PSGR *t = &passengerList[psgrNum - 1];
				PLAN p = travelPlans[t->ID];
				fprintf(OutF, "乘客%d:%s的旅行计划如下：\n", t->ID, t->name);
				fprintf(OutF, "起始地：%s\n", t->start->name);
				fprintf(OutF, "目的地：%s\n", p.dest->name);
				fprintf(OutF, "时间限制：%d小时\n", t->timeLimit);
				fprintf(OutF, "总风险：%.1lf\n", p.risk);
				fprintf(OutF, "总耗时：%d\n", p.timeSpend);
				fprintf(OutF, "所经过的车次按顺序如下:\n");
				int i = 0;
				while (travelPlans[t->ID].route[i])
				{
					switch (travelPlans[t->ID].route[i]->vehicle)
					{
					case 0:	fprintf(OutF, "C");	break;
					case 1:	fprintf(OutF, "T");	break;
					case 2:	fprintf(OutF, "A");	break;
					default:	break;
					}
					fprintf(OutF, "%d ", travelPlans[t->ID].route[i]->ID);
					i++;
				}
				fprintf(OutF, "\n");
				fprintf(OutF, "-------------------------------------------------------\n");
			}
			else if (tmp == 1)
			{
				if (psgrNum >= 1)
				{
					fprintf(OutF, "已输入1，开始查询乘客信息\n");
					printf("请输入要查询的乘客姓名\n");
					char s[30];
					scanf("%s", s);
					fprintf(OutF, "已输入乘客姓名为%s\n", t.name);
					for (int i = 0; i < psgrNum; i++)
					{
						if (strcmp(passengerList[i].name, s) == 0)
						{
							printf("姓名\tID\t出发地\t目的地\t限制时间\t所在航班\t所在城市\n");
							fprintf(OutF, "姓名\tID\t出发地\t目的地\t限制时间\t所在航班\t所在城市\n");
							PSGR tmp = passengerList[i];
							printf("%s\t%d\t%s\t%s\t%d小时\t", tmp.name, tmp.ID, tmp.start->name, tmp.dest->name, tmp.timeLimit);
							fprintf(OutF,"%s\t%d\t%s\t%s\t%d小时\t", tmp.name, tmp.ID, tmp.start->name, tmp.dest->name, tmp.timeLimit);
							if (tmp.isInDeparture == true)
							{
								switch (tmp.inDeparture->vehicle)
								{
								case 0:	printf("C"); fprintf(OutF, "C");  break;
								case 1:	printf("T"); fprintf(OutF, "T"); 	break;
								case 2:	printf("A");	fprintf(OutF, "A"); break;
								default:	break;
								}
								printf("%d\t\t", tmp.inDeparture->ID);
								fprintf(OutF, "%d\t\t", tmp.inDeparture->ID);
							}
							else
							{
								printf("null\t\t%s\n", tmp.inCity->name);
								fprintf(OutF, "null\t\t%s\n", tmp.inCity->name);
							}
						}
					}
				}
				else
				{
					printf("当前还未添加任何乘客！请尝试重新输入！\n");
					fprintf(OutF, "当前还未添加任何乘客！请尝试重新输入！\n");
				}
			}
			else if (tmp ==2)
			{
				fprintf(OutF, "已按2，结束输入\n");
				break;
			}
			else
			{
				printf("非法输入！请尝试重新输入！\n");
				fprintf(OutF, "非法输入！\n");
			}
		}
	}	
	fclose(OutF);
}

void citiesInit()
{
	cities[0] = { 0, "武汉", CITY_HIGH_RISK };
	cities[1] = { 1, "北京", CITY_HIGH_RISK };
	cities[2] = { 2, "深圳", CITY_HIGH_RISK };
	cities[3] = { 3, "上海", CITY_HIGH_RISK };
	cities[4] = { 4, "南昌", CITY_MID_RISK };
	cities[5] = { 5, "福州", CITY_MID_RISK };
	cities[6] = { 6, "长沙", CITY_MID_RISK };
	cities[7] = { 7, "重庆", CITY_MID_RISK };
	cities[8] = { 8, "大连", CITY_LOW_RISK };
	cities[9] = { 9, "衡水", CITY_LOW_RISK };
	cities[10] = { 10, "兰州", CITY_LOW_RISK };
}

void departureInit()
{
	memset(departureTable, 0, (sizeof(DPRT)) * DPRTNUM);
	unsigned int sTime[DPRTNUM];
	for (int i = 0; i < DPRTNUM; i++) //发车时间数组
		sTime[i] = (i + 6) % 24;
	unsigned int dTime[DPRTNUM] = {
		//6 7   8 9   10 11   12 13   14 15
		8 ,9,  10,11,  13,14,  14,15,  17,18,
		//16 17   18 19   20 21   22 23   0 1
		22,23,   2,3,   0,1,    2,3,  4,5, 
		//2 3   4 5   6 7  8 9  10 11
		6,7,  7,8,  15,16,  11,12,  14,15,   
		//12,13  14,15, 16,17,   18,19,  20,21 武汉始发
		1, 2,     0,20,    3,21,    4,15,   6,13,
		//22,23  0,1,    2,3,    4,5,    6,7 北京始发
		11, 21,   12,18,  23,0,  1,13,  10,23,     
		//8,9   10,11  12,13,  14,15  16,17深圳始发
		21,7,  23,19,  20,22, 1,14, 12,14,
		//18,19  20,21,  22,23  0,1    2,3  上海始发
		   6,7,    9,6,    8,11,  16,20,  18,22,
		//4,5   6,7     8,9,  10,11  12,13  南昌始发
		9,22, 14,16, 15,16,  20,7,  6,10,   
		//14,15  16,17  18,19  20,21  22,23 福州始发
		   1,12,   0,3,    1,5,    10,20,  17,19,   
		//0,1    2,3    4,5    6,7    8,9  长沙始发
		4,22,  11,15, 11,15,  13,4,   2,3,
		//10,11  12,13  14,15,  16,17  18,19重庆始发
		  20,8,  23,5,  0,5,    23,16,  13,8,
		//20,21  22,23    0,1    2,3    4,5 大连始发
		   16,5,   21,18,  20,0,  22,2,  12,21,
		//6,7    8,9   10,11  12,13  14,15 衡水始发
		 16,11,  4,1,   4,6,   6,8,   22,3,
		//16,17  18,19  20,21  22,23  0,1 兰州始发
		   8,9,   15,14,  17,17,  16,12,  16,13
	};

	for (int i = 0; i < 10; i++)
	{
		departureTable[i].ID = i;
		departureTable[i].vehicle = AIR;
		departureTable[i].risk = AIR_RISK;
	}
	departureTable[0].start = &cities[0];	departureTable[0].startTime = 8;
	departureTable[0].dest = &cities[1];	departureTable[0].arriveTime = 10;

	departureTable[1].start = &cities[1];	departureTable[1].startTime = 10;
	departureTable[1].dest = &cities[0];	departureTable[1].arriveTime = 12;

	departureTable[2].start = &cities[0];	departureTable[2].startTime = 10;
	departureTable[2].dest = &cities[2];	departureTable[2].arriveTime = 13;

	departureTable[3].start = &cities[2];	departureTable[3].startTime = 13;
	departureTable[3].dest = &cities[0];	departureTable[3].arriveTime = 16;

	departureTable[4].start = &cities[1];	departureTable[4].startTime = 14;
	departureTable[4].dest = &cities[2];	departureTable[4].arriveTime = 16;

	departureTable[5].start = &cities[2];	departureTable[5].startTime = 16;
	departureTable[5].dest = &cities[1];	departureTable[5].arriveTime = 18;

	departureTable[6].start = &cities[2];	departureTable[6].startTime = 18;
	departureTable[6].dest = &cities[3];	departureTable[6].arriveTime = 20;

	departureTable[7].start = &cities[3];	departureTable[7].startTime = 20;
	departureTable[7].dest = &cities[2];	departureTable[7].arriveTime = 22;

	departureTable[8].start = &cities[1];	departureTable[8].startTime = 9;
	departureTable[8].dest = &cities[5];	departureTable[8].arriveTime = 12;

	departureTable[9].start = &cities[5];	departureTable[9].startTime = 13;
	departureTable[9].dest = &cities[1];	departureTable[9].arriveTime = 16;


	for (int i = 10; i < 30; i += 2)
	{
		departureTable[i].ID = i;
		departureTable[i].vehicle = TRAIN;
		departureTable[i].risk = TRAIN_RISK;
		departureTable[i].start = &cities[(i - 10) / 2];
		//departureTable[i].startTime = (6 + i - 10) % 24;
		departureTable[i].dest = &cities[(i - 10) / 2 + 1];
		//departureTable[i].arriveTime = (10 + i - 10) % 24;
	}

	for (int i = 11; i < 30; i += 2)
	{
		departureTable[i].ID = i;
		departureTable[i].vehicle = TRAIN;
		departureTable[i].risk = TRAIN_RISK;
		departureTable[i].start = &cities[(i - 10 + 1) / 2];
		//departureTable[i].startTime = (10 + i - 10) % 24;
		departureTable[i].dest = &cities[(i - 10) / 2];
		//departureTable[i].arriveTime = (14 + i - 10) % 24;
	}

	for (int i = 30; i < DPRTNUM; i++)
	{
		departureTable[i].ID = i;
		departureTable[i].vehicle = CAR;
		departureTable[i].risk = CAR_RISK;
	}

	int k = 30;
	for (int i = 0; i < CITYNUM; i++)
	{
		for (int j = 0; j < CITYNUM; j++)
		{
			if (i != j)
			{
				departureTable[k].start = &cities[i];
				departureTable[k].dest = &cities[j];
				k++;
				if (k >= DPRTNUM) break;
			}
		}
		if (k >= DPRTNUM) break;
	}
	for (int i = 0; i < DPRTNUM; i++)
	{
		departureTable[i].startTime = sTime[i];
		departureTable[i].arriveTime = dTime[i];
	}
}