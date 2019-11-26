
#include "stdafx.h"
#include <stdint.h> // portable: uint64_t   MSVC: __int64 
#include <Windows.h>
#include "timer.h"

int CTimer::gettimeofday(struct timeval * tp, struct timezone * tzp)
{
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
    // until 00:00:00 January 1, 1970 
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;
}

CTimer::CTimer(){
	m_Started=false;
	m_nTimeOutValue=0;
}
CTimer::~CTimer(){
}
/** Start timer */
void CTimer::Start(void){
	m_Start=GetCurTime();
	m_Started=true;
}
/** If the differance of current time and m_Start time is grater than m_stTimeOutValue return ture else return false */
bool CTimer::TimeoutArrived(void){
	if(m_Started){
		m_Current=GetCurTime();
		unsigned long int nDiff=m_Current-m_Start;
		if(nDiff>=m_nTimeOutValue)
			return true;
		else
			return false;
	}
	return false;
}
/** Set time out value  */
void CTimer::SetTimeOutVal(unsigned long int nTime){
	m_nTimeOutValue=nTime;
}
/** Stop timer */
void CTimer::Stop(){
	m_Started=false;
}
/** return elapsed time from calling Start() */
unsigned long int CTimer::GetElapsedTime(void){
	if(m_Started){
		m_Current=GetCurTime();
		unsigned long int nDiff=m_Current-m_Start;
		return nDiff;
	}
	return 0;
}
/** Get current time in us */
//you can use any other function to get time value but set MAX_TIME_NUM for each function
unsigned long int CTimer::GetCurTime(void){
	struct timeval stTime;
	unsigned long int nRes;
	struct timezone *tz=NULL;
	gettimeofday(&stTime,tz);
	nRes=stTime.tv_sec*1000000L+stTime.tv_usec;
	return(nRes);
}

/** make a delay with microsecond unit and return actual time passed in usec*/
unsigned long int CTimer::Delay(unsigned long int usec){
	unsigned long int nStartTime=GetCurTime();
	/*struct timeval stTime;
	stTime.tv_sec=usec / 1000000L;
	stTime.tv_usec=usec % 1000000L;
	
	(void) select(1,(fd_set*)0,(fd_set*)0,(fd_set*)0,&stTime);
	*/
	Sleep(usec/1000);
	return(GetCurTime()-nStartTime);
}