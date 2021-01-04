#include <visualizer/pathfinder_app.h>

namespace pathfinder {

namespace visualizer {

PathfinderApp::PathfinderApp()
    : grid_(glm::vec2(kMargin, kMargin), kImageDimension,
            kWindowSize - 2 * kMargin) {
  ci::app::setWindowSize((int)kWindowSize, (int)kWindowSize);
}

void PathfinderApp::draw() {
  ci::Color8u background_color(0, 0, 0);
  ci::gl::clear(background_color);

  grid_.Draw();
}

void PathfinderApp::update() {
  grid_.Update();
}

void PathfinderApp::mouseDown(ci::app::MouseEvent event) {
  grid_.HandleBrush(event.getPos());
}

void PathfinderApp::mouseDrag(ci::app::MouseEvent event) {
  grid_.HandleBrush(event.getPos());
}

void PathfinderApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RETURN:
      grid_.SetState(true);
      break;

    case ci::app::KeyEvent::KEY_DELETE:
      grid_.Clear();
      grid_.SetState(false);
      break;

    case ci::app::KeyEvent::KEY_0:
      grid_.SetDrawState(0);
      break;

    case ci::app::KeyEvent::KEY_1:
      grid_.SetDrawState(1);
      break;

    case ci::app::KeyEvent::KEY_2:
      grid_.SetDrawState(2);
      break;

    case ci::app::KeyEvent::KEY_3:
      grid_.SetDrawState(3);
      break;
  }
}

}  // namespace visualizer

}  // namespace pathfinder
