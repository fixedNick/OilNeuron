#ifndef FILES_DATA_H
#define FILES_DATA_H

#include <string>
#include <vector>

using namespace std;

struct files_data
{
public:
	vector<int**> good_matrix;
	vector<int**> bad_matrix;
	int good_files_count;
	int bad_files_count;
	string good_files_directory;
	string bad_files_directory;
	files_data();
	files_data(const int& _good_files_count, const int& _bad_files_count, const string& _good_files_directory, const string& _bad_files_directory);
	void get_matrixes_from_files();
	int** get_matrix_from_file(string filename);
	//todo
	//int get_files_count_in_directory(char* dir);
};

#endif