#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdlib.h>

#include "./headers/camera.h"
#include "./headers/mouse.h"

#define TITLE ("Graphing Window")
#define WIDTH (600.0)
#define HEIGHT (600.0)

// tentative data struct
typedef struct Data
{
    Vec2 *entries;
    size_t size;
} Data;

void Filter(double *value)
{
    const static double RC = 0.2;
    static double last_value = 0;

    last_value += (-last_value + *value) * RC;

    *value = last_value;
}

int main(void)
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("Could not initialize SDL Video: %s\n", SDL_GetError());
        return 1;
    }

    SDL_version compiled;
    SDL_version linked;
    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    printf("We compiled against SDL version %d.%d.%d ...\n",
           compiled.major, compiled.minor, compiled.patch);
    printf("But we are linking against SDL version %d.%d.%d.\n",
           linked.major, linked.minor, linked.patch);

    SDL_Window *window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    if (!window)
    {
        printf("Could not create SDL Window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        printf("Could not create SDL Renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // event loop

    int running = 1;
    SDL_Event event;

    Camera camera =
        {
            {0, 0}, // Pan
            {1, 1}  // Zoom
        };

    Mouse mouse = GetMouse();

    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    Vec2 start_pan = {0, 0};
    Vec2 pre_zoom = GetMousePos(&mouse), post_zoom = pre_zoom;

    // test data

    // Vec2 data_m[100];

    // DO NOT MODIFY LATER
    Vec2 *init_data_ptr = malloc(sizeof(Vec2) * 100);

    for (int i = 0; i < 100; ++i)
    {
        double val = rand() % (int)(HEIGHT);

        Filter(&val);

        init_data_ptr[i] = (Vec2){i, val};
    }
    // END

    // MODIFY data.entries
    Data data =
        {
            init_data_ptr,
            100};
    // end test data

    while (running)
    {
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        int l = GetButton(&mouse, LEFT), m = GetButton(&mouse, MIDDLE), r = GetButton(&mouse, RIGHT);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_KEYUP:
            case SDL_KEYDOWN:
                keys = SDL_GetKeyboardState(NULL);

                if (keys[SDL_SCANCODE_ESCAPE])
                {
                    running = 0;
                    break;
                }

                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                l = GetButton(&mouse, LEFT);
                m = GetButton(&mouse, MIDDLE);
                r = GetButton(&mouse, RIGHT);

                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    l = event.button.state == SDL_PRESSED;
                    break;
                case SDL_BUTTON_RIGHT:
                    r = event.button.state == SDL_PRESSED;
                    break;
                case SDL_BUTTON_MIDDLE:
                    m = event.button.state == SDL_PRESSED;
                    break;
                }

                break;
            case SDL_MOUSEWHEEL:

                pre_zoom = FromCamera(&camera, GetMousePos(&mouse));

                event.wheel.y *= (event.wheel.direction == SDL_MOUSEWHEEL_NORMAL);

                double val = (event.wheel.y > 0) * 1.1 + (event.wheel.y < 0) * 0.9;
                UpdateZoom(&camera, (Vec2){val, val});

                // after updating the camera's zoom, this function returns a diff value
                post_zoom = FromCamera(&camera, GetMousePos(&mouse));

                // TODO: add a function for this
                camera.pan = Vec2_Add(camera.pan, Vec2_Sub(pre_zoom, post_zoom));

                break;
            }
        }

        const static Button PAN = LEFT;
        if (GetButtonPressed(&mouse, PAN))
        {
            start_pan = GetMousePos(&mouse);
        }
        if (GetButtonHeld(&mouse, PAN))
        {
            UpdatePan(&camera, GetMouseChange(&mouse));
            start_pan = GetMousePos(&mouse);
        }

        const static Button RESET = MIDDLE;
        if (GetButtonPressed(&mouse, RESET))
        {
            ResetCamera(&camera);
        }

        const static Button ADD = RIGHT;
        const static int STATIC_DATA = 0;
        if (GetButtonPressed(&mouse, ADD))
        {
            // add sequence
            if (STATIC_DATA)
            {
                data.entries = realloc(data.entries, sizeof(Vec2) * ++data.size);
                data.entries[data.size - 1] = (Vec2){data.size, HEIGHT - GetMousePos(&mouse).y};
            }
            else
            {
                int i;
                for (i = 0; i < data.size - 1; ++i)
                {
                    Vec2 *next = data.entries + i + 1;
                    --next->x;

                    data.entries[i] = *next;
                }
                data.entries[i] = (Vec2){data.size, HEIGHT - GetMousePos(&mouse).y};
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderClear(renderer);

        // rending code

        Vec2 last = data.entries[0];
        last.x *= (WIDTH / data.size);
        last.y = HEIGHT - last.y;

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        for (int i = 0; i < data.size; ++i)
        {
            Vec2 current = data.entries[i];
            current.x *= (WIDTH / data.size);
            current.y = HEIGHT - current.y;

            SDL_FRect to_draw = {current.x - 4, current.y - 4, 8, 8};

            Vec2 current_after = ToCamera(&camera, current);
            Vec2 last_after = ToCamera(&camera, last);

            to_draw = ToCameraR(&camera, to_draw);

            SDL_RenderDrawRectF(renderer, &to_draw);
            SDL_RenderDrawLineF(renderer, current_after.x, current_after.y, last_after.x, last_after.y);

            last = current;
        }

        SDL_RenderPresent(renderer);

        // Update mouse
        UpdateMouse(&mouse, (Vec2){mx, my}, l, m, r);

        SDL_Delay(1000.0 / 60.0);
    }

    free(data.entries);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}