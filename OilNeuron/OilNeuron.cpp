#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "files_data.h"
#include "Neuron.h"

using namespace std;

vector<Neuron> Neurons;

void print_menu(int& operation)
{
	cout << "0. Exit" << endl;
	cout << "1. Study neuron" << endl;
	cout << "Your choice: ";
	cin >> operation;
}

void write(string text)
{
	cout << text;
}

void writeline(string text)
{
	write(text);
	cout << endl;
}

Neuron study(files_data fd)
{
	Neuron neuron = Neuron();
	int restudy = 1;
	int iterations = 0;
	while (restudy != 0) 
	{
		restudy = 0;
		for (int i = 0; i < fd.good_files_count + fd.bad_files_count; i++)
		{
			if (i < fd.bad_files_count)
			{
				neuron.setup_input(fd.bad_matrix[i]);
				neuron.study(false, restudy);
				continue;
			}
			neuron.setup_input(fd.good_matrix[i - fd.bad_matrix.size()]);
			neuron.study(true, restudy);
		}
		cout << "Lap: " << ++iterations << endl;
	}
	cout << "Study complete" << endl;
		
	string weight_filename;
	cout << "Enter filename to save neuron weight: ";
	cin >> weight_filename;

	ofstream writer(weight_filename);
	for (int c = 0; c < Neuron::cols; c++) {
		for (int r = 0; r < Neuron::rows; r++)
			writer << neuron.weight[c][r] << ' ';
		writer << endl;
	}
	writer.close();

	return neuron;
}

int main()
{
	while (true)
	{
		int operation = 0;
		print_menu(operation);

		if (operation == 0)
		{
			writeline("Exit");
			return 0;
		}
		else if (operation == 1)
		{
			string good_files_directory, bad_files_directory;
			int good_files_count, bad_files_count;

			write("Enter good files directory name:");
			cin >> good_files_directory;
			write("Enter good files count:");
			cin >> good_files_count;

			write("Enter bad files directory name:");
			cin >> bad_files_directory;
			write("Enter bad files count:");
			cin >> bad_files_count;

			string matrix_name;
			write("Enter matrix name: ");
			cin >> matrix_name;

			files_data fd(matrix_name, good_files_count, bad_files_count, good_files_directory, bad_files_directory);
			fd.get_matrixes_from_files();

			auto n = study(fd);
			Neurons.push_back(n);	
		}
	}

	return 0;
}