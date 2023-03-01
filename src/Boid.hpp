
#include "glm/fwd.hpp"
#include "p6/p6.h"

#pragma once

class Boid {
private:
    // attributes
    glm::vec2 m_pos;   // position
    glm::vec2 m_vel;   // velocity
    glm::vec2 m_acc;   // acceleration
    float     m_angle; // direction

public:
    /* CONSTRUCTORS */
    Boid()
        : m_pos(0), m_vel(0), m_acc(0){};
    Boid(glm::vec2 position)
        : m_pos(position), m_vel(0), m_acc(0){};

    /* DESTRUCTOR */
    ~Boid();

    /* GETTEUR */
    glm::vec2 get_pos() { return m_pos; }
    glm::vec2 get_vel() { return m_vel; }

    /* SETTEUR */
    void set_pos(glm::vec2 position) { m_pos = position; }

    /* BOID VELOCITY */

    void update_position(float delta_time);
    void update_velocity();
    void update_acceleration();

    /* BOID RULES */

    // Cohesion
    //  ...

    // Separation
    //...

    // Alignment
    //...

    /* BOID WITH WINDOW */
    float stay_in_window();
};