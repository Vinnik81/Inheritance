#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include<iostream>
#include<Windows.h>
#include<math.h>
using namespace std;

//enum (enumeration - перечисление) - это набор именованных констант типа int.
namespace Geometry
{
	enum Color
	{
		red		= 0x000000FF,
		green	= 0x0000FF00,
		blue	= 0x00FF0000,
		yellow	= 0x0000FFFF,

		console_red = 0xCC,
		console_green = 0xAA,
		console_blue = 0x99,
		console_yellow = 0xEE,
		console_default = 0x07,


	};

	class Shape
	{
	protected:
		Color color;
		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_width;
	public:
		Color get_color()const
		{
			return color;
		}
		unsigned int get_start_x()const
		{
			return start_x;
		}
		unsigned int get_start_y()const
		{
			return start_y;
		}
		unsigned int get_line_width()const
		{
			return line_width;
		}
		void set_start_x(unsigned int start_x)
		{
			if (start_x > 800)start_x = 800;
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			if (start_y > 800)start_y = 800;
			this->start_y = start_y;
		}
		void set_line_width(unsigned int line_width)
		{
			if (line_width > 50)line_width = 50;
			this->line_width = line_width;
		}


		Shape(unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color) : color(color) 
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		};
		virtual ~Shape() {};
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;

		void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	class Square : public Shape
	{
	protected:
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side <= 0)side = 10;
			this->side = side;
		}
		Square
		(
			double side, 
			unsigned int start_x, unsigned int start_y, unsigned int line_width, 
			Color color
		) : Shape(start_x, start_y, line_width, color)
		{
			set_side(side);
		}
		~Square() {};

		double get_area()const
		{
			return side * side;
		}
		double get_perimeter()const
		{
			return side * 4;
		}
		void draw()const
		{
			/*HANDLE hCosole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hCosole, get_color());
			for (int i = 0; i < side; i++)
			{
				for (int i = 0; i < side; i++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hCosole, Color::console_default);*/
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Rectangle(hdc, start_x, start_y, start_x + side, start_y + side);

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Длинна стороны: " << side << endl;
			Shape::info();
		}
	};

	class Rectangle : public Shape
	{
	protected:
		double width;
		double length;
	public:
		double get_width()const
		{
			return width;
		}
		double get_length()const
		{
			return length;
		}
		void set_width(double width)
		{
			if (width <= 0)width = 20;
			this->width = width;
		}
		void set_length(double length)
		{
			if (length <= 0)length = 10;
			this->length = length;
		}

		Rectangle
		(
			double width, double length,
			unsigned int start_x, unsigned int start_y, unsigned int line_width,
			Color color) : Shape(start_x, start_y, line_width, color)
		{
			set_width(width);
			set_length(length);
		}
		~Rectangle() {};

		double get_area()const
		{
			return width * length;
		}
		double get_perimeter()const
		{
			return (width + length) * 2;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			//HWND hwnd = GetDesktopWindow();
			//HWND hwnd = FindWindow(NULL, L"Calculator");
			//HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + length);

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина прямоугольника: " << width << endl;
			cout << "Длинна прямоугольника: " << length << endl;
			Shape::info();
		}
	};

	class Circle : public Shape
	{
		double radius;
	public:
		double get_radius()const
		{
			return radius;
		}
		double get_diameter()const
		{
			return radius * 2;
		}
		void set_radius(double radius)
		{
			if (radius <= 0 || radius >= 500)radius = 500;
			this->radius = radius;
		}
		Circle
		(
			double radius,
			unsigned int start_x, unsigned int start_y, unsigned int line_width,
			Color color
		) : Shape(start_x, start_y, line_width, color)
		{
			set_radius(radius);
		}
		~Circle() {};
		double get_area()const
		{
			return M_PI * pow(radius, 2);
		}
		double get_perimeter()const
		{
			return 2 * M_PI * radius;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус круга: " << get_radius() << endl;
			cout << "Диаметр круга: " << get_diameter() << endl;
			Shape::info();
		}
	};

	class Triangle : public Shape
	{
	public:
		Triangle
		(
			unsigned int start_x, unsigned int start_y, unsigned int line_width,
			Color color
		) : Shape(start_x, start_y, line_width, color) {};
		~Triangle() {};

		virtual double get_height()const = 0;
	};

	class EquilateralTriangle : public Triangle
	{
		double side;
	public:
		EquilateralTriangle
		(
			double side,
			unsigned int start_x, unsigned int start_y, unsigned int line_width,
			Color color
		) : Triangle(start_x, start_y, line_width, color)
		{
			set_side(side);
		}
		~EquilateralTriangle() {};
		void set_side(double side)
		{
			if (side < 20)side = 20;
			if (side > 500)side = 500;
			this->side = side;
		}
		double get_side()const
		{
			return side;
		}
		double get_height()const
		{
			//return sqrt(pow(side, 2) - pow(side / 2, 2));
			return side * cos(30 * M_PI / 180);
		}
		double get_area()const
		{
			return get_height() * side / 4;
		}
		double get_perimeter()const
		{
			return side * 3;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			POINT points[] =
			{
				{start_x, start_y + side},
				{start_x + side, start_y + side},
				{start_x + side / 2, start_y + side - get_height()}
			};
			Polygon(hdc, points, sizeof(points) / sizeof(POINT));

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Длинна стороны: " << get_side() << endl;
			cout << "Высота: " << get_height() << endl;
			Shape::info();
		}
	};

	class IsosclesTriangle : public Triangle
	{
		double base;
		double base_angle;
	public:
		IsosclesTriangle
		(
			double base, double base_angle,
			unsigned int start_x, unsigned int start_y, unsigned int line_width,
			Color color
		) : Triangle(start_x, start_y, line_width, color) 
		{
			set_base(base);
			set_angle(base_angle);
		}
		~IsosclesTriangle() {};
		void set_base(double base)
		{
			if (base < 20)base = 20;
			if (base > 200)base = 200;
			this->base = base;
		}
		void set_angle(double angle)
		{
			if (angle < 10)angle = 10;
			if (angle > 89)angle = 89;
			this->base_angle = angle;
		}
		double get_base()const
		{
			return base;
		}
		double get_base_angle()const
		{
			return base_angle;
		}
		double get_side()const
		{
			return get_height() / sin(base_angle * M_PI / 180);
		}
		double get_height()const
		{
			return base / 2 * tan(base_angle * M_PI / 180);
		}
		double get_area()const
		{
			return base / 2 * get_height();
		}
		double get_perimeter()const
		{
			return get_side() * 2 + base;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT points[] =
			{
			{start_x, start_y + get_side()},
			{start_x + base, start_y + get_side()},
			{start_x + base / 2 , start_y + get_side() - get_height()},
			};
			Polygon(hdc, points, sizeof(points) / sizeof(POINT));

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Основание треугольника: " << get_base() << endl;
			cout << "Сторона треугольника : " << get_side() << endl;
			cout << "Угол между основанием и стороной: " << get_base_angle() << endl;
			cout << "Высота треугольника : " << get_height() << endl;
			Shape::info();
		}
	};

	class Parallelogram : public Rectangle
	{
		double angle;
	public:
		double get_angle()const
		{
			return angle;
		}
		void set_angle(double angle)
		{
			if (angle < 10)angle = 10;
			if (angle > 89)angle = 89;
			this->angle = angle;
		}

		Parallelogram
		(
			double angle,
			double width, double length,
			unsigned int start_x, unsigned int start_y, unsigned int line_width,
			Color color
		) : Rectangle(width, length, start_x, start_y, line_width, color)
		{
			set_angle(angle);
		}
		~Parallelogram() {};

		double get_height()const
		{
			return length * sin(angle * M_PI / 180);
		}
		double area()const
		{
			return width * get_height();
		}
		double get_perimeter()const
		{
		    return (width + length) * 2;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			
			POINT points[] =
			{
			{start_x, start_y},
			{start_x + width, start_y},
			{start_x + width * 1.5 , start_y + length - get_height()},
			{start_x + width / 2, start_y + length - get_height()},
			};
			Polygon(hdc, points, sizeof(points) / sizeof(POINT));

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина прямоугольника: " << width << endl;
			cout << "Длинна прямоугольника: " << length << endl;
			cout << "Угол между шириной и длинной: " << angle << endl;
			Shape::info();
		}
	};

	class Rhombus : public Square
	{
		double angle;
	public:
		double get_angle()const
		{
			return angle;
		}
		void set_angle(double angle)
		{
			if (angle < 10)angle = 10;
			if (angle > 90)angle = 90;
			this->angle = angle;
		}

		Rhombus(double angle, double side, unsigned int start_x, unsigned int start_y, unsigned int line_width,
			Color color) : Square(side, start_x, start_y, line_width, color)
		{
			set_angle(angle);
		}
		~Rhombus() {};

		double get_diaB()const
		{
			return 2 * side * cos((angle / 2) * M_PI / 180);
		}
		double get_diaS()const
		{
			return 2 * side * sin((angle / 2) * M_PI / 180);
		}
		double get_area()const
		{
			return 0.5 * get_diaB() * get_diaS();
		}
		double get_perimeter()const
		{
			return 4 * side;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT points[] =
			{
			{start_x + get_diaS() / 2, start_y},
			{start_x + get_diaS(), start_y + get_diaB() / 2},
			{start_x + get_diaS() / 2 , start_y + get_diaB()},
			{start_x, start_y + get_diaB() / 2},
			};
			Polygon(hdc, points, sizeof(points) / sizeof(POINT));

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона ромба: " << side << endl;
			cout << "Угол между сторонами: " << angle << endl;
			cout << "Большая диагональ: " << get_diaB() << endl;
			cout << "Малая диагональ: " << get_diaS() << endl;
			Shape::info();
		}

	};

	class Trapezoid : public Triangle
	{
		double base_a;
		double base_b;
		double side_c;
		double side_d;
		double angle;
	public:
		double get_base_a()const
		{
			return base_a;
		}
		double get_base_b()const
		{
			return base_b;
		}
		double get_side_c()const
		{
			return side_c;
		}
		double get_side_d()const
		{
			return side_d;
		}
		double get_angle()const
		{
			return angle;
		}
		void set_base_a(double base_a)
		{
			if (base_a <= 0)base_a = 10;
			this->base_a = base_a;
		}
		void set_base_b(double base_b)
		{
			if (base_b <= 0)base_b = 20;
			this->base_b = base_b;
		}
		void set_side_c(double side_c)
		{
			if (side_c <= 0)side_c = 10;
			this->side_c = side_c;
		}
		void set_side_d(double side_d)
		{
			if (side_d <= 0)side_d = 10;
			this->side_d = side_d;
		}
		void set_angle(double angle)
		{
			if (angle < 10)angle = 10;
			if (angle > 90)angle = 90;
			this->angle = angle;
		}

		Trapezoid
		(
			double base_a, double base_b, double side_c, double side_d, double angle,
			unsigned int start_x, unsigned int start_y, unsigned int line_width,
			Color color
		) : Triangle(start_x, start_y, line_width, color)
		{
			set_base_a(base_a);
			set_base_b(base_b);
			set_side_c(side_c);
			set_side_d(side_d);
			set_angle(angle);
		}
		~Trapezoid() {};

		double get_height()const
		{
			return side_c * sin(angle * M_PI / 180);
		}
		double get_area()const
		{
			return (base_a + base_b) / 2 * get_height();
		}
		double get_perimeter()const
		{
			return base_a + base_b + side_c + side_d;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT points[] =
			{
				{start_x + base_a / 2, start_y},
                {start_x + base_a * 1.5, start_y},
				{start_x + base_b, start_y + side_d - get_height()},
				{start_x, start_y + side_c - get_height()},
				};
			Polygon(hdc, points, sizeof(points) / sizeof(POINT));

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Основание a трапеции: " << base_a << endl;
			cout << "Основание b трапеции: " << base_b << endl;
			cout << "Сторона трапеции c : " << side_c << endl;
			cout << "Сторона трапеции d : " << side_d << endl;
			cout << "Угол между основанием и стороной: " << angle << endl;
			cout << "Высота трапеции : " << get_height() << endl;
			Shape::info();
		}
	};

	class Ellipse : public Shape
	{
		double semiaxis_a;
		double semiaxis_b;
	public:
		double get_semiaxis_a()const
		{
			return semiaxis_a;
		}
		double get_semiaxis_b()const
		{
			return semiaxis_b;
		}
		void set_semiaxis_a(double semiaxis_a)
		{
			if (semiaxis_a <= 0 || semiaxis_a >= 500)semiaxis_a = 500;
			this->semiaxis_a = semiaxis_a;
		}
		void set_semiaxis_b(double semiaxis_b)
		{
			if (semiaxis_b <= 0 || semiaxis_b >= 500)semiaxis_b = 400;
			this->semiaxis_b = semiaxis_b;
		}

		Ellipse
		(
			double semiaxis_a, double semiaxis_b,
			unsigned int start_x, unsigned int start_y, unsigned int line_width,
			Color color
		) : Shape(start_x, start_y, line_width, color)
		{
			set_semiaxis_a(semiaxis_a);
			set_semiaxis_b(semiaxis_b);
		}
		~Ellipse() {};

		double get_area()const
		{
			return M_PI * semiaxis_a * semiaxis_b;
		}
		double get_perimeter()const
		{
			return 4 * M_PI * semiaxis_a * semiaxis_b + pow((semiaxis_a - semiaxis_b), 2) / semiaxis_a + semiaxis_b;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Ellipse(hdc, start_x + semiaxis_a, start_y, start_x + semiaxis_a * 2, start_y + semiaxis_b);

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Большая полуось элипса: " << semiaxis_a << endl;
			cout << "Малая полуось элипса: " << semiaxis_b << endl;
			Shape::info();
		}
	};

}




void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::console_blue);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD console_rect{ 120,32 };
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &console_rect);

	Geometry:: Square square(100, 220, 10, 5, Geometry::Color::red);
	square.info();

	Geometry:: Rectangle rect(130, 70, 350, 30, 5, Geometry:: Color::blue);
	rect.info();

	Geometry::Circle circle(60, 500, 20, 5, Geometry::Color::yellow);
	circle.info();

	Geometry::EquilateralTriangle eqt(125, 620, 10, 5, Geometry::Color::green);
	eqt.info();

	Geometry::IsosclesTriangle isct(60, 80, 770, 10, 3, Geometry::Color::blue);
	isct.info();

	Geometry::Parallelogram parm(20, 150, 70, 220, 150, 5, Geometry::Color::blue);
	parm.info();

	Geometry::Rhombus rhom(60, 100, 520, 150, 5, Geometry::Color::red);
	rhom.info();

	Geometry::Trapezoid trap(90, 210, 200, 200, 30, 720, 250, 5, Geometry::Color::green);
	trap.info();

	Geometry::Ellipse ell(150, 80, 800, 250, 5, Geometry::Color::yellow);
	ell.info();
}