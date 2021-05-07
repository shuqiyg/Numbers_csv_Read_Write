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
#include "cstring.h"

namespace sdds {
	void strCpy(char* des, const char* src) {
		int index = 0;
		while (src[index] != '\0') {
			des[index] = src[index];
			index++;
		}
		des[index] = '\0';
	}

	int strLen(const char* s) {
		int i, count = 0;
		for (i = 0; s[i] != '\0'; i++) {
			count++;
		}
		return count;
	}

	void strCat(char* des, const char* src) {
		int len_src = strLen(src);
		int len_des = strLen(des);
		int i;
		for (i = 0; i <= len_src; i++) {
			des[len_des] = src[i];
			if (src[i] == '\0') break;
			len_des++;
		}
	}
}