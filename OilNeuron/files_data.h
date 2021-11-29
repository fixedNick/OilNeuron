#ifndef FILES_DATA_H
#define FILES_DATA_H

#include <string>
#include <vector>

using namespace std;

struct files_data
{
public:
	static string get_path(string directory, int id);

	vector<int**> good_matrix;
	vector<int**> bad_matrix;
	int good_files_count;
	int bad_files_count;
	string good_files_directory;
	string bad_files_directory;
	string matrix_name;
	files_data();
	files_data(string _matrix_name, const int& _good_files_count, const int& _bad_files_count, const string& _good_files_directory, const string& _bad_files_directory);
	void get_matrixes_from_files();

private:
	int** get_matrix_from_file(string filename);
};

#endif