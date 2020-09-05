#include <iostream>
#include <fstream>
#include "Vmath.h"
#include <string>
#include "MainFunct.h"
#include <windows.h>
#include <iomanip>
#include <ctime>

using namespace std;

	

int main(int argc, char** argv) {

    /// CALC Variables
    
	Vmath alocTab[800];
	bool clc = false;
	bool calcDone = false;
	int vars = 0;
	
	
	/// SETTINGS Variables
	
	char bcgColor = '7';
	char frgColor = '0';
	string clr;
	string opt;
	string version = "1.2";
	bool opened = true;
	
	
	/// SAVE Variables
	int clcSeed;
	fstream Vsave;
	fstream Esave;
	fstream seed;
	fstream dlts;
	string savesNms[800];
	int savesNr = 0;
	
	

	srand(time(0));
	seed.open("VDat/Fseed.vbf");
	
	for(int i=0; i<2500; i++){
		clcSeed = rand() % 10;
		seed << clcSeed;	
	}
	
	seed << "\n\n V" << version;
	
	seed.close();
	Esave.open("VDat/Econtent.vbf", ios::in);
	
	Esave >> bcgColor;
	Esave >> frgColor;
	
	clr = (string) "color " + bcgColor + frgColor;
	
	Esave >> savesNr;
	
	for(int i=0; i<savesNr; i++){
		Esave >> savesNms[i];
	}
	
	system(clr.c_str());
	
	Esave.close();
	
	
	cout << setprecision(150);
	while(opened){
	Esave.open("VDat/Econtent.vbf", ios::trunc | ios::out);
	Esave << bcgColor;
	Esave << frgColor << endl;
	Esave << savesNr << endl;
	for(int i=0; i<savesNr; i++){
		Esave << savesNms[i] << endl;
	}
	
	Esave.close();
	
	system("cls");	
	ent(2);
	spc(15);
	cout << "WARIABLEND v" + version + " Beta \n ";
	cout << "\n    Best way to calculate everything! Let's blend your variables!";
	ent(4);
	cout << " (1) VARIABLE CALCULATOR"; spc(6); cout << "(2) OPTIONS";
	cout << "\n\n (3) See commands"; spc(13); cout << "(4) Exit\n\n ";
	cin >> opt;
	
	if(opt == "1"){
	
		clc = true;
		string calculation;
		string Vname;
		while(clc){
		system("cls");
			
			if(vars > 0){
				if(calcDone){
					for(int i=0; i<vars; i++) cout << "\n\n : " << alocTab[i].getSFC("NM") << " = " << alocTab[i].result;
				}
				else{
					for(int i=0; i<vars; i++) cout << "\n\n : " << alocTab[i].getSFC("NM") << " = " << alocTab[i].getSFC("CC");	
				}
			}
			
			ent(5);
			cout << " >>  ";
			cin >> opt;
			if(opt == "Add" || opt == "add"){
				calcDone = false;
				bool correctN = true;
				cout << "\n\n : Write variable name: ";
				cin >> Vname;
				
				for(int c=0; c<vars; c++){
					if(Vname == alocTab[c].getSFC("NM")){
						correctN = false;	
					}
					else{
						correctN = true;
					}
				}
				
				while(!correctN){
					cout << "\n\n\n This variable name already exists, write another...";
					cout << "\n : Write variable name: ";
					cin >> Vname;
					
					for(int c=0; c<vars; c++){
						if(Vname == alocTab[c].getSFC("NM")){
							correctN = false;	
						}
						else{
							correctN = true;
						}
					}
					
				} 
				
				while(Vname.size() > 1){
					cout << "\n\n\n SO SORRY FOR THIS ERROR! We will fix it later, but now you can use names";
					cout << " only with one letter";
					cout << "\n : Write variable name: ";
					cin >> Vname;
				}
				
				while(Vname[0] > 47 && Vname[0] < 58 && Vname[0] == '+' && Vname[0] == '-' && Vname[0] == '*' && Vname[0] == '/'){
					cout << "\n\n\n You can not use this character in variable name";
					cout << "\n : Write variable name: ";
					cin >> Vname;
				}
				
				cout << "\n\n : Write variable calculation: ";
				cin >> calculation;
				
				
				
				alocTab[vars].modDat(2, calculation, Vname);
				
				cout << "\n\n OK! VARIABLE " << alocTab[vars].getSFC("NM") << " IS READY!!!";
				Sleep(150);	
				vars++;
			}
			if(opt == "Result" || opt == "result"){		
						
				int lns = 1;
				for(int i=0; i<vars; i++){

					alocTab[i].putToRes(alocTab);
					
					cout << "\n\n CALCULATION IN PROGRESS ";
					for(int l=0; l<lns; l++) cout << "|";
					Sleep(2);
					lns++;
					system("cls");
				}
				calcDone = true;	
			}
			
			if(opt == "clear" || opt == "Clear"){
		
				for(int i=0; i<vars; i++){
					alocTab[i].~Vmath();
				}
				
				vars = 0; 
			} 
			
			if(opt == "clear_last" || opt == "Clear_last"){
				if(vars){
					vars--;
					alocTab[vars].~Vmath();	
				}
	
			} 
			
			if(opt == "clear_var" || opt == "Clear_var"){
				string Vnm;
				cin >> Vnm;
				
				for(int i=0; i<vars; i++){
					if(alocTab[i].getSFC("NM") == Vnm){
						for(int j=i; j<vars - 1; j++){
							alocTab[j] = alocTab[j+1];
						}
					}
				}
				vars--;	
				alocTab[vars].~Vmath();
			}
			
			if(opt == "modify" || opt == "Modify"){
				string Vnm;
				cin >> Vnm;
				
				
				for(int i=0; i<vars; i++){
					if(alocTab[i].getSFC("NM") == Vnm){
						cout << "\n\n : Write new Calculation: "; cin >> calculation;
						alocTab[i].modDat(1, calculation);
						break;
					}
				}
				calcDone = false;	
			}
			
			if(opt == "Calc" || opt == "calc"){
				calcDone = false;	
			} 
			
			if(opt == "save" || opt == "Save"){
				string Sname;
				bool ok = false;
				
				Vsave.open("VDat/VContent.vbf", ios::app);
				cout << "\n\n : Variable save name: ";
				cin >> Sname;
				
				while(!ok){
				for(int i=0; i<savesNr; i++){
					if(Sname == savesNms[i]){
						cout << "\n\n\n This save name already exist, write another...";
						cout << "\n\n : Variable save name: ";
						cin >> Sname;
						ok = false;
					}
					else{
						ok = true;
					}
				}
				
				if(!savesNr) ok = true;
				
				}
			
				savesNms[savesNr] = Sname;
				savesNr++;
				
				Vsave << "[ " << Sname << " ] \n";
				Vsave << vars << endl;
				
			for(int i=0; i<vars; i++){
				 Vsave << alocTab[i].getSFC("NM") << "=" << alocTab[i].getSFC("CC") << endl; 
			}
			
				Vsave.close();
				
			}
			
			if(opt == "load" || opt == "Load"){
				Vsave.open("VDat/VContent.vbf");
				string ldName;
				string svName;
				
				string ignoreS;
				char ignoreC;
				
				char VarName;
				string VarNameS;
				
				string VarCalc;
				int vNm = 0;

				bool ok = false;
				
				cin >> ldName;
				
				while(!ok){
					Vsave >> ignoreC;
					Vsave >> svName;
					
					if(svName == ldName) ok = true;
					else{
						Vsave >> ignoreC;
						Vsave >> vNm;
						
						for(int i=0; i<vNm; i++){
							getline(Vsave, ignoreS);
						}
						
						getline(Vsave, ignoreS);
						
						if(Vsave.eof()){
							cout << "\n\n\n Incorrect save name...";
							break;
						}	
					}
				}
							
				if(ok){
					vars = 0;
					Vsave >> ignoreC;
					Vsave >> vNm;
					
					for(int i=0; i<vNm; i++){
						Vsave >> VarName;
						Vsave >> ignoreC;
						Vsave >> VarCalc;
						
						VarNameS = (string) "" + VarName;

						alocTab[vars].modDat(2, VarCalc, VarNameS);
						vars++;
					}
					
					alocTab[0].VQNT = vars;
					
				}		
				
				Vsave.close();	
			}
			
			if(opt == "My_saves" || opt == "my_saves"){
				for(int i=0; i<savesNr; i++){
					cout << "\n : " << savesNms[i];
				}
				ent(4);
				system("PAUSE");
				
			}
			
			if(opt == "delete_asv" || opt == "Delete_asv"){
				
				cout << "\n Are you sure? You want to delete all your saves?(y/n)\n ";
				cin >> opt;
				
				if(opt == "y" || opt == "Y"){
					savesNr = 0;
					dlts.open("VDat/VContent.vbf", ios::trunc | ios::out);
					
					dlts << "";
					dlts.close();	
				}
			}
			
			if(opt == "exit" || opt == "Exit") clc = false;
		}
	}
	else if(opt == "2"){
		char chrt;
		system("cls");
		ent(4);
		cout << " (1) Background color"; spc(6); cout << "(2) Characters color";
		cout << "\n (3) About Variablend\n\n ";
		cin >> opt;
		if(opt == "1"){
			system("cls");
			ent(4);	
			cout <<   " (1) Black"; spc(6); cout << "(2) Green";
			cout << "\n (3) Blue"; spc(6); cout << " (4) Yellow";
			cout << "\n (5) Purple"; spc(5); cout << "(6) White";
			cout << "\n (7) Gray"; spc(6); cout << " (8) Red\n\n ";
			cin >> chrt;
			switch(chrt){
				
				case '1': bcgColor = '0'; break;
				case '2': bcgColor = '2'; break; 
				case '3': bcgColor = '3'; break;
				case '4': bcgColor = '6'; break;
				case '5': bcgColor = '5'; break;
				case '6': bcgColor = '7'; break;
				case '7': bcgColor = '8'; break;
				case '8': bcgColor = '4'; break;	
				default:  bcgColor = '3'; break;
			}
			
			
			opt = "y";
			clr = (string) "color " + bcgColor + frgColor;
			
			if(bcgColor == frgColor){
				cout << "\n\n You are going to set background color the same as characters color, \n and you won't";
				cout << " see anything! For your own good I can't do it\n\n\n ";
				opt = "n";
				system("PAUSE");
			}
			
			if(opt == "y") system(clr.c_str());
					
		}
		else if(opt == "2"){
			system("cls");
			ent(4);	
			cout <<   " (1) Black"; spc(6); cout << "(2) Green";
			cout << "\n (3) Blue"; spc(6); cout << " (4) Yellow";
			cout << "\n (5) Purple"; spc(5); cout << "(6) White";
			cout << "\n (7) Gray"; spc(6); cout << " (8) Red\n\n ";
			cin >> chrt;
			switch(chrt){
				
				case '1': frgColor = '0'; break; 
				case '2': frgColor = 'A'; break; 
				case '3': frgColor = '3'; break; 
				case '4': frgColor = '6'; break; 
				case '5': frgColor = '5'; break; 
				case '6': frgColor = '7'; break; 
				case '7': frgColor = '8'; break;
				case '8': frgColor = '4'; break; 
				default:  frgColor = '0'; break;
			}
			
			opt = "y";
			clr = (string) "color " + bcgColor + frgColor;
			
			if(bcgColor == frgColor){
				cout << "\n\n You are going to set characters color the same as background color, \n and you won't";
				cout << " see anything! For your own good I can't do it\n\n\n ";
				opt = "n";
				system("PAUSE");
			}
			
			if(opt == "y") system(clr.c_str());	

		}
		else if(opt == "3"){
			system("cls");
			cout << "\n\n\n\n Variablend gives you ability to verify your equations with any maths variables";
			cout << "\n up to 800! Every variables what are dependent on each other";
			cout << "\n can be calculated here. Blend everything you want, Blend whenever you want... \n";
			cout << "\n\n ___Variablend " + version + "___ \n\n\n\n\n\n\n\n";
			system("PAUSE");
		}
	}
	else if(opt == "3"){
		system("cls");
		ent(4);
		cout << "\n > add  ---> Adds variable to blend";
		cout << "\n\n > clear_last  ---> Clears last added variable";
		cout << "\n\n > clear_var X  ---> Clears variable named X";
		cout << "\n\n > clear  ---> Clears whole blend";
		cout << "\n\n > result  ---> Gets calculations result";
		cout << "\n\n > calc  ---> Goes back to see calculations";
		cout << "\n\n > modify X  ---> Modifies variable calculation named X";
		cout << "\n\n > save  ---> Saves actual blend";
		cout << "\n\n > my_saves  ---> Shows yours already maked saves";
		cout << "\n\n > load SV  ---> Loads blend named SV";
		cout << "\n\n > delete_asv  ---> Removes all saves";
		cout << "\n\n > (Will work in future) delete_sv SV  ---> Removes save named SV";
		cout << "\n\n > exit  ---> Leaves calculator\n\n\n\n\n";
		system("PAUSE");
	}
	else if(opt == "4") opened = false;
		
}
	
	return 0;
}
