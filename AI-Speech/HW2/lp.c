#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 320
#define SAMPLING_RATE 8000
#define LP_POINT 10

FILE *fin, *low_envelope_fp;
float* dft(float* signal);


int main()
{
	float signal[N], log_arr[N], cepstrum[N], real[N], imag[N];
	float* spec_mag;
	float* low_envelope;
	short data;
	fopen_s(&fin, "Male.raw", "rb");

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

	for (int n = 160; n < N; n++) {
		signal[n] = 0;
	}

	// Autocorrelation
	float auto_correlation[LP_POINT + 1] = { 0.0, };
	
	for (int k = 0; k <= LP_POINT; k++) {
		for (int n = 0; n < N; n++) {
			if (0 <= n <= (N - 1 - k))
				auto_correlation[k] += signal[n + k] * signal[n];

			else
				continue;
		}
	}

	// Durbin algorithm
	float sum;
	float errors[LP_POINT + 1] = { 0.0, };
	float reflect_coef[LP_POINT + 1] = { 0.0, };
	float filter_coef[LP_POINT + 1][LP_POINT + 1];
	for (int i = 0; i <= LP_POINT; i++) {
		for (int j = 0; j <= LP_POINT; j++) {
			filter_coef[i][j] = 0.0;
		}
	}

	errors[0] = auto_correlation[0];

	for (int i = 1; i <= LP_POINT; i++) {
		sum = 0;
		for (int j = 1; j <= i - 1; j++) {
			sum += filter_coef[i - 1][j] * auto_correlation[i - j];
		}

		reflect_coef[i] = (auto_correlation[i] - sum) / errors[i - 1];
		filter_coef[i][i] = reflect_coef[i];

		for (int j = 1; j <= i - 1; j++) {
			filter_coef[i][j] = filter_coef[i - 1][j] - reflect_coef[i] * filter_coef[i - 1][i - j];
		}
		errors[i] = (1 - pow(reflect_coef[i], 2)) * errors[i - 1];
	}

	// Make a(n)
	float arr[N] = { 0, };
	arr[0] = 1;
	for (int i = 1; i < N; i++) {
		if (i <= LP_POINT)
			arr[i] = - filter_coef[LP_POINT][i];

		else
			arr[i] = 0;
	}

	// N-point DFT 
	spec_mag = dft(arr);

	float inversed[N];
	for (int i = 0; i < N; i++)
		inversed[i] = 1 / spec_mag[i];

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
