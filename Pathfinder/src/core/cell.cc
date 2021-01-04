#include "core/cell.h"

namespace pathfinder {

Cell::Cell(CellType type, int x_pos = 0, int y_pos = 0) {
  type_ = type;
  kPosition_ = glm::vec2(x_pos, y_pos);
}

const CellType& Cell::GetType() const {
  return type_;
}

const glm::vec2& Cell::GetPosition() const {
  return kPosition_;
}

void Cell::SetPreviousCell(Cell& previous_cell) {
  previous_cell_ = &previous_cell;
}

const Cell * Cell::GetPreviousCell() {
  return previous_cell_;
}

void Cell::SetGCost(const int new_cost) {
  g_cost_ = new_cost;
}

void Cell::SetHCost(const int new_cost) {
  h_cost_ = new_cost;
}

const int Cell::GetFCost() const {
  return g_cost_ + h_cost_;
}

const int Cell::GetGCost() const {
  return g_cost_;
}

void Cell::SetType(const CellType& type) {
  type_ = type;
}

}