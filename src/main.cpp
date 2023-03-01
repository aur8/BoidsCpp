#include <stdlib.h>
#include <cstdlib>
#include "glm/fwd.hpp"
#include "p6/p6.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

int main(int argc, char* argv[])
{
    { // Run the tests
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        // The CI does not have a GPU so it cannot run the rest of the code.
        const bool no_gpu_available =
            argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    // Actual app
    auto ctx = p6::Context{{.title = "ProgS4"}};
    ctx.maximize_window();

    float x = 0.0f;
    float y = 0.0f;

    std::vector<glm::vec2> boids(100);
    std::vector<float>     directions(100);

    // initialisation des positions de boid
    for (auto& boid : boids)
    {
        x = p6::random::number(-2, 2);
        y = p6::random::number(-1, 1);

        boid = glm::vec2(x, y);

        directions.push_back(p6::random::number(-1, 1));
    }

    // Declare your infinite update loop.
    ctx.update = [&]() {
        // Clear the background with a fading effect
        ctx.use_stroke = false;
        ctx.fill       = {0.2f, 0.1f, 0.3f, 0.1f};
        ctx.rectangle(p6::FullScreen{});

        // ctx.background({0.2f, 0.1f, 0.3f});

        ctx.fill = {1.f, 0.7f, 0.2f};

        for (auto& boid : boids)
        {
            boid.x += p6::random::number(-0.1, 0.1) * ctx.delta_time();
            boid.y += p6::random::number(-0.1, 0.1) * ctx.delta_time();

            ctx.circle(p6::Center{boid.x, boid.y}, p6::Radius{0.05f});
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}