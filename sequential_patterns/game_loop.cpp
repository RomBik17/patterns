
#include <iostream>


double previous = getCurrentTime();
double lag = 0.0;
while (true) {
    double current = getCurrentTime();
    //время между кадрами
    double elapsed = current - previous;
    previous = current;
    //время с начала игры
    lag += elapsed;

    processInput();

    //симулируем те вычисления, которые пропустились изза рендеринга, чтобы все вычисления были плавными
    while (lag >= MS_PER_UPDATE) {
        update();
        //вычисляем поока не компенсируем разницу времени
        lag -= MS_PER_UPDATE;
    }

    //рендерим с того момента, где остановились, чтобы не было дерганой картинки
    render(lag / MS_PER_UPDATE);
}