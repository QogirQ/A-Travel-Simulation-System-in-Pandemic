#pragma once

//���ų�������
#define CITY_LOW_RISK 0.2				//���еͷ���ֵ
#define CITY_MID_RISK 0.5				//�����з���ֵ
#define CITY_HIGH_RISK 0.9				//���и߷���ֵ
#define CAR_RISK 2							//������λʱ�����ֵ
#define TRAIN_RISK 5						//�𳵵�λʱ�����ֵ
#define AIR_RISK 9							//�ɻ���λʱ�����ֵ
#define CAR 0									//������������ֵ
#define TRAIN 1								//����𳵳���ֵ
#define AIR 2									//����ɻ�����ֵ
#define CITYNUM 11							//��������
#define DPRTNUM 140						//���ࡢ��������
#define SLEEPTIME 10000						//�ƽ�ʱ����Ϊ10��
#define MAX_PSGRNUM 500				//���˿�����

typedef struct city {
	unsigned int ID;		//����ID
	char name[20];		//��������
	double risk;			//���з���
}CITY;

typedef struct departure { //���ֽ�ͨ���ߵĳ���ͳһ����ΪDPRT
	unsigned int ID;					//����򳵴�ID
	unsigned int vehicle;			//��ͨ��������
	unsigned int risk;				//����ֵ
	unsigned int startTime;		//����ʱ��
	unsigned int arriveTime;	//����ʱ��
	CITY *start;						//ʼ������
	CITY *dest;						//�յ����
}DPRT;

typedef struct passenger {	//�˿�����ΪPSGR
	char name[20];					//�˿�����
	unsigned int ID;					//�˿�ID
	CITY *start;						//�˿�������
	CITY *dest;						//�˿��յ����
	unsigned int startTime;		//�˿�ʼ��ʱ�䣨����˿͵�ʱ�䣩
	unsigned int timeLimit;		
	//�˿����мƻ���ʱ�����ƣ���Ϊ0��ʾ��ʱ�����ƣ����������ٷ��ռƻ������������ʱ��ֵ������ʱ���ٷ��ռƻ�
	bool isInDeparture;			//���˿��ں���򳵴��д˱���Ϊ1��ͣ���ڳ�������˱���Ϊ0
	DPRT *inDeparture;			//�˿����ں���򳵴�
	CITY *inCity;						//�˿����ڳ���
}PSGR;

typedef struct plan {				//�˿����мƻ�
	unsigned int psgrID;			//�˿�ID
	unsigned int startTime;		//��ʼʱ��
	double risk;						//�ܷ���ֵ
	unsigned int timeSpend;	//�ܺ�ʱ
	CITY *dest;						//�ƻ�Ŀ�ĵ�
	DPRT *route[1000];			//�˼ƻ��еĺ���ͳ���
}PLAN;