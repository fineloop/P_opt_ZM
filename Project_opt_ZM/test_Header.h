#include "stdafx.h"
#include <iostream>
#include <vector>
#include "stdlib.h"
#include <string>
#include <fstream>

using namespace std;

void text_gen() {
	ofstream ofile("test_text_out.txt");
	ofile << "Hello World.";
}