#include "header.hpp"
using namespace sf;

void game() {
    int sizeBoardX = 10;
    int sizeBoardY = 10;

    int *board = (int *)malloc(sizeof(int) * sizeBoardX * sizeBoardY);

    int boats[] = {4, 3, 2, 1};  // Barcos com 2,3,4,5 quadrados
    int bombs = 50;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);
        window.display();
    }
}
