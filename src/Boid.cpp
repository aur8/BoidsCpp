#include "Boid.hpp"
#include "glm/common.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "p6/p6.h"
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <stdlib.h>
#include <vector>

void Boid::update_position(float delta_time, float ratio) {
  m_pos.x += m_vel.x * 2 * delta_time;
  m_pos.y += m_vel.y * 2 * delta_time;

  m_pos.x = stay_in_world(m_pos.x, ratio, -ratio);
  m_pos.y = stay_in_world(m_pos.y, 1.f, -1.f);
}

void Boid::update_velocity() {
  m_vel = glm::vec2(0.1, 0.1) * glm::normalize(m_direction);
}

// void Boid::update_direction(const std::vector<Boid> &boids) {
//   m_direction += this->cohesion(boids) + this->alignment(boids) +
//                  this->separation(boids) + p6::random::direction();
// }

// test separation
// void Boid::update_direction(const std::vector<Boid> &boids) {
//   m_direction += this->separation(boids) + p6::random::direction();
// }

// test alignement
void Boid::update_direction(const std::vector<Boid> &boids) {
  m_direction += this->alignment(boids);
}
float Boid::stay_in_world(const float &value, const float &max,
                          const float &min) {
  if (value >= max) {
    return -value;
  }
  if (value <= min) {
    return -value;
  }

  return value;
}

std::vector<Boid> Boid::get_neighbors(const std::vector<Boid> &boids,
                                      const float &distance_max) {
  std::vector<Boid> neighbors;
  for (auto other_boid : boids) {
    if (&other_boid != this) {
      if (glm::distance(other_boid.get_pos(), m_pos) <= distance_max) {
        neighbors.push_back(other_boid);
      }
    }
  }

  return neighbors;
}

glm::vec2 Boid::cohesion(const std::vector<Boid> &boids) {
  // find the neighbors
  std::vector<Boid> neighbors = get_neighbors(boids, 0.5f);

  // initialise our cohesion vector
  glm::vec2 coh(0.f, 0.f);

  // verify if the boid have neighbors
  if (neighbors.empty()) {
    return coh;
  }
  // apply cohesion to all neighbors
  for (auto other : neighbors) {
    coh += other.get_pos();
  }

  // divise by the number of neighbors
  coh /= (float)neighbors.size();

  // obtain a final vector
  coh -= m_pos;

  return glm::normalize(coh);
}

glm::vec2 Boid::alignment(const std::vector<Boid> &boids) {
  // find the neighbors
  std::vector<Boid> neighbors = get_neighbors(boids, 0.5f);

  // initialise our alignment vector
  glm::vec2 ali(0.f, 0.f);

  // verify if the boid have neighbors
  if (neighbors.empty()) {
    return ali;
  }
  // apply cohesion to all neighbors
  for (auto other : neighbors) {
    ali += other.get_pos();
  }

  // divise by the number of neighbors
  ali /= (float)neighbors.size();

  return glm::normalize(ali);
}

glm::vec2 Boid::separation(const std::vector<Boid> &boids) {
  // find the neighbors
  std::vector<Boid> neighbors = get_neighbors(boids, 0.5f);

  // initialise our separation vector
  glm::vec2 sep(0.f, 0.f);

  // verify if the boid have neighbors
  if (neighbors.empty()) {
    return sep;
  }

  for (auto other : neighbors) {
    glm::vec2 towardsMe;
    towardsMe = this->get_pos() - other.get_pos();

    if (length(towardsMe) > 0) {
      sep += glm::normalize(towardsMe) / length(towardsMe);
    }
  }
  return glm::normalize(sep);
}
