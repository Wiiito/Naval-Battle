#include <SFML/Graphics.hpp>

#include "src/game.cpp"
#include "src/players.cpp"
#include "src/startMenu.cpp"

int main() {
    int controlPanel = 1;
    window.setKeyRepeatEnabled(false);

    // Fontes
    font.loadFromFile("src/assets/fonts/Montserrat.OTF");

    while (window.isOpen()) {
        // "Loop" do menu
        switch (controlPanel) {
            case 0:

                break;

            default:
                menu();
                break;
        }
    }

    return 0;
}