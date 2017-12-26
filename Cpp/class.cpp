#include <iostream>

using namespace std;

class DayOfYear
{
public:
	/*
	 * Constructor:
	 *	-must have the same name as the class.
	 *	-cannot return a value.
	 *	-cannot be type of anything.
	 */
	DayOfYear(int month_val, int day_val);
	/* Default Constructor */
	DayOfYear();

	/*
	 * Default Destructor
	 * Unlike constructor, it never has parameters.
	 */
	~DayOfYear();

	void output(void);
	void input(void);

private:
	int month;
	int day;
	enum MonthName
	{
		JANUARY=1,
		FEBRUARY,
		MARCH,
		APRIL,
		MAY,
		JUNE,
		JULY,
		AUGUST,
		SEPTEMBER,
		OCTOBER,
		NOVEMBER,
		DECEMBER
	};
};

int main(void)
{
	/* Implicit calls */
	DayOfYear today;
	DayOfYear foo(3, 18);
	/* The proper way of calling constructor. */
	DayOfYear bar;
	DayOfYear spam;
	/* Invalid */
	// DayOfYear spam();

	/* Explicit calls */
	spam = DayOfYear(11, 11);

	today.input();
	today.output();
	foo.output();
	bar.output();
	spam.output();
	
	return 0;
}

/*
 * One way of defining it.
 * '::' is called scope resolution operator.
 */
DayOfYear::DayOfYear(int month_val, int day_val)
{
	month = month_val;
	day = day_val;
}
/*
 * Another way.
 * ':' is called initialization section.
 * */
DayOfYear::DayOfYear()
	:month(1), day(1)
{
	/* Empty */
}
DayOfYear::~DayOfYear()
{
	cout << "Destructor is called.\n";
}
void DayOfYear::input(void)
{
	cout << "Enter month\n";
	cin >> month;

	cout << "Enter day\n";
	cin >> day;
}
void DayOfYear::output(void)
{
	switch (month)
	{
		case DayOfYear::JANUARY:
			cout << "January ";
			break;

		case DayOfYear::FEBRUARY:
			cout << "February ";
			break;

		case DayOfYear::MARCH:
			cout << "March ";
			break;

		case DayOfYear::APRIL:
			cout << "April ";
			break;

		case DayOfYear::MAY:
			cout << "May ";
			break;

		case DayOfYear::JUNE:
			cout << "June ";
			break;

		case DayOfYear::JULY:
			cout << "July ";
			break;

		case DayOfYear::AUGUST:
			cout << "August ";
			break;

		case DayOfYear::SEPTEMBER:
			cout << "September ";
			break;

		case DayOfYear::OCTOBER:
			cout << "October ";
			break;

		case DayOfYear::NOVEMBER:
			cout << "November ";
			break;

		case DayOfYear::DECEMBER:
			cout << "December ";
			break;

		default:
			cout << "Invalid month ";
			break;
	}

	cout << day << endl;
}

