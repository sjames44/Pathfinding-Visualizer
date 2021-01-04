#include <string>
#include <vector>

#include "core/cell.h"

namespace pathfinder {

class Pathfinder {
 public:
  /**
   * Constructor for Pathfinder object
   * @param cells A vector of cells representing a map
   */
  Pathfinder(const std::vector<std::vector<Cell>>& cells, Cell& start, Cell& end);

  /**
   * Updates the current cell and the values of the new current cell
   * @return The new cell that is currently being occupied
   */
  Cell FindNextCell(Cell& current_cell);

  /**
   * Checks to see whether the current_cell is the end cell
   * @param current_cell
   * @return
   */
  bool PathFound(Cell& current_cell);

  /**
   * Method that will find the full path, from start to end
   * @return A vector representing the full path
   */


  /**
   * Method that will get the path from the last cell
   * @param end_cell
   * @return The vector of cells that are included in the path
   */
  std::vector<Cell>& GetPath(Cell& end_cell);

  /**
   * Will go through the whole process of finding the path from start_ to goal_
   * Doing so will populate the previous_cell member for each cell in the path
   */
  void FindPath();

  /**
   * Method that will update the grid of the pathfinder
   * @param new_grid The new grid
   * @param start The new start node
   * @param end The new end node
   */
  void SetGrid(std::vector<std::vector<Cell>>& new_grid, Cell& start, Cell& end);

  /**
   * Getter method that will return the open_set_
   */
  std::vector<Cell> GetOpenSet() const;

  /**
   * Helper method that checks if the given vector has the cell
   * @param vec The vector we are checking
   * @param cell The cell we are looking for
   * @return True if the cell is found in the vector, false otherwise
   */
  bool ContainsElement(const std::vector<Cell>& vec, const Cell& cell);

 private:
  /**
   * Helper method that will find the next cell to travel to on the map
   * given the current cell
   * @param current_cell The cell that is currently being occupied
   * @return The neighboring cell that needs to be traveled to
   */
  Cell CalculateNextCell(const Cell& current_cell);

  /**
   * Method that calculates the H cost of a given cell
   * @param cell The cell that the H cost will be calculated for
   * @return a double representing the H cost for that specific cell
   */
  int CalculateHCost(const Cell& cell);

  /**
   * Method that calculates the G cost of a given cell
   * @param cell The cell that the G cost will be calculated for
   * @return a double representing the G cost for that specific cell
   */
  int CalculateGCost(const Cell& cell);

  /**
   * Helper method that finds the neighbors of a given cell and adds
   * the proper ones to the open_set_
   * @param current_cell The cell that the neighbors will be found for
   * @return a vector containing all the neighbors of current_cell
   */
 void FindNeighbors(const Cell& current_cell);

  /**
   * Helper method that will remove an element from the given list
   * @param list The list where the element will be removed from
   * @param element The element to remove
   * @return The new list with the element removed
   */
  std::vector<Cell> RemoveElement(std::vector<Cell>& list, const Cell& element);

  std::vector<std::vector<Cell>> cells_;
  std::vector<Cell> open_set_;
  std::vector<Cell> closed_set_;
  std::vector<Cell> path_;

  Cell start_ = Cell(CellType::kEmpty, 0, 0);
  Cell goal_ = Cell(CellType::kEmpty, 0, 0);;
};

}  // namespace pathfinder


