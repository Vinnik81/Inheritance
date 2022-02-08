#include<iostream>
#include<fstream>
using namespace std;

//#define WRITE_TO_FILE

void main()
{
	setlocale(LC_ALL, "");
#ifdef WRITE_TO_FILE
	cout << "Hello World!" << endl;

	ofstream fout;
	fout.open("File.txt", std::ios_base::app);
	//app - Append(ix)
	fout << "Привет мир!" << endl;
	fout.close();

	system("notepad File.txt");
#endif // WRITE_TO_FILE

	ifstream fin("File.txt");
	if (fin.is_open())
	{
		// read file
		const unsigned int SIZE = 256;
	    char buffer[SIZE]{};
		while (!fin.eof())
		{
			//fin >> buffer;
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}
		fin.close();
	}
	else
	{
		cerr << "Error: file not found" << endl;
	}
}