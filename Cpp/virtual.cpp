#include <iostream>

using namespace std;

class Polygon
{
public:
	Polygon(int a, int b)
		:width(a), height(b)
	{
	}
	/* A pure virtual function */
	virtual int area() = 0;

	/* A virtual function */
	/*
	virtual int area()
	{
		return 0;
	}
	*/

protected:
	int width;
	int height;
};

class Rectangle : public Polygon
{
public:
	Rectangle(int a, int b)
		: Polygon(a, b)
	{
	}
	int area ()
	{
		return width * height;
	}
};

class Triangle : public Polygon
{
public:
	Triangle(int a, int b)
		: Polygon(a, b)
	{
	}
	int area ()
	{
		return (width * height / 2);
	}
};

int main (void)
{
	Rectangle rect(4, 5);
	Triangle trgl(4, 5);
	// Polygon poly(4, 5);

	Polygon *ppoly1 = &rect;
	Polygon *ppoly2 = &trgl;
	// Polygon *ppoly3 = &poly;

	cout << ppoly1->area() << '\n';
	cout << ppoly2->area() << '\n';
	// cout << ppoly3->area() << '\n';

	return 0;
}
