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
#ifndef SDDS_STATS_H_
#define SDDS_STATS_H_
#include <iostream>
namespace sdds {
   class Stats {   
	   char* fname{ nullptr };
	   double* numbers{ nullptr };
	   double dummy = 0.0;
	   unsigned numOfNumbers = 0;
	   unsigned numOfRows;
	   unsigned s_columnWidth;
	   unsigned s_noOfColumns;
	   unsigned s_precision;
	   void setEmpty(); 
	   void setFilename(const char* filename, bool isCopy = false);
	   void setnumOfNum();
	   void saveAs(const char*)const;
	   void loadNumbers();
   public:
	   unsigned getColumnWidth()const;
	   unsigned getNoOfColumns()const;
	   unsigned getPrecision()const;
	   std::istream& getFile(std::istream& istr);
	   Stats(unsigned columnWidth = 15, unsigned noOfColumns = 4, unsigned precision = 2);
	   Stats(const char* filename,
		   unsigned columnWidth = 15,
		   unsigned noOfColumns = 4,
		   unsigned precision = 2);
	   Stats(const Stats&); //copy constructor
	   ~Stats();
	   Stats& operator=(const Stats&); //copy assignment
	   double& operator[](unsigned idx); // returns the reference of the number 
	   double operator[](unsigned idx)const; // returns the value of number
	   operator bool()const;
	   void sort(bool ascending);
	   unsigned size()const;
	   const char* name()const;
	   unsigned occurrence(double min, double max, std::ostream& ostr = std::cout)const;
  };
   std::ostream& operator<<(std::ostream& ostr, const Stats& stats);
   std::istream& operator>>(std::istream& istr, Stats& stats);
}

#endif