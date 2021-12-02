#ifndef NEURON_H
#define NEURON_H
#include <string>
#include <vector>
#include "files_data.h"

using namespace std;

class Neuron
{
public:
	static const int cols = 50, rows = 50;
	static const int weight_limit = 100000;
	string name;
	files_data fd;
	int weight[cols][rows];
	int input_matrix[cols][rows];
	void get_axon();
	int get_weight_sum();
	bool check_result();
	bool load_weight_from_file();
	void recognize_letter();
	bool recognize(int** matrix);
	void study(bool real_result, int& restudy);
	void setup_input(int** p);
	Neuron();
	Neuron(string _name);
	Neuron(files_data _fd);
	int axon[cols][rows];
	int weight_sum;
	void add_weight();
	void decrease_weight();
};

#endif