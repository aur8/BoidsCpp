#include "Boid.hpp"
#include <stdlib.h>
#include <cmath>
#include <cstdlib>
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "p6/p6.h"

void Boid::update_position(float delta_time, float ratio)
{
    m_pos.x += m_vel.x * 2 * delta_time;
    m_pos.y += m_vel.y * 2 * delta_time;

    m_pos.x = stay_in_world(m_pos.x, ratio, -ratio);
    m_pos.y = stay_in_world(m_pos.y, 1.f, -1.f);
}

void Boid::update_velocity()
{
    m_vel += glm::vec2(0.01, 0.01) * p6::random::direction();
}

float Boid::stay_in_world(const float& value, const float& max, const float& min)
{
    if (value >= max)
    {
        return -value;
    }
    if (value <= min)
    {
        return -value;
    }

    return value;
}

std::vector<Boid> Boid::get_neighbors(const std::vector<Boid>& boids, const float& distance_max)
{
    std::vector<Boid> neighbors;
    for (auto other_boid : boids)
    {
        if (&other_boid != this)
        {
            if (glm::distance(other_boid.get_pos(), m_pos) <= distance_max)
            {
                neighbors.push_back(other_boid);
                std::cout << "pushback neighbourg" << std::endl;
            }
        }
    }

    return neighbors;
}

glm::vec2 Boid::cohesion(const std::vector<Boid>& boids)
{
    // find the neighbors
    std::vector<Boid> neighbors = get_neighbors(boids, 0.3f);

    // initialise our cohesion vector
    glm::vec2 coh;

    // apply cohesion to all neighbors
    for (auto other : neighbors)
    {
        coh += other.get_pos();
    }

    // divise by the number of neighbors
    coh /= (float)neighbors.size();

    // obtain a final vector
    coh -= m_pos;

    return glm::normalize(coh);
}