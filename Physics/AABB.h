#pragma once
#include <array>
#include <SFML/Graphics.hpp>
#include "../Engine/Helpers/Misc.h"
#include "../Engine/GameObject.h"

namespace Physics {
  class Point : public sf::Vector2f {
  public:
    using sf::Vector2f::Vector2f;

    static inline float dot(const Point &a, const Point &b) { return (a.x*b.x) + (a.y*b.y); }
    static inline float dot(const sf::Vector2f &a, const sf::Vector2f &b) { return (a.x*b.x) + (a.y*b.y); }
    static inline float perpDot(const Point &a, const Point &b) { return (a.y*b.x) - (a.x*b.y); }
    static inline float perpDot(const sf::Vector2f &a, const sf::Vector2f &b) { return (a.y*b.x) - (a.x*b.y); }

    Point& operator=(const sf::Vector2f &rhs) {
      if (this == &rhs) return *this;

      this->x = rhs.x;
      this->y = rhs.y;

      return *this;
    }

    sf::Vector2f asVector() const {
      return sf::Vector2f(this->x, this->y);
    }
  }; // End Point.
  // Line typedef;
  typedef std::pair<Point, Point> Line;
  typedef std::array<Line, 4> RectSides;

  struct AABB : public sf::FloatRect {
    using sf::FloatRect::FloatRect;

    RectSides getGlobalSides() const {
      RectSides sides;
      sides[0] = Line(Point(left+0, top+0), Point(left+width, top+0));
      sides[1] = Line(Point(left+width, top+0), Point(left+width, top+height));
      sides[2] = Line(Point(left+width, top+height), Point(left+0, top+height));
      sides[3] = Line(Point(left+0, top+height), Point(left+0, left+0));
      return sides;
    }

    void drawDebugRect() {
      sf::Vector2f bounds = sf::Vector2f(width, height);
      sf::RectangleShape debug(bounds);
      debug.setFillColor(sf::Color(255, 255, 255, 0));
      debug.setOutlineThickness(2);
      debug.setOutlineColor(sf::Color(0, 255, 40));
      debug.setPosition(sf::Vector2f(left, top));
      GSGetWindow->draw(debug);
    }
  }; // End AABB.

  static bool lineCollision(const Point &a1, const Point &a2,
    const Point &b1, const Point &b2,
    Point *out)
  {
    Point a(a2-a1);
    Point b(b2-b1);
    Point c(b2-a2);

    // Check if lines are parallel.
    float f = Point::perpDot(a,b);
    if(!f) return false;

    float aa = Point::perpDot(a,c);
    float bb = Point::perpDot(b,c);

    if(f < 0)
    {
      if(aa > 0)     return false;
      if(bb > 0)     return false;
      if(aa < f)     return false;
      if(bb < f)     return false;
    }
    else
    {
      if(aa < 0)     return false;
      if(bb < 0)     return false;
      if(aa > f)     return false;
      if(bb > f)     return false;
    }

    if(out) *out = b * (1.0f - (aa / f)) + b1;
    return true;
  } // End lineCollision.

  static bool lineIntersectsAABB(const Line &l,
                             const AABB &a, Point *out)
  {
    RectSides sides = a.getGlobalSides();
    Point p;
    for(int i=0; i<4; i++) {
      //std::cout << sides[i].first.x << " : " << sides[i].first.y << std::endl;
      //std::cout << l.first.x << " : " << l.first.y << std::endl;
      if(lineCollision(l.first, l.second, sides[i].first, sides[i].second, &p)) {
        if(out) *out = p;
        return true;
      }
    }
    return false;
  } // End intersectsAABB.

  static sf::Vector2f AABBGetOverlap(const AABB &a, const AABB &b) {
    sf::Vector2f nullResult(0.f, 0.f);
    float xOverlap = 0.0f, yOverlap = 0.0f;

    // Test X direction.
    if(a.left+a.width < b.left || b.left+b.width < a.left) {
        return nullResult;
    } else {
        // get center X's of this and other box
        float thisCenterX = a.left + (a.left + a.width) / 2;
        float otherCenterX = b.left + (b.left + b.width) / 2;

        if(thisCenterX < otherCenterX) {
            xOverlap = (a.left+a.width - b.left);
        } else {
            xOverlap = (b.left+a.width - a.left) * -1;
        }
    }

    // Test Y direction.
    if(a.top+a.height < b.top || b.top+b.height < a.top) {
        return nullResult;
    } else {
        // get center Y's of this and other box
        float thisCenterY = a.top + (a.top + a.height) / 2;
        float otherCenterY = b.top + (b.top + b.height) / 2;

        if(thisCenterY < otherCenterY) {
            yOverlap = (a.top+a.height - b.top);
        } else {
            yOverlap = (b.top+a.height - a.top) * -1;
        }
    }

    return sf::Vector2f((int)xOverlap, (int)yOverlap);
  }
} // End namespace.
