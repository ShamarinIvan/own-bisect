#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define N 60000000

void generate_random_array(long* arr, size_t size){
	for(size_t i = 0; i < size; ++i){
		arr[i] = rand() % N;
	}
}

void copy_array(long* src, long* dest, size_t size){
	for(size_t i = 0; i < size; ++i){
		dest[i] = src[i];
	}
}
void choose_random_pivot(long* first, long* last){
	size_t size = last - first;
	size_t pivot_index = rand() % size;
	long temp = first[pivot_index];
    first[pivot_index] = *(last - 1);
    *(last - 1) = temp;
}

long* lomuto_partition(long* first, long* last){
	choose_random_pivot(first, last);
	long pivot = *(last - 1);
	long* i = first;
	for(long* j = first; j < last - 1; ++j){
		if(*j < pivot){
			long temp = *i;
			*i = *j;
			*j = temp;
			i++;
		}
	}
    long temp = *i;
    *i = *(last - 1);
    *(last - 1) = temp;
    return i;
}

void quicksort_lomuto(long* first, long* last) {
    if (first < last) {
        long* pivot = lomuto_partition(first, last);
        quicksort_lomuto(first, pivot);
        quicksort_lomuto(pivot + 1, last);
    }
}

long* lomuto_partition_branchfree(long* first, long* last) {
    assert(first <= last);
    if (last - first < 2)
        return first;
    --last;
    if (*first > *last){
        
        long temp = *first;
		*first = *last;
		*last = temp;
	}
    long* pivot_pos = first;
    long pivot = *first;
    do {
        ++first;
        assert(first <= last);
    } while (*first < pivot);
    for (long* read = first + 1; read < last; ++read) {
        long x = *read;
        long smaller = -(x < pivot);
        long delta = smaller & (read - first);
        first[delta] = *first;
        read[-delta] = x;
        first -= smaller;
    }
    assert(*first >= pivot);
    --first;
    *pivot_pos = *first;
    *first = pivot;
    return first;
}

void quicksort_lomuto_branchfree(long* first, long* last) {
    if (first < last) {
        long* pivot = lomuto_partition_branchfree(first, last);
        quicksort_lomuto_branchfree(first, pivot);
        quicksort_lomuto_branchfree(pivot + 1, last);
    }
}

long* hoare_partition(long* first, long* last) {
    choose_random_pivot(first, last);
    long temp = *first;
    *first = *(last - 1);
    *(last - 1) = temp;
    long pivot = *first;
    long* left = first - 1;
    long* right = last;
    while (1) {
        do { right--; } while (*right > pivot);
        do { left++; } while (*left < pivot);
        if (left >= right) return right;
        long temp = *left;
        *left = *right;
        *right = temp;
    }
}

void quicksort_hoare(long* first, long* last) {
    if (first < last - 1) {
        long* pivot = hoare_partition(first, last);
        quicksort_hoare(first, pivot + 1);
        quicksort_hoare(pivot + 1, last);
    }
}

double measure_time(void (*sort_func)(long*, long*), long* arr, size_t size) {
    clock_t start = clock();
    sort_func(arr, arr + size);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL));
    long* original = (long*)malloc(N * sizeof(long));
    long* arr = (long*)malloc(N * sizeof(long));

    generate_random_array(original, N);

    copy_array(original, arr, N);
    printf("QuickSort (Ломуто): %.6f секунд\n", measure_time(quicksort_lomuto, arr, N));

    copy_array(original, arr, N);
    printf("QuickSort (Ломуто без ветвлений): %.6f секунд\n", measure_time(quicksort_lomuto_branchfree, arr, N));
    copy_array(original, arr, N);
    printf("QuickSort (Хоара): %.6f секунд\n", measure_time(quicksort_hoare, arr, N));

    free(original);
    free(arr);
    return 0;
}