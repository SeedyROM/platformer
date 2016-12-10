#pragma once

inline void psuedoClear(sf::RenderWindow &window, sf::Color color, int opacity) {
  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
  rectangle.setFillColor(sf::Color(color.r,color.g,color.b, opacity));
  window.draw(rectangle);
}

inline float clamp(float n, float lower, float upper) {
  return std::max(lower, std::min(n, upper));
}

inline float randFloat() {
  return ((float) rand() / (RAND_MAX)) + 1;
}

template<typename T>
const int sign(T x) {
  if(x > 0)      { return  1; }
  else if(x < 0) { return -1; }
  return  0;
}
