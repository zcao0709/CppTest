#include <iostream>

using namespace std;

static void calc(unsigned int *minimumMax, unsigned int *money, int s, int e,
				unsigned int sum, int split) {
	//cout << s << ',' << e << ',' << sum << ',' << split << endl;
	if (split == 1) {
		if (*minimumMax == 0 || *minimumMax < sum)
		*minimumMax = sum;
		return;
	}
	unsigned int average = sum / split;
	unsigned int partSum = 0;
	int i = s;
	while (i <= e) {
		partSum += money[i];
		if (partSum > average)
			break;
		i++;
	}
	unsigned int currentMax1, currentMax2, currentMinMax;
	if (i > s) {
		currentMax1 = partSum - money[i];
		calc(&currentMax1, money, i, e, sum-currentMax1, split-1);
	}
	if (i < e) {
		currentMax2 = partSum;
		calc(&currentMax2, money, i+1, e, sum-currentMax2, split-1);
	}

	if (i > s && i < e)
		currentMinMax = min<unsigned long>(currentMax1, currentMax2);
	else if (i <= s)
		currentMinMax = currentMax2;
	else
		currentMinMax = currentMax1;

	if (*minimumMax == 0 || *minimumMax < currentMinMax)
		*minimumMax = currentMinMax;

	return;
}
/*
int main() {
	int n;
	cin >> n;
	int k;
	cin >> k;

	unsigned int sum = 0;
	unsigned int *money = new unsigned int[n];
	unsigned int max = 0;
	for (int i = 0; i < n; i++) {
		cin >> money[i];
		if (money[i] == 0) {
			i--;
			n--;
			continue;
		}
		sum += money[i];
		if (max < money[i])
			max = money[i];
	}
	cout << "N: " << n << endl;
	unsigned int minimumMax = 0;
	if (k == 1)
		minimumMax = sum;
	else if (n <= k)
		minimumMax = max;
	else
		calc(&minimumMax, money, 0, n-1, sum, k);
	cout << minimumMax;
	delete [] money;
	return 0;
}
*/
