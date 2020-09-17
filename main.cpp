#include "headers/Graph.hpp"
#include <iostream>

#include "headers/Timer.hpp"

int main(void)
{

    struct DivFilter final : mp::Filter
    {
        double divisor;

        DivFilter(double div_by) : divisor { (div_by == 0) + div_by } {}
        ~DivFilter() {}    

        double operator()(double next) { return next / divisor; }

        PointerType clone() const
        {
            return std::unique_ptr<Filter>(new DivFilter(divisor));
        }
    };

    auto signum = [](double n) 
    {
        return (n > 0) - (n < 0);
    };

    struct SquareFilter final : mp::Filter
    {
        SquareFilter(){}
        ~SquareFilter(){}

        double operator()(double next) { return next * next * (next > 0) - (next < 0); }

        PointerType clone() const
        {
            return std::unique_ptr<Filter>(new SquareFilter());
        }
    };

    struct CubeFilter final : mp::Filter
    {
        CubeFilter(){}
        ~CubeFilter(){}

        double operator()(double next) { return next * next * next; }

        PointerType clone() const
        {
            return std::unique_ptr<Filter>(new CubeFilter());
        }
    };


    mp::Graph graph
    (
        "Graphing Title", 600,600, 

        {

        mp::DataQueue(200),
        mp::DataQueue(200, new SquareFilter()),
        mp::DataQueue(200, new CubeFilter())
        
        }
    );

    // mp::DataQueue copy_constructor(200, new mp::MovingAverage(24), 0.0);
    /*
    TODO:
        - Add filtering for graph datas
        - Add rendering configurations for graph data
        - Render text for graph data
        - Fix rendering glitch the minimum value is not 0
    */

    /*
    NOTE:
    add threading for getting keyboard and mouse input
    because if there is an interrupt the input doesnt change

    basically, make sure that g.Update() is always getting called
    */
    
    mp::Timer timer;
    bool is_inserting = false;

    const auto config = mp::RenderConfig(0, 1);

    while (graph.IsRunning())
    {
        if (graph.GetMouse().GetPressed(mp::Mouse::Button::MIDDLE))
            is_inserting = !is_inserting;

        double y = 600 - graph.GetMouse().GetPos().y;
        y /= 600.0;

        if (is_inserting)
            graph.Update(y);
        
        graph.Render(config);

        // std::cout << "Frames per second: " << (1.0 / timer.Poll()) << "\n";
    }

    return 0;
}