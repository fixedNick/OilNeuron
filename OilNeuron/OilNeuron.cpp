#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "files_data.h"
#include "Neuron.h"
#include "Fossil.h"
#include "DigFossil.h"

using namespace std;

vector<Fossil> Fossils;

void print_menu(int& operation)
{
	cout << "0. Exit" << endl;
	cout << "1. Add fossil and study that neurons" << endl;
	cout << "2. Search for fossil" << endl;
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
// todo: load_neurons
Neuron study(files_data fd)
{
	Neuron neuron = Neuron(fd); // ����������� ��� ���������� � �������/������ �������� � �������� � ��� ������ �������, ���� ����� �� ��������� � files_data
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

void start_dig(Fossil fossil_recognizer)
{
	// 1. �������� ������� ���������, ���� �� ��� ������ ���� ��������� �������������, �� ���� ����������� ������� ��� �������
	// + 1/n ������ �������
	// 2. ������ ���� �� ���������� ��������
	// 3. �������� ���������� ������� ��������� ��������
	// 4. ���� �� ���������� - ���������� ��� ��������� ������� ->
	// 5. -> ���� ���������� - ����������, ��� �� ������� �����
	// 6. -> ���� ��� - �����, ��� ����������� �������
	// 7.� ���� ����� ����� ���������� ��������� ��� �������, ���� ��� ��������, ����� ���� ������� ����� ������� ��� ���,
	// �� �� ����� ��� ����������

	// ������� ���������� ����� ������ ���
	// (������� � ��� ���� ������� ������ ��� �������������)
	vector<DigFossil> set_of_dig_fossils;
	int dig_fossils_count = 10;

	for (int i = 0; i < dig_fossils_count; i++)
	{
		DigFossil dig_fossil; // ���� �� ����������, ������� �� ����� ������������ ����� ��������� ����������
		// ��� ������� ������ ���������� ������� ������ ������� ������ � ����������, ������� ��� ����������, ������� �� ������ �� ���� ���� 3 �������, �� ���� 3 �������� ��� �������������
		// ����� ���� ������ ���������� ������� �� ����� (get_matrix_from_file)
		files_data fd = files_data();
		int files_in_dig_fossil_directory = 3; // ����� ��������� � ������� � �������� ������ ���������� ������
		for (int fe = 0; fe < files_in_dig_fossil_directory; fe++)
		{
			// examples_to_dig/0/0.txt - ����� ����. �.�. ���� ���������� ������ �������������, �� � �����:
			// examples_to_dig/0/ ����� ������ ��� �����:
			// 0.txt
			// 1.txt
			// 2.txt
			string path = "examples_to_dig/" + to_string(i) + "/" + to_string(fe) + ".txt";
			auto matrix = fd.get_matrix_from_file(path); // ��������� ������� �����������(�������)
			if(matrix != NULL)
				dig_fossil.add_element(matrix); // ��������� ����������� �������
		}
	}

	// � ������ ������ �� ������� � ������� ��� ����������, ������� ���������� � ��� �� ���� ��� ���������
	// �������� ��������, �������� �� ���� ���������� fossil_to_dig

	int counter = 0;
	for (auto fossil_to_dig : set_of_dig_fossils)
	{
		auto result = fossil_recognizer.is_digged_fossil_is_equal_this_fossil(fossil_to_dig);
		if (result == true)
			writeline("Digged fossil number #" + to_string(counter) + " is " + fossil_recognizer.name);
		else
			writeline("Digged fossil number #" + to_string(counter) + " is unknown");
	}
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
			// ������ ������ �� ����������
			Fossil fossil = Fossil();
			cout << "Enter fossil name: ";
			cin >> fossil.name;
			cout << "Enter neurons of fossil count: ";
			int fossil_neurons_count = -1;
			cin >> fossil_neurons_count;

			if (fossil_neurons_count <= 0)
			{
				cout << "Your fossil need some neurons..." << endl;
				continue;
			}

			for (int i = 0; i < fossil_neurons_count; i++)
			{
				files_data fd = files_data();
				string name;

				write("Enter fossil element name: ");
				cin >> name;

				write("Enter good files directory name:");
				cin >> fd.good_files_directory;
				write("Enter good files count:");
				cin >> fd.good_files_count;

				write("Enter bad files directory name:");
				cin >> fd.bad_files_directory;
				write("Enter bad files count:");
				cin >> fd.bad_files_count;

				fd.get_matrixes_from_files();
				auto fossil_studied_neuron = study(fd);
				fossil_studied_neuron.name = name;
				fossil_studied_neuron.fd = fd;
				fossil.add_neuron(fossil_studied_neuron);
			}

			Fossils.push_back(fossil);
		}
		else if (operation == 2)
		{
			// ����� ������ ����������� ����� ������� ���������
			if (Fossils.size() == 0)
			{
				writeline("You don't have any fossils");
				continue;
			}
			
			writeline("Choose witch product you want to dig from earth: ");
			for (int i = 0; i < Fossils.size(); i++)
				writeline(to_string(i) + ". " + Fossils[i].name);

			int nId;
			cin >> nId;
			if (nId >= Fossils.size() || nId < 0)
			{
				writeline("Invalid fossil number");
				continue;
			}

			// ������ ����� ����������� Fossils[nId];
			start_dig(Fossils[nId]);
		}
	}

	return 0;
}