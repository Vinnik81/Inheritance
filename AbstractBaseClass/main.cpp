#include<iostream>
#include<math.h>
using namespace std;

class Figure
{
protected:
	unsigned int a_x;
	unsigned int b_y;
	unsigned int line_width;

public:
	void set_a_x(unsigned int a_x)
	{
		this->a_x = a_x;
	}
	void set_b_y(unsigned int b_y)
	{
		this->b_y = b_y;
	}
	void set_line_widdth(unsigned int line_width)
	{
		this->line_width = line_width;
	}

	Figure(unsigned int a_x, unsigned int b_x, unsigned int line_width)
	{
		set_a_x(a_x);
		set_b_y(b_x);
		set_line_widdth(line_width);
		cout << "FConstructor:\t" << this << endl;
	}
	virtual ~Figure()
	{
		cout << "FDestructor:\t" << this << endl;
	}

	virtual double get_area()const = 0;
	virtual double get_perimeter()const = 0;
	virtual void draw()const = 0;
	virtual void print()const
	{
		cout << "Площадь:\t" << get_area() << endl;
		cout << "Периметр:\t" << get_perimeter() << endl;
		draw();
	}
};

class Square :public Figure
{
	double side;
public:
	double get_side()const
	{
		return side;
	}
	void set_side(double side)
	{
		this->side = side;
	}

	Square
	(
		unsigned int a_x, unsigned int b_y, unsigned int line_width,
		double side
	) :Figure(a_x, b_y, line_width)
	{
		set_side(side);
		cout << "SConstructor:\t" << this << endl;
	}
	~Square()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	double get_area()const
	{
		return side * side;
	}
	double get_perimeter()const
	{
		return side * 4;
	}
	void get_draw()const
	{
		for (int i = 0; i < side; i++)
		{
			for (int i = 0; i < side; i++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}
	void print()const
	{
		Figure::print();
		//cout << typeid(*this).name() << endl;
		cout << "Длинна стороны: " << side << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	
}