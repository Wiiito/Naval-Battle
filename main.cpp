#include <SFML/Graphics.hpp>

#include "src/initializeVariables.cpp"
#include "src/game.cpp"
#include "src/bot.cpp"
#include "src/startMenu.cpp"
#include "src/settings.cpp"
#include "src/languageMenu.cpp"
#include "src/winScreen.cpp"
#include "src/loseScreen.cpp"

int main() {
    initializeVar();
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);

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
                languagePanel();
                break;

            case 3:
                window.close();
                break;

            case 4:
                menu();
                break;

            case 5:
                winScreen();
                break;

            case 6:
                loseScreen();
                break;
        }
    }

    return 0;
}