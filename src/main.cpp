#include "Boid.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"
#include <cstdlib>
#include <stdlib.h>
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

int main(int argc, char *argv[]) {
  { // Run the tests
    if (doctest::Context{}.run() != 0)
      return EXIT_FAILURE;
    // The CI does not have a GPU so it cannot run the rest of the code.
    const bool no_gpu_available =
        argc >= 2 &&
        strcmp(argv[1], "-nogpu") ==
            0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    if (no_gpu_available)
      return EXIT_SUCCESS;
  }

  // Actual app
  auto ctx = p6::Context{{.title = "ProgS4"}};
  ctx.maximize_window();

  std::vector<Boid> boids(100);

  float square_radius = 0.f;
  const std::string text = "test imgui";

  // initialisation des positions de boid
  for (auto &boid : boids) {
    boid.set_pos(
        glm::vec2(p6::random::number(-2, 2), p6::random::number(-1, 1)));
  }

  // initialisation magnitude

  float cohesion_magnitude = 1.f;
  float alignment_magnitude = 1.f;
  float separation_magnitude = 1.f;

  // Declare your infinite update loop.
  ctx.update = [&]() {
    // Clear the background with a fading effect
    ctx.use_stroke = false;
    ctx.fill = {0.2f, 0.1f, 0.3f, 0.1f};
    // ctx.fill = {p6::random::number(-1, 0.5), p6::random::number(-1, 0.5),
    //             p6::random::number(-1, 0.5)}; // random
    ctx.rectangle(p6::FullScreen{});

    // ctx.background({0.2f, 0.1f, 0.3f});
    // ctx.fill = {1.f, 0.7f, 0.2f};
    // ctx.fill = {p6::random::number(0.5, 1), p6::random::number(0.5, 1),
    //             p6::random::number(0.5, 1)}; // random

    ImGui::Begin("Test");
    ImGui::SliderFloat("Cohesion Magnitude", &cohesion_magnitude, 0.f, 10.f);
    ImGui::SliderFloat("Aligment Magnitude", &alignment_magnitude, 0.f, 10.f);
    ImGui::SliderFloat("Separation Magnitude", &separation_magnitude, 0.f,
                       10.f);
    ImGui::End();

    for (auto &boid : boids) {
      boid.update_direction(boids);
      boid.update_velocity();
      boid.update_position(ctx.delta_time(), ctx.aspect_ratio());

      ctx.fill = {p6::random::number(0.5, 1), p6::random::number(0.5, 1),
                  p6::random::number(0.5, 1)};
      ctx.circle(p6::Center{boid.get_pos().x, boid.get_pos().y},
                 p6::Radius{0.01f});
    }
  };

  // Should be done last. It starts the infinite loop.
  ctx.start();
}