#include"state.h"

void changeState()
{
	for (int i = 0; i < psgrNum; i++)
	{
		PSGR *p = &passengerList[i];
		if (p->isInDeparture == false)//旅客处在某城市
		{
			for (int j = 0; travelPlans[p->ID].route[j] != 0; j++) //遍历旅行计划中所有航班车次
			{
				if (p->inCity && travelPlans[p->ID].route[j]->start->ID == p->inCity->ID)
				{
					//printf("计划中的第%d班：航班ID为%d，终点为%s\n", j, travelPlans[p->ID].route[j]->ID, travelPlans[p->ID].route[j]->dest->name);
					DPRT *t = travelPlans[p->ID].route[j];
					if ((hourTime % 24) == (int)t->startTime )
					{						
						p->inDeparture = t;
						p->inCity = NULL;
						p->isInDeparture = true;
					}
				}
			}
		}
		else//旅客处在某航班中
		{
			for (int j = 0; travelPlans[p->ID].route[j] != 0; j++) //遍历旅行计划中所有航班车次
			{
				if (p->inDeparture && travelPlans[p->ID].route[j]->dest->ID == p->inDeparture->dest->ID)
				{
					DPRT *t = travelPlans[p->ID].route[j];
					if ((hourTime % 24) ==t->arriveTime)
					{
						p->inCity = p->inDeparture->dest;
						p->inDeparture = NULL;
						p->isInDeparture = false;
					}
				}
			}
		}
	}
}