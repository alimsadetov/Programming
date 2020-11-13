#pragma once
long int factor(int n) {
	long int otvet = 1;
	int i;
	for (i = 1; i <= n; i++) {
		otvet = otvet * i;
	}
	return otvet;
}