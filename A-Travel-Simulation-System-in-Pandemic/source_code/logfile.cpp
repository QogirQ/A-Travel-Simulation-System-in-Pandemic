#include"logfile.h"

void fPrintDprt()
{
	FILE *OutF;
	if ((OutF = fopen("LogFile.txt", "a+")) == NULL)
	{ 
		printf("can not open file!\n");
		exit(0);
	}
	fprintf(OutF, "--------------------DepartureInfo---------------------\n");
	fprintf(OutF, "ID\t类型\t起点\t出发时间\t终点\t到达时间\n");
	for (int i = 0; i < DPRTNUM; i++)
	{
		DPRT tmp = departureTable[i];
		fprintf(OutF,"%d\t", tmp.ID);
		switch (tmp.vehicle)
		{
		case 0:	fprintf(OutF, "CAR\t");	break;
		case 1:	fprintf(OutF, "TRAIN\t");	break;
		case 2:	fprintf(OutF, "AIR\t");	break;
		default:	break;
		}
		fprintf(OutF, "%s\t", tmp.start->name);
		fprintf(OutF, "%d:00\t", tmp.startTime);
		fprintf(OutF, "%s\t", tmp.dest->name);
		fprintf(OutF, "%d:00\t", tmp.arriveTime);
		fprintf(OutF, "\n");
	}
	fprintf(OutF, "-------------------------------------------------------\n");
	fclose(OutF);
}

void fPrintPsgr()
{
	FILE *OutF;
	if ((OutF = fopen("LogFile.txt", "a+")) == NULL)
	{
		printf("can not open file!\n");
		exit(0);
	}
	//fprintf(OutF,"*******当前时间为第%d天%d:00********\n", dayTime, hourTime % 24);
	fprintf(OutF, "--------------------PassengerInfo---------------------\n");
	fprintf(OutF, "姓名\tID\t出发地\t目的地\t限制时间\t所在航班\t所在城市\n");
	for (int i = 0; i < psgrNum; i++)
	{
		PSGR tmp = passengerList[i];
		fprintf(OutF, "%s\t%d\t%s\t%s\t%d小时\t", tmp.name, tmp.ID, tmp.start->name, tmp.dest->name, tmp.timeLimit);
		if (tmp.isInDeparture == true)
		{
			switch (tmp.inDeparture->vehicle)
			{
			case 0:	fprintf(OutF, "C");	break;
			case 1:	fprintf(OutF, "T");	break;
			case 2:	fprintf(OutF, "A");	break;
			default:	break;
			}
			fprintf(OutF, "%d\t", tmp.inDeparture->ID);
			fprintf(OutF, "null\n");
		}
		else
		{
			fprintf(OutF, "null\t%s\n", tmp.inCity->name);
		}
	}
	fprintf(OutF, "-------------------------------------------------------\n");
	fclose(OutF);
}

//void fPrintPlan(PSGR *t)
//{
//	FILE *OutF;
//	if ((OutF = fopen("LogFile.txt", "a+")) == NULL)
//	{
//		printf("can not open file!\n");
//		exit(0);
//	}
//	PLAN p = travelPlans[t->ID];
//	fprintf(OutF, "乘客%d:%s的旅行计划如下：\n", t->ID, t->name);
//	fprintf(OutF, "起始地：%s\n", t->start->name);
//	fprintf(OutF, "目的地：%s\n", p.dest->name);
//	fprintf(OutF, "时间限制：%d小时\n", t->timeLimit);
//	fprintf(OutF, "总风险：%.1lf\n", p.risk);
//	fprintf(OutF, "总耗时：%d\n", p.timeSpend);
//	fprintf(OutF, "所经过的车次按顺序如下:\n");
//	int i = 0;
//	while (travelPlans[t->ID].route[i])
//	{
//		switch (travelPlans[t->ID].route[i]->vehicle)
//		{
//		case 0:	fprintf(OutF, "C");	break;
//		case 1:	fprintf(OutF, "T");	break;
//		case 2:	fprintf(OutF, "A");	break;
//		default:	break;
//		}
//		fprintf(OutF, "%d ", travelPlans[t->ID].route[i]->ID);
//		i++;
//	}
//	fprintf(OutF, "\n");
//	fprintf(OutF, "-------------------------------------------------------\n");
//	fclose(OutF);
//}

void printDprt()
{
	printf("--------------------DepartureInfo---------------------\n");
	printf("ID\t类型\t起点\t出发时间\t终点\t到达时间\n");
	for (int i = 0; i < DPRTNUM; i++)
	{
		DPRT tmp = departureTable[i];
		printf("%d\t", tmp.ID);
		switch (tmp.vehicle)
		{
		case 0:	printf("CAR\t");	break;
		case 1:	printf("TRAIN\t");	break;
		case 2:	printf("AIR\t");	break;
		default:	break;
		}
		printf("%s\t", tmp.start->name);
		printf("%d:00\t", tmp.startTime);
		printf("%s\t", tmp.dest->name);
		printf("%d:00\t", tmp.arriveTime);
		printf("\n");
	}
	printf("-------------------------------------------------------\n");
}

void printPsgr()
{
	printf("--------------------PassengerInfo---------------------\n");
	printf("姓名\tID\t出发地\t目的地\t限制时间\t所在航班\t所在城市\n");
	for (int i = 0; i < psgrNum; i++)
	{
		PSGR tmp = passengerList[i];
		printf("%s\t%d\t%s\t%s\t%d小时\t\t", tmp.name, tmp.ID, tmp.start->name, tmp.dest->name, tmp.timeLimit);
		if (tmp.isInDeparture == true)
		{
			switch (tmp.inDeparture->vehicle)
			{
			case 0:	printf("C");	break;
			case 1:	printf("T");	break;
			case 2:	printf("A");	break;
			default:	break;
			}
			printf("%d\t\t", tmp.inDeparture->ID);
			printf("null\n");
		}
		else
		{
			printf("null\t\t%s\n", tmp.inCity->name);
		}
	}
	printf("-------------------------------------------------------\n");
}

void printPlan(PSGR *t)
{
	PLAN p = travelPlans[t->ID];
	printf("乘客%d:%s的旅行计划如下：\n", t->ID, t->name);
	printf("起始地：%s\n",t->start->name);
	printf("目的地：%s\n",p.dest->name);
	printf("时间限制：%d小时\n", t->timeLimit);
	printf("总风险：%.1lf\n", p.risk);
	printf("总耗时：%d\n", p.timeSpend);
	printf("所经过车次按顺序如下:\n");
	int i = 0;
	while (travelPlans[t->ID].route[i])
	{
		switch (travelPlans[t->ID].route[i]->vehicle)
		{
		case 0:	printf("C");	break;
		case 1:	printf("T");	break;
		case 2:	printf("A");	break;
		default:	break;
		}
		printf("%d ", travelPlans[t->ID].route[i]->ID);
		i++;
	}
	printf("\n");
	printf("-------------------------------------------------------\n");
}
