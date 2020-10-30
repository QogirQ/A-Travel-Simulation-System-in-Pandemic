#include"route.h"

bool vis[CITYNUM+10];		//dfs��Ҫ�õ��Ľ��������
double minR[CITYNUM][5010];	//minR[i][j]��ʾ����ʼ�㵽����i������ʱ��Ϊj������·���ķ���ֵ
double minRisk;				//��С����ֵ
double totalRisk;			//��ǰ�ܷ���ֵ
unsigned int totalTime;		//��ǰ������ʱ��
DPRT *tRoute[1000][1000];	//�洢dfs�ҵ�����������·��
double tRisk[1000];			//�洢ÿһ������·�����ܷ���ֵ
unsigned int tTime[1000];	//�洢ÿһ������·������ʱ�仨��
int routeNum;				//dfs�ҵ������мƻ�����

//����aʱ����bʱ�̵�ʱ���ֵ��aΪ��ǰ��ʱ��,bΪ�Ϻ��ʱ��
unsigned int countTime(unsigned int a, unsigned int b)
{
	if (int((int)b - (int)a) >= 0) return (b - a);
	else return (b + 24 - a);
}

void dfsRoute(DPRT *tempDprt, PSGR *tempPsgr, CITY *tempCity, int step)
{
	if (step > 0) //���ÿͲ�����ʼ״̬
	{
		if (tempDprt->dest->ID == tempPsgr->dest->ID)//��ǰ���೵����ֱ�ӵ����յ�
		{
			//printf("�����ܵ����յ�\n");
			//����������·
			for (int i = 0; i < step; i++)
			{
				tRoute[routeNum][i] = travelPlans[tempPsgr->ID].route[i];
			}
			routeNum++;
			//printf("minRisk== %lf\n", minRisk);
			minRisk = min(minRisk, totalRisk);//�ؼ�һ��������ȡ����С����
			//printf("�޸ĺ�minRisk== %lf\n", minRisk);
			//printf("travelPlans[%d].risk = %lf\n", tempPsgr->ID, minRisk);
			return;
		}
		for (int i = 0; i < DPRTNUM; i++)//�������к��೵��
		{
			if (departureTable[i].start->ID == tempCity->ID)
			{
				if (!vis[departureTable[i].dest->ID])//��Ŀ�ĳ��л�δ����
				{
					//printf("step==%d������������/����:IDΪ%d��Ŀ�ĵ�Ϊ%s\n", step, departureTable[i].ID, departureTable[i].dest->name);
					//����ʱ�䣬����ʱ�����������Լ�֦��
					unsigned int timeAdd = countTime(departureTable[i].startTime, departureTable[i].arriveTime)
						+ countTime(tempDprt->arriveTime, departureTable[i].startTime);//���˺���ʱ��+�ڵ�ǰ����ͣ��ʱ��
					unsigned int spend = totalTime + timeAdd;
					if (tempPsgr->timeLimit && spend > tempPsgr->timeLimit)
					{
						//printf("��ʱΪ%d, ��ʱ�������˼ƻ�\n", spend);
						continue; //����ʱ������	
					}

					//ͨ���ȽϷ��ս��м�֦�������Լ�֦��
					double riskAdd = (departureTable[i].risk * countTime(departureTable[i].startTime, departureTable[i].arriveTime) )//�ڵ�ǰ����ͣ���ķ���+���˺���ķ���
						+ (tempCity->risk * countTime(tempDprt->arriveTime, departureTable[i].startTime) );
					if (totalRisk + riskAdd >= minRisk ||
						totalRisk + riskAdd >= minR[departureTable[i].dest->ID][spend])
					{
						//printf("���շ����ţ������˼ƻ�\n");
						continue;
					}
					//�ۼӼ����ʱ�ͷ���
					totalTime += timeAdd;
					totalRisk += riskAdd;

					minR[departureTable[i].dest->ID][spend] = totalRisk;
					vis[departureTable[i].dest->ID] = 1; //���
					travelPlans[tempPsgr->ID].route[step] = &departureTable[i];
					//printf("�ۼ��ܷ���Ϊ%lf����ʱΪ%d\n", totalRisk, totalTime);

					dfsRoute(&departureTable[i], tempPsgr, departureTable[i].dest, step + 1);  //����DFS����

					vis[departureTable[i].dest->ID] = 0;//����
					totalRisk -=riskAdd;	
					totalTime -= timeAdd;
					travelPlans[tempPsgr->ID].route[step] = NULL;
					//printf("step==%d, travelPlans[%d].risk = %lf\n", step, tempPsgr->ID, travelPlans[tempPsgr->ID].risk);
				}
			}
		}
		return;
	}
	else //���ÿʹ�����ʼ״̬ step == 0; ע���ÿ�����յ㲻������ͬ
	{
		for (int i = 0; i < DPRTNUM; i++)//�������к��೵��
		{
			if (departureTable[i].start->ID == tempCity->ID)
			{
				if (!vis[departureTable[i].dest->ID])//��Ŀ�ĳ��л�δ����
				{
					//printf("step== %d������������/����:IDΪ%d��Ŀ�ĵ�Ϊ%s\n", step, departureTable[i].ID, departureTable[i].dest->name);

					//����ʱ�䣬����ʱ�����������Լ�֦��
					unsigned int timeAdd = countTime(departureTable[i].startTime, departureTable[i].arriveTime)
						+ countTime(tempPsgr->startTime % 24, departureTable[i].startTime);//���˺���ʱ��+�ڵ�ǰ����ͣ��ʱ��
					unsigned int spend = totalTime + timeAdd;
					
					if (tempPsgr->timeLimit && spend > tempPsgr->timeLimit)	continue; //����ʱ������	

					//ͨ���ȽϷ��ս��м�֦�������Լ�֦��
					double riskAdd = (departureTable[i].risk * countTime(departureTable[i].startTime, departureTable[i].arriveTime) )//�ڵ�ǰ����ͣ���ķ���+���˺���ķ���
						+ (tempCity->risk * countTime(tempPsgr->startTime % 24, departureTable[i].startTime) );
					if (totalRisk + riskAdd >= minRisk ||
						totalRisk + riskAdd >= minR[departureTable[i].dest->ID][spend])
						continue;

					//�ۼӼ����ʱ�ͷ���
					totalTime += timeAdd;
					totalRisk += riskAdd;

					minR[departureTable[i].dest->ID][spend] = totalRisk;
					vis[departureTable[i].dest->ID] = 1; //���
					travelPlans[tempPsgr->ID].route[step] = &departureTable[i];
					//printf("�ۼ��ܷ���Ϊ%lf����ʱΪ%d\n", totalRisk, totalTime);

					dfsRoute(&departureTable[i], tempPsgr, departureTable[i].dest, step + 1);  //����DFS����
					//����
					vis[departureTable[i].dest->ID] = 0;
					totalRisk -= riskAdd;
					totalTime -= timeAdd;
					travelPlans[tempPsgr->ID].route[step] = NULL;
				}
			}
		}
		return;
	}
}

void findRoute(PSGR *tmp)
{
	for (int i = 0; i < CITYNUM; i++)
	{
		for (int j = 0; j < 5010; j++)
		{
			minR[i][j] = DBL_MAX;
		}
	}
	minRisk = DBL_MAX;
	
	memset(vis, 0, sizeof(vis));

	travelPlans[tmp->ID].psgrID = tmp->ID;
	travelPlans[tmp->ID].startTime = tmp->startTime % 24;
	travelPlans[tmp->ID].risk = travelPlans[tmp->ID].timeSpend = 0;
	totalRisk= totalTime = 0;
	travelPlans[tmp->ID].dest = tmp->dest;
	vis[tmp->start->ID] = 1;

	routeNum = 0;
	memset(tRisk, 0, sizeof(tRisk));
	memset(tTime, 0, sizeof(tTime));
	memset(tRoute, 0, sizeof(tRoute));
	//printf("��ʼ���ɳ˿�%d�����мƻ�:\n",tmp->ID);
	dfsRoute(&departureTable[0], tmp, tmp->start, 0);
	//printf("RouteNum=%d\n", routeNum);
	if (routeNum == 0)
	{
		return;
	}

	//��tRoute�л�ȡ��С����·��
	int k = 0;
	double min = DBL_MAX;
	//printf("RouteNum = %d\n", routeNum);
	for (int i = 0; i < routeNum; i++)
	{
		for (int j = 0; tRoute[i][j] != 0; j++)
		{
			if (j == 0)
			{
				tTime[i] += ( countTime(tmp->startTime, tRoute[i][j]->startTime) 
					+ countTime(tRoute[i][j]->startTime, tRoute[i][j]->arriveTime) );
				tRisk[i] += ( (tmp->inCity->risk * countTime(tmp->startTime, tRoute[i][j]->startTime) ) //��ʼ����ͣ������+��һ�����
					+ (tRoute[i][j]->risk * countTime(tRoute[i][j]->startTime, tRoute[i][j]->arriveTime) ) );
			}
			else
			{
				tTime[i] += ( countTime(tRoute[i][j - 1]->arriveTime, tRoute[i][j]->startTime)
					+ countTime(tRoute[i][j]->startTime, tRoute[i][j]->arriveTime) );
				tRisk[i] += ((tRoute[i][j]->start->risk * countTime(tRoute[i][j - 1]->arriveTime, tRoute[i][j]->startTime) )//���к򳵷���+�������
					+ (tRoute[i][j]->risk * countTime(tRoute[i][j]->startTime, tRoute[i][j]->arriveTime) ) );
			}
		}
		if (tRisk[i] < min )
		{
			min = tRisk[i];
			k = i;
		}
	}
	//printf("min = %lf, minRisk = %lf\n", min, minRisk);
	travelPlans[tmp->ID].risk = minRisk;
	travelPlans[tmp->ID].timeSpend = tTime[k];
	int j = 0;
	
	//����ʱ�������ټƻ����浽travelPlans��
	while (tRoute[k][j])
	{
		travelPlans[tmp->ID].route[j] = tRoute[k][j];
		j++;
	}
}
