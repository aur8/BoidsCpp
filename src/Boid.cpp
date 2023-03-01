#include "Boid.hpp"
#include <stdlib.h>
#include <cstdlib>
#include "glm/fwd.hpp"
#include "p6/p6.h"

void Boid::update_position(float delta_time)
{
    m_pos.x += m_vel.x * 10 * delta_time;
    m_pos.y += m_vel.y * 10 * delta_time;
}

void Boid::update_velocity()
{
    m_vel.x = p6::random::number(-1, 1);
    m_vel.y = p6::random::number(-1, 1);
}