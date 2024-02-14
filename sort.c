#include "sort.h"
#include "visualize.h"
 
void insertion_sort(SDL_Renderer* renderer, int arr[]) {
    int key, j;
    for (int i = 1; i < ARRAY_MAX_SIZE; ++i) {

        key = arr[i];
        for (j = i - 1; j >= 0 && arr[j] > key; --j) {
            arr[j + 1] = arr[j];
            visualize_array(renderer, arr, j, i);
        }
        arr[j + 1] = key;
    }
    return;
}

void merge(SDL_Renderer* renderer, int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        visualize_array(renderer, arr, k, k);
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        visualize_array(renderer, arr, k, k);
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        visualize_array(renderer, arr, k, k);
        k++;
    }
}

void mergeS(SDL_Renderer* renderer, int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeS(renderer, arr, left, mid);
        mergeS(renderer, arr, mid + 1, right);

        merge(renderer, arr, left, mid, right);
    }
}

void mergeSort(SDL_Renderer* renderer, int arr[]) { mergeS(renderer, arr, 0, ARRAY_MAX_SIZE); }

void selectionSort(SDL_Renderer* renderer, int arr[]) {
    int i, j, min_idx;
    
    for (i = 0; i < ARRAY_MAX_SIZE; i++) {
        min_idx = i;
        for (j = i + 1; j < ARRAY_MAX_SIZE; j++) {
            visualize_array(renderer, arr, j, i);
            if (arr[j] < arr[min_idx]) 
                min_idx = j;

        }
        
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void heapify(SDL_Renderer* renderer, int arr[], int n, int i, int heap_size) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < heap_size && arr[l] > arr[largest])
        largest = l;

    if (r < heap_size && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        // Swap arr[i] and arr[largest]
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        visualize_array(renderer, arr, i, heap_size); // Visualize swap

        heapify(renderer, arr, n, largest, heap_size);
    }
}

void heapSort(SDL_Renderer* renderer, int arr[]) {
    int n = ARRAY_MAX_SIZE;
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(renderer, arr, n, i, n);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        visualize_array(renderer, arr, i, n); // Visualize swap

        // call max heapify on the reduced heap
        heapify(renderer, arr, n, 0, i);
    }
}

int partition(SDL_Renderer* renderer, int arr[], int low, int high) {
    int pivot = arr[high]; // Pivot element
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
            visualize_array(renderer, arr, i, j);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    visualize_array(renderer, arr, i + 1, high);
    return (i + 1);
}

void quickSort(SDL_Renderer* renderer, int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(renderer, arr, low, high);

        quickSort(renderer, arr, low, pi - 1);
        quickSort(renderer, arr, pi + 1, high);
    }
}

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void countSort(SDL_Renderer* renderer, int arr[], int n, int exp) {
    int output[n];
    int i, count[10] = {0};

    // Count occurrences of digits
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Cumulative count
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now contains sorted numbers according to current digit
    for (i = 0; i < n; i++) {
        arr[i] = output[i];
        visualize_array(renderer, arr, i, -1); // Visualize sorting
    }
}

void radixSort(SDL_Renderer* renderer, int arr[]) {
    int m = getMax(arr, ARRAY_MAX_SIZE);

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(renderer, arr, ARRAY_MAX_SIZE, exp);
}


