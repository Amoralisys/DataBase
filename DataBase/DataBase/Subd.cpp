#include "CBD.h"
#define cout std::cout
#define cin std::cin

void SUBD(){
	cout << "Print M for manual input or print F for input from file" << '\n';
	char c;
	cin >> c;
	if (c == 'M'){
		CDB test;
		cin >> test;
		while (1){
			cout << '\n' << "Print C for printing table in console, F for printing table in file, I for insert query, S for save table on your computer or E for exit" << '\n';
			cin >> c;
			std::string s;
			if (c == 'C')
				cout << test;
			if (c == 'F')
			{
				cout << '\n' << "Print filename where you want to see table" << '\n';
				std::getchar();  
				std::getline(cin, s); 
				std::ofstream out(s); 
				out << test;
			}
			if (c == 'I')
			{
				cout << '\n' << "Insert query, format declared in documentation" << '\n';
				std::getchar();
				std::getline(cin, s);
				test.insert(s);
			}
			if (c == 'S')
			{
				cout << '\n' << "Print filename where you want to save table" << '\n';
				std::getchar();  
				std::getline(cin, s); 
				std::ofstream out(s); 
				test.save(out); 
			}
			if (c == 'E')
				break;
		}
	}
	else if (c == 'F'){
		CDB test;
		cout << '\n' << "Print filename" << '\n';
		std::string s;
		getchar();
		std::getline(cin, s);
		std::ifstream inp(s);
		inp >> test;
		while (1){
			cout << '\n' << "Print C for printing table in console, F for printing table in file, I for insert query, S for save table on your computer or E for exit" << '\n';
			cin >> c;
			std::string s;
			if (c == 'C')
				cout << '\n' << test;
			if (c == 'F')
			{
				cout << '\n' << "Print filename where you want to see table" << '\n';
				std::getchar();
				std::getline(cin, s);
				std::ofstream out(s);
				out << test;
			}
			if (c == 'I')
			{
				cout << '\n' << "Insert query, format declared in documentation" << '\n';
				std::getchar();
				std::getline(cin, s);
				test.insert(s);
			}
			if (c == 'S')
			{
				cout << '\n' << "Print filename where you want to save table" << '\n';
				std::getchar();
				std::getline(cin, s);
				std::ofstream out(s);
				test.save(out);
			}
			if (c == 'E')
				break;
		}

	}
	else {
		cout << '\n' << "Unexpected letter taken, program terminated" << '\n';
	}
	cout << '\n' << "See you later!" << '\n';
	system("PAUSE");
	return;
}