#include <iostream>
#include <chrono>
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
int bin_search(int* arr, int target, int left, int right) {
	int l = left, r = right, mid = 0;
	while (l <= r)
	{
		mid = (l + r) / 2;
		if (arr[mid] > target)
			r = mid - 1;
		else if (arr[mid] < target)
			l = mid + 1;
		else
			return mid;
	}
	return mid;
}
int exponential_search(int* arr, int target, int curCol) {
	int step = 1;
	for (; curCol >= 0; curCol -= step)
	{
		if (arr[curCol] <= target) {
			curCol = bin_search(arr, target, curCol, curCol + step);
			return curCol;
		}	
		step *= 2;
	}
	if (arr[0] <= target)
		curCol = bin_search(arr, target, 0, curCol + step);
	return curCol;
}
bool find_binary(int** arr, int M, int target) {
	for (int row = 0; row < M; row++)
		if (arr[row][bin_search(arr[row], target, 0, N - 1)] == target)
			return true;
	return false;
}
bool find_exponential(int** arr, int M, int target) {
	int n = N - 1;
	for (int row = 0; row < M; row++)
	{
		int index = exponential_search(arr[row], target, n);
		if (index >= 0 && arr[row][index] == target)
			return true;
	}
	return false;
}
void print_data(int numGeneration, int** arr, int M, int target) {
	auto start = std::chrono::steady_clock::now();
	bool isFound = find_linear(arr, M, target);
	auto end = std::chrono::steady_clock::now();

	std::cout << "Result from algorythm 1 (Data Generation " << numGeneration << "): " << isFound << " Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;

	start = std::chrono::steady_clock::now();
	isFound = find_binary(arr, M, target);
	end = std::chrono::steady_clock::now();
	std::cout << "Result from algorythm 2 (Data Generation " << numGeneration << "): " << isFound << " Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;

	start = std::chrono::steady_clock::now();
	isFound = find_exponential(arr, M, target);
	end = std::chrono::steady_clock::now();
	std::cout << "Result from algorythm 3 (Data Generation " << numGeneration << "): " << isFound << " Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
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
		std::cout << "Size: " << N * M << std::endl;
		print_data(1, arr, M, target);
		arr = generate_data2(M, &target);
		print_data(2, arr, M, target);
		free_space(arr, M);
	}
	return 0;
}