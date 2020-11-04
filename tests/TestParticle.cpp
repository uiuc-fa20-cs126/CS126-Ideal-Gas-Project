//
// Created by Eric Pfister on 11/3/20.
//

#define CATCH_CONFIG_MAIN

#include <Particle.h>
#include <catch2/catch.hpp>
#include <vector>

using namespace idealgas;
using namespace cinder;
using glm::vec2;
using std::vector;

void DoParticleUpdateStep(vector<Particle> &vec) {
  for (Particle &p : vec) {
    p.update(vec);
  }
}
TEST_CASE("Two particles Head on x-collision") {
  Particle::SetGlobalPhysicsBounds(Rectf(0, 0, 300, 100));
  vector<Particle> particles;
  particles.push_back(Particle(50, vec2(50, 50), vec2(10, 0)));
  particles.push_back(Particle(50, vec2(250, 50), vec2(-10, 0)));
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
    if (i <= 4) {
      REQUIRE(particles[0].isMovingTowards(particles[1]));
      REQUIRE(particles[1].isMovingTowards(particles[0]));
      REQUIRE(particles[0].position.x == 50 + 10 * i);
      REQUIRE(particles[1].position.x == 250 - 10 * i);
      REQUIRE(particles[0].velocity.x > 0);
      REQUIRE(particles[1].velocity.x < 0);
    } else {
      REQUIRE(!particles[0].isMovingTowards(particles[1]));
      REQUIRE(!particles[1].isMovingTowards(particles[0]));
      REQUIRE(particles[0].position.x == 100 - 10 * (i - 5));
      REQUIRE(particles[1].position.x == 200 + 10 * (i - 5));
      REQUIRE(particles[0].velocity.x < 0);
      REQUIRE(particles[1].velocity.x > 0);
    }
    DoParticleUpdateStep(particles);
  }
}
TEST_CASE("Two particles head on y-collision") {
  Particle::SetGlobalPhysicsBounds(Rectf(0, 0, 100, 300));
  vector<Particle> particles;
  particles.push_back(Particle(50, vec2(50, 50), vec2(0, 10)));
  particles.push_back(Particle(50, vec2(50, 250), vec2(0, -10)));
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
    if (i <= 4) {
      REQUIRE(particles[0].isMovingTowards(particles[1]));
      REQUIRE(particles[1].isMovingTowards(particles[0]));
      REQUIRE(particles[0].position.y == 50 + 10 * i);
      REQUIRE(particles[1].position.y == 250 - 10 * i);
      REQUIRE(particles[0].velocity.y > 0);
      REQUIRE(particles[1].velocity.y < 0);
    } else {
      REQUIRE(!particles[0].isMovingTowards(particles[1]));
      REQUIRE(!particles[1].isMovingTowards(particles[0]));
      REQUIRE(particles[0].position.y == 100 - 10 * (i - 5));
      REQUIRE(particles[1].position.y == 200 + 10 * (i - 5));
      REQUIRE(particles[0].velocity.y < 0);
      REQUIRE(particles[1].velocity.y > 0);
    }
    DoParticleUpdateStep(particles);
  }
}

TEST_CASE("Two particles head on xy collision") {
  Particle::SetGlobalPhysicsBounds(Rectf(0, 0, 300, 300));
  vector<Particle> particles;
  particles.push_back(Particle(50, vec2(50, 50), vec2(10, 10)));
  particles.push_back(Particle(50, vec2(250, 250), vec2(-10, -10)));
  for (size_t i = 0; i < 8; i++) {
    if (i <= 6) {
      REQUIRE(particles[0].isMovingTowards(particles[1]));
      REQUIRE(particles[1].isMovingTowards(particles[0]));

      REQUIRE(particles[0].position.x == 50 + 10 * i);
      REQUIRE(particles[0].position.y == 50 + 10 * i);

      REQUIRE(particles[1].position.x == 250 - 10 * i);
      REQUIRE(particles[1].position.y == 250 - 10 * i);

      REQUIRE(particles[0].velocity.x > 0);
      REQUIRE(particles[0].velocity.y > 0);

      REQUIRE(particles[1].velocity.x < 0);
      REQUIRE(particles[1].velocity.y < 0);
    } else {
      REQUIRE(!particles[0].isMovingTowards(particles[1]));
      REQUIRE(!particles[1].isMovingTowards(particles[0]));
      REQUIRE(particles[0].position.x == 120 - 10 * (i - 7));
      REQUIRE(particles[0].position.y == 120 - 10 * (i - 7));

      REQUIRE(particles[1].position.x == 200 + 10 * (i - 7));
      REQUIRE(particles[1].position.y == 200 + 10 * (i - 7));

      REQUIRE(particles[0].velocity.x < 0);
      REQUIRE(particles[0].velocity.y < 0);

      REQUIRE(particles[1].velocity.x > 0);
      REQUIRE(particles[1].velocity.y > 0);
    }
    DoParticleUpdateStep(particles);
  }
}

TEST_CASE("X Particle collision with right wall") {
  Particle::SetGlobalPhysicsBounds(Rectf(0, 0, 200, 100));
  vector<Particle> particles;
  particles.push_back(Particle(50, vec2(50, 50), vec2(10, 0)));
  for (size_t i = 0; i < 11; i++) {
    vec2 right_wall = vec2(200, particles[0].position.y);
    if (i <= 9) {
      REQUIRE(particles[0].isMovingTowards(right_wall));
      REQUIRE(particles[0].position.x == 50 + 10 * i);
      REQUIRE(particles[0].velocity.x > 0);
    } else {
      REQUIRE(!particles[0].isMovingTowards(right_wall));
      REQUIRE(particles[0].position.x == 150);
      REQUIRE(particles[0].velocity.x < 0);
    }
    DoParticleUpdateStep(particles);
  }
}
TEST_CASE("X Particle collision with left wall") {
  Particle::SetGlobalPhysicsBounds(Rectf(0, 0, 200, 100));
  vector<Particle> particles;
  particles.push_back(Particle(50, vec2(150, 50), vec2(-10, 0)));
  for (size_t i = 0; i < 11; i++) {
    vec2 left_wall = vec2(0, particles[0].position.y);
    if (i <= 9) {
      REQUIRE(particles[0].isMovingTowards(left_wall));
      REQUIRE(particles[0].position.x == 150 - 10 * i);
      REQUIRE(particles[0].velocity.x < 0);
    } else {
      REQUIRE(!particles[0].isMovingTowards(left_wall));
      REQUIRE(particles[0].position.x == 50);
      REQUIRE(particles[0].velocity.x > 0);
    }
    DoParticleUpdateStep(particles);
  }
}
TEST_CASE("Y Particle collision with bottom wall") {
  Particle::SetGlobalPhysicsBounds(Rectf(0, 0, 100, 200));
  vector<Particle> particles;
  particles.push_back(Particle(50, vec2(50, 50), vec2(0, 10)));
  for (size_t i = 0; i < 11; i++) {
    vec2 bottom_wall = vec2(particles[0].position.x, 200);
    if (i <= 9) {
      REQUIRE(particles[0].isMovingTowards(bottom_wall));
      REQUIRE(particles[0].position.y == 50 + 10 * i);
      REQUIRE(particles[0].velocity.y > 0);
    } else {
      REQUIRE(!particles[0].isMovingTowards(bottom_wall));
      REQUIRE(particles[0].position.y == 150);
      REQUIRE(particles[0].velocity.y < 0);
    }
    DoParticleUpdateStep(particles);
  }
}
TEST_CASE("Y Particle collision with top wall") {
  Particle::SetGlobalPhysicsBounds(Rectf(0, 0, 100, 200));
  vector<Particle> particles;
  particles.push_back(Particle(50, vec2(50, 150), vec2(0, -10)));
  for (size_t i = 0; i < 11; i++) {
    vec2 top_wall = vec2(particles[0].position.x, 0);
    if (i <= 9) {
      REQUIRE(particles[0].isMovingTowards(top_wall));
      REQUIRE(particles[0].position.y == 150 - 10 * i);
      REQUIRE(particles[0].velocity.y < 0);
    } else {
      REQUIRE(!particles[0].isMovingTowards(top_wall));
      REQUIRE(particles[0].position.y == 50);
      REQUIRE(particles[0].velocity.y > 0);
    }
    DoParticleUpdateStep(particles);
  }
}
