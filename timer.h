//	ver 1.1
//	method GetCurTime is now public and m_Started is now protected
//	ver 1.0
//	first release
#ifndef TIME_H
#define TIME_H

#include <time.h>

class CTimer {
public: 
	CTimer();
	~CTimer();
	/** Start timer */
	void Start(void);
	/** Stop timer */
	void Stop();
	/** If the differance of current time and m_Start time is grater than m_stTimeOutValue return ture else return false */
	bool TimeoutArrived(void);
	/** Get Elapsed time from last start call */
	unsigned long int GetElapsedTime(void);
	/** Set time out value  */
	void SetTimeOutVal(unsigned long int nTime);
	/** make a delay with microsecond unit */
	unsigned long int Delay(unsigned long int usec);
	/** Get current time in us */
	static unsigned long int GetCurTime(void);
	/** Returns current time in ms (windows version)*/
	static unsigned long int GetTickCount(void){
		return (GetCurTime()/1000l);
	}
	static int gettimeofday(struct timeval * tp, struct timezone * tzp);
protected: // Protected attributes
	unsigned long int m_Current;
	unsigned long int m_Start;
	unsigned long int m_nTimeOutValue;
	bool	m_Started;
};
#endif
