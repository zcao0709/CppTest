#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n;
	unsigned int a0;
	cin >> a0;
	if (n < 2) {
		cout << a0;
		return 0;
	}
	unsigned int a1;
	cin >> a1;
	unsigned long s1 = a0 + a1;
	if (n < 3) {
		cout << s1;
		return 0;
	}
	unsigned int a2;
	cin >> a2;
	unsigned long s2 = a0 + a2;
	unsigned long s3 = a1 + a2;
	//cout << s1 << " " << s2 << " " << s3 << endl;

	for (int i = 3; i < n; i++) {
		unsigned int ai;
		cin >> ai;
		unsigned long newS1 = max(max(s1, s2), s3);
		s3 = s2 + ai;
		s2 = s1 + ai;
		s1 = newS1;
		//cout << s1 << " " << s2 << " " << s3 << endl;
	}
	cout << max(max(s1, s2), s3);
}
