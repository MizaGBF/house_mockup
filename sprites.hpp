#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SFML/Graphics.hpp>
#include <random>

class Sprites
{
    public:
        Sprites();
        ~Sprites();
        void update();
        void draw(sf::RenderWindow& window);

    protected:
        // font
        sf::Font font;
        // background stuff
        sf::Texture bg_t[3];
        sf::Sprite bg_s[3];
        // sietes
        sf::Texture tex;
        sf::Sprite spr[3];
        sf::Sprite* sorted[3];
        // siete statuses and text
        sf::Text txt[3];
        int states[3];
        bool flipped[3];
        int mvcount[3];
        sf::Vector2f target[3];
        // rng stuff
        std::mt19937_64 gen;
        std::uniform_int_distribution<unsigned int> dis;
};

#endif // SPRITE_HPP
