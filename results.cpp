#include "results.h"
#include "stdio.h"
#include "math.h"

Results::Results(Data_Store* d_pointer){
	d=d_pointer;
}



double Results::calculate_distance(int x1, int y1, int x2, int y2 ){
	double dist_squared=(x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
	double distance = sqrt(dist_squared);
	return distance;
}

int Results::check_collision(){
	
	if (d->vision[d->vision_radius][d->vision_radius]==kCollision){
		return 1;	
	}
	else {
		return 0;
	}
}

char Results::identify_obstacle(){
	if (d->map[d->location_values[0]][d->location_values[1]]==kObstacle){
		return kObstacle;
	}
	else{
		return kActor;
	}
	
}

double Results::calculate_score(){
	
	if (d->x_history.size()>1){
		double current_distance= calculate_distance(d->destination_values[0], d->destination_values[0], 
	                                            d->location_values[0], d->location_values[0]);
		//printf("%lf ", current_distance);											
		double previous_distance= calculate_distance(d->destination_values[0], d->destination_values[0],
	                                             d->x_history[d->x_history.size()-2], d->y_history[d->y_history.size()-2]);
	
		//printf("%lf ", previous_distance);	
		double distance_change=current_distance-previous_distance;
	
		//printf("%lf\n", distance_change);
		if (check_collision()==0){
			d->results.push_back(-1*distance_change);
			d->collision_status=0;
			d->collision_id=(char)0;
			
		}
		else{
			d->collision_status=1;
			d->collision_id=identify_obstacle();
			printf("collided with %c\n", d->collision_id);
			d->results.push_back(-50);
			
		}
	}
	else {
		d->results.push_back(0);
	}
	return d->results.back();
	
	
}

