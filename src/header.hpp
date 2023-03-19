// Header archive
#pragma once // To reduce build times to 1 only
#include <SFML/Graphics.hpp>
using namespace sf;

class DoubleBoat {
    private:
    /* data */

    public:
    DoubleBoat(/* args */);
    ~DoubleBoat();
};


class TripleBoat {
    private:
    /* data */

    public:
    TripleBoat(/* args */);
    ~TripleBoat();
};

class QuadraBoat {
    private:
    /* data */

    public:
    QuadraBoat(/* args */);
    ~QuadraBoat();
};

class QuintaBoat {
    private:
    /* data */

    public:
    QuintaBoat(/* args */);
    ~QuintaBoat();
};

class Player {
    private:
    /* data */

    public:
    Player(/* args */);
    ~Player();
};

RenderWindow window(VideoMode(800, 600), "Naval Battle", Style::Titlebar | Style::Close);
Event event;
Player player;