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
	cout << "2. Search for oil" << endl;
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
	Neuron neuron = Neuron(fd.matrix_name);
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

void start_dig(int neuron_number)
{
	// 1. Получаем матрицы элементов, одна из них должна быть выбранной пользователем, то есть обязательно завести все матрицы
	// + 1/n леывые матрицы
	// 2. делаем цикл по полученным матрицам
	// 3. Пытаемся распознать матрицу выбранным нейроном
	// 4. Если не получилось - используем все остальные нейроны ->
	// 5. -> Если получилось - показываем, что за элемент нашли
	// 6. -> Если нет - Пишем, что неизвестный элемент
	// 7.В этом месте может предложить запомнить его матрицу, дать ему название, чтобы если элемент будет встрчен еще раз,
	// то мы могли его распознать

	files_data fd = files_data();
	int examples_count = 10;
	vector<int**> examples_matrix; // 1.
	for (int i = 0; i < examples_count; i++)
	{
		auto matrix = fd.get_matrix_from_file("examples/" + to_string(i) + ".txt");
		if (matrix == NULL)
			continue;
		examples_matrix.push_back(matrix);
	}

	for (auto matrix : examples_matrix) // 2.
	{
		auto choosen_neuron_result = Neurons[neuron_number].recognize(matrix);
		if (choosen_neuron_result == false)
		{
			// Пары (номер нейрона, какую сумму весов получил)
			vector<pair<int, int>> weights;
			for (int i = 0; i < Neurons.size(); i++)
			{
				if (i == neuron_number) continue;
				auto axon_weight = Neurons[i].get_weight_sum();
				pair<int, int> neuron_and_weight = pair<int, int>(neuron_number, axon_weight);
				weights.push_back(neuron_and_weight);
			}
			sort_vector(weights); // !K

		}
	}
}

void sort_vector(vector<pair<int, int>>& v)
{
	//
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
		else if (operation == 2)
		{
			if (Neurons.size() == 0)
			{
				writeline("You don't have any studied neurons");
				continue;
			}
			
			writeline("Choose witch product you want to dig from earth: ");
			for (int i = 0; i < Neurons.size(); i++)
				writeline(to_string(i) + ". " + Neurons[i].name);

			int nId;
			cin >> nId;
			if (nId >= Neurons.size() || nId < 0)
			{
				writeline("Invalid product number");
				continue;
			}

			start_dig(nId);
		}
	}

	return 0;
}