#include <SFML/Graphics.hpp>

#include "src/game.cpp"
#include "src/players.cpp"
#include "src/startMenu.cpp"

int main() {
    window.setKeyRepeatEnabled(false);

    // Fontes
    font.loadFromFile("src/assets/fonts/Montserrat.OTF");

    while (window.isOpen()) {
        // "Loop" do menu
        switch (controlPanel) {
            case 0:
                game();
                break;

            case 2:
                window.close();

            default:
                menu();
                break;
        }
    }

    return 0;
}