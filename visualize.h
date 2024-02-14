#ifndef _VISUALIZE_H_
#define _VISUALIZE_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#define     WINDOW_HEIGHT    900
#define     WINDOW_WIDTH    1800

#define     ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

void init_array(int[]);
void shuffle_array(int[]);
void visualize_array(SDL_Renderer*, int[], int, int);
void visualize_final(SDL_Renderer*, int[]);
void swap(int*, int*);

#endif
