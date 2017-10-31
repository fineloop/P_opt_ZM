// Project_opt_ZM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ZM_Generater.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#ifndef _USE_OLD_OSTREAMS
using namespace std;
#endif

/**************************************************
Struktur fuer eine Zeile der Schaltwerkstabelle
**************************************************/
class state_tabrow {										//tablerow
	string					curs;							//current state
	int cinput;
	int inputp;												//binaere Eingagnsmoeglichkeiten
	int coutput;
	vector<string>			statetrans;						//state transition - Uebergangszustaende
	vector<vector<bool>>	bitout;							//boolsche Bitausgaenge - Adressierung: bitout[Input][Nr. Ausgangsvariable]
public:
	state_tabrow() {};
	state_tabrow(string cS,int cI,int cO) {					// cI: count Input
		curs = "";
		curs = cS;
		inputp = pow(2, cinput);
		cinput = cI;
		coutput = cO;
		statetrans.resize(inputp);
		bitout.resize(inputp);
	};
	void assign_curs(string s) { curs = s; };
	void assign_packet(int p,string nS, vector<bool> bO) {	 // p: position, nS: next state, bO= bitout 
		statetrans[p] = nS;
		bitout[p] = bO;
	};
	void print_curs() { cout << curs; };
	void print_statetrans(int ii) { cout << statetrans[ii]; }
	void print_bitout(int ii) {								// das muss noch ueberladen werden
		for (int iii = 0; iii < coutput; iii++) 
			{ 
				if (iii == 0) { cout << "(" << bitout[ii][iii] << ","; }
				else if (iii == (coutput - 1)) { cout << bitout[ii][iii] << ")"; }
				else { cout << bitout[ii][iii] << ","; }
			} 
		}						
};
/*************************************************/
/**************************************************
allgemeine Klasse fuer eine Zustandsmaschine
**************************************************/
class automat {
	int cinput;				//count of inputs
	int inputp;				//binaere Eingagnsmoeglichkeiten
	int coutput;			//count of outputs
	int cstates;			//count of states
	vector<string> InputNames;
	vector<string> StatusNames;
	vector<string> OutputNames;
	vector<state_tabrow> total_states;	//row vector - Vektor aller Reihen einer Tabelle

public:
	automat() {								//Konstruktor fuer undefinierten Automaten
		cinput = 0;
		inputp = 0;
		coutput = 0;
		cstates = 0; 
	}
	automat(int ci, int co, int cs, vector<string> InN, vector<string> StN, vector<string> OutN) {		//Konstruktor fuer anlegen eines Automaten mit entsprechender Speicherallokierung fuer alle Werte der Schaltwerktabelle und Dummyzustaenden/-werten
		cinput = ci;
		inputp = pow(2, cinput);
		coutput = co;
		cstates = cs;
		total_states.resize(cstates);
		InputNames = InN;
		StatusNames = StN;
		OutputNames = OutN;

		for (int ii = 0; ii < total_states.size(); ii++) {
			string puf;
			puf = (char)(65 + ii);
			total_states[ii] = state_tabrow(puf, cinput, coutput);
		}
	};
	void push_name(string x, string name)		// x: (in/state/out), name: the name to push_back
	{
		if (x == "in") { InputNames.push_back(name); }
		else if (x == "state") { StatusNames.push_back(name); }
		else if (x == "out") { OutputNames.push_back(name); }
		else { cout << "error while pushing back a name !!" << endl; };
	}
	void assign_total_state_tabrow_curs(int S, string s) { // S: zustand, s: name des Zustands 
		total_states[S].assign_curs(s);
	};
	void assign_total_state_tabrow_packet(int S, int p, vector<bool> b, string nS) {	// S: Zustand nummer, p : möglichkeit(possibility)/ index, b: bitout,  nS: next State
		total_states[S].assign_packet(p, nS, b);
	}
	void print_name(string t, int S, int p) { // t: type (in/state/out),	S: state Nummer (falls ein state zu ausdruecken ist),	p: index
		if (t == "in") { cout << InputNames[p]; }
		else if (t == "state") { total_states[S].print_curs(); }
		else if (t == "out") { cout << OutputNames[p]; }
		else {cout << "ERROR Namen Ausdruck problem";};
	}
	void consoleprinttable() {
		cout << endl << "Console print Table: ";
		// Zeile 1
		cout << endl;
		print_name("in", 0, 0);
		cout  <<"|";
		for (int ii = 0; ii < inputp; ii++) { cout << "\t"; }
		cout << " |";
		cout << endl;
		print_name("in", 0, 1);
		cout << "|";
		for (int ii = 0; ii < inputp; ii++) { cout << "\t"; }
		cout << " |";
		cout << endl;
		print_name("in", 0, 2);
		cout << "|";
		for (int ii = 0; ii < inputp; ii++) { cout << "\t"; }
		cout << " |" << endl;
		cout << "_|_";
		for (int ii = 0; ii < (3*inputp); ii++) { cout << "____"; }
		
		
		cout << endl;
		total_states[0].print_curs();
		cout << "|";
		for (int ii = 0; ii < inputp; ii++) { cout << "\t"; }
		cout << " |";


		cout << endl;
//		for (int ii = 0; ii < inputp * 2; ii++) {
//			if (ii == inputp)
//				cout << " | " << ii%inputp;
//			else
//				cout << " " << ii%inputp;
//			if (ii >= inputp)
//				for (int jj = 1; jj < coutput; jj++)
//					cout << " ";
//		}
		cout << endl;
//		// Zeile 2
//		int ss = 2 + inputp * 2 * 2 + inputp * (coutput - 1) + 2;
//		for (int ii = 0; ii < ss; ii++) {
//			if (ii == 1 || ii == 2 + 2 * inputp + 1) cout << "|";
//			else cout << "-";
//		}
//		cout << endl;
//		// Zustandzeilen
//		for (int state = 0; state < cstates; state++) {
//			cout << rowvec[state].curs << "|";
//			for (int ii = 0; ii < inputp; ii++) {
//				cout << " " << rowvec[state].statetrans[ii];
//			}
//			cout << " |";
//			for (int ii = 0; ii < inputp; ii++) {
//				cout << " ";
//				for (int jj = 0; jj < coutput; jj++)
//					cout << rowvec[state].bitout[ii][jj];
//			}
//			cout << endl;
//		}
	}
	
};
/*************************************************/
void read_file(string file_name,automat &a,int cI,int cS, int cO) { // p: possibiltiy number (index des state_tabrows )

	ifstream infile(file_name);
	if (!infile) { cout << "Cannot open File" << endl; };
	const int Max = 150; char Buffer[Max + 1];
	int StN = 1; // Zustand Nummer (wird automatisiert erst mal jetzt erste zustand)
	int l = 1; // first line (wird später geschleift) 
	infile.getline(Buffer, Max);

//	cout << "eingelesene Zeile:" << endl << Buffer << endl;

	string string_in(Buffer);						// convert char array to string
	string separator = "[()]>: ,\n\t.";				//chars that separates words
	string token;									//extracted word
	int completelen = string_in.size();
	int endpos = 0;									//Endposition of a word
	int startpos = 0;								//Startposition of word
	string_in = string_in + '\n';					//delimiter was skipped during read
	int count = 1;									//Word counter

	int jj=0;			// index um ein string aufzusammeln
	while (1) {
		vector<bool> bitout_Buf; 
		
		string NextState;
		startpos = string_in.find_first_not_of(separator, endpos);												// Skip leading separators
		if (startpos == string_in.npos) break;																	// Check on string end
		endpos = string_in.find_first_of(separator, startpos);													// Find end of word
		if (endpos == string_in.npos) break;																	// Check on string end
		token = string_in.substr(startpos, endpos - startpos);													// Extract the word
		if (count <= cI) { a.push_name("in", token); }															// eingang namen speichern
		else if (count == ((2 * cI) + 1)) { a.assign_total_state_tabrow_curs(StN-1, token);  }						// current state name speichern
		else if ((count > ((2 * cI) + 1)) && ((count <= (((2 * cI) + 1) + cO)))) { a.push_name("out", token); }	// Ausgang namen speichern
		else if (count > (((2 * cI) + 1) + cO)) { if (jj < cO) {	if (token == "1") { bitout_Buf.push_back(1); jj++;}
																	else { bitout_Buf.push_back(1); } 
																}
													else { NextState = token; a.assign_total_state_tabrow_packet(StN, l, bitout_Buf, NextState); };}
		else { if(!((count > cI) && (count <= 2*cI))) cout << "ERROR ERROR ERROR bei dem Eilesen von bitout und Next state"; };
		//cout << count << ". " << token << endl;																	// Print word, number
		count++;																								// Increment counter
		
	}
}
/**************************************************
Main
**************************************************/
void main()
{
	int cinput = 3;			// Dummyauto....
	int coutput = 2;
	int cstates = 3;
	string file_name = "ZustandMaschine_323.txt";

	// Datei erstellen: der Unterschied zwischen random und nicht random ist die Reihenfolge der möglichkeiten von den Eingangsvariablen 
	nicht_random_text_generater(cinput, coutput, cstates, file_name);
	// random_text_generater(cinput, coutput, cstates, file_name);

	vector<string> InN; // = { "i","j","k" };
	vector<string> StN; // = { "a","b" };
	vector<string> OutN; // = { "c","d","e" };



	automat A(cinput, coutput, cstates,InN,StN,OutN);			// Dummyautomat anlegen mit 3 Eingaengen, 4 Ausgaengen und 4 moeglichen Zustaenden
	
	read_file(file_name, A,cinput,cstates,coutput);
	A.consoleprinttable();
	cout << endl << endl << endl;
	//automat B(2, 2, 10);
	//B.consoleprinttable();

}

