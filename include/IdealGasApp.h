//
// Created by Eric Pfister on 11/3/20.
//

#ifndef IDEAL_GAS_PFISTERFACTOR_IDEALGASAPP_H
#define IDEAL_GAS_PFISTERFACTOR_IDEALGASAPP_H

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>
#include <vector>
#include <Particle.h>
#include <Histogram.h>
#include <ParticleSimulation.h>

namespace idealgas {

/**
 * The cinder application class
 */
class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

  /**
   * Called every frame to draw things to the screen
   */
  void draw() override;

  /**
   * Called every frame to update the program's state
   * Called before the draw method
   */
  void update() override;

  /**
   * Called when a mouse button is down
   * If the shift key is held down, moves the particle physics window's center to the mouse's location
   * @param event the mouse event
   */
  void mouseDown(ci::app::MouseEvent event) override;
  /**
   * Called when a mouse button is up
   * If the shift key isn't down and the left button is released, we perturb the simulation by adding small random velocities to each of the particles
   * @param event the mouse event
   */
  void mouseUp(ci::app::MouseEvent event) override;
  /**
   * Called when a mouse button is held and dragged
   * If the shift key is held down, moves the particle physics window's center to the mouse's location
   * @param event the mouse event
   */
  void mouseDrag(ci::app::MouseEvent event) override;

  /**
   * Called when a keyboard button is down
   * Sets the isShiftDown variable
   * @param event the keyboard event
   */
  void keyDown(ci::app::KeyEvent event) override;
  /**
   * Called when a keyboard button is up
   * Sets the isShiftDown variable
   * @param event the keyboard event
   */
  void keyUp(ci::app::KeyEvent event) override;

 private:
  const float HEAVY_PARTICLE_MASS = 200;
  const float MEDIUM_PARTICLE_MASS = 100;
  const float LIGHT_PARTICLE_MASS = 50;
  /**
   * Within the IdealGasApp constructor, each particle type (heavy, medium, light) is spawned PARTICLE_COUNT_OF_EACH_TYPE number of times
   * The total number of particles is then PARTICLE_COUNT_OF_EACH_TYPE * 3
   */
  const size_t PARTICLE_COUNT_OF_EACH_TYPE = 50;
  /**
   * Physics particle window within the app
   */
  ci::Rectf particle_window_ = ci::Rectf(375, 150, 775, 550);
  /**
   * Heavy histogram window within the app
   */
  ci::Rectf heavy_histogram_window_ = ci::Rectf(100, 50, 300, 150);
  /**
   * Medium histogram window within the app
   */
  ci::Rectf medium_histogram_window_ = ci::Rectf(100, 250, 300, 350);
  /**
   * Light histogram window within the app
   */
  ci::Rectf light_histogram_window_ = ci::Rectf(100, 450, 300, 550);
  /**
   * Our particle simulation handler
   */
  ParticleSimulation simulation_ = ParticleSimulation(cinder::Rectf());
  /**
   * Our list of histograms displayed with the simulation
   */
  std::vector<Histogram> histograms_;
  /**
   * Whether or not the shift key is down, used as a keybind to move the physics window around
   */
  bool isShiftDown;
  /**
   * Internal helper method to grab the speeds of particles with a certain mass
   * @param mass the mass to check against
   * @return a vector of speeds for particles with the passed in mass
   */
  std::vector<double> GetSpeedsOfParticlesWithMass(float mass);
};

}  // namespace idealgas
#endif //IDEAL_GAS_PFISTERFACTOR_IDEALGASAPP_H
