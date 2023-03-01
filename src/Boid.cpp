#include "Boid.hpp"
#include <stdlib.h>
#include <cstdlib>
#include "glm/fwd.hpp"
#include "p6/p6.h"

void Boid::update_position(float delta_time)
{
    m_pos.x += m_vel.x * 2 * delta_time;
    m_pos.y += m_vel.y * 2 * delta_time;
}

void Boid::update_velocity()
{
    m_vel += glm::vec2(0.01, 0.01) * p6::random::direction();
}

float stay_in_world(float value, float max, float min)
{
    if (value == max)
    {
        value = min;
    }
    if (value == min)
    {
        value = max;
    }
    return value;
}