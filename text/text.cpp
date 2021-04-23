#include "text.h"

void Text:: printTRL(ostream& out, unit* root, unit* curr, int level) const
{
	if (root == nullptr)
		return;
	if (root == curr)
		out << ">|";
	else
		out << " |";
	for (int i = 0; i < level; i++)
		out << "  ";
	out << root->value.getLine();
	out << endl;
	printTRL(out, root->right, curr, level + 1);
	printTRL(out, root->left, curr, level);
}

void Text::writeFile(ofstream& out, unit* curr, int level) const
{
	if (curr == nullptr)
		return;
	if (curr != root)
		out << endl;
	for (int i = 0; i < level; i++)
		out << "    ";
	out << curr->value.getLine();
	writeFile(out, curr->right, level + 1);
	writeFile(out, curr->left, level);
}

void Text::removeBranch()
{
	if (curr->right != nullptr)
	{
		unit* temp = curr->right;
		path.push(curr);
		path.push(temp);
		if (temp->left != nullptr)
			path.push(temp->left);
		if (temp->right != nullptr)
			path.push(temp->right);
		while (path.top() != curr)
		{
			temp = path.top();
			path.pop();
			if (temp->left != nullptr)
				path.push(temp->left);
			if (temp->right != nullptr)
				path.push(temp->right);
			delete temp;
		}
		path.pop();
	}
	unit* temp = curr;
	if (this->top())
	{
		if (curr->right == temp)
		{
			curr->right = temp->left;
			if (temp->left == nullptr)
				curr->value.setValue(" ''");
		}
		if (curr->left == temp)
			curr->left = temp->left;
	}
	else
	{
		root = temp->left;
		curr = root;
	}
	delete temp;
}

void Text::removeBranch(unit* element)
{
	if (element == nullptr)
		return;
	removeBranch(element->right);
	removeBranch(element->left);
	delete element;
}

unit* Text::getUnit(string& line)
{
	if (line == "")
		return nullptr;
	if (root == nullptr)
		return nullptr;
	list<string> path = split(line, '.');
	string last = path.back();
	path.pop_back();
	unit* temp = root;
	while (!path.empty())
	{
		if (temp->value.getValue()->getType() != object_type::Title)
		{
			if (temp->left == nullptr)
				return nullptr;
			temp = temp->left;
			continue;
		}
		if (temp->value.getKey() != path.front())
		{
			if (temp->left == nullptr)
				return nullptr;
			temp = temp->left;
			continue;
		}
		temp = temp->right;
		path.pop_front();
	}
	while (true)
	{
		if (temp->value.getKey() != last)
		{
			if (temp->left == nullptr)
				return nullptr;
			temp = temp->left;
			continue;
		}
		break;
	}
	return temp;
}

void Text::addLeft(const string& line)
{
	Line* l = new Line(line);
	if (curr == nullptr)
	{
		root = new unit(*l, root, nullptr);
		curr = root;
	}
	else
		curr->left = new unit(*l, curr->left);
}

void Text::addRight(const string& line)
{
	Line* l = new Line(line);
	if (curr == nullptr)
	{
		root = new unit(*l, nullptr, root);
		curr = root;
	}
	else
	{
		if (curr->value.getValue()->getType() == object_type::String)
			curr->value.setValue("");
		curr->right = new unit(*l, curr->right);
	}
}

bool Text::right()
{
	if (curr == nullptr)
		return false;
	if (curr->right == nullptr)
		return false;
	path.push(curr);
	curr = curr->right;
	return true;
}

bool Text::left()
{
	if (curr == nullptr)
		return false;
	if (curr->left == nullptr)
		return false;
	path.push(curr);
	curr = curr->left;
	return true;
}

bool Text::top()
{
	if (path.empty())
		return false;
	curr = path.top();
	path.pop();
	return true;
}

bool Text::overTop()
{
	if (path.empty())
		return false;
	unit* temp = curr;
	while (true)
	{
		if (path.top()->right == temp)
		{
			curr = path.top();
			path.pop();
			return true;
		}
		temp = path.top();
		path.pop();
		if (path.empty())
			return false;
	}
	return true;
}

string Text::getValue(string& path)
{
	unit* temp = getUnit(path);
	if (temp == nullptr)
		return "";
	return temp->value.getValue()->getLine();
}

void Text::replace(const string& line)
{
	Line* l = new Line(line);
	if (curr == nullptr)
		throw logic_error("Can't replace, becouse current is nullptr!");
	curr->value = *l;
}

void Text::replaceKey(const string& line)
{
	if (curr == nullptr)
		throw logic_error("Can't replace key, becouse current is nullptr!");
	curr->value.setKey(line);
}

void Text::replaceValue(const string& line)
{
	if (curr == nullptr)
		throw logic_error("Can't replace value, becouse current is nullptr!");
	if (curr->right != nullptr)
		throw logic_error("Can't replace value, becouse current is title.");
	curr->value.setValue(line);
}

void Text::remove()
{
	if (curr == nullptr)
		throw logic_error("Con't remove line in empty text.");
	removeBranch();
}

ifstream& operator>>(ifstream& in, Text& t)
{
	t.removeBranch(t.root);
	t.root = nullptr;
	t.curr = nullptr;
	while (!t.path.empty()) { t.path.pop(); }
	int prevLevel = 0;
	while (!in.eof())
	{
		string line;
		getline(in, line);
		int i = 0;
		while (line[i] == ' ')
			i++;
		line.erase(0, i);
		i /= 4;
		if (i > prevLevel)
		{
			t.addRight(line);
			t.right();
			prevLevel = i;
			continue;
		}
		for (i; i < prevLevel; prevLevel--)
		{
			t.overTop();
		}
		t.addLeft(line);
		t.left();
	}
	while (t.top()) {}
	return in;
}