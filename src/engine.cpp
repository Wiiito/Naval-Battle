using namespace sf;

void render() {
    RenderWindow window(VideoMode(800, 600), "SFML works!", Style::Titlebar | Style::Close);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);
        window.display();
    }
}