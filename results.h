#ifndef RESULTS_H
#define RESULTS_H

#include "data_store.h"

class Results {
	public:
		Data_Store* d; 
		
		Results(Data_Store *d_pointer);
		double calculate_distance(int x1, int y1, int x2, int y2);
		int check_collision();
		char identify_obstacle();
		double calculate_score();

};


#endif /*RESULTS_H_H*/