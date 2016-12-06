#pragma once
#include "Engine/GameObject.h"

class Cloud : public GameObject {
public:
  Cloud() {
    setPosition(GSGetWindowSize.x + 500, rand() % GSGetWindowSize.y);
    setVelocity(-(rand() % 600 + 360), getVelocity().y);
    setScale(randFloat() * 1.3f, randFloat() * 1.3f);
    //setScale(getScale().x * 0.75, getScale().y * 0.75);
    setColor(sf::Color(255, 255, 255, 128 + randFloat() * 128 ));
  }
  void update(sf::Time delta) {
    //int ms = life.getElapsedTime().asMilliseconds();
    if(getPosition().x <= -getGlobalBounds().width-20) destroy();
    _update(delta);
  }
private:
  sf::Clock life;
  int size = 0;
};
