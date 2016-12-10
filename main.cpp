#include <cmath>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Engine/GameState.h"
#include "Engine/Stage.h"
#include "Physics/AABB.h"
#include "Physics/QuadTree.h"

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

    Player p1;
    p1.setTextureRect(sf::IntRect(96*3, 0, 96, 96));
    p1.loadSprite("Resources/Images/ship.png");
    p1.setScale(0.75, 0.75);
    p1.setPosition(350, GSGetWindowSize.y/2);
    level->addObjectToStage(5, &p1);

    Line l(Point(0, 400), Point(900, 400));

    GameObject p2;
    p2.setTextureRect(sf::IntRect(96*3, 0, 96, 96));
    p2.loadSprite("Resources/Images/ship.png");
    //p2.setScale(1, 3);
    p2.setPosition(500, GSGetWindowSize.y/2);
    level->addObjectToStage(5, &p2);

    GameObject p3(p2);
    p3.setPosition(500, GSGetWindowSize.y/2 + 72);
    level->addObjectToStage(5, &p3);

    sf::Texture particleTexture;
    particleTexture.loadFromFile("Resources/Images/cloud.png");

    QuadTree<AABB> quadTree(AABB(0,0,2048,2048));

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

        psuedoClear(window, sf::Color(0, 20, 50),
                   (GSGetTime.asMilliseconds() <= 500) ? 255 : 140);

        if(GSGetTime.asMilliseconds() % 10 == 0 ) {
         for(int i=0; i < 4; i++) {
           Cloud *c = new Cloud();
           c->loadSprite(particleTexture);
           level->addObjectToStage(rand() % 5 + 1, c);
         }
        }

        if((int)GSGetTime.asMilliseconds() % 2 == 0) {
          AABB bounds = p1.getAABB();
          quadTree.insert(
            AABB(
              bounds.left+(bounds.width/2),
              bounds.top+(bounds.height/2),
              bounds.width,
              bounds.height
            )
          );
        }

        GSGetCurrentStage->draw(window);
        p1.getAABB().drawDebugRect();
        p2.getAABB().drawDebugRect();

        auto objects = quadTree.queryRange(AABB(0, 0, 1024, 1024));

        window.display();
    }

    return 0;
}
