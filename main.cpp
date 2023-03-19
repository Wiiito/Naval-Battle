#include <SFML/Graphics.hpp>
#include <iostream>

#include "src/game.cpp"
#include "src/players.cpp"
#include "src/startMenu.cpp"

int main() {
    int controlPanel = 1;
    CircleShape shape(200.f);
    shape.setFillColor(Color::Black);

    while (window.isOpen()) {
        Event ev;
        // "Loop" do menu
        switch (controlPanel) {
            case 0:
                window.clear(Color::White);
                window.draw(shape);
                window.display();
                break;

            default:
                menu(ev);
                break;
        }
    }

    return 0;
}