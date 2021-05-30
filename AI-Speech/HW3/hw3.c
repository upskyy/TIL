#include <stdio.h>
#include <stdlib.h>

#define DIM 10
#define EPOCH 1
#define CHECK_POINT 500

void supervised_train(float* weight, float lr);

int main() {
	float weight[DIM] = { 0.0 , };
	float lr = 0.1;

	// init weight
	for (int i = 0; i < DIM; i++)
		weight[i] = ((float)rand() / RAND_MAX) - 0.5;

	for (int epoch = 0; epoch < EPOCH; epoch++)
		supervised_train(weight, lr);
}

void supervised_train(float* weight, float lr) {
	FILE *fin, *fout;
	float input[DIM] = { 0.0, };
	float target = 0.0;
	float loss = 0.0;
	float error = 0.0;

	fopen_s(&fin, "trainingDB.dat", "rt");
	fopen_s(&fout, "output.dat", "wt");

	for (int timestep = 1; timestep < 1001; timestep++) {
		// read data  
		for (int i = 0; i < DIM; i++)
			fscanf_s(fin, "%f", input + i);
		fscanf_s(fin, "%f", &target);

		// forward
		float hypothesis = 0.0;
		for (int i = 0; i < DIM; i++)
			hypothesis += input[i] * weight[i];

		error = (hypothesis - target);
		loss = ((error * error) / 2);

		// update
		for (int i = 0; i < DIM; i++)
			weight[i] -= (lr * input[i] * error);

		// save result
		for (int i = 0; i < DIM; i++)
			fprintf(fout, "%10.7f ", weight[i]);
		fprintf(fout, "%10.7f\n", loss);

		if (timestep % CHECK_POINT == 0.0)
			printf("%10.7f\n", loss);
	}
	fclose(fin);
	fclose(fout);
}
