#include <visualizer/grid.h>

namespace pathfinder {

namespace visualizer {

using glm::vec2;

Grid::Grid(const vec2& top_left_corner, size_t num_cells_per_side,
           double map_size, double brush_radius)
    : top_left_corner_(top_left_corner),
      num_pixels_per_side_(num_cells_per_side),
      pixel_side_length_(map_size / num_cells_per_side),
      brush_radius_(brush_radius) {
  cells_.resize(num_pixels_per_side_);
  for (size_t row = 0; row < num_pixels_per_side_; row++) {
    for (size_t col = 0; col < num_pixels_per_side_; col++) {
      Cell new_cell = Cell(CellType::kEmpty, row, col);
      cells_[row].push_back(new_cell);
    }
  }
  cells_.resize(num_pixels_per_side_ * num_pixels_per_side_);
  pathfinder_ = Pathfinder(cells_, cells_[0][0],
                           cells_[cells_.size() - 1][cells_.size() - 1]);
}

void Grid::Draw() const {
  for (size_t row = 0; row < num_pixels_per_side_; ++row) {
    for (size_t col = 0; col < num_pixels_per_side_; ++col) {
      switch (cells_[row][col].GetType()) {
        case CellType::kEmpty:
          ci::gl::color(ci::Color("white"));
          break;

        case CellType::kWall:
          ci::gl::color(ci::Color("black"));
          break;

        case CellType::kStart:
          ci::gl::color(ci::Color("red"));
          break;

        case CellType::kEnd:
          ci::gl::color(ci::Color("blue"));
      }

      // If the cell is apart of the path found from the pathfinder or
      // the cell that is currently being looked at, it will be colored
      // green instead
      if (path_found_) {
        if (ContainsElement(path_, cells_[row][col])) {
          ci::gl::color(ci::Color("green"));
        }
      } else {
        if (current_cell_.GetPosition().x == row &&
            current_cell_.GetPosition().y == col) {
          ci::gl::color(ci::Color("green"));
        }
      }

      vec2 pixel_top_left = top_left_corner_ + vec2(col * pixel_side_length_,
                                                    row * pixel_side_length_);

      vec2 pixel_bottom_right =
          pixel_top_left + vec2(pixel_side_length_, pixel_side_length_);
      ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);

      ci::gl::drawSolidRect(pixel_bounding_box);

      ci::gl::color(ci::Color("black"));
      ci::gl::drawStrokedRect(pixel_bounding_box);
    }
  }
}

void Grid::Update() {
  if (pathfinding_) {
    FindPath();
  }
}

void Grid::HandleBrush(const vec2& brush_screen_coords) {
  vec2 brush_sketchpad_coords =
      (brush_screen_coords - top_left_corner_) / (float)pixel_side_length_;

  for (size_t row = 0; row < num_pixels_per_side_; ++row) {
    for (size_t col = 0; col < num_pixels_per_side_; ++col) {
      vec2 pixel_center = {col + 0.5, row + 0.5};

      // Whenever the user draws a cell, it will change the state of that cell
      // based on the current draw_state
      if (glm::distance(brush_sketchpad_coords, pixel_center) <=
          brush_radius_) {
        switch (draw_state_) {
          case 0:
            cells_[row][col] = Cell(CellType::kEmpty, row, col);
            break;

          case 1:
            cells_[row][col] = Cell(CellType::kStart, row, col);
            start_point = true;
            current_cell_ = cells_[row][col];
            start_cell_ = cells_[row][col];
            break;

          case 2:
            cells_[row][col] = Cell(CellType::kEnd, row, col);
            end_point = true;
            end_cell_ = cells_[row][col];
            break;

          case 3:
            cells_[row][col] = Cell(CellType::kWall, row, col);
            break;
        }
      }
    }
  }
  allowed_ = start_point && end_point;
}

void Grid::Clear() {
  cells_.clear();
  cells_.resize(num_pixels_per_side_);
  for (size_t row = 0; row < num_pixels_per_side_; row++) {
    for (size_t col = 0; col < num_pixels_per_side_; col++) {
      Cell new_cell = Cell(CellType::kEmpty, row, col);
      cells_[row].push_back(new_cell);
    }
  }
}

void Grid::SetDrawState(int state) {
  draw_state_ = state;
}

void Grid::SetState(bool pathfinding) {
  pathfinding_ = pathfinding;
  if (pathfinding_) {
    pathfinder_.SetGrid(cells_, start_cell_, end_cell_);
  } else if (!pathfinding) {
    path_.clear();
  }
}

void Grid::FindPath() {
  /*
   * allowed_ ensures there is a start and end point, meaning a path can be
   * found pathfinding_ checks to see if the user wants to pathfind
   */
  if (allowed_ && pathfinding_) {
    if (current_cell_.GetPosition() != end_cell_.GetPosition()) {
      current_cell_ = pathfinder_.FindNextCell(current_cell_);
    } else {
      pathfinding_ = false;
      path_ = pathfinder_.GetPath(end_cell_);
      path_found_ = true;
    }
  }
}

bool Grid::ContainsElement(std::vector<Cell> list, Cell element) const {
  for (Cell cell : list) {
    if (cell.GetPosition() == element.GetPosition()) {
      return true;
    }
  }
  return false;
}

}  // namespace visualizer

}  // namespace pathfinder
