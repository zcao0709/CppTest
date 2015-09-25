#include <iostream>
#include <set>

using namespace std;

class Orbit {
private:
	unsigned long radius;

public:
	Orbit(int radius) {
		this->radius = radius;
	}

	~Orbit() {

	}

	bool operator<(const Orbit &o) const {
		return radius < o.radius;
	}

	bool operator==(Orbit &o) const {
		return radius == o.radius;
	}

	void increase() {
		radius *= 2;
	}

	unsigned long getRadius() const {
		return radius;
	}
};
/*
int main() {
	int n;
	cin >> n;
	set<Orbit> *orbits = new set<Orbit>();
	for (int i = 0; i < n; i++) {
		long radius;
		cin >> radius;
		Orbit *o = new Orbit(radius);
		while (1) {
			set<Orbit>::iterator pos = orbits->find(*o);
			if (pos == orbits->end()) {
				orbits->insert(*o);
				break;
			} else {
				o->increase();
				orbits->erase(pos);
				delete &(*pos);
			}
		}
	}
	cout << orbits->size() << endl;
	for (set<Orbit>::iterator pos = orbits->begin(); pos != orbits->end(); pos++) {
		cout << pos->getRadius() << endl;
	}
	return 0;
}
*/
