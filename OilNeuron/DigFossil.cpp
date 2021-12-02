#include "DigFossil.h"

void DigFossil::add_element(int** element)
{
	fossil_elements.push_back(element);
}
vector<int**> DigFossil::get_elements()
{
	return fossil_elements;
}

int DigFossil::get_elements_count()
{
	return fossil_elements.size();
}