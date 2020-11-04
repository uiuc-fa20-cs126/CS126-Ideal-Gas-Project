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
  /**
   * Our list of particles in the simulation
   */
  std::vector<Particle> particles_;
  /**
   * Whether or not the shift key is down, used as a keybind to move the physics window around
   */
  bool isShiftDown;
};

}  // namespace idealgas
#endif //IDEAL_GAS_PFISTERFACTOR_IDEALGASAPP_H
