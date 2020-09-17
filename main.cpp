#include "headers/Graph.hpp"
#include <iostream>

#include "headers/Timer.hpp"

int main(void)
{

    mp::Graph graph
    (
        "Graphing Title", 600,600, 

        {

        mp::DataQueue(200), 
        mp::DataQueue(200, new mp::MovingAverage(24)),
        mp::DataQueue(200, new mp::LowPassFilter(0.5))
        
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
    bool is_running = false;

    while (graph.IsRunning())
    {
        if (graph.GetMouse().GetPressed(mp::Mouse::Button::MIDDLE))
            is_running = !is_running;

        double y = 600 - graph.GetMouse().GetPos().y;
        
        if (is_running)
            graph.Insert(y);
        
        graph.Update(mp::RenderConfig(0,600));

        std::cout << "Frames per second: " << (1.0 / timer.Poll()) << "\n";
    }

    return 0;
}