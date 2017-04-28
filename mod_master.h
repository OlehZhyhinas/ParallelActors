#ifndef MOD_MASTER_H
#define MOD_MASTER_H

#include "data_store.h"

class Mod_Master {
public:
	
	double max_distance;
	Data_Store* d;
	
	Mod_Master(Data_Store *d_pointer);
	double distance_change(int x, int y); //calculate the change in distance to this point
	double distance(int x1, int y1, int x2, int y2 );
	void calculate_attractivness(int x, int y); //calculated the score of a certain point
	void calculate_all_attractivness(); //calculated all the scores on the map
	void update_point_values();  //updates the point values in data_store
	void collision_handler();
	
	
	
	
	
	
	
};
#endif /*MOD_MASTER_H*/
