#ifndef CBD
#define CBD
#include <memory>
#include <iostream>
#include <fstream>
#include <string>

class CDB{
public:
	CDB();
	friend std::istream& operator>>(std::istream&, CDB&);//checked
	friend std::ifstream& operator>>(std::ifstream&, CDB&);//checked
	friend std::ostream& operator<<(std::ostream&, const CDB&);//checked
	friend std::ofstream& operator<<(std::ofstream&, const CDB&);//checked
	void save(std::ofstream&) const;//checked
	void insert(std::string);//checked
private:
	class CDBImpl;
	std::shared_ptr<CDBImpl> ptr;
};

void SUBD();
#endif
