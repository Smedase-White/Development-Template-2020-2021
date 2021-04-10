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
		cout << "\n1 - Удалить текущую строчку.\n";
		cout << "2 - Добавить новую строчку.\n";
		cout << "3 - Добавить новую подстрочку.\n";
		cout << "4 - Перейти на следущую строчку.\n";
		cout << "5 - Перейти на первую подстрочку.\n";
		cout << "6 - Перейти на предыдущую строчку.\n";
		cout << "7 - Заменить текущую строчку.\n";
		cout << "8 - Заменить ключ текущей строчки.\n";
		cout << "9 - Заменить значение текущей строчки.\n";
		cout << "i - Считать фалй.\n";
		cout << "o - Записать в файл.\n";
		cout << "\nq - Выйти из программы.\n";
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