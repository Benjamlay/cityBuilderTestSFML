﻿#include "motion/a_star.h"

#include <iostream>
#include <queue>
#include <span>

using namespace core::motion;

namespace motion::Astar {
  struct aStarNode {
    sf::Vector2f position;
    float g;
    float h;
    float f;

    aStarNode* previous_node;

    aStarNode(sf::Vector2f position, float g, float h, aStarNode* prev) : position(position),
                                                                          g(g),
                                                                          h(h),
                                                                          f(g + h),
                                                                          previous_node(prev)
    {
    }

    friend bool operator<(aStarNode const &left, aStarNode const &right){
      return left.f > right.f;
    }
};

  float heuristic(sf::Vector2f p1, sf::Vector2f p2){
    return (p2 - p1).length();
  }

  std::array<sf::Vector2f, 4> neighbours = {
    sf::Vector2f(0, 16),
    sf::Vector2f(16, 0),
    sf::Vector2f(0, -16),
    sf::Vector2f(-16, 0)
  };

  Path ReconstitutePath(aStarNode &start_node){
    Path path;
    std::vector<sf::Vector2f> pathPoints;
    aStarNode *current_node = &start_node;

    while (current_node != nullptr) {
      pathPoints.emplace_back(current_node->position);
      current_node = current_node->previous_node;
    }

    std::reverse(pathPoints.begin(), pathPoints.end());
    path.Fill(pathPoints);

    return path;
  }

  Path GetPath(sf::Vector2f start, sf::Vector2f end, std::span<const sf::Vector2f> walkableTiles) {
    Path aStarPath;

    //Are start / end point in walkables tiles ?
    auto f = std::find(walkableTiles.begin(), walkableTiles.end(), start);
    if (f == walkableTiles.end()) {
      return aStarPath;
    }

    auto g = std::find(walkableTiles.begin(), walkableTiles.end(), end);
    if (g == walkableTiles.end()) {
      return aStarPath;
    }

    // ---------------------------------------------
    std::vector<aStarNode> closedList;

    std::priority_queue<aStarNode> openList;
    openList.push(aStarNode(start, 0, heuristic(start, end), nullptr));

    while (!openList.empty()) {
      aStarNode currentNode = openList.top();
      openList.pop();


      if (currentNode.position == end) {
        return ReconstitutePath(currentNode);
      }

      for (auto neighbour: neighbours) {
        sf::Vector2f newPosition = currentNode.position + neighbour;
        auto f = std::find(walkableTiles.begin(), walkableTiles.end(), newPosition);

        if (f != walkableTiles.end()) {

          auto g = std::find_if(
              closedList.begin(),
              closedList.end(),
                              [&newPosition](const aStarNode &n) {
                                return newPosition == n.position;
                              }
          );

          // new node
          aStarNode newNode = aStarNode(
              newPosition,
              currentNode.g + 1,
              heuristic(newPosition, end),
              new aStarNode(currentNode)
          );

          if (g == closedList.end()) {
            openList.push(newNode);
          }
          closedList.emplace_back(newNode);
        }
      }
    }
    return aStarPath;
  }
}