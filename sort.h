#ifndef _SORT_H_
#define _SORT_H_

#define ARRAY_MAX_SIZE 600
#define MAX(x, y) (x > y) ? x : y

#include <SDL2/SDL.h>
#include "visualize.h"

void insertion_sort(SDL_Renderer*, int[]);
void mergeSort(SDL_Renderer*, int[]);
void selectionSort(SDL_Renderer*, int[]);
void heapSort(SDL_Renderer*, int []);
void quickSort(SDL_Renderer*, int[], int, int);
void radixSort(SDL_Renderer* renderer, int arr[]);

#endif
