#include "sort.h"

int main() {
    int arr[ARRAY_MAX_SIZE];
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    if (SDL_INIT_VIDEO < 0) {
        fprintf(stderr, "ERROR: SDL_INIT_VIDEO\n");
        exit(1);
    }

    window = SDL_CreateWindow (
                "Sorting",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                WINDOW_WIDTH,
                WINDOW_HEIGHT,
                SDL_WINDOW_BORDERLESS
             );
    
    if (!window) {
        fprintf(stderr, "ERROR: SDL_CreateWindow\n");
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "ERROR: SDL_CreateRenderer\n");
        exit(1);
    }

    init_array(arr);
    shuffle_array(arr);

    visualize_array(renderer, arr, -1, -1); 

    SDL_Event event;
    bool isStart = false;
    while (!isStart) {
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_1:
                        isStart = true;
                        mergeSort(renderer, arr);
                        break;
                    case SDLK_2:
                        isStart = true;
                        radixSort(renderer, arr);
                        break;
                    case SDLK_3:
                        isStart = true;
                        quickSort(renderer, arr, 0, ARRAY_MAX_SIZE - 1);
                        break;
                    case SDLK_4:
                        isStart = true;
                        heapSort(renderer, arr);
                        break;
                }
                break;
        }
    }

    visualize_array(renderer, arr, -1, -1);
    visualize_final(renderer, arr);

    SDL_Delay(1000);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}


// Makes a sorted array
void init_array(int arr[]) {
    for (size_t i = 0; i <= ARRAY_MAX_SIZE; ++i)
        arr[i] = (i + 1);
    return;
}

// Shuffles a sorted array
void shuffle_array(int arr[]) {
    srand(time(0));
    int randIdx;

    for (size_t i = 0; i < ARRAY_MAX_SIZE; ++i) {
        randIdx = (rand() % ARRAY_MAX_SIZE + 1);
        swap(&arr[i], &arr[randIdx]);
    }
    return;
}

void visualize_array(SDL_Renderer* renderer, int arr[], int red, int green) {
    SDL_Rect rectangle;
    int max_value = ARRAY_MAX_SIZE;

    // Calculate the scale factor to fit the maximum value within the window height
    float scale_factor = (float)WINDOW_HEIGHT / max_value;

    // Calculate the width of each rectangle
    rectangle.w = (float)WINDOW_WIDTH / ARRAY_MAX_SIZE;
    
    SDL_RenderClear(renderer);
    for (size_t i = 0; i < ARRAY_MAX_SIZE; ++i) {
        // Scale the height of the rectangle
        rectangle.h = arr[i] * scale_factor;

        // Set the position of the rectangle
        rectangle.x = i * rectangle.w;
        rectangle.y = WINDOW_HEIGHT - rectangle.h; // Start from the bottom of the window
        
        // Draw rectangle
        if ( (red - i) <= 10) SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        else if (green == i) SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
        else SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        

        SDL_RenderFillRect(renderer, &rectangle);
        // Draw rectangle border
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    }
    SDL_RenderPresent(renderer);
}

void visualize_final(SDL_Renderer* renderer, int arr[]) {
    SDL_Rect rectangle;
    int max_value = ARRAY_MAX_SIZE;

    // Calculate the scale factor to fit the maximum value within the window height
    float scale_factor = (float)WINDOW_HEIGHT / max_value;

    // Calculate the width of each rectangle
    rectangle.w = (float)WINDOW_WIDTH / ARRAY_MAX_SIZE;
    
    for (size_t i = 0; i < ARRAY_MAX_SIZE; ++i) {
        // Scale the height of the rectangle
        rectangle.h = arr[i] * scale_factor;

        // Set the position of the rectangle
        rectangle.x = i * rectangle.w;
        rectangle.y = WINDOW_HEIGHT - rectangle.h; // Start from the bottom of the window
        
        // Draw rectangle
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &rectangle);

        // Draw rectangle border
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

        SDL_Delay(2);
        SDL_RenderPresent(renderer);
    }
}

void swap(int* a, int* b) {
    int tmp = *b;
    *b = *a;
    *a = tmp;
}
