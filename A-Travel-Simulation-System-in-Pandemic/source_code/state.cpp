#include"state.h"

void changeState()
{
	for (int i = 0; i < psgrNum; i++)
	{
		PSGR *p = &passengerList[i];
		if (p->isInDeparture == false)//�ÿʹ���ĳ����
		{
			for (int j = 0; travelPlans[p->ID].route[j] != 0; j++) //�������мƻ������к��೵��
			{
				if (p->inCity && travelPlans[p->ID].route[j]->start->ID == p->inCity->ID)
				{
					//printf("�ƻ��еĵ�%d�ࣺ����IDΪ%d���յ�Ϊ%s\n", j, travelPlans[p->ID].route[j]->ID, travelPlans[p->ID].route[j]->dest->name);
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
		else//�ÿʹ���ĳ������
		{
			for (int j = 0; travelPlans[p->ID].route[j] != 0; j++) //�������мƻ������к��೵��
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