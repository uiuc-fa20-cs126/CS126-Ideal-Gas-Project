//
// Created by Eric Pfister on 11/3/20.
//

#define CATCH_CONFIG_MAIN

#include <Particle.h>
#include <ParticleSimulation.h>
#include <catch2/catch.hpp>
#include <vector>

using namespace idealgas;
using namespace cinder;
using glm::vec2;
using std::vector;

TEST_CASE("Two particles Head on x-collision") {
  ParticleSimulation simulation(Rectf(0, 0, 300, 100));
  simulation.AddParticle(Particle(vec2(50, 50), vec2(10, 0), 50));
  simulation.AddParticle(Particle(vec2(250, 50), vec2(-10, 0), 50));
  /*
    Particles should move towards each other like so
    xPos1 | xPos2 | Towards/Away
    50 | 250 | (towards)
    60 | 240 | (towards)
    70 | 230 | (towards)
    80 | 220 | (towards)
    90 | 210 | (towards)
    100 | 200 | (away)
   */
  for (size_t i = 0; i < 7; i++) {
    auto particles = simulation.GetParticles();
    if (i <= 4) {
      REQUIRE(particles[0].IsMovingTowards(particles[1]));
      REQUIRE(particles[1].IsMovingTowards(particles[0]));
      REQUIRE(particles[0].position.x == 50 + 10 * i);
      REQUIRE(particles[1].position.x == 250 - 10 * i);
      REQUIRE(particles[0].velocity.x > 0);
      REQUIRE(particles[1].velocity.x < 0);
    } else {
      REQUIRE(!particles[0].IsMovingTowards(particles[1]));
      REQUIRE(!particles[1].IsMovingTowards(particles[0]));
      REQUIRE(particles[0].position.x == 100 - 10 * (i - 5));
      REQUIRE(particles[1].position.x == 200 + 10 * (i - 5));
      REQUIRE(particles[0].velocity.x < 0);
      REQUIRE(particles[1].velocity.x > 0);
    }
    simulation.Update();
  }
}
TEST_CASE("Two particles head on y-collision") {
  ParticleSimulation simulation(Rectf(0, 0, 100, 300));
  simulation.AddParticle(Particle(vec2(50, 50), vec2(0, 10), 50));
  simulation.AddParticle(Particle(vec2(50, 250), vec2(0, -10), 50));
  /*
   Particles should move towards each other like so
    yPos1 | yPos2 | Towards/Away
    50 | 250 | (towards)
    60 | 240 | (towards)
    70 | 230 | (towards)
    80 | 220 | (towards)
    90 | 210 | (towards)
    100 | 200 | (away)
   */
  for (size_t i = 0; i < 7; i++) {
    auto particles = simulation.GetParticles();
    if (i <= 4) {
      REQUIRE(particles[0].IsMovingTowards(particles[1]));
      REQUIRE(particles[1].IsMovingTowards(particles[0]));
      REQUIRE(particles[0].position.y == 50 + 10 * i);
      REQUIRE(particles[1].position.y == 250 - 10 * i);
      REQUIRE(particles[0].velocity.y > 0);
      REQUIRE(particles[1].velocity.y < 0);
    } else {
      REQUIRE(!particles[0].IsMovingTowards(particles[1]));
      REQUIRE(!particles[1].IsMovingTowards(particles[0]));
      REQUIRE(particles[0].position.y == 100 - 10 * (i - 5));
      REQUIRE(particles[1].position.y == 200 + 10 * (i - 5));
      REQUIRE(particles[0].velocity.y < 0);
      REQUIRE(particles[1].velocity.y > 0);
    }
    simulation.Update();
  }
}

TEST_CASE("Two particles head on xy collision") {
  ParticleSimulation simulation(Rectf(0, 0, 300, 300));
  simulation.AddParticle(Particle(vec2(50, 50), vec2(10, 10), 50));
  simulation.AddParticle(Particle(vec2(250, 250), vec2(-10, -10), 50));
  for (size_t i = 0; i < 8; i++) {
    auto particles = simulation.GetParticles();
    if (i <= 6) {
      REQUIRE(particles[0].IsMovingTowards(particles[1]));
      REQUIRE(particles[1].IsMovingTowards(particles[0]));

      REQUIRE(particles[0].position.x == 50 + 10 * i);
      REQUIRE(particles[0].position.y == 50 + 10 * i);

      REQUIRE(particles[1].position.x == 250 - 10 * i);
      REQUIRE(particles[1].position.y == 250 - 10 * i);

      REQUIRE(particles[0].velocity.x > 0);
      REQUIRE(particles[0].velocity.y > 0);

      REQUIRE(particles[1].velocity.x < 0);
      REQUIRE(particles[1].velocity.y < 0);
    } else {
      REQUIRE(!particles[0].IsMovingTowards(particles[1]));
      REQUIRE(!particles[1].IsMovingTowards(particles[0]));
      REQUIRE(particles[0].position.x == 120 - 10 * (i - 7));
      REQUIRE(particles[0].position.y == 120 - 10 * (i - 7));

      REQUIRE(particles[1].position.x == 200 + 10 * (i - 7));
      REQUIRE(particles[1].position.y == 200 + 10 * (i - 7));

      REQUIRE(particles[0].velocity.x < 0);
      REQUIRE(particles[0].velocity.y < 0);

      REQUIRE(particles[1].velocity.x > 0);
      REQUIRE(particles[1].velocity.y > 0);
    }
    simulation.Update();
  }
}

TEST_CASE("X Particle collision with right wall") {
  ParticleSimulation simulation(Rectf(0, 0, 200, 100));
  simulation.AddParticle(Particle(vec2(50, 50), vec2(10, 0), 50));
  for (size_t i = 0; i < 11; i++) {
    auto particles = simulation.GetParticles();
    vec2 right_wall = vec2(200, particles[0].position.y);
    if (i <= 9) {
      REQUIRE(particles[0].IsMovingTowards(right_wall));
      REQUIRE(particles[0].position.x == 50 + 10 * i);
      REQUIRE(particles[0].velocity.x > 0);
    } else {
      REQUIRE(!particles[0].IsMovingTowards(right_wall));
      REQUIRE(particles[0].position.x == 150);
      REQUIRE(particles[0].velocity.x < 0);
    }
    simulation.Update();
  }
}
TEST_CASE("X Particle collision with left wall") {
  ParticleSimulation simulation(Rectf(0, 0, 200, 100));
  simulation.AddParticle(Particle(vec2(150, 50), vec2(-10, 0), 50));
  for (size_t i = 0; i < 11; i++) {
    auto particles = simulation.GetParticles();
    vec2 left_wall = vec2(0, particles[0].position.y);
    if (i <= 9) {
      REQUIRE(particles[0].IsMovingTowards(left_wall));
      REQUIRE(particles[0].position.x == 150 - 10 * i);
      REQUIRE(particles[0].velocity.x < 0);
    } else {
      REQUIRE(!particles[0].IsMovingTowards(left_wall));
      REQUIRE(particles[0].position.x == 50);
      REQUIRE(particles[0].velocity.x > 0);
    }
    simulation.Update();
  }
}
TEST_CASE("Y Particle collision with bottom wall") {
  ParticleSimulation simulation(Rectf(0, 0, 100, 200));
  simulation.AddParticle(Particle(vec2(50, 50), vec2(0, 10), 50));
  for (size_t i = 0; i < 11; i++) {
    auto particles = simulation.GetParticles();
    vec2 bottom_wall = vec2(particles[0].position.x, 200);
    if (i <= 9) {
      REQUIRE(particles[0].IsMovingTowards(bottom_wall));
      REQUIRE(particles[0].position.y == 50 + 10 * i);
      REQUIRE(particles[0].velocity.y > 0);
    } else {
      REQUIRE(!particles[0].IsMovingTowards(bottom_wall));
      REQUIRE(particles[0].position.y == 150);
      REQUIRE(particles[0].velocity.y < 0);
    }
    simulation.Update();
  }
}
TEST_CASE("Y Particle collision with top wall") {
  ParticleSimulation simulation(Rectf(0, 0, 100, 200));
  simulation.AddParticle(Particle(vec2(50, 150), vec2(0, -10), 50));
  for (size_t i = 0; i < 11; i++) {
    auto particles = simulation.GetParticles();
    vec2 top_wall = vec2(particles[0].position.x, 0);
    if (i <= 9) {
      REQUIRE(particles[0].IsMovingTowards(top_wall));
      REQUIRE(particles[0].position.y == 150 - 10 * i);
      REQUIRE(particles[0].velocity.y < 0);
    } else {
      REQUIRE(!particles[0].IsMovingTowards(top_wall));
      REQUIRE(particles[0].position.y == 50);
      REQUIRE(particles[0].velocity.y > 0);
    }
    simulation.Update();
  }
}
