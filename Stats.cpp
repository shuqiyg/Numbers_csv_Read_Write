/* W06 DIY
   Name: Shuqi Yang
   Std ID: 132162207
   Email: syang136@myseneca.ca
   Date: 03-02-2021
   -------------------------------------------------------
   I have done all the coding by myself and only copied the
   code that my professor provided to complete my workshops
   and assignments.
 */
#include "Stats.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits.h>
#include "cstring.h"
using namespace std;

namespace sdds {
	
	Stats::Stats(unsigned columnWidth, unsigned noOfColumns, unsigned precision){
		setEmpty();
		s_columnWidth = columnWidth;
		s_noOfColumns = noOfColumns;
		s_precision = precision;
	}
	Stats::Stats(const char* filename,
		unsigned columnWidth,
		unsigned noOfColumns,
		unsigned precision) {
		setEmpty();
		s_columnWidth = columnWidth;
		s_noOfColumns = noOfColumns;
		s_precision = precision;
		if (filename != nullptr) {
			setFilename(filename);
			setnumOfNum();
			loadNumbers();
		}
	}
	Stats::Stats(const Stats& st) {
		s_columnWidth = st.s_columnWidth;
		s_noOfColumns = st.s_noOfColumns;
		s_precision = st.s_precision;
		setEmpty();
		if (st.fname!= nullptr) {		
			setFilename(st.fname, true);
			st.saveAs(fname);
			setnumOfNum();
			loadNumbers();
		}
	}//copy constructor
	Stats::~Stats() {
		delete[] fname;
		fname = nullptr;
		delete[] numbers;
		numbers = nullptr;
	}
	void Stats::saveAs(const char* filename)const {
		ofstream of_obj(filename);
		for (unsigned i = 0; i < numOfNumbers; i++) {
			of_obj << numbers[i];
			if (i < numOfNumbers -1 ) {
				of_obj << ',';
			}
		}
	}
	Stats& Stats::operator=(const Stats& st) {
		if (st.fname != nullptr && this->fname != nullptr && fname != st.fname) {
			delete[] numbers;
			numbers = nullptr;
			s_columnWidth = st.s_columnWidth;
			s_noOfColumns = st.s_noOfColumns;
			s_precision = st.s_precision;		
			st.saveAs(this->fname);
			setnumOfNum();
			loadNumbers();
		}
		return *this;  
	}//copy assignment
	double& Stats::operator[](unsigned idx) {
		double* val = &dummy;
		if (fname!= nullptr) {
			val = &numbers[idx % numOfNumbers];
		}
		return *val;

		/* --- This version is not so clean and it's cumbersome ----
		if (fname != nullptr) {
			if (idx > numOfNumbers - 1) {
				idx = idx % numOfNumbers;
			}
			return numbers[idx];
		}
		//else {
			//return 0.0;
		*/		
	}// returns the reference of the number 
	double Stats::operator[](unsigned idx)const {
		if (fname != nullptr) {
			if (idx > numOfNumbers - 1) {
				idx = idx % numOfNumbers;
			}
			return numbers[idx];
		}
		else {
			return 0.0;
		}
	}// returns the value of number
	void Stats::setEmpty() {
		delete[] fname;
		fname = nullptr;
		delete[] numbers;
		numbers = nullptr;
	}
	void Stats::setnumOfNum() {
		ifstream if_obj(fname);
		unsigned file_num;
		char comma;
		while (if_obj) {
			if_obj >> file_num >> comma;
			numOfNumbers++;
		}
		if (numOfNumbers == 0) {
			delete[] fname;
			fname = nullptr;
		}	
	}
	void Stats::loadNumbers() {
		if (fname != nullptr) {
			delete[] numbers;
			numbers = new double[numOfNumbers];
			ifstream if_obj(fname);
			unsigned valid_read = 0;
			char comma;
			for (unsigned i = 0; i < numOfNumbers && if_obj; i++) {
				if_obj >> numbers[i] >> comma;
				valid_read++;
			}
			numOfNumbers = valid_read;
		}
	}
	void Stats::setFilename(const char* filename, bool isCopy) {
		if (isCopy) {
			char* temp = new char[strLen(filename) + 3];
			strCpy(temp, "C_");
			strCat(temp, filename);
			delete fname;
			fname = new char[strLen(filename) + 3];
			strCpy(fname, temp);
			delete[] temp;
		}
		else {
			delete[] fname;
			fname = new char[strLen(filename) + 1];
			strCpy(fname, filename);
		}
	}
	Stats::operator bool()const {
		return fname != nullptr;
	}
	unsigned Stats::getColumnWidth() const{
		return s_columnWidth;
	}
	unsigned Stats::getNoOfColumns() const{
		return s_noOfColumns;
	}
	unsigned Stats::getPrecision() const{
		return s_precision;
	}
	void Stats::sort(bool ascending) {
		int i, j;
		double temp;
		if (ascending) {	
			for (i = numOfNumbers - 1; i > 0; i--) {
				for (j = 0; j < i; j++) {
					if (numbers[j] > numbers[j + 1]) {
						temp = numbers[j];
						numbers[j] = numbers[j + 1];
						numbers[j + 1] = temp;
					}
				}
			}
		}else {
			for (i = numOfNumbers - 1; i > 0; i--) {
				for (j = 0; j < i; j++) {
					if (numbers[j] < numbers[j + 1]) {
						temp = numbers[j];
						numbers[j] = numbers[j + 1];
						numbers[j + 1] = temp;
					}
				}
			}
		}
	}
	unsigned Stats::size()const {
		return numOfNumbers;
	}
	const char* Stats::name()const {
		return fname;
	}
	unsigned Stats::occurrence(double min, double max, std::ostream& ostr)const {
		unsigned occur = 0;
		ostr.setf(ios::fixed);
		ostr.precision(getPrecision());
		for (unsigned i = 0; i < size(); i++) {
			ostr.width(getColumnWidth());
			if (numbers[i] >= min && numbers[i] <= max) {
				occur++;
				if ( (occur - 1) % (getNoOfColumns()) == 0 ) {
					ostr << endl;
				}
				ostr << numbers[i];			
			}		
		}	
		if (occur != 0) {
			ostr.width(0);
			ostr << endl << "Total of " << occur << " numbers are between " << min << " and " << max << endl;
		}	
		ostr.unsetf(ios::fixed);
		ostr.precision(2);
		return occur;
	}
	std::istream& Stats::getFile(std::istream& istr) {
		string fname;
		istr >> fname;
		istr.ignore(INT_MAX, '\n');
		setFilename(fname.c_str());
		setnumOfNum();
		loadNumbers();
		return istr;
	}
	std::ostream& operator<<(std::ostream& ostr, const Stats& stats) {
		unsigned occur = 0;
		if (stats.name() != nullptr) {
			ostr  << stats.name() << endl;
			for (int i = 0; i < strLen(stats.name()); i++) {
				ostr << '=';
			}
			ostr << endl;
			ostr.setf(ios::fixed);
			ostr.precision(stats.getPrecision());
			for (unsigned i = 0; i < stats.size(); i++) {
				ostr.width(stats.getColumnWidth());
				if (i % (stats.getNoOfColumns()) == 0) {
					ostr << endl;
				}
				ostr << stats[i];
				occur++;
			}
			ostr << endl << "Total of " << occur << " listed!" << endl;
		}
		return ostr;
	}
	std::istream& operator>>(std::istream& istr, Stats& stats) {
		return stats.getFile(istr);
	}
};
