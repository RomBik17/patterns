
#include <iostream>


double previous = getCurrentTime();
double lag = 0.0;
while (true) {
    double current = getCurrentTime();
    //Time between frames
    double elapsed = current - previous;
    previous = current;
    //Time from beginning
    lag += elapsed;

    processInput();

    //We simulate the calculations that we missed because of rendering, to keep image on screen smooth
    while (lag >= MS_PER_UPDATE) {
        update();
        //Calculate until we compensate for the time difference
        lag -= MS_PER_UPDATE;
    }

    //Start to render from the momemt when we stopped, to keep image on screen smooth
    render(lag / MS_PER_UPDATE);
}