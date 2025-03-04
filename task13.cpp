#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#include <vector>
#include <deque>
#include <stack>
#include <cstdlib>
using namespace std;
int lomuto_partition(vector<int>& arr, int low, int high) {
    int pivot_index = low + rand() % (high - low + 1);
    swap(arr[pivot_index], arr[high]);
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

int findOrderStatistic(vector<int> arr, int k) {
    int left = 0;
    int right = arr.size() - 1;
    while (true) {
        int mid = lomuto_partition(arr, left, right);

        if (mid == k - 1) {
            return arr[mid];
        }
        else if (k - 1 < mid) {
            right = mid-1;
        }
        else {
            left = mid+1;
        }
    }
}

double solution(vector<int> arr) {
    int length = arr.size();
    if (length % 2 == 0) {
        return ((findOrderStatistic(arr, length / 2) + findOrderStatistic(arr, length / 2 + 1)) / 2.0);
    }
    else {
        return findOrderStatistic(arr, length / 2 + 1);
    }
}
int main() {
    vector<int> arr = { 10, 7, 8, 9, 1};
    cout << solution(arr);
    return 0;
}
