#include <iostream>
#include <fstream>
#include <string>
#include <stack>

#include "text_format.h"

using namespace std;

template <class T>
struct DLink
{
	DLink* left;
	DLink* right;
	T value;
	DLink(T& val, DLink<T>* l = nullptr, DLink<T>* r = nullptr) : value(val), left(l), right(r) {};
};

typedef DLink<Line>	unit;

class Text
{
private:
	unit* root;
	unit* curr;
	stack<unit*> path;

	void printTRL(ostream&, unit* root, unit* curr, int level) const;
	void writeFile(ofstream&, unit*, int level) const;

	void removeBranch(unit* element);
	void removeBranch();

	unit* getUnit(string& path);

public:
	Text() { root = curr = nullptr; }
	~Text() { if (root != nullptr) removeBranch(root); }

	bool right();
	bool left();
	bool top();
	bool overTop();

	void addLeft(const string& line);
	void addRight(const string& line);

	void replace(const string& line);
	void replaceKey(const string& line);
	void replaceValue(const string& line);
	void remove();

	string getValue(string& path);

	friend ostream& operator<<(ostream& out, const Text& t)
	{
		t.printTRL(out, t.root, t.curr, 0);
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const Text& t)
	{
		t.writeFile(out, t.root, 0);
		return out;
	}

	friend ifstream& operator>>(ifstream& in, Text& t);
};