#include "sprites.hpp"
#include <string>

Sprites::Sprites()
{
    std::random_device rd;
    gen = std::mt19937_64(rd());
    font.loadFromFile("font.ttf");
    std::string files[3] = {"bg_1.jpg", "img_30002.png", "img_40002.png"};
    for(int i = 0; i < 3; ++i)
    {
        bg_t[i].loadFromFile(files[i]);
        bg_s[i].setTexture(bg_t[i]);
        switch(i)
        {
            case 0:
                bg_s[i].setPosition(-50, -200);
                break;
            case 1:
                bg_s[i].setPosition(246-50, 300);
                break;
            case 2:
                bg_s[i].setPosition(246-60, 100);
                break;
        }
    }

    tex.loadFromFile("render.png");
    tex.setSmooth(true);
    for(int i = 0; i < 3; ++i)
    {
        spr[i].setTexture(tex);
        spr[i].setPosition(450+50*i, 365+50*i);
        spr[i].setOrigin(63, 209);
        spr[i].setScale(0.5, 0.5);
        states[i] = 2 + (dis(gen) % 50);
        flipped[i] = false;
        txt[i].setCharacterSize(20);
        txt[i].setFont(font);
        txt[i].setString(std::to_string(i));
        txt[i].setFillColor(sf::Color::White);
        txt[i].setPosition(450+50*i, 365+50*i);
        sorted[i] = &(spr[i]);
    }
}

Sprites::~Sprites()
{
    //dtor
}

void Sprites::update()
{
    for(int i = 0; i < 3; ++i)
    {
        switch(states[i])
        {
            case 0: // idle
            {
                sf::Vector2u t;
                while(true) // generate a random valid position
                {
                    t.x = 300 + (dis(gen) % 400);
                    t.y = 300 + (dis(gen) % 200);
                    if((t.x > 313 && t.x < 313+339 && t.y > 391 && t.y < 391+107) ||
                    (t.x > 424 && t.x < 424+117 && t.y > 335 && t.y < 335+225) ||
                    (t.x > 364 && t.x < 364+235 && t.y > 364 && t.y < 364+165))
                        break;
                }
                target[i] = {(float)t.x, (float)t.y};
                states[i] = 1;
                mvcount[i] = 0;
                break;
            }
            case 1: // moving
            {
                auto& pos = spr[i].getPosition();
                sf::Vector2f delta(target[i].x - pos.x, target[i].y - pos.y); // get delta to target destination
                if(delta.x < -2) delta.x = -2; // cap it
                else if(delta.x > 2) delta.x = 2;
                if(delta.y < -2) delta.y = -2;
                else if(delta.y > 2) delta.y = 2;
                spr[i].move(delta); // move
                mvcount[i]++;
                if(i == 1) // effect on sprite 1
                {
                    if(mvcount[i] % 6 < 3) spr[i].setOrigin(63, 209 + 2*(mvcount[i] % 6));
                    else spr[i].setOrigin(63, 209 + 2*(6 - mvcount[i] % 6));
                }
                else if(i == 2) // effect on sprite 2
                {
                    if(mvcount[i] % 6 < 3) spr[i].setScale(0.5 - 0.01*(mvcount[i] % 6), 0.5);
                    else spr[i].setScale(0.5 - 0.01*(6 - mvcount[i] % 6), 0.5);
                }
                txt[i].setPosition(spr[i].getPosition()); // update text pos
                if(spr[i].getPosition() == target[i]) // reset sprite and put to cooldown if destination reached
                {
                    states[i] = 2 + (dis(gen) % 50);
                    spr[i].setOrigin(63, 209);
                    spr[i].setScale(0.5, 0.5);
                }
                break;
            }
            default: // cooldown
                states[i]--;
                if(states[i] == 1) states[i] = 0;
                break;
        }
    }
    for(int i = 0; i < 2; ++i) // sort sprite by Y position
    {
        for(int j = 1; j < 3; ++j)
        {
            if(sorted[i]->getPosition().y > sorted[j]->getPosition().y)
            {
                sf::Sprite* p = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = p;
            }
        }
    }
}

void Sprites::draw(sf::RenderWindow& window) // draw bg, siete and then text
{
    for(int i = 0; i < 3; ++i)
        window.draw(bg_s[i]);
    for(int i = 0; i < 3; ++i)
        window.draw(*(sorted[i]));
    for(int i = 0; i < 3; ++i)
        window.draw(txt[i]);
}
