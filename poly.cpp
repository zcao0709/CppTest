#include <iostream>
#include <iterator>
#include <list>
#include <stack>

using namespace std;

class Moves {
private:
	list<char> *moves;
	list<char>::iterator pos;
	string raw;
	unsigned int idx;

	stack<unsigned int> *fp;
	stack<unsigned int> *dp;
	stack<unsigned int> *cp;

	int total;
public:
	Moves(string &s) {
		raw = s;
		idx = 0;

		moves = new list<char>;
		pos = moves->begin();

		fp = new stack<unsigned int>;
		dp = new stack<unsigned int>;
		cp = new stack<unsigned int>;

		total = 0;
	}

	void traverse() {
		firstPass();
		secondPass();
	}

	void print() {
		if (moves->empty())
			cout << "empty";
		else
			copy(moves->begin(), moves->end(), ostream_iterator<char>(cout, " "));
		cout << endl << total << endl;
	}

private:
	void clearStack(stack<unsigned int> *s) {
		while (!s->empty())
			s->pop();
	}

	void firstPass() {
		for (; idx < raw.length(); idx++) {
			if (moves->empty())
				moves->push_back(raw[idx]);
			else {
				if (moves->back() == raw[idx])
					moves->push_back(raw[idx]);
				else
					firstFix();
			}
		}
		applyDp();
		cout << "first ";
		print();
	}

	void secondPass() {
		while (!moves->empty()) {
			clearStack(fp);
			clearStack(dp);
			clearStack(cp);
			list<char>::iterator lastPos = moves->begin();
			int i = 0;
			for (pos = moves->begin(); pos != moves->end(); pos++, i++) {
				if (pos != moves->begin()) {
					lastPos = pos;
					lastPos--;
				} else {
					continue;
				}
				if (*lastPos == *pos) {
					continue;
				} else if (clockwise(*lastPos, *pos)) {
					cout << *pos << " clockwise" << endl;
					fp->push(i);
				} else if (turnback(*lastPos, *pos)) {
					cout << *pos << " turnback" << endl;
					dp->push(i);
					pos++;
					applyDp();
					pos--;
				} else {
					cout << *pos << " ctclockwise" << endl;
					if (!cp->empty() && cp->top() > fp->top()) {
						applyCp();
					}
				}
			}
		}
	}

	void firstFix() {
		if (clockwise(raw[idx])) {
			cout << raw[idx] << " clockwise" << endl;
			if (!fp->empty() && fp->top() == moves->size()-1)
				applyFp();
			else {
				while (!fp->empty())
					fp->pop();
				fp->push(moves->size());
				moves->push_back(raw[idx]);
			}
		} else if (turnback(raw[idx])) {
			cout << raw[idx] << " turnback" << endl;
			dp->push(moves->size());
			moves->push_back(raw[idx]);
		} else {
			cout << raw[idx] << " ctclockwise" << endl;
			applyDp();
			moves->push_back(raw[idx]);
		}
	}

	void applyCp() {

		list<char>::iterator midPos = pos;
		midPos--;
		char mid = *midPos;
		int midNum = 1;
		while (*(--midPos) == mid)
			midNum++;
		list<char>::iterator leftPos = midPos;
		midPos++;
		list<char>::iterator rightPos = pos;
		char left = *midPos;
		char right = *rightPos;
		int num = 1;
		while (++rightPos != moves->end()) {
			if (*rightPos != right)
				break;
			if (leftPos == moves->begin())
				break;
			if (*(--leftPos) != left) {
				leftPos++;
				break;
			}
			num++;
		}
		total += (num * midNum);
		fixDp(leftPos);
		moves->erase(leftPos, midPos);
		pos = moves->erase(pos, rightPos);
		pos--;
	}

	void applyFp() {
		list<char>::iterator leftPos = moves->end();
		leftPos--;
		list<char>::iterator forErase = leftPos;
		char left = *(--leftPos);
		char right = raw[idx++];
		while (idx < raw.length() && raw[idx] == right) {
			if (leftPos == moves->begin())
				break;
			if (*(--leftPos) != left) {
				leftPos++;
				break;
			}
			idx++;
		}
		idx--;
		fixDp(leftPos);
		moves->erase(leftPos, forErase);
		print();
	}

	void applyDp() {
		while (!dp->empty()) {
			unsigned int p = dp->top();
			dp->pop();
			list<char>::iterator rightPos = moves->begin();
			advance(rightPos, p);
			list<char>::iterator leftPos = rightPos;
			char right = *rightPos;
			char left = *(--leftPos);
			cout << left << ", " << right << endl;
			while (++rightPos != moves->end()) {
				if (*rightPos != right)
					break;
				if (leftPos == moves->begin())
					break;
				if (*(--leftPos) != left) {
					leftPos++;
					break;
				}
			}
			//cout << *leftPos << ", " << *rightPos << endl;
			fixDp(leftPos);
			moves->erase(leftPos, rightPos);
			print();

		}
	}

	void fixDp() {
		while (!dp->empty()) {
			if (dp->top() >= moves->size())
				dp->pop();
			else
				break;
		}
	}

	void fixDp(list<char>::iterator leftPos) {
		if (!dp->empty()) {
			list<char>::iterator pos = moves->begin();
			advance(pos, dp->top());
			if (pos == leftPos)
				dp->pop();
		}
	}

	bool turnback(char c) {
		return turnback(moves->back(), c);;
	}

	bool turnback(char a, char c) {
		return (a == 'N' && c == 'S') || (a == 'S' && c == 'N')
				|| (a == 'E' && c == 'W') || (a == 'W' && c == 'E');
	}

	bool clockwise(char c) {
		return clockwise(moves->back(), c);
	}

	bool clockwise(char a, char c) {
		return (a == 'N' && c == 'E') || (a == 'E' && c == 'S')
					|| (a == 'S' && c == 'W') || (a == 'W' && c == 'N');
	}

	bool ctclockwise(char c) {
		return ctclockwise(moves->back(), c);
	}

	bool ctclockwise(char a, char c) {
		return (a == 'N' && c == 'W') || (a == 'W' && c == 'S')
					|| (a == 'S' && c == 'E') || (a == 'E' && c == 'N');
	}
};

int main() {
	//int n;
	//cin >> n;
	string s;
	cin >> s;

	Moves *m = new Moves(s);
	m->traverse();
	m->print();

	return 0;
}
