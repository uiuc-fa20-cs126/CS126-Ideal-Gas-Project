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

class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

  void draw() override;

  void update() override;

  void mouseDown(ci::app::MouseEvent event) override;
  void mouseUp(ci::app::MouseEvent event) override;

        void mouseDrag(ci::app::MouseEvent event) override;

        void keyDown(ci::app::KeyEvent event) override;


    private:
  std::vector<Particle> particles_;
    };

}  // namespace idealgas
#endif //IDEAL_GAS_PFISTERFACTOR_IDEALGASAPP_H
