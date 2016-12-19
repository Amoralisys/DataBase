#ifndef CBD
#define CBD
#include <memory>
#include <iostream>
#include <fstream>
#include <string>

enum sortDir{ ASC, DESC };

class CDB{
public:
	CDB();
	friend std::istream& operator>>(std::istream&, CDB&);//checked
	friend std::ifstream& operator>>(std::ifstream&, CDB&);//checked
	friend std::ostream& operator<<(std::ostream&, const CDB&);//checked
	friend std::ofstream& operator<<(std::ofstream&, const CDB&);//checked
	void save(std::ofstream&) const;//checked
	void doModifications(const std::string);
	CDB select(const std::string) const;//will appear after sort
	void sortBy(std::string, sortDir);//started writing
	void insert(std::string);//checked
private:
	class CDBImpl;
	std::shared_ptr<CDBImpl> ptr;
	void update(std::string);
	void erase(std::string);
};

void SUBD();
#endif