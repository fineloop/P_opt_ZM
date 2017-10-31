#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "math.h"
#include <vector>
#include <cstdlib>
#include <string>
#include "stdio.h"

using namespace std;

// anzahl moeglichkeiten
int possibilities(int x) { 
			int p; p = pow(2, x); return p; 
			}
// wahrheitstabelle generator
vector<vector<bool>> reality_Table_generator(int count) {
	int cIV = count;
	int possibilities = pow(2, cIV);

	vector<bool> WT;	WT.resize(cIV);  // wharheitstabelle hilfsvariablen 
	for (int jj = 0; jj < cIV; jj++) { WT[jj] = 0; };



	// wahrheitstabelle
	vector<vector<bool>> posi(possibilities);

	//alles auf 0
	for (int jj = 0; jj < possibilities; jj++) { for (int ij = 0; ij < cIV; ij++) { posi[jj].push_back(0); }; }
	// alles durchlaufen	
	for (int jj = 0; jj < possibilities; jj++)
	{
		for (int ii = cIV - 2; ii >= 0; ii--)
		{
			if (jj != 0)
			{
				if ((posi[jj][ii + 1] == 0) && (posi[jj - 1][ii + 1] == 1))
				{
					WT[ii] = WT[ii] ^ 1;
				}
			}
			posi[jj][ii] = WT[ii];
		}
		for (int ij = 0; ij < cIV; ij++) { posi[jj][ij] = WT[ij]; }

		WT[cIV - 1] = WT[cIV - 1] ^ 1;
	}
	return posi;
}
// wahrheitstabelle ausdrueker
void print_realityTable(vector<vector<bool>> RT) {
	int hight = RT.size();
	int width = RT[0].size();

	for (int jj = 0; jj < hight; jj++) {
		for (int ij = 0; ij < width; ij++)
		{
			if (ij == 0) { cout << '[' << RT[jj][ij] << ','; }
			else if (ij == width - 1) { cout << RT[jj][ij] << ']'; }
			else { cout << RT[jj][ij] << ','; }
		}
		cout << endl;
	}
}
// gives a random sequence as long as the reality table (this helps to reorder the table randomly )
vector<int> random_sequence(int p) {
	vector<int> seq(p);
	for (int ii = 0; ii < p; ii++) {
		int x = 0;
		seq[ii] = rand() % p;
		while( x == 0)
		{
					if(ii > 0)
					{
						for(int iii=ii-1; iii >=0; iii--)
							{
								if (seq[ii] == seq[iii]) { seq[ii] = rand() % p; break; };
								if (iii == 0) x = 1;
							}
					}
					else
					{
						x = 1;
					}
		}
	};
	return seq;
};
// Namen Vergabe
vector<string> naming(int cIV, int cSV, int cOV) {
	int all_in_all = cIV + cSV + cOV;
	vector<string> names(all_in_all);

	for (int ii = 0; ii < all_in_all; ii++)
	{
		if (all_in_all < 26)
			names[ii] = 97 + ii;
	};

	return names;
}
// print input names
void print_input_name(int cIV, vector<string> names) {
	for (int ii = 0; ii < cIV; ii++) {
		if (ii == 0) { cout << "[" << names[ii] << ","; }
		else if (ii == cIV - 1) {cout << names[ii] << "]";}
		else { cout << names[ii] << ",";}
	};
}
// print input names
void print_Output_name(int cOV, vector<string> names) {
	for (int ii = (names.size()-cOV); ii < names.size(); ii++) {
		if (ii == (names.size() - cOV )) { cout << "[" << names[ii] << ","; }
		else if (ii == (names.size() - 1)) { cout << names[ii] << "]"; }
		else { cout << names[ii] << ","; }
	};
}
// print possibility 
void print_possibility(int cIV, vector<vector<bool>> IV_RT, int jj) {
		for (int ii = 0; ii < cIV; ii++) 
				{
					if (ii == 0) { cout << "(" << IV_RT[jj][ii] << ","; }
					else if (ii == cIV - 1) { cout << IV_RT[jj][ii] << ")"; }
					else { cout << IV_RT[jj][ii] << ","; }
				};
}
// ZustandMaschine random Text Generator
void random_text_generater(int cIV, int cSV, int cOV, string s) { // cIV : count Input			Variables
												 // cSV : count statustrans		Variables
												 // cOV : count output			Variables	
	vector<string> names = naming( cIV, cSV, cOV);
	int all_in_all = cIV + cSV + cOV;

	ofstream ofile(s);


	int p_Input = possibilities(cIV);
	int p_Output = possibilities(cOV);

	// wahrheitstabellen
	//********************
	vector<vector<bool>> IV_RT(p_Input),OV_RT(p_Output);
	// INPUT RealityTable
	IV_RT = reality_Table_generator(cIV);
	// OUTPUT RealityTable
	OV_RT = reality_Table_generator(cOV);
	
	// ascci small letters are from 97 to 122

	// random sequence laenge input moeglcihkeiten
	vector<int> Input_r_s = random_sequence(p_Input);
	vector<int> Output_r_s = random_sequence(p_Output);
	vector<int> Stat_r_s = random_sequence(cSV);

	// Ausgabe dass die datei erstellt wurde 	
	cout << endl << "a State machine random Text with :  " << endl << "\t\"" << cIV << "\" Input variables:" << "\t";
	for(int ii = 0; ii< cIV; ii++){ cout << names[ii] << "\t"; }; cout << endl;
	cout << "\t\"" << cSV << "\" Status variables: " << "\t";
	for (int ii = cIV; ii< cIV+cSV; ii++) { cout << names[ii] << "\t"; }; cout << endl;
	cout << "\t\"" << cOV << "\" Ouput variables: " << "\t";
	for (int ii = cIV+cSV; ii< cIV+cSV+cOV; ii++) { cout << names[ii] << "\t" ; }; cout << endl;
	cout << "has been generated. " << endl << endl;
	
	// falls man die wahrheitstabelle inschauen mag
	// cout << "Input reality table : " << endl;
	// print_realityTable(IV_RT);

	for(int ii = 0;ii<p_Input;ii++){
	
	print_input_name(cIV,names);
	//print_input_name_to_file
		for (int ii = 0; ii < cIV; ii++) {
			if (ii == 0) { ofile << "[" << names[ii] << ","; }
			else if (ii == cIV - 1) { ofile << names[ii] << "]"; }
			else { ofile << names[ii] << ","; }
		};

	cout << ":";
	ofile << ":";
	
	print_possibility(cIV, IV_RT, Input_r_s[ii]);
	//print_possibility_to_file
		for (int iii = 0; iii < cIV; iii++)
		{
			if (iii == 0) { ofile << "(" << IV_RT[Input_r_s[ii]][iii] << ","; }
			else if (iii == cIV - 1) { ofile << IV_RT[Input_r_s[ii]][iii] << ")"; }
			else { ofile << IV_RT[Input_r_s[ii]][iii] << ","; }
		};	

	cout << "(" << names[1+cSV+(Input_r_s[ii]%cSV)]<< ")";
	ofile << "(" << names[1 + cSV + (Input_r_s[ii] % cSV)] << ")";
	
	cout << " > ";
	ofile << " > ";

	print_Output_name(cOV, names);
	//print_Output_name_to_file
		for (int ii = (names.size() - cOV); ii < names.size(); ii++) {
			if (ii == (names.size() - cOV)) { ofile << "[" << names[ii] << ","; }
			else if (ii == (names.size() - 1)) { ofile << names[ii] << "]"; }
			else { ofile << names[ii] << ","; }
		};
	
	cout << ":";
	ofile << ":";
	
	print_possibility(cOV, OV_RT, Output_r_s[ii%p_Output]);
	//print_possibility_to_file
	for (int iii = 0; iii < cOV; iii++)
		{
			if (iii == 0) { ofile << "(" << OV_RT[Output_r_s[ii%p_Output]][iii] << ","; }
			else if (iii == cOV - 1) { ofile << OV_RT[Output_r_s[ii%p_Output]][iii] << ")"; }
			else { ofile << OV_RT[Output_r_s[ii%p_Output]][iii] << ","; }
		};

	cout << "(" << names[1 + cSV + ((Input_r_s[ii]+ (Input_r_s[ii]/2+1)) % cSV)] << ")";
	ofile << "(" << names[1 + cSV + ((Input_r_s[ii] + (Input_r_s[ii] / 2 + 1)) % cSV)] << ")";
	
	cout << endl;
	ofile << endl;	
	}
	cout << endl;	
}

void nicht_random_text_generater(int cIV, int cSV, int cOV, string s) { // cIV : count Input			Variables
																  // cSV : count statustrans		Variables
																  // cOV : count output			Variables	
	vector<string> names = naming(cIV, cSV, cOV);
	int all_in_all = cIV + cSV + cOV;

	ofstream ofile(s);


	int p_Input = possibilities(cIV);
	int p_Output = possibilities(cOV);

	// wahrheitstabellen
	//********************
	vector<vector<bool>> IV_RT(p_Input), OV_RT(p_Output);
	// INPUT RealityTable
	IV_RT = reality_Table_generator(cIV);
	// OUTPUT RealityTable
	OV_RT = reality_Table_generator(cOV);

	// ascci small letters are from 97 to 122

	// random sequence laenge input moeglcihkeiten
	vector<int> Input_r_s = random_sequence(p_Input);
	vector<int> Output_r_s = random_sequence(p_Output);
	vector<int> Stat_r_s = random_sequence(cSV);

	// Ausgabe dass die datei erstellt wurde 	
	cout << endl << "a State machine random Text with :  " << endl << "\t\"" << cIV << "\" Input variables:" << "\t";
	for (int ii = 0; ii< cIV; ii++) { cout << names[ii] << "\t"; }; cout << endl;
	cout << "\t\"" << cSV << "\" Status variables: " << "\t";
	for (int ii = cIV; ii< cIV + cSV; ii++) { cout << names[ii] << "\t"; }; cout << endl;
	cout << "\t\"" << cOV << "\" Ouput variables: " << "\t";
	for (int ii = cIV + cSV; ii< cIV + cSV + cOV; ii++) { cout << names[ii] << "\t"; }; cout << endl;
	cout << "has been generated. " << endl << endl;

	// falls man die wahrheitstabelle inschauen mag
	// cout << "Input reality table : " << endl;
	// print_realityTable(IV_RT);

	for (int ii = 0; ii<p_Input; ii++) {

		print_input_name(cIV, names);
		//print_input_name_to_file
		for (int ii = 0; ii < cIV; ii++) {
			if (ii == 0) { ofile << "[" << names[ii] << ","; }
			else if (ii == cIV - 1) { ofile << names[ii] << "]"; }
			else { ofile << names[ii] << ","; }
		};

		cout << ":";
		ofile << ":";

		print_possibility(cIV, IV_RT, ii);
		//print_possibility_to_file
		for (int iii = 0; iii < cIV; iii++)
		{
			if (iii == 0) { ofile << "(" << IV_RT[ii][iii] << ","; }
			else if (iii == cIV - 1) { ofile << IV_RT[ii][iii] << ")"; }
			else { ofile << IV_RT[ii][iii] << ","; }
		};

		// print start Zustand 
		cout << "(" << names[1 + cSV ] << ")";
		ofile << "(" << names[1 + cSV ] << ")";

		cout << " > ";
		ofile << " > ";

		print_Output_name(cOV, names);
		//print_Output_name_to_file
		for (int ii = (names.size() - cOV); ii < names.size(); ii++) {
			if (ii == (names.size() - cOV)) { ofile << "[" << names[ii] << ","; }
			else if (ii == (names.size() - 1)) { ofile << names[ii] << "]"; }
			else { ofile << names[ii] << ","; }
		};

		cout << ":";
		ofile << ":";

		print_possibility(cOV, OV_RT, Output_r_s[ii%p_Output]);
		//print_possibility_to_file
		for (int iii = 0; iii < cOV; iii++)
		{
			if (iii == 0) { ofile << "(" << OV_RT[Output_r_s[ii%p_Output]][iii] << ","; }
			else if (iii == cOV - 1) { ofile << OV_RT[Output_r_s[ii%p_Output]][iii] << ")"; }
			else { ofile << OV_RT[Output_r_s[ii%p_Output]][iii] << ","; }
		};

		//print Ziel Zustand
		cout << "(" << names[1 + cSV + ((Input_r_s[ii] + (Input_r_s[ii] / 2 + 1)) % cSV)] << ")";
		ofile << "(" << names[1 + cSV + ((Input_r_s[ii] + (Input_r_s[ii] / 2 + 1)) % cSV)] << ")";

		cout << endl;
		ofile << endl;
	}
	cout << endl;
}