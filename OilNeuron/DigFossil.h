#ifndef _DIG_ELEMENT_H
#define _DIG_ELEMENT_H
#include <vector>

using namespace std;

class DigFossil
{
	vector<int**> fossil_elements;
public:
	void add_element(int** element);
	vector<int**> get_elements();
	int get_elements_count();
};

#endif