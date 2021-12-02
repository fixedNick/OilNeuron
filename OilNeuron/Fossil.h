#ifndef _FOSSIL_H
#define _FOSSIL_H

#include "Neuron.h"
#include "DigFossil.h"
#include <vector>
#include <string>

using namespace std;

// Класс любого ископаемого
class Fossil
{
	vector<Neuron> neurons;
public:
	string name;
	Fossil();
	Fossil(string _name);

	bool is_this_fossil(int** found_elements);
	void add_neuron(Neuron n);
	bool is_digged_fossil_is_equal_this_fossil(DigFossil digged_fossil);
};

#endif