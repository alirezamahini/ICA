# ICA
Imperialist Competition Algorithm implementation class in VC++ 
By defining an object of this class and setting the relevant parameters through constructor function arguments, 
an Imperialist competition algorithm can be implemented for a problem. The constructor function parameters describe as follow:
    ParIndex: list of index values of any country parameter.
    ParamVal: list of possible values of each country parameters.
    CountryNum: the number of countries.
    ImpNum: the number of imperialists in the beginning decade.
    DecadeNum: number of decades( maximum number of repetitions algorithm).
    RevolutionRate: the rate of revolution event in countries.
    IsEqualParamValAllowed: if each parameter value must be unique this parameter must set to false.
    CostFunc: fitness function address that must return a double value.
    inAcceptableCostVal: unacceptable maximum value for cost function( if a country has a cost value as equal as or grater than from it. will be eliminated in the execution cycle.
    logfileName: file name for reporting the operations
after the creation of an ICA object via calling the Compet() function, the best answer in the map format of<int ,int> will return to you 
