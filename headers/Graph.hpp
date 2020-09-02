#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

// contain all the sdl in this file

#include "Camera.hpp"

#include <string>

#include <deque>
#include <vector>

#include "Mouse.hpp"
#include "Keyboard.hpp"

namespace mp
{

    class GraphData
    {
    private:
        std::deque<double> y_values;

        std::string title;

        unsigned int size;
        double min;
        double max;

    public:
        GraphData(const std::string &title, unsigned int size, double maxValue, double minValue);
        ~GraphData();

        void Insert(double value);

        // Getters
        double GetSize() const;
        double GetMin() const;
        double GetMax() const;
        const std::string &GetTitle() const;

        double operator[](int index) const;
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

        // Graphs
        std::vector<GraphData> graphs;

    public:
        Graph(const std::string &title, unsigned int WIDTH, unsigned int HEIGHT, const std::vector<GraphData> &data);
        ~Graph();

        bool IsRunning() const;
        void Update();

        void Insert(double y);
        const Mouse &GetMouse() const;
        const Keyboard &GetKeyboard() const;
    };

} // namespace mp

#endif