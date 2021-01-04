#include <core/pathfinder.h>
#include <math.h>

namespace pathfinder {

Pathfinder::Pathfinder(const std::vector<std::vector<Cell>>& cells, Cell& start,
                       Cell& end) {
  cells_ = cells;

  // Populates start_ and goal_ cell variables
  for (const std::vector<Cell>& row : cells_) {
    for (Cell cell : row) {
      if (cell.GetType() == CellType::kStart) {
        start_ = cell;
      } else if (cell.GetType() == CellType::kEnd) {
        goal_ = cell;
      }
    }
  }
  start_.SetGCost(0);
  start_.SetHCost(CalculateHCost(start_));
  open_set_.push_back(start_);
}

Cell Pathfinder::FindNextCell(Cell& current_cell) {
  Cell next_cell = CalculateNextCell(current_cell);
  next_cell.SetPreviousCell(current_cell);

  if (open_set_.empty() || next_cell.GetPosition() == goal_.GetPosition()) {
    return next_cell;
  } else {
    current_cell = next_cell;
    return current_cell;
  }
}

Cell Pathfinder::CalculateNextCell(const Cell& current_cell) {
  FindNeighbors(current_cell);
  int lowest_index = 0;

  // Find Cell in the open_set_ with the lowest F_Cost to move to
  for (size_t neighbor = 0; neighbor < open_set_.size(); neighbor++) {
    open_set_[neighbor].SetGCost(CalculateGCost(open_set_[neighbor]));
    open_set_[neighbor].SetHCost(CalculateHCost(open_set_[neighbor]));
    if (open_set_[neighbor].GetFCost() < open_set_[lowest_index].GetFCost()) {
      if (open_set_[neighbor].GetPosition() != current_cell.GetPosition()) {
        lowest_index = neighbor;
      }
    }
  }

  // Checks to see if we are at the end node
  if (open_set_[lowest_index].GetType() == CellType::kEnd) {
    return open_set_[lowest_index];
  }

  Cell current = open_set_[lowest_index];

  open_set_ = RemoveElement(open_set_, current);
  closed_set_.push_back(current);
  return current;
}

void Pathfinder::FindNeighbors(const Cell& current_cell) {
  if (current_cell.GetPosition() == start_.GetPosition()) {
    closed_set_.push_back(start_);
  }
  size_t x = current_cell.GetPosition().x;
  size_t y = current_cell.GetPosition().y;

  //-1 to 1 in order to check the 8 cells surrounding current_cell
  for (int row = -1; row <= 1; row++) {
    for (int col = -1; col <= 1; col++) {
      // Make sure we aren't considering the current cell as a neighbor
      if (row == 0 && col == 0) {
        col++;
      }
      int x_coord = x + row;
      int y_coord = y + col;
      bool valid_spot;

      // Checks to see if the spot we are looking at is one that we can actually
      // move to
      if ((x_coord < 0 || y_coord < 0) ||
          (x_coord > cells_.size() - 1 || y_coord > cells_.size() - 1) ||
          (row != 0 && col != 0)) {
        valid_spot = false;
      } else {
        valid_spot = true;
      }

      if (valid_spot) {
        Cell neighbor = cells_[x_coord][y_coord];
        if (!(neighbor.GetType() == CellType::kWall ||
              ContainsElement(closed_set_, neighbor))) {
          int temp_g = current_cell.GetGCost() + 1;
          if (ContainsElement(open_set_, neighbor)) {
            if (temp_g < neighbor.GetGCost()) {
              neighbor.SetGCost(temp_g);
            }
          } else {
            neighbor.SetGCost(temp_g);
            neighbor.SetHCost(CalculateHCost(neighbor));
            open_set_.push_back(neighbor);
          }
        }
      }
    }
  }
}

int Pathfinder::CalculateGCost(const Cell& cell) {
  double x_distance = std::abs(start_.GetPosition().x - cell.GetPosition().x);
  double y_distance = std::abs(start_.GetPosition().y - cell.GetPosition().y);
  return x_distance + y_distance;
}

int Pathfinder::CalculateHCost(const Cell& cell) {
  double x_distance = std::abs(goal_.GetPosition().x - cell.GetPosition().x);
  double y_distance = std::abs(goal_.GetPosition().y - cell.GetPosition().y);
  return x_distance + y_distance;
}

bool Pathfinder::PathFound(Cell& current_cell) {
  if ((current_cell.GetPosition() == goal_.GetPosition()) &&
      current_cell.GetType() == CellType::kEnd) {
    return true;
  }
  return false;
}

bool Pathfinder::ContainsElement(const std::vector<Cell>& vec,
                                 const Cell& cell) {
  for (const Cell& current_cell : vec) {
    if (current_cell.GetPosition() == cell.GetPosition()) {
      return true;
    }
  }
  return false;
}

std::vector<Cell> Pathfinder::RemoveElement(std::vector<Cell>& list,
                                            const Cell& element) {
  std::vector<Cell> temp_array;
  for (const Cell& cell : list) {
    if (cell.GetPosition() == element.GetPosition()) {
      continue;
    } else {
      temp_array.push_back(cell);
    }
  }

  return temp_array;
}

std::vector<Cell>& Pathfinder::GetPath(Cell& end_cell) {
  Cell temp_cell = end_cell;
  path_.push_back(temp_cell);

  while (temp_cell.GetPreviousCell() != nullptr &&
         (temp_cell.GetPosition().x > 0 && temp_cell.GetPosition().y > 0)) {
    path_.push_back(*temp_cell.GetPreviousCell());
    temp_cell = *temp_cell.GetPreviousCell();
  }

  return path_;
}

void Pathfinder::FindPath() {
  Cell current_cell = start_;
  while (current_cell.GetPosition() != goal_.GetPosition()) {
    current_cell = FindNextCell(current_cell);
  }
}

void Pathfinder::SetGrid(std::vector<std::vector<Cell>>& new_grid, Cell& start,
                         Cell& end) {
  cells_ = new_grid;
  start_ = start;
  goal_ = end;
}

std::vector<Cell> Pathfinder::GetOpenSet() const {
  return open_set_;
}

}  // namespace pathfinder