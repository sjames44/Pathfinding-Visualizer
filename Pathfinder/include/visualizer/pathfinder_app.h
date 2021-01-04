#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "grid.h"

namespace pathfinder {

namespace visualizer {

class PathfinderApp : public ci::app::App {
 public:
  PathfinderApp();

  void draw() override;
  void update() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

  const double kWindowSize = 875;
  const double kMargin = 25;
  const size_t kImageDimension = 28;

 private:
  Grid grid_;
};

}  // namespace visualizer

}  // namespace pathfinder
