#include <iostream>

using namespace std;

class Foo
{
public:
	Foo(int x_val, int y_val)
		:x(x_val), y(y_val) {};
	Foo() {};

	int get_x(void) const { return x; };
	int get_y(void) const { return y; };

	void output(void)
	{
		cout << "(" << get_x() << "," << get_y() << ")" << endl;
	}
	/* Using friend */
	friend bool operator ==(const Foo& operand1, const Foo& operand2);

private:
	int x;
	int y;
};

/* Not using friend */
const Foo operator +(const Foo& operand1, const Foo& operand2);

int main(void)
{
	Foo spam(1, 3);
	Foo bar(2, 7);
	Foo bang(3, 10);

	Foo eggs = spam + bar;
	eggs.output();

	cout << "Are bang and eggs the same?: " << (bang == eggs) << endl;

	return 0;
}

const Foo operator +(const Foo& operand1, const Foo& operand2)
{
	int sum_x = operand1.get_x() + operand2.get_x();
	int sum_y = operand1.get_y() + operand2.get_y();

	return Foo(sum_x, sum_y);
}
bool operator ==(const Foo& operand1, const Foo& operand2)
{
	return (operand1.get_x() == operand2.get_x()) &&
		(operand1.get_y() == operand2.get_y());
}

