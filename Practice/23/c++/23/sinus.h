#ifndef SINUS_H
#define SINUS_H
#include "factorial.h"
float sinus(float x, int k) {
	int n;
	float otvet = 0;
	for (n = 0; n <= k; n++) {
		otvet += pow(-1, n) * pow(x, 2 * n + 1) / factor(2 * n + 1);
	}
	return otvet;
}
#endif