#include<iostream>
using namespace std;

class Human
{
protected:
	std::string last_name;
	std::string first_name;
	unsigned int age;
public:
	const std::string get_last_name()const
	{
		return last_name;
	}
	const std::string get_first_name()const
	{
		return first_name;
	}
	unsigned int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(unsigned int age)
	{
		this->age = age;
	}
	Human(const std::string& last_name,const std::string& first_name, unsigned int age)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}
	virtual void print()const
	{
		cout << last_name << " " << first_name << " " << age << " " << "���" << endl;
	}
};

class Employee :public Human
{
	std::string position;

public:
	const std::string& get_position()const
	{
		return position;
	}
	void set_position(const std::string& position)
	{
		this->position = position;
	}
	virtual double get_salary()const = 0;

	Employee
	(
		const std::string& last_name, const std::string& first_name, unsigned int age,
		const std::string& position
	) :Human(last_name, first_name, age)
	{
		set_position(position);
		cout << "EConstructor:\t" << this << endl;
	}
	~Employee()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	void print()const
	{
		Human::print();
		cout << position << endl;
	}
};

class ParmamentEmployee : public Employee
{
	double salary;
public:
	double get_salary()const
	{
		return salary;
	}
	void set_salary(double salary)
	{
		this->salary = salary;
	}
	
	ParmamentEmployee
	(
		const std::string& last_name, const std::string& first_name, unsigned int age,
		const std::string& position, double salary
	): Employee(last_name, first_name, age, position)
	{
		set_salary(salary);
		cout << "PConstructor:\t" << this << endl;
	}
	~ParmamentEmployee()
	{
		cout << "PDeconstructor:\t" << this << endl;
	}
	void print()const
	{
		Employee::print();
		cout << salary << endl;
	}
};

class HourlyEmployee : public Employee
{
	double rate;
	int hours;

public:
	double get_rate()const
	{
		return rate;
	}
	int get_hours()const
	{
		return hours;
	}
	double get_salary()const
	{
		return rate * hours;
	}
	void set_rate(double rate)
	{
		this->rate = rate;
	}
	void set_hours(int hours)
	{
		this->hours = hours;
	}
	HourlyEmployee
	(
		const std::string& last_name, const std::string& first_name, unsigned int age,
		const std::string& position,
		double rate, int hours
	) :Employee(last_name, first_name, age, position)
	{
		set_rate(rate);
		set_hours(hours);
		cout << "HConstructor:\t" << this << endl;
	}
	~HourlyEmployee()
	{
		cout << "HDeconstructor:\t" << this << endl;
	}
	void print()const
	{
		Employee::print();
		cout << "����������: " << hours << " �����" << "; " << "��������: " << get_salary() << endl;
	}
};


void main()
{
	setlocale(LC_ALL, "");

	//Generalisation:
	Employee* department[] =
	{
		new ParmamentEmployee("�������", "�������", 65, "��������� ������", 160000),
		new ParmamentEmployee("����������", "��������", 50, "������� �������", 40000),
		new ParmamentEmployee("�����������", "��������", 42, "�������-��������", 23248),
		new ParmamentEmployee("���������������", "�����", 30, "���������� IT", 12000),
		new HourlyEmployee("����������", "�������", 22, "������� 3 ���.", 120, 168),
		new HourlyEmployee("��������", "�����", 25, "������� 2 ���.", 158, 170),
		new HourlyEmployee("������������", "������", 38, "������� 1 ���.", 200, 162),
		new HourlyEmployee("��������", "����", 46, "�������-����������", 180, 230),
	};
	
	//Specialisation:
	double total_salary = 0;
	for (int i = 0; i < sizeof(department) / sizeof(Employee*); i++)
	{
		cout << "\n----------------------------------------\n";
		department[i]->print();
		total_salary += department[i]->get_salary();
	}
	cout << "\n----------------------------------------\n";
	cout << "�������� ����� ������: " << total_salary;
	cout << "\n----------------------------------------\n";
}