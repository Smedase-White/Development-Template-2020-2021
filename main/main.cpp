#include "text.h"

int main() 
{
	setlocale(LC_ALL, "Russian");
	Text t;
	bool run = true;
	while (run)
	{
		system("cls");
		cout << t;
		cout << "\n1 - ������� ������� �������.\n";
		cout << "2 - �������� ����� �������.\n";
		cout << "3 - �������� ����� ����������.\n";
		cout << "4 - ������� �� �������� �������.\n";
		cout << "5 - ������� �� ������ ����������.\n";
		cout << "6 - ������� �� ���������� �������.\n";
		cout << "7 - �������� ������� �������.\n";
		cout << "8 - �������� ���� ������� �������.\n";
		cout << "9 - �������� �������� ������� �������.\n";
		cout << "i - ������� ����.\n";
		cout << "o - �������� � ����.\n";
		cout << "\nq - ����� �� ���������.\n";
		char s;
		cin >> s;
		cin.get();
		try
		{
			switch (s)
			{
			case '1':
				t.remove();
				break;
			case '2':
			{
				string line; getline(cin, line);
				t.addLeft(line);
				break;
			}
			case '3':
			{
				string line; getline(cin, line);
				t.addRight(line);
				break;
			}
			case '4':
				t.left();
				break;
			case '5':
				t.right();
				break;
			case '6':
				t.top();
				break;
			case '7':
			{
				string line; getline(cin, line);
				t.replace(line);
				break;
			}
			case '8':
			{
				string line; getline(cin, line);
				t.replaceKey(line);
				break;
			}
			case '9':
			{
				string line; getline(cin, line);
				t.replaceValue(line);
				break;
			}
			case 'i':
			{
				string line; getline(cin, line);
				ifstream fileI("..\\" + line);
				if (fileI.is_open())
					fileI >> t;
				fileI.close();
				break;
			}
			case 'o':
			{
				string line; getline(cin, line);
				ofstream fileO("..\\" + line);
				if (fileO.is_open())
					fileO << t;
				fileO.close();
				break;
			}
			case 'z':
			{
				string line; getline(cin, line);
				cout << t.getValue(line) << '\n';
				system("pause");
				break;
			}
			case 'q':
				run = false;
				break;
			default:
				break;
			}
		}
		catch (logic_error l)
		{
			cout << l.what() << '\n';
			system("pause");
		}
	}
	return 0;
}