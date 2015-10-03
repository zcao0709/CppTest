#include <iostream>
#include <iterator>
#include <algorithm>
#include <list>
#include <stack>

using namespace std;

enum {STRAIGHT, TURNBACK, CTCLOCKWS, CLOCKWISE};

class direction {
public:
    /*
    * 0: straight
    * 1: turn back
    * 2: counter-clockwise
    * 3: clockwise
    */
    int type;
    int left;
    int mid;
    int right;
    int len;
    int idx;

    direction *prev;
    direction *next;

    direction(int type, int idx) {
        this->type = type;
        left = 1;
        mid = 0;
        right = 0;
        len = 1;
        this->idx = idx;
        prev = NULL;
        next = NULL;
    }
};

class Moves {
private:
    direction *head;
    direction *tail;
    string raw;
    unsigned int idx;

    int total;
public:
    Moves(string &s) {
        raw = s;
        idx = 0;

        direction *d = new direction(0, 0);
        head = tail = d;

        total = 0;
    }

    void direct() {
        char last = raw[0];
        //direction *lastCtclockws = NULL;
        direction *lastClockwise = NULL;
        direction *lastTurnback = NULL;
        for (unsigned int i = 1; i < raw.length(); i++) {
            char c = raw[i];
            int type = addDirection(last, c, i);
            if (type == TURNBACK) {
            	if (lastTurnback != NULL) {
            		removeTurnback(lastTurnback);
            	}
            	lastTurnback = tail;
            } else if (type == CLOCKWISE) {
            	if (lastClockwise != NULL) {
                    if (tail->prev->type == TURNBACK && tail->prev->prev->type == TURNBACK) {
                        removeTurnback(tail->prev);
                        lastTurnback = NULL;
                    }
                    if (tail->type == CLOCKWISE && tail->prev->type == CLOCKWISE && tail->prev->len == 1) {
                    	removeDoubleClockwise(tail);
                    }
            	} else {
            		lastClockwise = tail;
            	}
            } else if (type == CTCLOCKWS) {
            	lastClockwise = NULL;
            		if (lastTurnback != NULL) {
            			removeTurnback(lastTurnback);
            			lastTurnback = NULL;
            		}
            		if (tail->type == CTCLOCKWS && tail->prev->type == CTCLOCKWS) {
            			removeDoubleCtclockws(tail);
            		}
            } else {
            	lastClockwise = NULL;
            }
            last = raw[tail->idx];
        }
        print();
        /*
        removeDoubleClockwise();
        print();
        removeTurnback();
        print();
        removeDoubleClockwise();
        print();
        */
        while (head != tail) {
        	removeDoubleCtclockws();
        	print();
        	removeTurnback();
        	print();
        }
        cout << total << endl;
    }

    void print() {
        for (direction *d = head; d != NULL; d = d->next)
            cout << "printing " << raw[d->idx] << " len" << d->len << " " << d->type << endl;
        //cout << endl;
    }

private:
    void removeDoubleCtclockws() {
    	cout << "removeDoubleCtclockws" << endl;
    	direction *lastCtclockws = NULL;
    	for (direction *d = head; d != NULL; d = d->next) {
    		if (d->type == CTCLOCKWS) {
    			if (lastCtclockws == NULL)
    				lastCtclockws = d;
    			else
    				d = removeDoubleCtclockws(d);
    		} else if (d->type == TURNBACK) {
    			d = removeTurnback(d);
    			print();
    		} else if (d->type == CLOCKWISE)
    			lastCtclockws = NULL;

    		if (d == NULL)
    			break;
    	}
    }

    direction *removeDoubleCtclockws(direction *d) {
    	direction *mid = d->prev;
    	while (mid->type == STRAIGHT) {
    		mid = mid->prev;
    	}
    	int num = 0;
    	d = removeTurnback(mid->prev, d, &num);
    	cout << "num " << num << endl;
    	total += (num * mid->len);
    	return d;
    }

    void removeDoubleClockwise() {
    	cout << "removeDoubleClockwise" << endl;
        direction *lastClockwise = NULL;
        for (direction *d = head; d != NULL; d = d->next) {
            if (d->type == CLOCKWISE) {
                if (lastClockwise == NULL)
                    lastClockwise = d;
                else {
                    if (d->prev->type == TURNBACK && d->prev->prev->type == TURNBACK) {
                        removeTurnback(d->prev);
                    }
                    if (d->type == CLOCKWISE && d->prev->type == CLOCKWISE && d->prev->len == 1) {
                    	d = removeDoubleClockwise(d);
                    	if (d == NULL)
                    		break;
                    }
                }
            } else if (d->type == STRAIGHT || d->type == CTCLOCKWS)
                lastClockwise = NULL;
        }
    }

    direction *removeDoubleClockwise(direction *d) {
    	//cout << "removing " << raw[d->idx] << " " << d->type << endl;
    	direction *mid = d->prev;
    	d = removeTurnback(mid->prev, d);
    	//fixAfterDelete(mid);
    	//if (d != NULL)
    		//fixAfterDelete(d);
    	return d;
    }

    void removeTurnback() {
    	cout << "removeTurnback" << endl;
        for (direction *d = head; d != NULL; d = d->next) {
            if (d->type == TURNBACK)
                d = removeTurnback(d);
            if (d == NULL)
            	break;
        }
    }

    direction *removeTurnback(direction *d) {
    	return removeTurnback(d->prev, d);
    }

    direction *removeTurnback(direction *left, direction *right) {
    	return removeTurnback(left, right, NULL);
    }

    direction *removeTurnback(direction *left, direction *right, int *num) {
        cout << "removing " << raw[left->idx] << " " << raw[right->idx] << " " << right->type << endl;
        bool iterable = false;
        if (left->next == right)
        	iterable = true;
        int len = 1;
        //if (left->type == STRAIGHT && right->type == STRAIGHT) {
        	len = min<unsigned int>(left->len, right->len);
        //}
        if (num != NULL)
        	*num += len;
        char deleteChar = raw[right->idx];
        if ((left->len -= len) == 0) {
            left = remove(left)->prev;
        }
        //d = d->next;
        //if (d->len == 1) {
            //next = d->next;
            //right = remove(right);
        //}
        if ((right->len -= len) == 0) {
        	//right->len -= len;
        	//if (right->len == 0) {
        		//d = d->next;
        		right = remove(right);
        	//}
        }
        cout << "removed " << left << " " << right << endl;
        /*if (left != NULL) {
        	fixAfterDelete(left->next);
        	if (left->next != right)
        		fixAfterDelete(right);
        }*/
        if (right == NULL || left == NULL) {
        	fixRightDelete(left);
        	fixLeftDelete(right);
            return right;
        }
        if (turnback(raw[left->idx], raw[right->idx])
        		&& (raw[right->idx] == deleteChar || iterable)) {
        	print();
        	cout << "continue removing" << endl;
        	return removeTurnback(left, right, num);
        }
        /*
        direction *toFix = head;
        if (left != NULL)
        	toFix = left->next;
        if (toFix != right)
        	fixAfterDelete(toFix);
        */
        if (left->next == right) {
        	fixRightDelete(left);
        } else {
        	fixRightDelete(left);
        	fixLeftDelete(right);
        }
        return right;
    }

    direction *fixRightDelete(direction *d) {
    	if (d == NULL) {
    		if (head != NULL)
    			head->type = 0;
    		return d;
    	}
    	if (d->next == NULL)
    		return d;
    	char left = raw[d->idx];
    	char right = raw[d->next->idx];
    	if (straight(left, right)) {
    		d->len += d->next->len;
    		remove(d->next);
    	} else {
    		int type = TURNBACK;
            if (ctclockwise(left, right))
                type = CTCLOCKWS;
            else if (clockwise(left, right))
            	type = CLOCKWISE;
            d->next->type = type;
    	}
    	return d;
    }

    direction *fixLeftDelete(direction *d) {
    	if (d == NULL)
    		return d;
    	if (d->prev == NULL) {
    		d->type = 0;
    		return d;
    	}
    	char right = raw[d->idx];
    	char left = raw[d->prev->idx];
        if (straight(left, right)) {
        	d->type = d->prev->type;
        	d->len += d->prev->len;
        	remove(d->prev);
        	/*
        	if (d->prev->type == 0) {
        		d->len += d->prev->len;
        		remove(d->prev);
        	} else {
        		d->type = 0;
        		if (straight(right, raw[d->next->idx])) {
        			//fixAfterDelete(d->next);
        			d->len += d->next->len;
        			remove(d->next);
        		}
        	}
        	*/
        } else {
            int type = TURNBACK;
            if (ctclockwise(left, right))
                type = CTCLOCKWS;
            else if (clockwise(left, right))
            	type = CLOCKWISE;
            //if (d->len == 1)
                d->type = type;
            //else {
                //d->len--;
                //direction *newd = new direction(type, d->idx);
                //add(newd, d->prev);
            //}
        }
        return d;
    }

    int addDirection(char last, char c, int idx) {
    	int type;
        if (straight(last, c))
            type = STRAIGHT;
        else if (turnback(last, c))
            type = TURNBACK;
        else if (ctclockwise(last, c))
            type = CTCLOCKWS;
        else
            type = CLOCKWISE;

    	add(type, idx);
    	return type;
    }

    void add(int type, int idx) {
        cout << "adding " << raw[idx] << " " << type << endl;
        if (type == 0) {
            tail->len++;;
        } else {
            direction *d = new direction(type, idx);
            tail->next = d;
            d->prev = tail;
            tail = d;
        }
    }

    void add(direction *d, direction *prev) {
        direction *next = prev->next;
        d->prev = prev;
        if (prev == NULL)
            head = d;
        else
            prev->next = d;

        d->next = next;
        if (next == NULL)
            tail = d;
        else
            next->prev = d;
    }

    direction *remove(direction *d) {
        direction *prev = d->prev;
        direction *next = d->next;
        if (prev == NULL)
            head = next;
        else
            prev->next = next;

        if (next == NULL)
            tail = prev;
        else
            next->prev = prev;
        delete d;
        return next;
    }

    bool straight(char a, char c) {
        return a == c;
    }

    bool turnback(char a, char c) {
        return (a == 'N' && c == 'S') || (a == 'S' && c == 'N')
                || (a == 'E' && c == 'W') || (a == 'W' && c == 'E');
    }

    bool clockwise(char a, char c) {
        return (a == 'N' && c == 'E') || (a == 'E' && c == 'S')
                    || (a == 'S' && c == 'W') || (a == 'W' && c == 'N');
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
    m->direct();
    //m->print();

    return 0;
}
