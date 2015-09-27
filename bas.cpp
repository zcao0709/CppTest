#include <iostream>

using namespace std;

static void calc(unsigned long *minimumMax, unsigned long *money, int s, int e,
				unsigned long sum, int split) {
	//cout << s << ',' << e << ',' << sum << ',' << split << endl;
	if (split == 1) {
		if (*minimumMax == 0 || *minimumMax < sum)
		*minimumMax = sum;
		return;
	}
	unsigned long average = sum / split;
	unsigned long partSum = 0;
	int i = s;
	while (i <= e) {
		partSum += money[i];
		if (partSum > average)
			break;
		i++;
	}
	unsigned long currentMax1, currentMax2, currentMinMax;
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

int main() {
	int n;
	cin >> n;
	int k;
	cin >> k;

	unsigned long sum = 0;
	unsigned long *money = new unsigned long[n];
	unsigned long max = 0;
	for (int i = 0; i < n; i++) {
		cin >> money[i];
		if (money[i] == 0) {
			i--;
			k--;
			continue;
		}
		sum += money[i];
		if (max < money[i])
			max = money[i];
	}
	unsigned long minimumMax = 0;
	if (k == 1)
		minimumMax = sum;
	else if (n == k)
		minimumMax = max;
	else
		calc(&minimumMax, money, 0, n-1, sum, k);
	cout << minimumMax;
	delete [] money;
	return 0;
}
