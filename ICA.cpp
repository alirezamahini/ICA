#include "stdafx.h"
#include "ICA.h"


ICA::ICA(void)
{
}
ICA::ICA(list<int> ParamIndex, list<int> ParamVal, int CountryNum, int ImpNum, int DecadeNum,double RevolutionRate, bool IsEqualParamValAllowed,  const CostfunType &CostFunc, double inAcceptableCostVal, string logfileName): Cost(CostFunc){
	m_ParamIndex=ParamIndex;
	m_ParamVal=ParamVal;
	m_CountryNum=CountryNum;
	m_ImpNum=ImpNum;
	m_DecadeNum=DecadeNum;
	m_IsEqualParamValAllowed=IsEqualParamValAllowed;
	m_RevolutionRate=RevolutionRate;
	m_InAcceptableCostVal=inAcceptableCostVal;
	m_Timer.Start();
	if(m_ImpNum>=m_CountryNum){
		cout<<"Error: Impires must be less than countries\n";
		exit(0);
	}
	m_LogFile.open(logfileName);
	if(!m_LogFile){
		cout<<"can not open file:" <<logfileName<<endl;
		exit(0);
	}
	m_LogFile.clear();
	unsigned long int t=m_Timer.GetElapsedTime();
	m_LogFile<<t/1000<<":\tICA START\n imper="<<m_ImpNum<<"\t country="<<m_CountryNum<<"\tDecades="<<m_DecadeNum<<"\n";
	
}
void ICA::InitializeCountries(){
	if(!m_CountryList.empty()) return;
	for(int i=0;i<m_CountryNum;i++){
		Country_Profile Profile;
		for (list<int>::iterator it = m_ParamIndex.begin(); it != m_ParamIndex.end(); it++){
			list<int>::iterator itRsc = m_ParamVal.begin();
			advance(itRsc,myrandom(m_ParamVal.size()));
			Profile.Country[(*it)]=(*itRsc);
		}
		Profile.Cost=Cost(Profile.Country);
		if(Profile.Cost>=m_InAcceptableCostVal){
			i--;
			continue;
		}
		m_CountryList.push_back(Profile);
	}
	unsigned long int t=m_Timer.GetElapsedTime();
	m_LogFile<<t/1000<<":\tCountries have been Initialized\n";
	
}
void ICA::InitializeCountries(map<int,int> *Countries, int n){
	for(int i=0;i<n;i++){
		Country_Profile Profile;
		Profile.Country=Countries[i];
		Profile.Cost=Cost(Profile.Country);
		if(Profile.Cost>=m_InAcceptableCostVal){
			continue;
		}
		m_CountryList.push_back(Profile);
	}
	for(int i=m_CountryList.size();i<m_CountryNum;i++){
		Country_Profile Profile;
		for (list<int>::iterator it = m_ParamIndex.begin(); it != m_ParamIndex.end(); it++){
			list<int>::iterator itRsc = m_ParamVal.begin();
			advance(itRsc,myrandom(m_ParamVal.size()));
			Profile.Country[(*it)]=(*itRsc);
		}
		Profile.Cost=Cost(Profile.Country);
		if(Profile.Cost>=m_InAcceptableCostVal){
			i--;
			continue;
		}
		m_CountryList.push_back(Profile);
	}
	unsigned long int t=m_Timer.GetElapsedTime();
	m_LogFile<<t/1000<<":\tCountries have been Initialized\n";
	
}
void ICA::InitializeCountries(list<map<int,int>> Countries){
	for(int i=0; i<Countries.size();i++){
		//list<map<int,int>>::iterator it=Countries->begin();it!=Countries->end();it++){
		Country_Profile Profile;
		Profile.Country=*(Countries.begin());
		Countries.pop_front();
		Profile.Cost=Cost(Profile.Country);
		if(Profile.Cost>=m_InAcceptableCostVal){
			continue;
		}
		m_CountryList.push_back(Profile);
	}
	for(int i=m_CountryList.size();i<m_CountryNum;i++){
		Country_Profile Profile;
		for (list<int>::iterator it = m_ParamIndex.begin(); it != m_ParamIndex.end(); it++){
			list<int>::iterator itRsc = m_ParamVal.begin();
			advance(itRsc,myrandom(m_ParamVal.size()));
			Profile.Country[(*it)]=(*itRsc);
		}
		Profile.Cost=Cost(Profile.Country);
		if(Profile.Cost>=m_InAcceptableCostVal){
			i--;
			continue;
		}
		m_CountryList.push_back(Profile);
	}
	unsigned long int t=m_Timer.GetElapsedTime();
	m_LogFile<<t/1000<<":\tCountries have been Initialized\n";
	
}

void ICA::InitializeImpires(){
	//select Imperialists
	m_CountryList.sort();
	Imper_Profile imp;
	for(int i=0;i<m_ImpNum;i++){
		imp.Imper=m_CountryList.front();
		m_ImperList.push_back(imp);
		m_CountryList.pop_front();
	}
	//assign colonies
	list<Imper_Profile>::iterator itImp = m_ImperList.begin();
	for (list<Country_Profile>::iterator it = m_CountryList.begin(); it != m_CountryList.end(); it++){
		if(itImp==m_ImperList.end())
			itImp=m_ImperList.begin();
		itImp->ColonyList.push_back(*it);
		itImp++;
	}
	unsigned long int t=m_Timer.GetElapsedTime();
	m_LogFile<<t/1000<<":\tImpers have been constructed\n";

}
void ICA::ColonyCostCalc(){
	for(list<Imper_Profile>::iterator itImp=m_ImperList.begin();itImp!=m_ImperList.end();itImp++){
		for(list<Country_Profile>::iterator itCol=itImp->ColonyList.begin();itCol!=itImp->ColonyList.end();itCol++){
			itCol->Cost=Cost(itCol->Country);
		}
	}
}
void ICA::Assimulate_Clony_to_Imper(){
	for(list<Imper_Profile>::iterator itImp=m_ImperList.begin();itImp!=m_ImperList.end();itImp++){
		for(list<Country_Profile>::iterator itCol=itImp->ColonyList.begin();itCol!=itImp->ColonyList.end();itCol++){
			int n=0,m=1;
			while(n++!=itImp->Imper.Country.size()){
				map<int,int>::iterator it;
				it=itImp->Imper.Country.begin();
				advance(it,rand()%itImp->Imper.Country.size());
				if(itCol->Country[it->first]!=it->second){
					itCol->Country[it->first]=it->second;
					if(!m--) break;
				}
			}
			//itCol->Cost=Cost(itCol->Country);
		}
	}
}
void ICA::Doing_Revolution(){
	int n=int(m_RevolutionRate*m_ImperList.size());
	for(int i=0;i<n;i++){
		list<Imper_Profile>::iterator itImp=m_ImperList.begin();
		advance(itImp,rand()%m_ImperList.size());
		for(list<Country_Profile>::iterator colIt=itImp->ColonyList.begin();colIt!=itImp->ColonyList.end();colIt++){
			map<int,int>::iterator it1,it2;
			it1=colIt->Country.begin();
			it2=colIt->Country.begin();
			advance(it1,rand()%colIt->Country.size());
			advance(it2,rand()%colIt->Country.size());
			int temp=it1->second;
			it1->second=it2->second;
			it2->second=temp;
			//colIt->Cost=Cost(colIt->Country);
		}
	}
}
void ICA::Colony_Imper_swap(){
	for(list<Imper_Profile>::iterator itImp=m_ImperList.begin();itImp!=m_ImperList.end();itImp++){
		for(list<Country_Profile>::iterator colIt=itImp->ColonyList.begin();colIt!=itImp->ColonyList.end();colIt++){
			//colIt->Cost=Cost(colIt->Country);
			if(colIt->Cost<itImp->Imper.Cost){
				colIt->Country.swap(itImp->Imper.Country);
				double temp=colIt->Cost;
				colIt->Cost=itImp->Imper.Cost;
				itImp->Imper.Cost=temp;
			}
		}
	}
	
}
void ICA::Eliminate_Weakest_Imper(){
	m_ImperList.sort();
	Country_Profile ElimImp=m_ImperList.back().Imper;
	if(m_ImperList.back().ColonyList.empty()){//if weakest has no clony
		m_ImperList.begin()->ColonyList.push_back(ElimImp);//move it to the strongest
		m_ImperList.pop_back();//eliminate it from imperList
		m_ImpNum=m_ImperList.size();
		return;
	}
	list<Country_Profile>::iterator it=m_ImperList.back().ColonyList.begin();//Get the first colony of weekest
	m_ImperList.begin()->ColonyList.push_back(*it);//move it to strongest
	m_ImperList.back().ColonyList.pop_front();//eliminate from weekList
}
void ICA::Merge_Similar_Impers(){
	for(list<Imper_Profile>::iterator it=m_ImperList.begin();it!=m_ImperList.end();it++){
		double key=it->Imper.Cost;
		list<Imper_Profile>::iterator it1=it;
		while(it1!=m_ImperList.end()){
			advance(it1,1);
			list<Imper_Profile>::iterator it2=find_if(it1,m_ImperList.end(), [key](const Imper_Profile & m) -> bool { return m.Imper.Cost ==key ; });
			if(it2!=m_ImperList.end()){ 
				it->ColonyList.insert(it->ColonyList.end(),it2->ColonyList.begin(), it2->ColonyList.end());
				it->ColonyList.push_back(it2->Imper);
				m_ImperList.erase(it2);
			}
		}
		
	}
}
double ICA::Compet(map<int,int> &Imperialist){
	int n=0;
	double cost=DBL_MAX;
	InitializeCountries();
	InitializeImpires();
	while(n!=m_DecadeNum /*&& m_ImperList.size()!=1*/){
		Assimulate_Clony_to_Imper();
		Doing_Revolution();
		ColonyCostCalc();
		Colony_Imper_swap();
		Eliminate_Weakest_Imper();
		Merge_Similar_Impers();
		m_ImperList.sort();
		unsigned long int t=m_Timer.GetElapsedTime();
		m_LogFile<<"\n"<<t/1000<<"\t\t"<<n++<<"\t\t"<<m_ImpNum<<"\t"<<m_ImperList.begin()->Imper.Cost;
		
		if(m_ImperList.begin()->Imper.Cost<cost){
			cost=m_ImperList.begin()->Imper.Cost;
			cout<<"\nDecade=\t"<<n<<"\tImperNum=\t"<<m_ImpNum<<"\t\tcost=\t"<<m_ImperList.begin()->Imper.Cost<<"\n";
		}else cout<<"Decade=\t"<<n<<"\tImperNum=\t"<<m_ImpNum<<"\t\tcost=\t"<<m_ImperList.begin()->Imper.Cost<<"\r";
	}
	cout<<"\n";
	m_ImperList.sort();
	Imper_Profile BestImp=m_ImperList.front();
	Imperialist=BestImp.Imper.Country;
	return BestImp.Imper.Cost;
}
ICA::~ICA(void)
{
	m_LogFile.close();
}
