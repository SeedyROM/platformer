#pragma once
#include <functional>
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>

#include "RenderQueue.h"

class Stage {
public:
  Stage() { }
  virtual ~Stage() {}

  void draw(sf::RenderWindow &window) {
    RenderPriorityQueue queue(m_renderQueues);
    while(!queue.empty()) {
      queue.top()->draw(window);
      queue.pop();
    }
  }

  void addRenderQueue(RenderQueue *renderQueue) {
    m_renderQueues.push(renderQueue);
  }

  void addObjectToStage(int depth, GameObject *gameObject) {
    // If there are no render queues make one!
    if(m_renderQueues.empty()) {
      RenderQueue *queue = new RenderQueue(depth);
      queue->addToQueue(gameObject);
      m_renderQueues.push(queue);
      return; // Escape!
    }
    // Add to existing queue..
    RenderPriorityQueue queues(m_renderQueues);
    while(!queues.empty()) {
      if(queues.top()->getDepth() == depth) {
        queues.top()->addToQueue(gameObject);
        return; // Exit because we've found our match.
      } else {
        queues.pop();
      }
    }
    // Or create a new queue at depth.
    RenderQueue *queue = new RenderQueue(depth);
    queue->addToQueue(gameObject);
    m_renderQueues.push(queue);
  }

private:
  RenderPriorityQueue m_renderQueues;
};
