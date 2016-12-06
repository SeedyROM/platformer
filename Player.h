#pragma once
#include <algorithm>
#include "Engine/GameObject.h"
#include "Engine/Helpers/Misc.h"

class Player : public GameObject {
public:
  float movementSpeed = 250;
  float acceleration = 15;
  float damping = 0.91;


  void update(sf::Time delta) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      setVelocity(getVelocity().x, getVelocity().y - acceleration);
      setVelocity(getVelocity().x, clamp(getVelocity().y, -movementSpeed, movementSpeed));
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      setVelocity(getVelocity().x, getVelocity().y + acceleration);
      setVelocity(getVelocity().x, clamp(getVelocity().y, -movementSpeed, movementSpeed));
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      setVelocity(getVelocity().x - acceleration, getVelocity().y);
      setVelocity(clamp(getVelocity().x, -movementSpeed, movementSpeed), getVelocity().y);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      setVelocity(getVelocity().x + acceleration, getVelocity().y);
      setVelocity(clamp(getVelocity().x, -movementSpeed, movementSpeed), getVelocity().y);
    }

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
       !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
       !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
       !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      setVelocity(getVelocity().x * damping, getVelocity().y * damping);
    }

    // Keep our player in the correction portion of the screen.
    //setPosition(clamp(getPosition().x, getGlobalBounds().width / 2, GSGetWindowSize.x - 80), clamp(getPosition().y,
    //                  getGlobalBounds().width / 2, GSGetWindowSize.y - (getGlobalBounds().height / 2)));

    _update(delta);
  }
};
