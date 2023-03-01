#pragma once

class Boid {
private:
  // attributes
  float m_x;
  float m_y;
  float m_angle;

public:
  /* CONSTRUCTORS */
  Boid() : m_x(0), m_y(0), m_angle(0){};
  Boid(float x, float y, float angle) : m_x(x), m_y(y), m_angle(angle){};
  Boid(float x) : m_x(x), m_y(x), m_angle(0){};
};