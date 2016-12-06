#pragma once
#include <list>
#include <functional>
#include <iostream>

class MenuItem {
public:
  MenuItem() {}
  MenuItem(const std::string text) {
    m_text = text;
  }
  MenuItem(const std::string text, std::function<void()> action) {
    m_text = text;
    m_function = action;
  }

  void setAction(std::function<void()> action) {
    m_function = action;
  }
  void runAction() {
    m_function();
  }

  void setSelected(bool selected) { m_selected = selected; }
  bool isSelected() { return m_selected;
  }
private:
  std::function<void()> m_function;
  bool m_selected = false;
  std::string m_text;
};

class Menu {
public:
  Menu() {}
  virtual ~Menu() {}

  MenuItem &getSelectedItem() {
    return *m_itemsIterator;
  }
  void addMenuItem(MenuItem &item) {
    m_items.push_back(item);
    if (m_items.size() <= 1) m_itemsIterator = m_items.begin();
  }
  void activateItem() {
    m_itemsIterator->runAction();
  }

  void selectNextItem() {
    m_itemsIterator->setSelected(false);
    if(m_itemsIterator == m_items.end()) {
      m_itemsIterator = m_items.begin();
    } else {
      ++m_itemsIterator;
    }
    m_itemsIterator->setSelected(true);
  }
  void selectLastItem() {
    m_itemsIterator->setSelected(false);
    if(m_itemsIterator == m_items.begin()) {
      m_itemsIterator = m_items.end();
    } else {
      --m_itemsIterator;
    }
    m_itemsIterator->setSelected(true);
  }
private:
  std::list<MenuItem> m_items;
  std::list<MenuItem>::iterator m_itemsIterator;
};
