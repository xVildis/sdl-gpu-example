#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_gpu.h>

int main(int argc, char* argv[])
{
    // specifying disable vsync in GPU_Init doesn't work
    GPU_SetPreInitFlags(GPU_INIT_DISABLE_VSYNC);
    GPU_Target* target = GPU_Init(1280, 720, GPU_DEFAULT_INIT_FLAGS);

    if(!target) {
        printf("couldn't initialize gpu target");
        return 1;
    }

    // image from NASA
    GPU_Image* image = GPU_LoadImage("assets/test.png");

    if(!image) {
        printf("no img\n");
        return 1;
    }

    const uint64_t counter_freq = SDL_GetPerformanceFrequency();

    bool running = true;
    while (running)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
                running = false;

            switch(e.type)
            {
                case SDL_KEYUP: {
                    SDL_KeyboardEvent ke = e.key;
                    if(ke.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    }
                    break;
                }

                default:
                    break;
            }
        }

        uint64_t start_count = SDL_GetPerformanceCounter();

        GPU_Clear(target);
        GPU_SetAnchor(image, 0.0f, 0.0f);

        float scale_x = ((float)target->w / (float)image->w), 
              scale_y = ((float)target->h / (float)image->h);
        GPU_BlitScale(image, NULL, target, 0.f, 0.f, scale_x, scale_y );

        GPU_Flip(target);

        uint64_t end_count = SDL_GetPerformanceCounter();
        uint64_t count_delta = end_count - start_count;

        double deltatime = ((double)count_delta / (double)counter_freq) * 1000.f;
        printf("frametime: %f\n", deltatime);
    }

    GPU_FreeImage(image);
    GPU_FreeTarget(target);
    GPU_Quit();

    return 0;
}