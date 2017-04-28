#include "mod_master.h"
#include "math.h"
#include "stdio.h"

Mod_Master::Mod_Master(Data_Store* d_pointer){
		d=d_pointer;
		
}

double Mod_Master::distance_change(int x, int y){
	double distance1=0;
	double distance2=0;
	
	distance2=distance(x, y, d->location_values[0], d->location_values[1]); //current distance
	
	if (d->x_history.size()>1){
		distance1=distance(x, y, d->x_history[d->x_history.size()-2], d->y_history[d->y_history.size()-2]); //previous distance	
	}
	else{
		distance1=distance2; //previous distance is meanigless, so make it equal to current distance
	}
	return (distance2-distance1); 
}

double Mod_Master::distance(int x1, int y1, int x2, int y2){
	double dist_squared=(x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
	double distance = sqrt(dist_squared);
	return distance;
}

void Mod_Master::calculate_attractivness(int x, int y){//fails for calculating score of current location of actor, due to division by zero
	
	double result=d->results.back();
	
	double delta_distance=distance_change(x,y);
	
	double base_score=-1*result*delta_distance;
	double actual_score= base_score/(distance(x, y, d->location_values[0], d->location_values[1])
	                                *distance(x, y, d->location_values[0], d->location_values[1]));
	
	if (d->map[x][y] == kActor || d->map[x][y] == kObstacle || d->map[x][y] == kDestination){
		d->location_attractivness[x][y]+=actual_score;
		/*printf("actual score: %.1lf \n", actual_score);
		printf("base score: %.1lf \n", base_score);
		printf("result: %.1lf \n", result);
		printf("distance: %.1lf \n", delta_distance);*/
	}
	else{
		d->location_attractivness[x][y]=0;
	}
}

void Mod_Master::calculate_all_attractivness(){
	for (int x=0; x<d->size_x; x++){
		for (int y=0; y<d->size_y; y++){
			if (x!= d->location_values[0] || y!=d->location_values[1]){
				calculate_attractivness(x, y);
			}
		}
	}
	collision_handler();
	//update_point_values();
	//d->print_location_attractivness();
}

void Mod_Master::update_point_values(){
	std::vector<double> destination;
	std::vector<double> actor;
	std::vector<double> obstacle;
	
	destination.push_back(0);
	actor.push_back(0);
	obstacle.push_back(0);
	
	for (int x=0; x<d->size_x; x++){
		for (int y=0; y<d->size_y; y++){
			switch (d->map[x][y]){
				case kActor :
					actor.push_back(d->location_attractivness[x][y]);
					break;
				case kDestination : 
					destination.push_back(d->location_attractivness[x][y]);
					break; 
				case kObstacle : 
					obstacle.push_back(d->location_attractivness[x][y]);
					break;
				default :
					break;
			}	
		}
	}
	
	double dest_avg=0;
	for (int i = 0; i < destination.size(); i++) dest_avg += destination[i];
	dest_avg=dest_avg/destination.size();
	
	double act_avg=0;
	for (int i = 0; i < actor.size(); i++) act_avg += actor[i];
	act_avg=act_avg/actor.size();
	
	
	double obst_avg=0;
	for (int i = 0; i < obstacle.size(); i++) obst_avg += obstacle[i];
	obst_avg=obst_avg/actor.size();
	
	
	
}

void Mod_Master::collision_handler(){
	for (int x=0; x<d->size_x; x++){
		for (int y=0; y<d->size_y; y++){
			if (d->map[x][y]==d->collision_id){
				d->location_attractivness[x][y] -= 50;
			}
		}
	}
	
	
}







