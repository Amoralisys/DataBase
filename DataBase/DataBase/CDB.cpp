#include "CBD.h"
#include <vector>
#include <list>
#include <iterator>
#include <set>

class CDB::CDBImpl{
public:
	std::list<std::vector<int>> intFields;
	std::list<std::vector<std::string>> strFields;
	std::set<int> freeObjects;
	std::vector<std::string> intLabels;//макс 11 символов
	std::vector<std::string> strLabels;
	std::vector<int> strFieldsWidth;
	std::list<std::vector<int>>::iterator inIntList(int pos);
	std::list<std::vector<std::string>>::iterator inStringList(int pos);
	int objAmount;
};

CDB::CDB(){
	ptr = std::make_shared<CDBImpl>();
}


std::list<std::vector<int>>::iterator CDB::CDBImpl::inIntList(int pos){
	std::list<std::vector<int>>::iterator it=this->intFields.begin();
	for (int i = 0; i < pos; ++i){
		it++;
	}
	return it;
}

std::list<std::vector<std::string>>::iterator CDB::CDBImpl::inStringList(int pos){
	std::list<std::vector<std::string>>::iterator it = this->strFields.begin();
	for (int i = 0; i < pos; ++i){
		it++;
	}
	return it;
}

std::istream& operator>>(std::istream& inp, CDB& dest){
	int length;
	inp >> length;
	dest.ptr->intLabels.resize(length);
	std::getchar();
	for (int i = 0; i < length; ++i){
		dest.ptr->intFields.emplace_back();
		std::getline(inp, dest.ptr->intLabels[i]);
	}
	inp >> length;
	dest.ptr->strLabels.resize(length);
	for (int i = 0; i < length; ++i){
		dest.ptr->strFields.emplace_back();
		int t;
		inp >> t;
		std::getchar();
		dest.ptr->strFieldsWidth.push_back(t);
		std::getline(inp, dest.ptr->strLabels[i]);
	}
	inp >> length;
	dest.ptr->objAmount = length;
	int intCount = dest.ptr->intFields.size();
	int strCount = dest.ptr->strFields.size();
	for (int i = 0; i < length; ++i){
		for (int j = 0; j < intCount; ++j){
			int t;
			inp >> t;
			std::getchar();
			(*dest.ptr->inIntList(j)).push_back(t);
		}
		for (int j = 0; j < strCount; ++j){
			std::string buf;
			std::getline(inp, buf);
			(*dest.ptr->inStringList(j)).push_back(buf);
		}
	}
	return inp;
}

std::ifstream& operator>>(std::ifstream& inp, CDB& dest){
	int length;
	inp >> length;
	dest.ptr->intLabels.resize(length);
	char c;
	inp.get(c);
	for (int i = 0; i < length; ++i){
		dest.ptr->intFields.emplace_back();
		std::getline(inp, dest.ptr->intLabels[i]);
	}
	inp >> length;
	dest.ptr->strLabels.resize(length);
	for (int i = 0; i < length; ++i){
		dest.ptr->strFields.emplace_back();
		int t;
		inp >> t;
		inp.get(c);
		dest.ptr->strFieldsWidth.push_back(t);
		std::getline(inp, dest.ptr->strLabels[i]);
	}
	inp >> length;
	dest.ptr->objAmount = length;
	int intCount = dest.ptr->intFields.size();
	int strCount = dest.ptr->strFields.size();
	for (int i = 0; i < length; ++i){
		for (int j = 0; j < intCount; ++j){
			int t;
			inp >> t;
			inp.get(c);
			(*dest.ptr->inIntList(j)).push_back(t);
		}
		for (int j = 0; j < strCount; ++j){
			std::string buf;
			std::getline(inp, buf);
			(*dest.ptr->inStringList(j)).push_back(buf);
		}
	}
	return inp;
}

std::ostream& operator<<(std::ostream& out, const CDB& src){
	int intCount = src.ptr->intFields.size();
	int strCount = src.ptr->strFields.size();
	for (int i = 0; i < intCount; ++i){
		int counter=0;
		while (counter <= 11 && counter < src.ptr->intLabels[i].length()){
			out << src.ptr->intLabels[i][counter];
			counter++;
		}
		while (counter <= 11){
			out << ' ';
			counter++;
		}
		out << '|';
	}
	for (int i = 0; i < strCount; ++i){
		int counter = 0;
		int amount = src.ptr->strFieldsWidth[i];
		while (counter < amount && src.ptr->strLabels[i][counter] != 0){
			out << src.ptr->strLabels[i][counter];
			counter++;
		}
		while (counter < amount){
			out << ' ';
			counter++;
		}
		out << '|';
	}
	out << '\n';
	int objAmount = src.ptr->objAmount;
	for (int i = 0; i < objAmount; ++i){
		if (src.ptr->freeObjects.find(i) == src.ptr->freeObjects.end()){
			for (int j = 0; j < intCount; ++j){
				int digitsCount = 0;
				if ((*src.ptr->inIntList(j))[i] < 0){
					digitsCount = 1;
				}
				int value = abs((*src.ptr->inIntList(j))[i]);
				while (value > 0){
					digitsCount++;
					value /= 10;
				}
				for (digitsCount; digitsCount < 12; ++digitsCount){
					out << ' ';
				}
				out << (*src.ptr->inIntList(j))[i] << '|';
			}
			for (int j = 0; j < strCount; ++j){
				int counter = 0;
				int amount = src.ptr->strFieldsWidth[j];
				while (counter < amount && (*src.ptr->inStringList(j))[i][counter] != 0){
					out << (*src.ptr->inStringList(j))[i][counter];
					counter++;
				}
				while (counter < amount){
					out << ' ';
					counter++;
				}
				out << '|';
			}
			out << '\n';
		}
	}
	return out;
}


std::ofstream& operator<<(std::ofstream& out, const CDB& src){
	int intCount = src.ptr->intFields.size();
	int strCount = src.ptr->strFields.size();
	for (int i = 0; i < intCount; ++i){
		int counter = 0;
		while (counter <= 11 && counter < src.ptr->intLabels[i].length()){
			out << src.ptr->intLabels[i][counter];
			counter++;
		}
		while (counter <= 11){
			out << ' ';
			counter++;
		}
		out << '|';
	}
	for (int i = 0; i < strCount; ++i){
		int counter = 0;
		int amount = src.ptr->strFieldsWidth[i];
		while (counter < amount && src.ptr->strLabels[i][counter] != 0){
			out << src.ptr->strLabels[i][counter];
			counter++;
		}
		while (counter < amount){
			out << ' ';
			counter++;
		}
		out << '|';
	}
	out << '\n';
	int objAmount = src.ptr->objAmount;
	for (int i = 0; i < objAmount; ++i){
		if (src.ptr->freeObjects.find(i) == src.ptr->freeObjects.end()){
			for (int j = 0; j < intCount; ++j){
				int digitsCount = 0;
				if ((*src.ptr->inIntList(j))[i] < 0){
					digitsCount = 1;
				}
				int value = abs((*src.ptr->inIntList(j))[i]);
				while (value > 0){
					digitsCount++;
					value /= 10;
				}
				for (digitsCount; digitsCount < 12; ++digitsCount){
					out << ' ';
				}
				out << (*src.ptr->inIntList(j))[i] << '|';
			}
			for (int j = 0; j < strCount; ++j){
				int counter = 0;
				int amount = src.ptr->strFieldsWidth[j];
				while (counter < amount && (*src.ptr->inStringList(j))[i][counter] != 0){
					out << (*src.ptr->inStringList(j))[i][counter];
					counter++;
				}
				while (counter < amount){
					out << ' ';
					counter++;
				}
				out << '|';
			}
			out << '\n';
		}
	}
	return out;
}

void CDB::save(std::ofstream& dest) const{
	int t = this->ptr->intFields.size();
	dest << t << '\n';
	for (int i = 0; i < t; ++i){
		dest << this->ptr->intLabels[i] << '\n';
	}
	int s = this->ptr->strFields.size();
	dest << s << '\n';
	for (int i = 0; i < s; ++i){
		dest << this->ptr->strFieldsWidth[i] << '\n';
		dest << this->ptr->strLabels[i] << '\n';
	}
	int size = this->ptr->objAmount;
	dest << size << '\n';
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < t; ++j){
			dest << (*this->ptr->inIntList(j))[i] << '\n';
		}
		for (int j = 0; j < s; ++j){
			dest << (*this->ptr->inStringList(j))[i] << '\n';
		}
	}
}



void CDB::insert(std::string command){
	int t = this->ptr->intFields.size();
	int s = this->ptr->strFields.size();
	int curPos = 0;
	for (int i = 0; i < t; ++i){
		int pos = command.find_first_of(' ', curPos);
		(*this->ptr->inIntList(i)).push_back(stoi(command.substr(curPos, pos - curPos )));
		curPos = pos + 1;
	}
	curPos++;
	for (int i = 0; i < s; ++i){
		int pos = command.find_first_of('\'', curPos);
		(*this->ptr->inStringList(i)).push_back(command.substr(curPos, pos - curPos));
		curPos = pos + 3;
	}
	this->ptr->objAmount++;
}
