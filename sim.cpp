#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	unsigned long begin;
	unsigned long end;
	cin >> begin;
	cin >> end;

	int n;
	cin >> n;

	unsigned long fork[n];
	unsigned long kill[n];
	for (int i = 0; i < n; i++) {
		unsigned long f, k;
		cin >> f;
		cin >> k;
		if (k < begin || f > end) {
			n--;
			i--;
			continue;
		}
		if (f < begin)
			f = begin;
		fork[i] = f < begin ? begin : f;
		kill[i] = k;
	}
	sort(fork, fork + n);
	sort(kill, kill + n);
	for (int i = 0; i < n; i++)
		cout << fork[i] << ' ';
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << kill[i] << ' ';
	cout << endl;
	if (n == 0) {
		cout << 0 << endl;
		cout << 0 << endl;
		return 0;
	}
	int i = 1, j = 0;
	while (i < n && fork[i] == fork[i-1])
		i++;
	int min, max, sim;
	min = max = sim = i;
	if (fork[0] > begin || kill[n-1] < end)
		min = 0;
	while (i < n || j < n) {
		if(i < n && fork[i] <= kill[j]) {
			sim++;
			if (sim > max)
				max = sim;
			i++;
		} else {
			if (kill[j] > end)
				break;
			sim--;
			if (sim < min)
				min = sim;
			j++;
		}
	}
	cout << min << endl;
	cout << max << endl;
	return 0;
}
