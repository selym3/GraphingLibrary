#include "../headers/Graph.hpp"
#include <stdexcept>

#include <sstream>

#include <cmath>

using namespace mp;

/*
Graphs can only exist in the same scope as it is coded now.
*/

RenderConfig::RenderConfig(double a , double b): 
    min { a }, max { b}
{
}

RenderConfig::~RenderConfig() {}

double RenderConfig::GetMin() const { return min; }
double RenderConfig::GetMax() const { return max; }

Graph::Graph(const std::string &title, unsigned int WIDTH, unsigned int HEIGHT, const std::vector<DataQueue> &data)
    : w{WIDTH}, h{HEIGHT}, isRunning{true}
{

    if (SDL_WasInit(SDL_INIT_VIDEO) != SDL_INIT_VIDEO)
    {
        if (SDL_Init(SDL_INIT_VIDEO))
        {
            std::stringstream ss;
            ss << "Unable to initialize SDL " << SDL_GetError();

            throw std::runtime_error(ss.str());
        }

        SDL_version compiled;
        SDL_version linked;

        SDL_VERSION(&compiled);
        SDL_GetVersion(&linked);
        printf("We compiled against SDL version %d.%d.%d ...\n",
               compiled.major, compiled.minor, compiled.patch);
        printf("But we are linking against SDL version %d.%d.%d.\n",
               linked.major, linked.minor, linked.patch);
    }

    keyboard.Set(SDL_GetKeyboardState(NULL));

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    if (!window)
        throw std::runtime_error("Could not create graph window.");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
        throw std::runtime_error("Could not create graph renderer");

    graphs = data;

}

Graph::~Graph()
{

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Graph::IsRunning() const { return isRunning; }

void Graph::Render(const RenderConfig &config)
{
    bool l = mouse.Get(Mouse::Button::LEFT);
    bool m = mouse.Get(Mouse::Button::MIDDLE);
    bool r = mouse.Get(Mouse::Button::RIGHT);

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            return;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            keyboard.Set(SDL_GetKeyboardState(NULL));
            if (keyboard.Get(SDL_SCANCODE_ESCAPE))
            {
                isRunning = false;
            }

            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:

            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                l = event.button.state == SDL_PRESSED;
                break;
            case SDL_BUTTON_MIDDLE:
                m = event.button.state == SDL_PRESSED;
                break;
            case SDL_BUTTON_RIGHT:
                r = event.button.state == SDL_PRESSED;
                break;
            }

            break;
        case SDL_MOUSEWHEEL:

            Vec2 m_pos = mouse.GetPos();

            start_zoom = camera[m_pos];

            event.wheel.y *= (event.wheel.direction == SDL_MOUSEWHEEL_NORMAL);

            // add in zoom speed inside of camera class
            double val = (event.wheel.y > 0) * 1.1 + (event.wheel.y < 0) * 0.9;
            camera.zoom *= val;

            start_zoom -= camera[m_pos];

            camera.pan += (start_zoom);

            break;
        }
    }

    static constexpr Mouse::Button PAN = Mouse::Button::LEFT;
    if (mouse.GetPressed(PAN))
        start_pan = mouse.GetPos();

    if (mouse.GetHeld(PAN))
    {
        camera.pan -= ((mouse.GetChange()) / camera.zoom);
        start_pan = mouse.GetPos();
    }

    static constexpr Mouse::Button RESET = Mouse::Button::RIGHT;
    if (mouse.GetHeld(RESET))
    {
        camera.Reset();
    }

    // here i would draw to the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    for (auto &x : graphs)
    {

        const double min = config.GetMin();
        const double absolute_min = min * ((min > 0) - (min < 0));

        const double pixels = double(w) / (config.GetMax() - min);

        const int n = x.GetSize();

        const double scalar = double(w / n);

        double last_x = 0;
        double last_y = h - x.front();

        int i = 0;

        for (const double &y : x)
        {
            double current_x = scalar * i++;
            double current_y = h - (pixels * (absolute_min + y));

            Vec2 current = camera(Vec2(current_x, current_y));
            Vec2 last = camera(Vec2(last_x, last_y));

            SDL_FRect to_draw = {(float)current_x - 4, (float)current_y - 4, 8, 8};
            to_draw = camera(to_draw);

            // SDL_RenderDrawRectF(renderer, &to_draw);
            SDL_RenderDrawLineF(renderer, (float)current.x, (float)current.y, (float)last.x, (float)last.y);

            last_x = current_x;
            last_y = current_y;
        }
    }

    SDL_RenderPresent(renderer);

    int x;
    int y;
    SDL_GetMouseState(&x, &y);

    mouse.Update(Vec2(x, y), l, m, r);
}

void Graph::Update(double y)
{
    for (auto& x : graphs)
        x.Update(y);
}

const Mouse &Graph::GetMouse() const { return mouse; }
const Keyboard &Graph::GetKeyboard() const { return keyboard; }