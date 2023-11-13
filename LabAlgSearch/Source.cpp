#include <iostream>
#include <chrono>
#include <fstream>
std::ofstream fout;
#include "funcs.hpp"

int main() {
	fout.open("inputLog.txt");
	int M;
	for (int x = 1; x <= 13; x++)
	{
		M = pow(2, x);
		int target;
		int** arr = generate_data1(M, &target);
		fout << "Size: " << N * M << std::endl;
		std::cout << "Size: " << N * M << std::endl;
		print_data(1, arr, M, target);
		arr = generate_data2(M, &target);
		print_data(2, arr, M, target);
		free_space(arr, M);
	}
	fout.close();
	return 0;
}