#pragma once
#include <vector>
#include <typeinfo>
#include <csignal>

#include "SFML/Graphics.hpp"
#include "AABB.h"

namespace Physics {
  template<typename T>
  struct QuadTree {
    static const int maxNodeCapacity = 4;
    AABB bounds;
    QuadTree *nodes[4];
    std::vector<T> objects;

    enum Node { NW, NE,
                SW, SE };

    QuadTree() : nodes() {}
    QuadTree(AABB _bounds) : bounds(_bounds), nodes() {}

    bool insert(T object) {
      if(!bounds.intersects(object))
        return false;

      if(objects.size() < maxNodeCapacity) {
        objects.push_back(object);
        return true;
      }

      if(nodes[Node::NW] == nullptr) {
        subdivide();
      }

      if(nodes[Node::NW]->insert(object)) return true;
      if(nodes[Node::NE]->insert(object)) return true;
      if(nodes[Node::SW]->insert(object)) return true;
      if(nodes[Node::SE]->insert(object)) return true;

      return false;
    }

    std::vector<T> queryRange(const AABB range) {
      std::vector<T> pointsInRange;

      if(!bounds.intersects(range))
        return pointsInRange;

      for(unsigned int i = 0; i < objects.size(); i++) {
        if(range.intersects(objects[i]))
          pointsInRange.push_back(objects[i]);
      }

      if(nodes[Node::NW] == nullptr)
        return pointsInRange;


      for(int i = 0; i < 4; i++) {
        for(T &n : nodes[i]->queryRange(range)) {
          pointsInRange.push_back(n);
        }
      }

      // pointsInRange.push_back(nodes[Node::NW]->queryRange(range));
      // pointsInRange.push_back(nodes[Node::NE]->queryRange(range));
      // pointsInRange.push_back(nodes[Node::SW]->queryRange(range));
      // pointsInRange.push_back(nodes[Node::SE]->queryRange(range));

      bounds.drawDebugRect();
      return pointsInRange;
    }

    void subdivide() {
      nodes[Node::NW] = new QuadTree(
        AABB(
          bounds.left, bounds.top,
          bounds.width / 2, bounds.height / 2
        )
      );
      nodes[Node::NE] = new QuadTree(
        AABB(
          bounds.left + (bounds.width / 2), bounds.top,
          bounds.width / 2, bounds.height / 2
        )
      );
      nodes[Node::SW] = new QuadTree(
        AABB(
          bounds.left, bounds.top + (bounds.height / 2),
          bounds.width / 2, bounds.height / 2
        )
      );
      nodes[Node::SE] = new QuadTree(
        AABB(
          bounds.left + (bounds.width / 2), bounds.top + (bounds.height / 2),
          bounds.width / 2, bounds.height / 2
        )
      );
    }

    void draw() {}

  };
}
