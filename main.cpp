#include <SFML/Graphics.hpp>

#include "src/game.cpp"
#include "src/players.cpp"
#include "src/startMenu.cpp"

int main() {
    int controlPanel = 1;
    CircleShape shape(200.f);
    shape.setFillColor(Color::Black);

    font.loadFromFile("src/assets/fonts/Montserrat.OTF");

    window.setKeyRepeatEnabled(false);

    // Fontes

    while (window.isOpen()) {
        // "Loop" do menu
        switch (controlPanel) {
            case 0:
                window.clear(Color::White);
                window.draw(shape);
                window.display();
                break;

            default:
                menu();
                break;
        }
    }

    return 0;
}