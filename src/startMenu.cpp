using namespace sf;

void menu(Event ev) {
    while (window.pollEvent(ev)) {
        if (ev.type == sf::Event::Closed)
            window.close();
    }
}