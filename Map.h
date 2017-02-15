//===================================
// include guard
#ifndef MAP_H
#define MAP_H

//===================================
// included dependencies
#include <vector>
#include <string>
#include "Actor.h"
#include "Coordinate.h"

//===================================
// the class
class Map {
  private: 
    const static char kObstacle        = 'O';
    const static char kEmpty           = 'E';
    const static char kActor           = 'A';
    const static char kCollision       = 'C';
    const static int default_map_cols = 300;
    const static int default_map_rows = 300;
    const static int default_vision_radius = 30;
    const static int default_actor_half_rows = 5;
    const static int default_actor_half_cols = 5;
    std::vector< std::vector<char> > map;
    int map_rows;
    int map_cols;
    int actor_half_rows;
    int actor_half_cols;
    int vision_radius;
    int step_size;
    bool AddActorCases(int row, int col);
    bool ClearActorCases(int row, int col);
    bool CheckCollisionCases(int row, int col);
    bool RandomEmptyLocationCases(int row, int col);
    bool IsValidStep(Coordinate old_pos, Coordinate new_pos);
  public:
    Map();
    Map(std::vector< std::vector<char> > input_map);
    void InitializeActorDimensions();
    void InitializeActorDimensions(int in_actor_half_rows, int in_actor_half_cols);
    void InitializeVision();
    void InitializeStepSize();
    void set_step_size(int new_step_size);
    void set_vision_radius(int new_radius);
    void set_map(std::vector< std::vector<char> > new_map);
    void AddActor(Actor actor);
    void ClearActor(Actor actor);
    void MoveActor(Actor actor, Coordinate new_pos);
    void CheckCollision(Actor actor);
    bool AtDestination(Actor actor);
    std::vector< std::vector<char> > GetSurroundings(Coordinate coordinate);
    bool out_of_bounds(int row, int col);
    Coordinate RandomEmptyLocation();
    Coordinate RandomDestination();
    bool IterateThroughActorDimensions(Coordinate coordinate, bool (Map::*f)(int, int));
};

#endif /* MAP_H */
