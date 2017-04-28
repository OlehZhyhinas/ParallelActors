#ifndef EVALUATION_H
#define EVALUATION_H

#include "math.h"
#include "data_store.h"

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

class Evaluation {
public:
	Data_Store* d;
	
	std::vector<int> shortest_path_next;
	std::vector<int> best_target;
	
	int direction;  //1,2,3,4
	Evaluation(Data_Store *d_pointer);
	
	void shortest_path();//finds the next step in the shortest path to precieved destination
	void next_move(); //ouputs the next move to the data_store
	
	
	
	
	
	
	
};
#endif /*EVALUATION_H*/
