#pragma once
#include "iostream"
#include "string"
#include "list"
#include "map"
#include "functional"
#include "algorithm"
#include "fstream"
#include "timer.h"

using namespace std;
typedef function<double(map<int,int>)> CostfunType;
struct Country_Profile{
	friend bool operator<(const Country_Profile &p1,const Country_Profile &p2){
		return (p1.Cost<p2.Cost);
	}
	friend bool operator==(const Country_Profile &p1,const Country_Profile &p2){
		return (p1.Cost==p2.Cost && p1.Country==p2.Country);
	}
	map<int,int> Country;
	double Cost;
};	

struct Imper_Profile{
	friend bool operator<(const Imper_Profile &p1,const Imper_Profile &p2){
		return (p1.Imper.Cost<p2.Imper.Cost);
	}
	Country_Profile	Imper;
	list<Country_Profile> ColonyList;
};	
class ICA
{
	list<int> m_ParamIndex;//list of country field Index
	list<int> m_ParamVal;//list of country field value
	double m_InAcceptableCostVal;//Value of the Country's cost that is not acceptable
	int m_CountryNum;
	int m_ImpNum;
	int m_DecadeNum;
	bool m_IsEqualParamValAllowed;
	double m_RevolutionRate;
	list<Country_Profile> m_CountryList;
	list<Imper_Profile> m_ImperList;
	int myrandom (int i) {	
		int x=std::rand()%i;
		return x;
	}
	string m_LogFileName;
	ofstream m_LogFile;
	CostfunType	Cost;
	CTimer m_Timer;
	void SetCost(const CostfunType & CostFunc){ Cost=CostFunc;}
	void Assimulate_Clony_to_Imper();
	void Doing_Revolution();
	void Colony_Imper_swap();
	void ColonyCostCalc();
	void Merge_Similar_Impers();
	void InitializeCountries();
	void InitializeImpires();
	void Eliminate_Weakest_Imper();

public:
	ICA(void);
	ICA(list<int> ParIndex, list<int> ParamVal, int CountryNum, int ImpNum, int DecadeNum,double RevolutionRate, bool IsEqualParamValAllowed, const CostfunType &CostFunc, double inAcceptableCostVal, string logfileName);
	~ICA(void);
	void InitializeCountries(map<int,int> *Countries, int n);
	void InitializeCountries(list<map<int,int>> Countries);
	double Compet(map<int,int> &Imperialist);


};


