#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 

using namespace std;

enum Special { ПЗ, КН, ІТ, СА };

string s_special[] = {
	"Інженерія програмного забезпечення",
	"Комп'ютерні науки",
	"Інформаційні системи та технології",
	"Системний Аналіз" };

struct student
{
	string prizv;
	int kurs;
	Special spec;
	int math;
	int informatic;
	int physics;
	union {
		int programing;
		int history;
		int distmath;
	};
};

void Create(student* s, const int kilkist);
void Print(student* s, const int kilkist);

void Sort(student* s, const int kilkist);
int* IndexSort(student* s, const int kilkist);
void PrintIndexSorted(student* s, int* I, const int kilkist);
int BinSearch(student* s, const int kilkist, const string prizv, const int kurs, const int matematic);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int klkst_student;
	cout << "Введіть кількість студентів: "; cin >> klkst_student;
	cout << endl;
	student* s = new student[klkst_student];

	string prizv;
	int kurs;
	int matematic;
	int found;

	int menuItem;
	do {
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних" << endl;
		cout << " [4] - індексне впорядкування та вивід даних" << endl;
		cout << " [5] - бінарний пошук студента" << endl << endl;

		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть пункт меню: "; cin >> menuItem;
		switch (menuItem)
		{
		case 1:
			Create(s, klkst_student);
			break;
		case 2:
			Print(s, klkst_student);
			break;
		case 3:
			Sort(s, klkst_student);
			break;
		case 4:
			PrintIndexSorted(s, IndexSort(s, klkst_student), klkst_student);
			break;
		case 5:
			cout << "Введіть ключі пошуку:" << endl;
			cin.get();
			cin.sync();
			cout << " прізвище: ";
			getline(cin, prizv);

			cout << " курс: ";
			cin >> kurs;

			cout << " бал з математики: "; cin >> matematic;
			cout << endl;
			if ((found = BinSearch(s, klkst_student, prizv, kurs, matematic)) != -1)
				cout << "Знайдено студента в списку під номером" << found + 1 << endl;
			else
				cout << "Шуканого студента в списку не знайдено" << endl;
			break;

		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
		cout << endl;
	} while (menuItem != 0);

	delete[] s;
}

void Create(student* s, const int kilkist)
{
	int kurs, special;
	for (int i = 0; i < kilkist; i++)
	{
		cout << endl;
		cout << "студент № " << i + 1 << endl;

		cin.get();
		cin.sync();

		cout << "  прізвище: "; getline(cin, s[i].prizv);
		cout << "  курс: "; cin >> s[i].kurs;
		cout << "спеціальність(0 -Інженерія програмного забезпечення, 1 - Комп'ютерні науки, 2 - Інформаційні системи та технології, 3 -Системний Аналіз):";cin >> special;
		s[i].spec = (Special)special;
		cout << "  оцінка з фізики: "; cin >> s[i].math;
		cout << "  оцінка з математики: "; cin >> s[i].informatic;
		switch (special)
		{
		case 0:
			cout << "  оцінка з програмування: "; cin >> s[i].programing;
			break;
		case 1:
			cout << "  оцінка з історії: "; cin >> s[i].history;
			break;
		case 2:
		case 3:
		case 4:
			cout << "  оцінка з дискретної математики: "; cin >> s[i].distmath;
			break;
		default:
			cout << "Ви ввели помилкове значення! " << endl;
		}
		cout << endl;
	}
}

void Print(student* s, const int kilkist)
{
	cout << "============================================================================================================================"
		<< endl;
	cout << "| №  | Прізвище     | Курс | Спеціальність           | Фізика | Математика  | Програмування | Історія |Дискретна|"
		<< endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < kilkist; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " "
			<< "| " << setw(13) << left << s[i].prizv
			<< "| " << setw(3) << right << s[i].kurs << "  "
			<< "| " << setw(23) << left << s_special[s[i].spec] << " "
			<< "| " << setw(4) << right << s[i].math << "   "
			<< "| " << setw(6) << right << s[i].informatic << "      ";
		switch (s[i].spec)
		{
		case 0:
			cout << "| " << setw(7) << right << s[i].programing << "       |" << setw(18) << "|" << setw(13) << "|" << endl;
			break;
		case 1:
			cout << "| " << setw(15) << "|" << setw(10) << right << s[i].history << "       |" << setw(13) << "|" << endl;
			break;
		case 2:
		case 3:
		case 4:
			cout << "| " << setw(15) << "|" << setw(18) << "|" << right << setw(7) << s[i].distmath << "     |" << endl;
			break;
		}
	}
	cout << "============================================================================================================================" << endl;
}

void Sort(student* s, const int kilkist)
{
	student tmp;

	for (int i0 = 0; i0 < kilkist - 1; i0++)
		for (int i1 = 0; i1 < kilkist - i0 - 1; i1++)
		{
			if ((s[i1].spec > s[i1 + 1].spec)
				|| (s[i1].spec == s[i1 + 1].spec && s[i1].math > s[i1 + 1].math)
				|| (s[i1].spec == s[i1 + 1].kurs && s[i1].math == s[i1 + 1].math && s[i1].prizv < s[i1 + 1].prizv)
				)
			{
				tmp = s[i1];
				s[i1] = s[i1 + 1];
				s[i1 + 1] = tmp;
			}

		}
}

int* IndexSort(student* s, const int kilkist)
{
	int* I = new int[kilkist];

	for (int i = 0; i < kilkist; i++)
		I[i] = i;

	int i, j, value;
	for (i = 1; i < kilkist; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && (
				(s[I[j]].spec > s[value].spec)
				||
				(s[I[j]].spec == s[value].spec && s[I[j]].math > s[value].math
				||
				(s[I[j]].spec == s[value].kurs && s[I[j]].math == s[value].math && s[I[j]].prizv > s[value].prizv)
				);
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(student* s, int* I, const int kilkist)
{
	cout << "============================================================================================================================"
		<< endl;
	cout << "| №  | Прізвище     | Курс | Спеціальність           | Фізика | Математика  | Програмування | Історія| Дискретна |"
		<< endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < kilkist; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " "
			<< "| " << setw(13) << left << s[I[i]].prizv
			<< "| " << setw(3) << right << s[I[i]].kurs << "  "
			<< "| " << setw(23) << left << s_special[s[I[i]].spec] << " "
			<< "| " << setw(4) << right << s[I[i]].math << "   "
			<< "| " << setw(6) << right << s[I[i]].informatic << "      ";
		switch (s[i].spec)
		{
		case 0:
			cout << "| " << setw(7) << right << s[I[i]].programing << "       |" << setw(18) << "|" << setw(13) << "|" << endl;
			break;
		case 1:
			cout << "| " << setw(15) << "|" << setw(10) << right << s[I[i]].history << "       |" << setw(13) << "|" << endl;
			break;
		case 2:
		case 3:
		case 4:
			cout << "| " << setw(15) << "|" << setw(18) << "|" << right << setw(7) << s[I[i]].distmath << "     |" << endl;
			break;
		}
	}
	cout << "============================================================================================================================";
}

int BinSearch(student* s, const int kilkist, const string prizv, const string spec, const int math)
{
	int L = 0, R = kilkist - 1, m;
	do {
		m = (L + R) / 2;
		if (s[m].spec == spec&& s[m].math == math && s[m].prizv == prizv)
			return m;
		if (
			(s[m].spec < spec)
			|| (s[m].spec == spec && s[m].math< math)
			|| (s[m].spec== spec && s[m].math == math && s[m].prizv < prizv)
			)
		{
			R = m - 1;
		}
		else
		{
			L = m + 1;
		}
	} while (L <= R);
	return -1;
}