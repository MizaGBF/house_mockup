#include <SFML/Graphics.hpp>
#include <string>
#include "sprites.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Test");
    window.setFramerateLimit(30);
    Sprites sprites;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sprites.update();

        window.clear(sf::Color::Black);
        sprites.draw(window);
        window.display();
    }

    return 0;
}
