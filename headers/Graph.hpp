#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

// contain all the sdl in this file

#include "Camera.hpp"
#include "DataBuffer.hpp"

#include <string>

#include <vector>

#include "Mouse.hpp"
#include "Keyboard.hpp"

namespace mp
{

    struct RenderConfig
    {
        double min;
        double max;

        RenderConfig(double maxValue, double minValue);
        ~RenderConfig();

        double GetMin() const;
        double GetMax() const;

    };

    class Graph
    {
    private:
        // SDL backend
        SDL_Window *window;
        SDL_Renderer *renderer;

        // Event loop
        bool isRunning;
        SDL_Event event;
        Mouse mouse;
        Keyboard keyboard;

        // Rendering & Pan/Zoom
        Camera camera;
        mp::Vec2 start_pan, start_zoom;
        unsigned int w, h;

        using ArrayType = std::vector<DataQueue>;

        // Graphs
    public:
        ArrayType graphs;

    public:
        Graph(const std::string& title, unsigned int WIDTH, unsigned int HEIGHT, const ArrayType& data);
        ~Graph();

        bool IsRunning() const;
        void Render(const RenderConfig&);

        void Update(double y);

        const Mouse &GetMouse() const;
        const Keyboard &GetKeyboard() const;
    };

} // namespace mp

#endif