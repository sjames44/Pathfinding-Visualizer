#pragma once

#include "cinder/gl/gl.h"
#include "core/pathfinder.h"

namespace pathfinder {

namespace visualizer {

/**
 * A sketchpad which will be displayed in the Cinder application and respond to
 * mouse events. Furthermore, the sketchpad can output its current state in the
 * same format as the Naive Bayes image data files.
 */
class Grid {
 public:
  /**
   * Creates a sketchpad.
   * (Note that sketchpad pixels are larger than screen pixels.)
   *
   * @param top_left_corner     the screen coordinates of the top left corner of
   *                            the sketchpad
   * @param num_pixels_per_side the number of sketchpad pixels in one row/column
   *                            of the sketchpad
   * @param map_size      the side length of the sketchpad, measured in
   *                            screen pixels
   * @param brush_radius        the maximum distance (measured in sketchpad
   *                            pixels) from the brush that will be shaded
   */
  Grid(const glm::vec2& top_left_corner, size_t num_cells_per_side,
       double map_size, double brush_radius = 0.5);

  /**
   * Displays the current state of the sketchpad in the Cinder application.
   */
  void Draw() const;

  /**
   * Update the current_cell that is being looked at
   */
  void Update();

  /**
   * Shades in the sketchpad pixels whose centers are within brush_radius units
   * of the brush's location. (One unit is equal to the length of one sketchpad
   * pixel.)
   *
   * @param brush_screen_coords the screen coordinates at which the brush is
   *           located
   */
  void HandleBrush(const glm::vec2& brush_screen_coords);

  /**
   * Set all of the cells to an empty state and clear different member variables
   */
  void Clear();

  /**
   * Sets the draw state to the given state
   * 0 means drawing an empty cell
   * 1 means drawing an start cell
   * 2 means drawing an end cell
   * 3 means drawing an obstacle
   * @param state integer representing the current state of the cell
   */
  void SetDrawState(int state);

  /**
   * Setter method that will set the state of the app to either pathfinding
   * or not pathfinding
   * @param pathfinding Boolean representing whether or not the user wants to
   * start pathfinding
   */
  void SetState(bool pathfinding);

 private:
  /**
   * Helper method that will find the path based on the pathfinding state and
   * if there is a start and end node
   */
  void FindPath();

  /**
   * Helper method that checks if a certain vector contains an element
   * @param list The list that we want to check
   * @param element The element that we are looking for
   * @return true if the vector does contain the element, false if it doesn't
   */
  bool ContainsElement(std::vector<Cell> list, Cell element) const;

  glm::vec2 top_left_corner_;
  size_t num_pixels_per_side_;
  double pixel_side_length_;
  double brush_radius_;

  std::vector<Cell> path_;
  Cell start_cell_ = Cell(CellType::kEmpty, 0, 0);
  Cell end_cell_ = Cell(CellType::kEmpty, 0, 0);
  std::vector<std::vector<Cell>> cells_;
  Cell current_cell_ = Cell(CellType::kEmpty, 0, 0);
  pathfinder::Pathfinder pathfinder_ =
      Pathfinder(cells_, start_cell_, start_cell_);
  int draw_state_ = 0;
  bool pathfinding_ = false;
  bool allowed_ = false;
  bool start_point = false;
  bool end_point = false;
  bool path_found_ = false;
};

}  // namespace visualizer

}  // namespace pathfinder
