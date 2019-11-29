#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "iostream"
#include "string"
#include "timer.h"
using namespace std;
static const string STR_RSRC_TYPE[]={"IOT_GW","FOG","CLOUD"};
static const string STR_RSRC_STAT[]={"IDLE","BUSY","FAIL"};
static const string STR_TASK_STAT[]={"Waiting","In_process","Completed","Crashed"};


enum Stat_Type
{
	WAITING=0,
	IN_PROCESS=1,
	COMPLETED,
	CRASHED
};
enum RSRC_TYPE
{
	IOT_GW,
	FOG,
	CLOUD
};
enum RSRC_STAT{
	IDLE,
	BUSY,
	FAIL
};
enum SCHEDULE_TYPE{
	FIFO,
	SJF
};
#endif
