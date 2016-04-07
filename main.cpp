#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <string>
using namespace std;

int main(int argc, char **argv){
	int numNeurons = 100;
	int numPatterns = 50;
	int patterns[numPatterns][numNeurons];
	double weights[numNeurons][numNeurons];
	double local;
	int patternStable[numPatterns];
	int updatedP[numPatterns][numNeurons];
	double stableSum;
	double stableProb;
	int stableCount;
	bool stable;

	for (int j = 0; j < numNeurons; j++){
		for (int i = 0; i < numNeurons; i++){
			weights[i][j] = 0.00;
		}
	}

	for (int i = 0; i < numPatterns; i++){
		patternStable[i] = 1;
	}

	ofstream fo;
	string sfo = "stableSum.txt";
	fo.open(sfo.c_str());
	if (fo.fail()){
		exit(1);
	}

	ofstream f;
	string sf = "UnstableProb.txt";
	f.open(sf.c_str());
	if (f.fail()){
		exit(2);
	}

	srand(time(0));
	stableProb = 0.00;
	int stableS = 0;
	for (int k = 0; k < numPatterns; k++){

		// randomly generate 50 bipolar vectors of states 1 or -1 and imprint patterns/store in weights array
		for(int i = 0; i < numNeurons; i++){
			patterns[k][i] = 1 - 2 * (rand() % 2);
		}

		// imprint patterns
		for (int i = 0; i < numNeurons; i++){
			for (int j = 0; j < numNeurons; j++){
				if (i != j){
					weights[i][j] += patterns[k][i]*patterns[k][j];
				}
				if (i == j){
					weights[i][j] = 0;
				}
			}
		}

		// test for stability
		stableCount = 0;
		stable = true;
		for (int m = 0; m <= k; m++){
			for (int n = 0; n < numNeurons; n++){		
				
				local = 0.00;
				for (int l = 0; l < numNeurons; l++){
					local += ((weights[n][l]) / (numNeurons)) * (patterns[m][l]);
				}

				if (local < 0){
					updatedP[m][n] = -1;
				}
				if (local >= 0){
					updatedP[m][n] = 1;
				}

				if (updatedP[m][n] != patterns[m][n]){
					patternStable[n] = 0;	
					stable = false;
				}

				stableSum = 0.00;
				for (int i = 0; i < numPatterns; i++){
					stableSum += patternStable[i];
				}

			}

			if (stable){
				stableCount++;
			}

		}


		printf("k = %d\n", k);
		fo << stableCount << endl;

		stableProb = stableSum/numPatterns;

		f << 1-stableProb << endl;

		printf("stable patterns: %d\n", stableCount);
		printf("probability of stable imprints: %f\n", stableProb);
		printf("probability of unstable imprints: %f\n", 1-stableProb);

	}

	return 0;

}



