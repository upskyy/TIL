#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 1600
#define SAMPLING_RATE 16000

// 1 : 16000 = 0.28 : x1
// 1 : 16000 = 0.41 : x2
// 1 : 16000 = 0.29 : x3
// 1 : 16000 = 0.15 : x4
// 1 : 16000 = 0.06 : x5
// 1 : 16000 = 0.13 : x6
// 1 : 16000 = 0.13 : x7
// 1 : 16000 = 0.17 : x8
int skip[8] = {
	SAMPLING_RATE * 0.28,   
	SAMPLING_RATE * 0.41,   
	SAMPLING_RATE * 0.29,   
	SAMPLING_RATE * 0.15,   
	SAMPLING_RATE * 0.06,   
	SAMPLING_RATE * 0.13,   
	SAMPLING_RATE * 0.13,   
	SAMPLING_RATE * 0.17
};
FILE *fin;

float calculate(int idx);

int main()
{
	float note_freq[8] = {0.0, };
	fopen_s(&fin, "input16k.raw", "rb");
	
	for (int i = 0; i < 8; i++) {
		note_freq[i] = calculate(i);
		printf("%d : %.2f\n", i + 1, note_freq[i]);
	}

	_fcloseall();
}

float calculate(int idx)
{
	float signal[N], spec_real[N], spec_imag[N], spec_mag[N], freq;
	short data;

	// skip to the start
	for (int n = 0; n < skip[idx]; n++)
		fread(&data, 2, 1, fin);

	// read data
	for (int n = 0; n < N; n++) {
		fread(&data, 2, 1, fin);
		signal[n] = (float)data; // input array
	}

	// Hamming window
	float window[N] = {0.0, };

	for (int n = 0; n < N; n++) {
		window[n] = 0.54 - 0.46 * cos((2 * 3.14 * n) / (N - 1));
	}

	for (int n = 0; n < N; n++) {
		signal[n] *= window[n];
	}

	// N-point DFT 
	for (int k = 0; k < N; k++) {
		spec_real[k] = 0.0;
		spec_imag[k] = 0.0;
		for (int n = 0; n < N; n++) {
			spec_real[k] += (signal[n] * cos(2 * 3.14 * k * n / N));
			spec_imag[k] -= (signal[n] * sin(2 * 3.14 * k * n / N));
		}
		spec_mag[k] = pow(abs(spec_real[k]), 2) + pow(abs(spec_imag[k]), 2);
		spec_mag[k] = sqrt(spec_mag[k]);
	}

	// peak magnitude 
	float max_magnitude = 0.0;
	int max_idx = -1;

	for (int n = 0; n < N; n++) {
		if (max_magnitude < spec_mag[n]) {
			max_magnitude = spec_mag[n];
			max_idx = n;
		}
	}

	// freq (Hz)
	freq = (float)max_idx * (float)(SAMPLING_RATE / N);
	
	if (freq > (float)(SAMPLING_RATE / 2)) {
		freq = (SAMPLING_RATE - freq);
	}


	return freq;
}

