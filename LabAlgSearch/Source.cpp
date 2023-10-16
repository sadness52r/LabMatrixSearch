#include <iostream>
#define N 8192

long long** generate_data1(int M, int* target) {
	long long** arr = new long long* [M];
	for (int i = 0; i < M; i++) {
		arr[i] = new long long[N];
		for (int j = 0; j < N; j++)
			arr[i][j] = (long long)((N / M * i + j) * 2);
	}
	(*target) = 2 * N + 1;
	return arr;
}
bool find_linear(long long** arr, int M, int target) {
	int row = 0, col = N - 1;
	while (row < M && col > -1)
	{
		if (arr[row][col] > target)
			col--;
		else if (arr[row][col] < target)
			row++;
		else
			return true;
	}
	return false;
}
void print_data(long long** arr, int M, int target) {
	std::cout << "Target = " << target << std::endl;
	std::cout << "Has target found? " << find_linear(arr, M, target) << std::endl;
}
void free_space(long long** arr, int M) {
	for (int i = 0; i < M; i++)
		delete[] arr[i];
	delete[] arr;
}

int main() {
	int M;
	for (int x = 3; x <= N; x += 2)
	{
		M = pow(2, x);
		int target;
		long long** arr = generate_data1(M, &target);
		print_data(arr, M, target);
		free_space(arr, M);
	}
	return 0;
}