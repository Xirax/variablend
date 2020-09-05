#include <string>
#include <cstdlib>
#include <vector>
#include <windows.h>

using namespace std;

class Vmath{
	
	string name;
	string calc;
	bool firstMod;

	
	
		float verCalc(bool mod, Vmath tbcN[], string cc=""){
		if(!mod) cc = calc;	
		vector <float> nums;
		vector <char> chr;
		vector <short> chrL;
		string toConv = "";
		string recG = "";
		bool found = false;
		bool error = false;
		
		
		for(int i=0; i<cc.size(); i++){
			
			if(cc[i] > 47 && cc[i] < 58){
				while(cc[i] > 47 && cc[i] < 58){ toConv += cc[i]; i++; } 
				nums.push_back(SToF(toConv));
				toConv = "";
				i--;
			}
			else if(cc[i] == '+' || cc[i] == '-'){
				chr.push_back(cc[i]);
				chrL.push_back(1);
			}
			else if(cc[i] == '*' || cc[i] == '/'){
				chr.push_back(cc[i]);
				chrL.push_back(2);
			}
			else if(cc[i] == '('){
				int newOpener = 0;
				
				i++;
				while(cc[i] != ')' || newOpener != 0){
					recG += cc[i];
					if(cc[i] == ')') newOpener--;
					if(cc[i] == '(') newOpener++;
					i++;
				}
				nums.push_back(verCalc(true, tbcN,  recG));
				recG = "";
			}
			else{
				
				for(int v=0; v<=VQNT; v++){
					if(cc[i] == tbcN[v].name[0] && cc[i] != name[0]){
						nums.push_back(verCalc(true, tbcN, tbcN[v].getSFC("CC")));
						found = true;
					}
					
				}
				
				if(!found){
					cout << "\n\n\n UNEXPECED ERROR, CHECK YOUR CALCULATIONS...\n\n\n";
					system("PAUSE");
					error = true;
					break;
				}
				else{
					found = false;
				}	
			}	
		}
		
		if(!error){
			
		if(nums.size() > 1){
			
		for(int i=0; i<(nums.size() - 2); i++){
			if(chrL.at(i) == 2){
				
				if(chr.at(i) == '*') nums[i] = nums.at(i) * nums.at(i+1);
				else nums[i] = nums.at((i)) / nums.at(i+1);	
			
				nums.erase(nums.begin() + (i+1));
				chr.erase(chr.begin() + i);
				chrL.erase(chrL.begin() + i);	
			}
			else{
				if(chrL.at(i+1) == 2){
					
				if(chr.at(i+1) == '*') nums[i+1] = nums.at(i+1) * nums.at(i+2);		
				else nums[i+1] = nums.at((i+1)) / nums.at(i+2);	
		
				nums.erase(nums.begin() + (i+2));
				chr.erase(chr.begin() + (i+1));
				chrL.erase(chrL.begin() + (i+1));
				
				}
				else{
					if(chr.at(i) == '+') nums[i] = nums.at(i) + nums.at(i+1);
					else nums[i] = nums.at(i) - nums.at(i+1);		
					
					nums.erase(nums.begin() + (i+1));
					chr.erase(chr.begin() + i);
					chrL.erase(chrL.begin() + i);				
				}
			}
			
			i = -1;
			
		}
			
			if(chr.at(0) == '*'){
				nums[0] *= nums.at(1);
			}
			else if(chr.at(0) == '/'){
				nums[0] /= nums.at(1);
			}
			else if(chr.at(0) == '+'){
				nums[0] += nums.at(1);
			}
			else if(chr.at(0) == '-'){
				nums[0] -= nums.at(1);
			}
			
		}
		
		return nums.at(0);	
		
	}
	}
	
	/////////////////////////////////////////////
	/////////////////////////////////////////////
	
	public:
	
	/////////////////////////////////////////////
	/////////////////////////////////////////////
		
	float result;
	static int VQNT;
		
	Vmath(){
		name = "";
		calc = "";
		firstMod = true;
	}
	
 	~Vmath(){
 		VQNT--;
 		name = "";
		calc = "";
		firstMod = false;
	 }
	
	
	float SToF(string sfloat);
		
	void modDat(int thsToModify, string CALC = "", string nm = ""){
		if(thsToModify >= 1){
			calc = CALC;
		}
		
		if(thsToModify >= 2){
			name = nm;
		}
		
		if(firstMod){
			VQNT += 1;
			firstMod = false;
		}		
	}
	
	/////////////////////////////////////////////
	
	string getSFC(string what){
		
		if(what == "NAME" || what == "NM"){
			return  name;
		}
		else if(what == "CALC" || what == "CC"){
			return calc;
		}
		
	}
	
	/////////////////////////////////////////////	
	
	void putToRes(Vmath tbcF[]){
		result = verCalc(false, tbcF);
	}
	
	
	
			
};


int Vmath::VQNT = 0;


float Vmath::SToF(string sfloat){
	string cp = "";
	int sv = sfloat.size() - 1;
	int multi = 1;
	float fConv;
	
	for(int i=0; i<sfloat.size(); i++){
		if(sfloat[i] != '.') cp += sfloat[i];
		else sv = i;
	}
	
	sv = sfloat.size() - 1 - sv;
	
	for(int i=0; i<sv; i++){
		multi *= 10;
	}
	
	fConv = atoi(cp.c_str());
	fConv /= multi;
	
	return fConv;	
}
