#include "cinder/gl/gl.h"

namespace pathfinder {

enum class CellType {
  kEmpty,
  kWall,
  kStart,
  kEnd,
};

class Cell {
 public:
  /**
   * Constructor for Cell object
   * @param type The type of cell being created (kStart, kEnd, kEmpty, or kWall)
  */
  Cell(CellType type, int x_pos, int y_pos);

  /**
   * Helper method that returns the CellType of the cell
   * @return The enum representing the cell's CellType
  */
  const CellType& GetType() const;

  /**
   * Setter method that will update the type of the cell
   * @param type The new CellType for the cell
   */
  void SetType(const CellType& type);

  /**
   * Getter method that will get the position of the cell
   * @return the (row,col) position of the cell as a vec2
   */
  const glm::vec2& GetPosition() const;

  /**
   * Setter method that will set the previous_cell of the current cell to the
   * parameter
   * @param previous_cell the cell preceding the current cell
   */
  void SetPreviousCell(Cell& previous_cell);

  /**
   * Getter method that returns the current cell's previous cell
   * @return the current cell's previous cell
  */
  const Cell * GetPreviousCell();

  /**
   * Setter method that sets the G Cost of the cell to the given value
   * @param new_cost the new g cost
   */
  void SetGCost(const int new_cost);

  /**
   * Setter method that sets the H Cost of the cell to the given value
   * @param new_cost the new H Cost
   */
  void SetHCost(const int new_cost);

  /**
   * Getter method that returns the G Cost of the current cell
   * @return the G Cost of the current cell as an int
   */
  const int GetGCost() const;

  /**
   * Getter method that will return the F Cost of the given cell,
   * calculated from the G and H costs
   * @return the F Cost of the current cell as an int
   */
  const int GetFCost() const;

 private:
  CellType type_;

  glm::vec2 kPosition_;
  int g_cost_ = 0;
  int h_cost_ = 0;

  Cell * previous_cell_;
};

} //namespace pathfinder