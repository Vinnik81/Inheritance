#include<iostream>
#include<math.h>
using namespace std;

class Figure
{
public:

	Figure()
	{
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
	(double side)
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
		return pow(side,2);
	}
	double get_perimeter()const
	{
		return side * 4;
	}
	void draw()const
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
		cout << typeid(*this).name() << endl;
		cout << "Длинна стороны: " << side << endl;
	}
};

class Rectangle : public Figure
{
	double side_a;
	double side_b;
public:
	double get_side_a()const
	{
		return side_a;
	}
	double get_side_b()const
	{
		return side_b;
	}
	void set_side_a(double side_a)
	{
		this->side_a = side_a;
	}
	void set_side_b(double side_b)
	{
		this->side_b = side_b;
	}

	Rectangle(double side_a, double side_b)
	{
		set_side_a(side_a);
		set_side_b(side_b);
		cout << "RConstructor:\t" << this << endl;
	}
	~Rectangle()
	{
		cout << "RDestructor:\t" << this << endl;
	}

	double get_area()const
	{
		return side_a * side_b;
	}
	double get_perimeter()const
	{
		return 2 * (side_a + side_b);
	}
	void draw()const
	{
		for (int i = 0; i < side_b; i++)
		{
			for (int i = 0; i < side_a; i++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}
	void print()const
	{
		Figure::print();
		cout << typeid(*this).name() << endl;
		cout << "Длинна стороны: " << side_a << endl;
		cout << "Длинна стороны: " << side_b << endl;
	}
};
class Circle : public Figure
{
	double radius;
	double PI = 3.1415926;
public:
	double get_radius()const
	{
		return radius;
	}
	void set_radius(double radius)
	{
		this->radius = radius;
	}

	Circle(double radius)
	{
		set_radius(radius);
		cout << "CConstructor:\t" << this << endl;
	}
	~Circle()
	{
		cout << "CDestructor:\t" << this << endl;
	}

	double get_area()const
	{
		return PI * pow(radius, 2);
	}
	double get_perimeter()const
	{
		return 2 * PI * radius;
	}
	void draw()const
	{
		cout << "Круг" << endl;
	}
	void print()const
	{
		Figure::print();
		cout << typeid(*this).name() << endl;
		cout << "Радиус круга: " << radius << endl;
	}
};

class Triangle : public Figure
{
	double height;
	double side;
public:
	double get_side()const
	{
		return side;
	}
	double get_height()const
	{
		return sqrt(3) / 2 * side;
	}
	void set_side(double side)
	{
		this->side = side;
	}

	Triangle(double side)
	{
		set_side(side);
		cout << "TConstructor:\t" << this << endl;
	}
	~Triangle()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	double get_area()const
	{
		return (get_height() / 2) * side;
	}
	double get_perimeter()const
	{
		return side * 3;
	}
	void draw()const
	{
		for (int i = 0; i < side; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}
	void print()const
	{
		Figure::print();
		cout << typeid(*this).name() << endl;
		cout << "Длинна треугольника: " << side << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	Square s(5);
	s.print();
	cout << "\n-----------------------------------------------------------\n";
	Rectangle r(8, 5);
	r.print();
	cout << "\n-----------------------------------------------------------\n";
	Circle c(5);
	c.print();
	cout << "\n-----------------------------------------------------------\n";
	Triangle t(8);
	t.print();
	cout << "\n-----------------------------------------------------------\n";
}