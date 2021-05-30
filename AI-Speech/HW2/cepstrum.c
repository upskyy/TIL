#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 320
#define SAMPLING_RATE 8000
#define LOW_TIME_POINT 15

FILE *fin, *low_envelope_fp;
float* dft(float* signal);

int main()
{
	float signal[N], log_arr[N], cepstrum[N], real[N], imag[N];
	float* spec_mag; 
	float* low_envelope;
	short data;
	fopen_s(&fin, "Male.raw", "rb");
	fopen_s(&low_envelope_fp, "low_envelope.txt", "wb");

	// Read data
	for (int n = 0; n < N; n++) {
		fread(&data, 2, 1, fin);
		signal[n] = (float)data;
	}

	// Hamming window
	float window[N] = { 0.0, };

	for (int n = 0; n < N; n++) {
		window[n] = 0.54 - 0.46 * cos((2 * 3.14 * n) / (N - 1));
	}

	for (int n = 0; n < N; n++) {
		signal[n] *= window[n];
	}

	// N-point DFT 
	spec_mag = dft(signal);

	// log
	for (int n = 0; n < N; n++)
		log_arr[n] = log10(spec_mag[n]);

	// Inverse DFT
	for (int k = 0; k < N; k++) {
		real[k] = 0.0;
		imag[k] = 0.0;

		for (int n = 0; n < N; n++) {
			real[k] += log_arr[n] * cos(2 * 3.14 * n * k / (float)N);
			imag[k] += log_arr[n] * sin(2 * 3.14 * n * k / (float)N);
		}
		cepstrum[k] = real[k] - imag[k];
	}

	// low-time liftering
	float low_time[N];
	for (int n = 0; n < N; n++) {
		if (n < LOW_TIME_POINT || n >(N - LOW_TIME_POINT))
			low_time[n] = cepstrum[n];
		else
			low_time[n] = 0.0;
	}

	// DFT
	low_envelope = dft(low_time);
	
	for (int i = 0; i < N; i++)
		fprintf(low_envelope_fp, "%10.4f\n", low_envelope[i]);

	_fcloseall();
}

float* dft(float* signal) {
	float spec_real[N], spec_imag[N], spec_mag[N];

	for (int k = 0; k < N; k++) {
		spec_real[k] = 0.0;
		spec_imag[k] = 0.0;

		for (int n = 0; n < N; n++) {
			spec_real[k] += (signal[n] * cos(2 * 3.14 * k * n / N));
			spec_imag[k] -= (signal[n] * sin(2 * 3.14 * k * n / N));
		}
		spec_mag[k] = pow(spec_real[k], 2) + pow(spec_imag[k], 2);
		spec_mag[k] = sqrt(spec_mag[k]);
	}

	return spec_mag;
}