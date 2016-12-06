#include <cmath>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Engine/GameState.h"
#include "Engine/Stage.h"
#include "Physics/AABB.h"

#include "Player.h"
#include "Cloud.h"

#include "Engine/Helpers/Misc.h"
#include "Engine/GUI/Menu.h"

using namespace Physics;

int main()
{
    // TODO: Read config information from a file.

    // Window state and timers.
    GSInit(1000, 600, "Testing!");
    window.setVerticalSyncEnabled(true);

    // Debug level.
    Stage *level = new Stage();
    GSSetCurrentStage(level);

    Player *p1 = new Player();
    p1->setTextureRect(sf::IntRect(96*3, 0, 96, 96));
    p1->loadSprite("Resources/Images/ship.png");
    p1->setScale(0.75, 0.75);
    p1->setPosition(350, GSGetWindowSize.y/2);
    level->addObjectToStage(5, p1);

    GameObject *p2 = new GameObject();
    p2->setTextureRect(sf::IntRect(96*3, 0, 96, 96));
    p2->loadSprite("Resources/Images/ship.png");
    p2->setScale(0.75, 0.75);
    p2->setPosition(500, GSGetWindowSize.y/2);
    level->addObjectToStage(5, p2);

    sf::Texture particleTexture;
    particleTexture.loadFromFile("Resources/Images/cloud.png");

    // Game loop...
    while (window.isOpen())
    {
        // Handle timers.
        deltaClock.restart();

        // Check for window events.
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Ctrl-C to quit.
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C) &&
           sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        {
          window.close();
        }

        psuedoClear(window, sf::Color(94, 152, 171),
                   (GSGetTime.asMilliseconds() <= 500) ? 255 : 200);

        if(GSGetTime.asMilliseconds() % 10 == 0 ) {
         for(int i=0; i < 4; i++) {
           Cloud *c = new Cloud();
           c->loadSprite(particleTexture);
           level->addObjectToStage(rand() % 5 + 1, c);
         }
        }

        sf::Vector2f overlap = AABBGetOverlap(
          (AABB)p1->getGlobalBounds(),
          (AABB)p2->getGlobalBounds()
        );
        if(overlap != sf::Vector2f(0, 0)) std::cout << overlap.x << " : " << overlap.y << "\n";


        GSGetCurrentStage->draw(window);
        p1->drawDebugRect();
        p2->drawDebugRect();

        window.display();
    }

    return 0;
}
