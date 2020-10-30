#include"route.h"

bool vis[CITYNUM+10];		//dfs需要用到的结点标记数组
double minR[CITYNUM][5010];	//minR[i][j]表示从起始点到城市i，花费时间为j的最优路径的风险值
double minRisk;				//最小风险值
double totalRisk;			//当前总风险值
unsigned int totalTime;		//当前花费总时间
DPRT *tRoute[1000][1000];	//存储dfs找到的所有旅行路径
double tRisk[1000];			//存储每一条旅行路径的总风险值
unsigned int tTime[1000];	//存储每一条旅行路径的总时间花费
int routeNum;				//dfs找到的旅行计划数量

//计算a时刻与b时刻的时间差值，a为较前的时刻,b为较后的时刻
unsigned int countTime(unsigned int a, unsigned int b)
{
	if (int((int)b - (int)a) >= 0) return (b - a);
	else return (b + 24 - a);
}

void dfsRoute(DPRT *tempDprt, PSGR *tempPsgr, CITY *tempCity, int step)
{
	if (step > 0) //若旅客不是起始状态
	{
		if (tempDprt->dest->ID == tempPsgr->dest->ID)//当前航班车次能直接到达终点
		{
			//printf("航班能到达终点\n");
			//保存旅行线路
			for (int i = 0; i < step; i++)
			{
				tRoute[routeNum][i] = travelPlans[tempPsgr->ID].route[i];
			}
			routeNum++;
			//printf("minRisk== %lf\n", minRisk);
			minRisk = min(minRisk, totalRisk);//关键一步，最终取得最小风险
			//printf("修改后minRisk== %lf\n", minRisk);
			//printf("travelPlans[%d].risk = %lf\n", tempPsgr->ID, minRisk);
			return;
		}
		for (int i = 0; i < DPRTNUM; i++)//遍历所有航班车次
		{
			if (departureTable[i].start->ID == tempCity->ID)
			{
				if (!vis[departureTable[i].dest->ID])//若目的城市还未经过
				{
					//printf("step==%d，搜索到航班/车次:ID为%d，目的地为%s\n", step, departureTable[i].ID, departureTable[i].dest->name);
					//计算时间，若超时则丢弃（可行性剪枝）
					unsigned int timeAdd = countTime(departureTable[i].startTime, departureTable[i].arriveTime)
						+ countTime(tempDprt->arriveTime, departureTable[i].startTime);//将乘航班时间+在当前城市停留时间
					unsigned int spend = totalTime + timeAdd;
					if (tempPsgr->timeLimit && spend > tempPsgr->timeLimit)
					{
						//printf("耗时为%d, 超时，放弃此计划\n", spend);
						continue; //超出时间限制	
					}

					//通过比较风险进行剪枝（最优性剪枝）
					double riskAdd = (departureTable[i].risk * countTime(departureTable[i].startTime, departureTable[i].arriveTime) )//在当前城市停留的风险+将乘航班的风险
						+ (tempCity->risk * countTime(tempDprt->arriveTime, departureTable[i].startTime) );
					if (totalRisk + riskAdd >= minRisk ||
						totalRisk + riskAdd >= minR[departureTable[i].dest->ID][spend])
					{
						//printf("风险非最优，放弃此计划\n");
						continue;
					}
					//累加计算耗时和风险
					totalTime += timeAdd;
					totalRisk += riskAdd;

					minR[departureTable[i].dest->ID][spend] = totalRisk;
					vis[departureTable[i].dest->ID] = 1; //标记
					travelPlans[tempPsgr->ID].route[step] = &departureTable[i];
					//printf("累计总风险为%lf，耗时为%d\n", totalRisk, totalTime);

					dfsRoute(&departureTable[i], tempPsgr, departureTable[i].dest, step + 1);  //继续DFS搜索

					vis[departureTable[i].dest->ID] = 0;//回溯
					totalRisk -=riskAdd;	
					totalTime -= timeAdd;
					travelPlans[tempPsgr->ID].route[step] = NULL;
					//printf("step==%d, travelPlans[%d].risk = %lf\n", step, tempPsgr->ID, travelPlans[tempPsgr->ID].risk);
				}
			}
		}
		return;
	}
	else //若旅客处在起始状态 step == 0; 注意旅客起点终点不允许相同
	{
		for (int i = 0; i < DPRTNUM; i++)//遍历所有航班车次
		{
			if (departureTable[i].start->ID == tempCity->ID)
			{
				if (!vis[departureTable[i].dest->ID])//若目的城市还未经过
				{
					//printf("step== %d，搜索到航班/车次:ID为%d，目的地为%s\n", step, departureTable[i].ID, departureTable[i].dest->name);

					//计算时间，若超时则丢弃（可行性剪枝）
					unsigned int timeAdd = countTime(departureTable[i].startTime, departureTable[i].arriveTime)
						+ countTime(tempPsgr->startTime % 24, departureTable[i].startTime);//将乘航班时间+在当前城市停留时间
					unsigned int spend = totalTime + timeAdd;
					
					if (tempPsgr->timeLimit && spend > tempPsgr->timeLimit)	continue; //超出时间限制	

					//通过比较风险进行剪枝（最优性剪枝）
					double riskAdd = (departureTable[i].risk * countTime(departureTable[i].startTime, departureTable[i].arriveTime) )//在当前城市停留的风险+将乘航班的风险
						+ (tempCity->risk * countTime(tempPsgr->startTime % 24, departureTable[i].startTime) );
					if (totalRisk + riskAdd >= minRisk ||
						totalRisk + riskAdd >= minR[departureTable[i].dest->ID][spend])
						continue;

					//累加计算耗时和风险
					totalTime += timeAdd;
					totalRisk += riskAdd;

					minR[departureTable[i].dest->ID][spend] = totalRisk;
					vis[departureTable[i].dest->ID] = 1; //标记
					travelPlans[tempPsgr->ID].route[step] = &departureTable[i];
					//printf("累计总风险为%lf，耗时为%d\n", totalRisk, totalTime);

					dfsRoute(&departureTable[i], tempPsgr, departureTable[i].dest, step + 1);  //继续DFS搜索
					//回溯
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
	//printf("开始生成乘客%d的旅行计划:\n",tmp->ID);
	dfsRoute(&departureTable[0], tmp, tmp->start, 0);
	//printf("RouteNum=%d\n", routeNum);
	if (routeNum == 0)
	{
		return;
	}

	//从tRoute中获取最小风险路由
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
				tRisk[i] += ( (tmp->inCity->risk * countTime(tmp->startTime, tRoute[i][j]->startTime) ) //起始城市停留风险+第一班风险
					+ (tRoute[i][j]->risk * countTime(tRoute[i][j]->startTime, tRoute[i][j]->arriveTime) ) );
			}
			else
			{
				tTime[i] += ( countTime(tRoute[i][j - 1]->arriveTime, tRoute[i][j]->startTime)
					+ countTime(tRoute[i][j]->startTime, tRoute[i][j]->arriveTime) );
				tRisk[i] += ((tRoute[i][j]->start->risk * countTime(tRoute[i][j - 1]->arriveTime, tRoute[i][j]->startTime) )//城市候车风险+航班风险
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
	
	//将限时风险最少计划保存到travelPlans中
	while (tRoute[k][j])
	{
		travelPlans[tmp->ID].route[j] = tRoute[k][j];
		j++;
	}
}
