#include <SFML/Graphics.hpp>

#include "src/game.cpp"
#include "src/initializeVariables.cpp"
#include "src/players.cpp"
#include "src/settings.cpp"
#include "src/startMenu.cpp"
#include "src/rockets.cpp"

int main() {
    initializeVar();
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);

    // Fontes
    font.loadFromFile("src/assets/fonts/Montserrat.OTF");

    while (window.isOpen()) {
        // "Loop" do menu
        switch (controlPanel) {
            case 0:
                game();
                break;

            case 1:
                settings();
                break;

            case 2:
                window.close();
                break;

            default:
                menu();
                break;
        }
    }

    return 0;
}