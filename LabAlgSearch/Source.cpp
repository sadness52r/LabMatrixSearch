#include <iostream>
#define N 8192

int** generate_data1(int M, int* target) {
	int** arr = new int* [M];
	for (int i = 0; i < M; i++) {
		arr[i] = new int[N];
		for (int j = 0; j < N; j++)
			arr[i][j] = (N / M * i + j) * 2;
	}
	(*target) = 2 * N + 1;
	return arr;
}
int** generate_data2(int M, int* target) {
	int** arr = new int* [M];
	for (int i = 0; i < M; i++) {
		arr[i] = new int[N];
		for (int j = 0; j < N; j++)
			arr[i][j] = (N / M * i * j) * 2;
	}
	(*target) = 16 * N + 1;
	return arr;
}
bool find_linear(int** arr, int M, int target) {
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
bool bin_search(int* arr, int target, int left, int right) {
	int l = left, r = right;
	while (l <= r)
	{
		int mid = (l + r) / 2;
		if (arr[mid] > target)
			r = mid - 1;
		else if (arr[mid] < target)
			l = mid + 1;
		else
			return true;
	}
	return false;
}
bool find_binary(int** arr, int M, int target) {
	for (int row = 0; row < M; row++)
		if (bin_search(arr[row], target, 0, N - 1))
			return true;
	return false;
}
bool find_exponential(int** arr, int M, int target) {
	int col = N - 1, i = 0, r = N - 1, l = 0;
	for (int row = 0; row < M; row++)
	{
		while (col > -1)
		{
			if (arr[row][col] > target)
				r = col;
			else if (arr[row][col] < target)
				l = col;
			else
				return true;
			col -= pow(2, i);
		}
		if (bin_search(arr[row], target, l, r))
			return true;
		else
			l = 0, i = 0;
	}
	return false;
}
void free_space(int** arr, int M) {
	for (int i = 0; i < M; i++)
		delete[] arr[i];
	delete[] arr;
}

int main() {
	int M;
	for (int x = 0; x <= 13; x++)
	{
		M = pow(2, x);
		int target;
		int** arr = generate_data1(M, &target);
		find_linear(arr, M, target);
		find_binary(arr, M, target);
		find_exponential(arr, M, target);
		arr = generate_data2(M, &target);
		find_linear(arr, M, target);
		find_binary(arr, M, target);
		find_exponential(arr, M, target);

		free_space(arr, M);
	}
	return 0;
}