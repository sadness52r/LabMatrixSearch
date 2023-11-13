#pragma once

#define N 8192

int** generate_data1(int M, int* target);
int** generate_data2(int M, int* target);
bool find_linear(int** arr, int M, int target);
int bin_search(int* arr, int target, int left, int right);
int exponential_search(int* arr, int target, int curCol);
bool find_binary(int** arr, int M, int target);
bool find_exponential(int** arr, int M, int target);
void print_data(int numGeneration, int** arr, int M, int target);
void free_space(int** arr, int M);