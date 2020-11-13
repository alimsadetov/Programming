#ifndef SOCHETANIYA_H
#define SOCHETANIYA_H
#include "factorial.h"
long int soch(int k, int n) {
	long int otvet;
	otvet = factor(n) / (factor(k) * factor(n - k));
	return otvet;
}
#endif