#include <core/pathfinder.h>

#include <catch2/catch.hpp>
#include <vector>

TEST_CASE("Test Pathfinder") {
  // Setting up a sample 5x5 grid
  std::vector<std::vector<pathfinder::Cell>> grid;
  grid.resize(5);
  for (size_t row = 0; row < 5; row++) {
    for (size_t col = 0; col < 5; col++) {
      pathfinder::Cell new_cell =
          pathfinder::Cell(pathfinder::CellType::kEmpty, row, col);
      grid[row].push_back(new_cell);
    }
  }

  grid[0][0].SetType(pathfinder::CellType::kStart);
  grid[4][4].SetType(pathfinder::CellType::kEnd);

  pathfinder::Cell start_ = grid[0][0];
  pathfinder::Cell end_ = grid[4][4];

  pathfinder::Pathfinder test_pathfinder =
      pathfinder::Pathfinder(grid, start_, end_);

  SECTION("Test that program can stop when path is found") {
    REQUIRE(test_pathfinder.PathFound(grid[4][4]));
  }

  SECTION("Test finding next cell") {
    SECTION("Test that proper cell is chosen with no walls or end cell") {
      REQUIRE(test_pathfinder.FindNextCell(grid[2][2]).GetPosition() ==
              grid[2][3].GetPosition());
    }

    SECTION("Test that a wall is not included as a valid cell to move to") {
      grid[2][2].SetType(pathfinder::CellType::kWall);
      REQUIRE(test_pathfinder.FindNextCell(grid[2][2]).GetPosition() !=
              grid[2][3].GetPosition());
      REQUIRE(test_pathfinder.FindNextCell(grid[2][2]).GetPosition() ==
              grid[3][2].GetPosition());
    }

    SECTION("Test that an element from the closed set is not included") {
      REQUIRE(test_pathfinder.FindNextCell(grid[0][1]).GetPosition() !=
              start_.GetPosition());
    }

    SECTION("Test Finding Neighbors") {
      SECTION(
          "Test that the pathfinder wont check neighbors outside of the grid") {
        // Since FindNextCell utilizes FindNeighbors, by testing it and making
        // sure an error isn't thrown, I ensure its not checking outside of the
        // grid
        SECTION("Test top side") {
          REQUIRE(test_pathfinder.FindNextCell(start_).GetPosition() ==
                  grid[0][1].GetPosition());
        }

        SECTION("Test right side") {
          REQUIRE(test_pathfinder.FindNextCell(grid[0][4]).GetPosition() ==
                  grid[1][4].GetPosition());
        }

        SECTION("Test left side") {
          REQUIRE(test_pathfinder.FindNextCell(grid[2][0]).GetPosition() ==
                  grid[2][1].GetPosition());
        }

        SECTION("Test bottom side") {
          REQUIRE(test_pathfinder.FindNextCell(grid[4][1]).GetPosition() ==
                  grid[4][2].GetPosition());
        }
      }

      SECTION(
          "Test that the the pathfinder won't check cells that it can't "
          "access") {
        REQUIRE(test_pathfinder.FindNextCell(grid[2][2]).GetPosition() !=
                grid[3][3].GetPosition());
      }

      SECTION(
          "Test that the algorithm does not consider diagonals as a viable "
          "movement") {
        REQUIRE(test_pathfinder.FindNextCell(grid[3][3]).GetPosition() !=
                end_.GetPosition());
      }
    }

    SECTION("Test that cell is removed from open_set after its found") {
      pathfinder::Cell new_cell = test_pathfinder.FindNextCell(start_);
      std::vector<pathfinder::Cell> set = test_pathfinder.GetOpenSet();
      REQUIRE(!test_pathfinder.ContainsElement(set, start_));
    }
  }

  SECTION("Test Algorithm") {
    SECTION("Test that proper cell is chosen") {
      SECTION("Test that proper cell is chosen normally") {
        REQUIRE(test_pathfinder.FindNextCell(grid[2][2]).GetPosition().x ==
                grid[2][2].GetPosition().x);
        REQUIRE(test_pathfinder.FindNextCell(grid[2][2]).GetPosition().y ==
                grid[2][3].GetPosition().y);
      }

      SECTION("Test that proper cell is chosen when next to the end node") {
        REQUIRE((test_pathfinder.FindNextCell(grid[3][3]).GetPosition().x ==
                 grid[4][4].GetPosition().x));
        REQUIRE((test_pathfinder.FindNextCell(grid[3][3]).GetPosition().y ==
                 grid[4][4].GetPosition().y));
      }
    }

    SECTION("Test that proper path is found at the end") {
      test_pathfinder.FindPath();
      std::vector<pathfinder::Cell> path = test_pathfinder.GetPath(end_);

      SECTION("Test that it goes from the start_ to the end_") {
        SECTION("Test that it has start_") {
          REQUIRE(path[path.size() - 1].GetPosition() == end_.GetPosition());
        }

        SECTION("Test that it goes till the end_") {
          REQUIRE(path[0].GetPosition() == end_.GetPosition());
        }

        SECTION("Test key points in the path") {
          SECTION("Test that the turning point is there") {
            REQUIRE(path[4].GetPosition() == grid[4][0].GetPosition());
          }
        }
      }
    }

    SECTION("Test that F Cost is calculated correctly") {
      std::vector<pathfinder::Cell> path = test_pathfinder.GetPath(end_);
      REQUIRE(path[path.size() - 1].GetFCost() == 8);
    }

    SECTION("Test ContainsElement") {
      SECTION("Make sure the method properly detects an element within a set") {
        SECTION("Test beginning of vector") {
          REQUIRE(test_pathfinder.ContainsElement(grid[0], start_));
        }

        SECTION("Test middle of vector") {
          REQUIRE(test_pathfinder.ContainsElement(grid[0], grid[0][5]));
        }

        SECTION("Test end of vector") {
          REQUIRE(test_pathfinder.ContainsElement(grid[grid.size() - 1], end_));
        }
      }

      SECTION(
          "Mak sure the method returns false if an element is not in the set") {
        REQUIRE(!test_pathfinder.ContainsElement(grid[0], end_));
      }
    }
  }
}