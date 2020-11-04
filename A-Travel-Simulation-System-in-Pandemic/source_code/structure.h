#pragma once

//符号常量定义
#define CITY_LOW_RISK 0.2				//城市低风险值
#define CITY_MID_RISK 0.5				//城市中风险值
#define CITY_HIGH_RISK 0.9				//城市高风险值
#define CAR_RISK 2							//汽车单位时间风险值
#define TRAIN_RISK 5						//火车单位时间风险值
#define AIR_RISK 9							//飞机单位时间风险值
#define CAR 0									//定义汽车常量值
#define TRAIN 1								//定义火车常量值
#define AIR 2									//定义飞机常量值
#define CITYNUM 11							//城市数量
#define DPRTNUM 140						//航班、车次总数
#define SLEEPTIME 10000						//推进时间间隔为10秒
#define MAX_PSGRNUM 500				//最大乘客数量

typedef struct city {
	unsigned int ID;		//城市ID
	char name[20];		//城市名字
	double risk;			//城市风险
}CITY;

typedef struct departure { //三种交通工具的车次统一命名为DPRT
	unsigned int ID;					//航班或车次ID
	unsigned int vehicle;			//交通工具类型
	unsigned int risk;				//风险值
	unsigned int startTime;		//出发时间
	unsigned int arriveTime;	//到达时间
	CITY *start;						//始发城市
	CITY *dest;						//终点城市
}DPRT;

typedef struct passenger {	//乘客命名为PSGR
	char name[20];					//乘客名字
	unsigned int ID;					//乘客ID
	CITY *start;						//乘客起点城市
	CITY *dest;						//乘客终点城市
	unsigned int startTime;		//乘客始发时间（输入乘客的时间）
	unsigned int timeLimit;		
	//乘客旅行计划的时间限制：若为0表示无时间限制，将生成最少风险计划；否则根据限时的值生成限时最少风险计划
	bool isInDeparture;			//若乘客在航班或车次中此变量为1，停留在城市中则此变量为0
	DPRT *inDeparture;			//乘客所在航班或车次
	CITY *inCity;						//乘客所在城市
}PSGR;

typedef struct plan {				//乘客旅行计划
	unsigned int psgrID;			//乘客ID
	unsigned int startTime;		//起始时间
	double risk;						//总风险值
	unsigned int timeSpend;	//总耗时
	CITY *dest;						//计划目的地
	DPRT *route[1000];			//此计划中的航班和车次
}PLAN;