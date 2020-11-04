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
	printf("��ǰʱ��Ϊ��%d��%d:00\n", dayTime, hourTime % 24);
	fprintf(OutF,"��ǰʱ��Ϊ��%d��%d:00\n", dayTime, hourTime % 24);
	PSGR t;
	char tName[20];
	printf("��Ҫ��ӳ˿ͻ��ѯ��Ϣ�밴�����\n");
	if ( _kbhit() )
	{
		int tmp;
		while (1) 
		{
			printf("��ӳ˿��밴0����ѯ�˿��밴1����2��������\n");
			scanf("%d", &tmp);
			if (tmp == 0)
			{
				fprintf(OutF, "������0����ʼ��ӳ˿�\n");
				t.ID = psgrNum;
				printf("������˿�����:\n");
				scanf("%s", t.name);
				fprintf(OutF, "������˿�����Ϊ%s\n", t.name);

				printf("������˿ͳ�����:\n");
				scanf("%s", tName);
				fprintf(OutF, "������˿ͳ�����Ϊ%s\n", tName);
				for (int i = 0; i < CITYNUM; i++)
				{
					if (strcmp(tName, cities[i].name) == 0)
						t.start = &cities[i];
				}
				printf("������˿�Ŀ�ĵ�:\n");
				scanf("%s", tName);
				fprintf(OutF, "������˿�Ŀ�ĵ�Ϊ%s\n", tName);
				for (int i = 0; i < CITYNUM; i++)
				{
					if (strcmp(tName, cities[i].name) == 0)
						t.dest = &cities[i];
				}
				printf("������˿�����ʱ��:\n");
				scanf("%u", &t.timeLimit);
				fprintf(OutF, "������˿�����ʱ��Ϊ%u\n", t.timeLimit);

				t.startTime = hourTime;
				t.inCity = t.start;
				t.isInDeparture = false;
				passengerList[psgrNum] = t;
				psgrNum++;
				findRoute(&passengerList[psgrNum - 1]);
				while (travelPlans[psgrNum - 1].route[0] == NULL)
				{
					printf("�Ҳ���������ʱҪ������мƻ���\n");
					fprintf(OutF, "�Ҳ���������ʱҪ������мƻ���\n");

					printf("����������˿�����ʱ�䣺\n");
					scanf("%u", &passengerList[psgrNum - 1].timeLimit);
					fprintf(OutF, "��������˿�����ʱ��Ϊ%u\n", passengerList[psgrNum - 1].timeLimit);
					findRoute(&passengerList[psgrNum - 1]);
				}
				printPlan(&passengerList[psgrNum - 1]);
				PSGR *t = &passengerList[psgrNum - 1];
				PLAN p = travelPlans[t->ID];
				fprintf(OutF, "�˿�%d:%s�����мƻ����£�\n", t->ID, t->name);
				fprintf(OutF, "��ʼ�أ�%s\n", t->start->name);
				fprintf(OutF, "Ŀ�ĵأ�%s\n", p.dest->name);
				fprintf(OutF, "ʱ�����ƣ�%dСʱ\n", t->timeLimit);
				fprintf(OutF, "�ܷ��գ�%.1lf\n", p.risk);
				fprintf(OutF, "�ܺ�ʱ��%d\n", p.timeSpend);
				fprintf(OutF, "�������ĳ��ΰ�˳������:\n");
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
					fprintf(OutF, "������1����ʼ��ѯ�˿���Ϣ\n");
					printf("������Ҫ��ѯ�ĳ˿�����\n");
					char s[30];
					scanf("%s", s);
					fprintf(OutF, "������˿�����Ϊ%s\n", t.name);
					for (int i = 0; i < psgrNum; i++)
					{
						if (strcmp(passengerList[i].name, s) == 0)
						{
							printf("����\tID\t������\tĿ�ĵ�\t����ʱ��\t���ں���\t���ڳ���\n");
							fprintf(OutF, "����\tID\t������\tĿ�ĵ�\t����ʱ��\t���ں���\t���ڳ���\n");
							PSGR tmp = passengerList[i];
							printf("%s\t%d\t%s\t%s\t%dСʱ\t", tmp.name, tmp.ID, tmp.start->name, tmp.dest->name, tmp.timeLimit);
							fprintf(OutF,"%s\t%d\t%s\t%s\t%dСʱ\t", tmp.name, tmp.ID, tmp.start->name, tmp.dest->name, tmp.timeLimit);
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
					printf("��ǰ��δ����κγ˿ͣ��볢���������룡\n");
					fprintf(OutF, "��ǰ��δ����κγ˿ͣ��볢���������룡\n");
				}
			}
			else if (tmp ==2)
			{
				fprintf(OutF, "�Ѱ�2����������\n");
				break;
			}
			else
			{
				printf("�Ƿ����룡�볢���������룡\n");
				fprintf(OutF, "�Ƿ����룡\n");
			}
		}
	}	
	fclose(OutF);
}

void citiesInit()
{
	cities[0] = { 0, "�人", CITY_HIGH_RISK };
	cities[1] = { 1, "����", CITY_HIGH_RISK };
	cities[2] = { 2, "����", CITY_HIGH_RISK };
	cities[3] = { 3, "�Ϻ�", CITY_HIGH_RISK };
	cities[4] = { 4, "�ϲ�", CITY_MID_RISK };
	cities[5] = { 5, "����", CITY_MID_RISK };
	cities[6] = { 6, "��ɳ", CITY_MID_RISK };
	cities[7] = { 7, "����", CITY_MID_RISK };
	cities[8] = { 8, "����", CITY_LOW_RISK };
	cities[9] = { 9, "��ˮ", CITY_LOW_RISK };
	cities[10] = { 10, "����", CITY_LOW_RISK };
}

void departureInit()
{
	memset(departureTable, 0, (sizeof(DPRT)) * DPRTNUM);
	unsigned int sTime[DPRTNUM];
	for (int i = 0; i < DPRTNUM; i++) //����ʱ������
		sTime[i] = (i + 6) % 24;
	unsigned int dTime[DPRTNUM] = {
		//6 7   8 9   10 11   12 13   14 15
		8 ,9,  10,11,  13,14,  14,15,  17,18,
		//16 17   18 19   20 21   22 23   0 1
		22,23,   2,3,   0,1,    2,3,  4,5, 
		//2 3   4 5   6 7  8 9  10 11
		6,7,  7,8,  15,16,  11,12,  14,15,   
		//12,13  14,15, 16,17,   18,19,  20,21 �人ʼ��
		1, 2,     0,20,    3,21,    4,15,   6,13,
		//22,23  0,1,    2,3,    4,5,    6,7 ����ʼ��
		11, 21,   12,18,  23,0,  1,13,  10,23,     
		//8,9   10,11  12,13,  14,15  16,17����ʼ��
		21,7,  23,19,  20,22, 1,14, 12,14,
		//18,19  20,21,  22,23  0,1    2,3  �Ϻ�ʼ��
		   6,7,    9,6,    8,11,  16,20,  18,22,
		//4,5   6,7     8,9,  10,11  12,13  �ϲ�ʼ��
		9,22, 14,16, 15,16,  20,7,  6,10,   
		//14,15  16,17  18,19  20,21  22,23 ����ʼ��
		   1,12,   0,3,    1,5,    10,20,  17,19,   
		//0,1    2,3    4,5    6,7    8,9  ��ɳʼ��
		4,22,  11,15, 11,15,  13,4,   2,3,
		//10,11  12,13  14,15,  16,17  18,19����ʼ��
		  20,8,  23,5,  0,5,    23,16,  13,8,
		//20,21  22,23    0,1    2,3    4,5 ����ʼ��
		   16,5,   21,18,  20,0,  22,2,  12,21,
		//6,7    8,9   10,11  12,13  14,15 ��ˮʼ��
		 16,11,  4,1,   4,6,   6,8,   22,3,
		//16,17  18,19  20,21  22,23  0,1 ����ʼ��
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