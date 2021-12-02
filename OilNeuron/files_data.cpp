#include "files_data.h"
#include "Neuron.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

files_data::files_data()
{
	good_files_count = 0;
	bad_files_count = 0;
	good_files_directory = "";
	bad_files_directory = "";
}

files_data::files_data(const int& _good_files_count, const int& _bad_files_count, const string& _good_files_directory, const string& _bad_files_directory)
{
	good_files_count = _good_files_count;
	bad_files_count = _bad_files_count;
	good_files_directory = _good_files_directory;
	bad_files_directory = _bad_files_directory;
}

void files_data::get_matrixes_from_files()
{
	for (int gc = 0; gc < good_files_count; gc++)
	{
		auto matrix = get_matrix_from_file(good_files_directory + "/" + to_string(gc) + ".txt");
		if (matrix == NULL) 
			continue;
		good_matrix.push_back(matrix);
	}

	for (int bc = 0; bc < bad_files_count; bc++)
	{
		auto matrix = get_matrix_from_file(bad_files_directory + "/" + to_string(bc) + ".txt");
		if (matrix == NULL)
			continue;
		bad_matrix.push_back(matrix);
	}
}

int** files_data::get_matrix_from_file(string filename)
{
	int** matrix = new int* [Neuron::cols];
	for (int c = 0; c < Neuron::cols; c++)
		matrix[c] = new int[Neuron::rows];

	ifstream reader(filename);
	if (reader.is_open() == false)
	{
		cout << "File " << filename << " doesn't exists";
		return NULL;
	}

	for (int c = 0; c < Neuron::cols; c++)
		for (int r = 0; r < Neuron::rows; r++)
			cin >> matrix[c][r];

	return matrix;
}