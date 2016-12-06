#pragma once
#include <functional>
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>

#include "GameObject.h"

class RenderQueue {
public:
  RenderQueue() {}
  RenderQueue(int depth) {
    m_depth = depth;
  }
  ~RenderQueue() {}

  void update(sf::Time delta) {}

  void draw(sf::RenderWindow &window) {
    for(auto &o : m_objectQueue) {
      if(o->isDestroyed()) {
        auto i = &o - &m_objectQueue[0];
        m_objectQueue.erase(m_objectQueue.begin() + i);
      }
      o->update(sf::seconds(1.f / GSGetMaxFPS)); // FIX THIS
      window.draw(*o);
    }
  }

  void addToQueue(GameObject *gameObject) {
    m_objectQueue.push_back(gameObject);
  }

  int getDepth() const { return m_depth; }
  void setDepth(int depth) { m_depth = depth; }
private:
  int m_depth = 0;
  std::vector<GameObject *> m_objectQueue;
};

struct CompareRenderQueueDepth : std::binary_function<RenderQueue*, RenderQueue*, bool> {
  bool operator()(RenderQueue *lhs, RenderQueue *rhs) const {
    return lhs->getDepth() > rhs->getDepth();
  }
};
typedef std::priority_queue<RenderQueue, std::deque<RenderQueue *>, CompareRenderQueueDepth> RenderPriorityQueue;
