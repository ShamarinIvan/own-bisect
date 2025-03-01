import unittest.case
import random
import string
def counting_sort(array, pos):
    n = len(array)
    output = [0] * n
    counts = [0] * 256
    for word in array:
        counts[ord(word[pos])] += 1
    for i in range(1, 256):
        counts[i] += counts[i-1]
    for i in range(n-1, -1, -1):
        char = array[i][pos]
        output[counts[ord(char)] - 1] = array[i]
        counts[ord(char)] -= 1
    for i in range(n):
        array[i] = output[i]
a = [123,456,295,111,444,695]
def radix_sort(array):
    t = len(array[0])

    for i in range(t-1, -1, -1):
        counting_sort(array, i)

def mergeSort(arr, l, r):
    if l < r:
        mid = (l + r) // 2
        mergeSort(arr, l, mid)
        mergeSort(arr, mid + 1, r)
        merge(arr, l, mid, r)

def merge(arr, l, mid, r):
    n1 = mid - l + 1
    n2 = r - mid
    N1 = [0] * n1
    N2 = [0] * n2
    for i in range(n1):
        N1[i] = arr[l + i]
    for i in range(n2):
        N2[i] = arr[mid + 1 + i]
    i = 0
    j = 0
    k = l
    while i < n1 and j < n2:
        if N1[i] < N2[j]:
            arr[k] = N1[i]
            i += 1
        else:
            arr[k] = N2[j]
            j += 1
        k += 1
    while i < n1:
        arr[k] = N1[i]
        k += 1
        i += 1
    while j < n2:
        arr[k] = N2[j]
        k += 1
        j += 1

class TestRadixSort(unittest.TestCase):
    def test_sort(self):
        k = 10
        m = 5
        a = [''.join(random.choice(string.ascii_letters) for i in range(m)) for i in range(k)]
        b = a
        mergeSort(a, 0, k-1)
        radix_sort(b)
        self.assertEqual(a, b)



if __name__ == "__main__":
    unittest.main()