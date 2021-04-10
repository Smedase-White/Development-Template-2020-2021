#pragma once
#include <string>
#include <list>

using namespace std;

inline list<string> split(const string& line, char spliter)
{
	list<string> list;
	string underpart = "";
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == spliter)
		{
			list.push_back(underpart);
			underpart = "";
			continue;
		}
		underpart += line[i];
	}
	list.push_back(underpart);
	return list;
}

inline list<string> split(const string& line, char spliter, int max_size)
{
	list<string> list;
	string underpart = "";
	int count = 0, i = 0;
	for (i; i < line.size(); i++)
	{
		if (line[i] == spliter)
		{
			list.push_back(underpart);
			underpart = "";
			count++;
			if (count + 1 == max_size)
				break;
			continue;
		}
		underpart += line[i];
	}
	i++;
	for (i; i < line.size(); i++)
		underpart += line[i];
	list.push_back(underpart);
	return list;
}

enum class object_type
{
	String, Comment, Title
};

class Object
{
public:
	virtual string getString() const = 0;

	virtual object_type getType() const = 0;
	virtual string getLine() const = 0;
};

class String : public Object
{
private:
	string value;
public:
	String(const string& v) : value(v) {};
	string getString() const { return value; }

	object_type getType() const { return object_type::String; }
	string getLine() const { return value; }
};

class Comment : public Object
{
private:
	string value;
public:
	Comment(const string& v) : value(v) {};
	string getString() const { return value; }

	object_type getType() const { return object_type::Comment; }
	string getLine() const { return "#" + value; }
};


class Title : public Object
{
public:
	string getString() const { return ""; }

	object_type getType() const { return object_type::Title; }
	string getLine() const { return ""; }
};

class Line
{
private:
	string key;
	Object* value;
public:
	Line(const string& line)
	{
		if (line[0] == '#')
		{
			key = "";
			string s = line;
			s.erase(0, 1);
			value = new Comment(s);
			return;
		}
		list<string> underparts = split(line, ':', 2);
		if (underparts.size() == 1)
		{
			key = "";
			value = new Comment(underparts.front());
		}
		else
		{
			key = underparts.front();
			if (underparts.back() == "")
				value = new Title();
			else
				value = new String(underparts.back());
		}
	}
	string getKey() { return key; }
	void setKey(const string& s) 
	{ 
		key = s; 
		if (value->getType() == object_type::Comment)
			value = new String(value->getString());
	}
	Object* getValue() { return value; }
	void setValue(const string& s) 
	{
		if (s == "")
			value = new Title();
		else
			value = new String(s); 
	}
	string getLine() 
	{
		switch (value->getType())
		{
		case object_type::String :
			return key + ":" + value->getLine();
		case object_type::Comment:
			return value->getLine();
		case object_type::Title:
			return key + ":";
		default:
			return "";
		}
	}
};