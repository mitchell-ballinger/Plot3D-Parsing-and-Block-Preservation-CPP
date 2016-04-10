// import_pl3D.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int subStrInt(string l, int a[]) {
	string str = "";
	for (int x = a[0]; x < a[1] + 1; x++) {
		str += l[x];
	}
	return stoi(str);
}

double subStrDbl(string l, int a[]) {
	string str = "";
	for (int x = a[0]; x < a[1] + 1; x++) {
		str += l[x];
	}
	return stod(str);
}

int main(){
	int nb;
	string del = " \f\n\r\t\v";
	string block_junk;
	string line;

	ifstream ifs("3D.ascii.xyz");
	ifs >> nb;

	int *nbi = new int[nb];
	int *nbj = new int[nb];
	int *nbk = new int[nb];
	int *dim = new int[nb];

	int LOC[16][2] = { { 0 } };
	int b = 0;
	int e = 0;
	int c = 0;
	int LC = 0;
	int dMAX;

	//cout << typeid(nblocks).name() << nblocks << endl;
	getline(ifs, block_junk);
	getline(ifs, line);

	//########################################
	// Line Processing of Block Dimensions
	//########################################
	for (unsigned int n = 1; n < line.length(); n++) {
		if (isspace(line[n - 1]) && isspace(line[n])) {   // _, _
			continue;
		}
		if (!isspace(line[n - 1]) && !isspace(line[n])) { // #, #
			continue;
		}
		if (isspace(line[n - 1]) && !isspace(line[n])) {  // _, #
			b = n;
		}
		if (!isspace(line[n - 1]) && isspace(line[n])) {  // #, _
			e = n - 1;
		}
		if (n == 1) {                                     // [#
			if (!isspace(line[n - 1])) {
				b = n - 1;
			}
		}
		if (n == (line.length() - 1)) {                   // #]
			if (!isspace(line[n + 1])) {
				e = n;
			}
		}
		if ((b != 0) && (e != 0)) {
			LOC[c][0] = b;
			LOC[c][1] = e;
			c += 1;
			b = 0;
			e = 0;
		}
	}

	//########################################
	// Setting Block Dimensions
	//########################################
	int bpl = (c + 1) / 3; // Blocks Per Line
	for (int m = 0; m < bpl; m++) { // Cycle First Set of Blocks Per Line, Set Dimensions
		nbi[LC] = subStrInt(line, LOC[3 * m]);
		nbj[LC] = subStrInt(line, LOC[3 * m + 1]);
		nbk[LC] = subStrInt(line, LOC[3 * m + 2]);
		dim[LC] = nbi[LC] * nbj[LC] * nbk[LC];
		dMAX = dim[LC];
		//cout << nbi[LC] << " | ";
		//cout << nbj[LC] << " | ";
		//cout << nbk[LC] << " || ";
		//cout << LC << " -- " << dim[LC] << endl;
		LC++;
	}
	cout << endl;
	for (int n = 0; n < (nb / bpl) - 1; n++) { // Cycle Remaining Lines of Blocks, Set Dimensions
		getline(ifs, line);
		for (int m = 0; m < bpl; m++) {
			nbi[LC] = subStrInt(line, LOC[3 * m]);
			nbj[LC] = subStrInt(line, LOC[3 * m + 1]);
			nbk[LC] = subStrInt(line, LOC[3 * m + 2]);
			dim[LC] = nbi[LC] * nbj[LC] * nbk[LC];
			if (dim[LC] > dMAX) {
				dMAX = dim[LC];
			}
			//cout << nbi[LC] << " | ";
			//cout << nbj[LC] << " | ";
			//cout << nbk[LC] << " || ";
			//cout << LC << " -- " << dim[LC] << endl;
			LC++;
		}
	}

	b = 0;
	e = 0;
	c = 0;

	int F = 0;
	int POS[3][2] = { { 0 } };
	getline(ifs, line);
	int END = line.length();
	//########################################
	// Line Processing of Vertex Data
	//########################################
	for (int n = 1; n < END; n++) {
		if (n == 1) {                           // [#
			if (!isspace(line[n - 1])) {
				b = n - 1;
				F++;
			}
		}
		if (n == (END - 1)) {                   // #]
			if (!isspace(line[n + 1])) {
				e = n;
				F++;
			}
		}
		if (F == 2) {
			POS[c][0] = b;
			POS[c][1] = e;
			b = 0;
			e = 0;
			F = 0;
			c++;
		}
		if (isspace(line[n - 1]) && isspace(line[n])) {   // _, _
			continue;
		}
		if (!isspace(line[n - 1]) && !isspace(line[n])) { // #, #
			continue;
		}
		if (isspace(line[n - 1]) && !isspace(line[n])) {  // _, #
			b = n;
			F++;
		}
		if (!isspace(line[n - 1]) && isspace(line[n])) {  // #, _
			e = n - 1;
			F++;
		}
	}

	struct bl{
		double *vx;
		double *vy;
		double *vz;
	};
	bl *BLOCK = new bl[nb];
	//########################################
	// Accessing Block Vertices
	//########################################
	// Cycle First Set of Vertex Data
	//BLOCK[0].vx = new double[dMAX];
	//BLOCK[0].vy = new double[dMAX];
	//BLOCK[0].vz = new double[dMAX];
	//BLOCK[0].vx[0] = subStrDbl(line, POS[0]);
	//BLOCK[0].vy[0] = subStrDbl(line, POS[1]);
	//BLOCK[0].vz[0] = subStrDbl(line, POS[2]);
	//cout << BLOCK[0].vx[0] << " | ";
	//cout << BLOCK[0].vy[0] << " | ";
	//cout << BLOCK[0].vz[0] << endl;
	for (int x = 0; x < nb; x++) {
		int d = dim[x];
		BLOCK[x].vx = new double[d];
		BLOCK[x].vy = new double[d];
		BLOCK[x].vz = new double[d];
		for (int y = 0; y < d; y++) {
			BLOCK[x].vx[y] = subStrDbl(line, POS[0]);
			BLOCK[x].vy[y] = subStrDbl(line, POS[1]);
			BLOCK[x].vz[y] = subStrDbl(line, POS[2]);
			//cout.precision(7);
			//cout << "scientific:\n" << std::scientific;
			//cout << BLOCK[x].vx[y] << " | ";
			//cout << BLOCK[x].vy[y] << " | ";
			//cout << BLOCK[x].vz[y] << endl;
			//cout << d + nb/2 << endl;
			getline(ifs, line);
		}
		cout << d << endl;
	}
	
//	getline(ifs, line);

	return 0;
}

