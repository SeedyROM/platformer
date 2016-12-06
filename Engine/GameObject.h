#pragma once
#include <SFML/Graphics.hpp>

class GameObject : public sf::Sprite {
public:
  GameObject() : sf::Sprite() {}
  virtual ~GameObject() {}

  sf::Vector2f getVelocity() const { return m_velocity; }
  void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }
  void setVelocity(float x, float y) { m_velocity = sf::Vector2f(x, y); }

  int loadSprite(std::string location) {
    if(!m_texture.loadFromFile(location)) return -1;
    setTexture(m_texture);
    setOrigin(sf::Vector2f(getTextureRect().width / 2,
                           getTextureRect().height / 2));
    return  0;
  }
  int loadSprite(sf::Texture &texture) {
    setTexture(texture);
    setOrigin(sf::Vector2f(getTextureRect().width / 2,
                           getTextureRect().height / 2));
    return  0;
  }

  void destroy() { m_destroyed = true; }
  bool isDestroyed() { return m_destroyed; }

  int getDepth() { return m_depth; }
  void setDepth(int depth) { m_depth = depth; }

  void drawDebugRect() {
    sf::Vector2f bounds = sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height);
    sf::RectangleShape debug(bounds);
    debug.setFillColor(sf::Color(255, 255, 255, 0));
    debug.setOutlineThickness(2);
    debug.setOutlineColor(sf::Color(0, 255, 40));
    debug.setPosition(getPosition() - (bounds / 2.f));
    GSGetWindow->draw(debug);
  }

  virtual void update(sf::Time) {}

protected:
  void _update(sf::Time delta) {
    setPosition(getPosition() + (getPosition() - m_oldPosition + getVelocity() * (float)delta.asSeconds() * 2.0f));
    m_oldPosition = getPosition();
  }

private:
  sf::Vector2f m_oldPosition;
  sf::Vector2f m_velocity;
  sf::Texture  m_texture;
  int          m_depth = 0;
  bool         m_destroyed = false;
};
