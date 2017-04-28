#include "data_store.h"
#include "stdio.h"

Data_Store::Data_Store(){
	size_x=default_map_cols;
	size_y=default_map_rows;
	
	actor_half_rows=default_actor_half_rows;
	actor_half_cols=default_actor_half_cols;
	vision_radius=default_vision_radius;
	
	location_values.push_back(size_x/2);
	location_values.push_back(size_y/2);
	
	next_move.push_back(location_values[0]);
	next_move.push_back(location_values[1]);
	
	x_history.push_back(location_values[0]);
	y_history.push_back(location_values[1]);
	
	destination_values.push_back(size_x/4);
	destination_values.push_back(size_y/4);
	
	x_dest_history.push_back(destination_values[0]);
	y_dest_history.push_back(destination_values[1]);
	
	
	initialize_vision();
	initialize_map();
	initialize_points_values();
	initialize_location_attractivness();
	
	
	
	
}

Data_Store::Data_Store(int map_x_size, int map_y_size, int act_x_size, int act_y_size, int v_radius){
	size_x=map_x_size;
	size_y=map_y_size;
	
	actor_half_rows=act_y_size;
	actor_half_cols=act_x_size;
	vision_radius=v_radius;
	
	location_values.push_back(0);
	location_values.push_back(0);
	
	next_move.push_back(0);
	next_move.push_back(0);
	
	x_history.push_back(0);
	y_history.push_back(0);
	
	destination_values.push_back(0);
	destination_values.push_back(0);
	
	x_dest_history.push_back(0);
	y_dest_history.push_back(0);
		
	
	initialize_vision();
	initialize_map();
	initialize_points_values();
	initialize_location_attractivness();
	
	
	
	
}

void Data_Store::update_map(){
	
	int x_start=location_values[0]-vision_radius;
	int y_start=location_values[1]-vision_radius;

	for (int x=0; x<2*vision_radius+1; x++){
		for (int y=0; y<2*vision_radius+1; y++){
			if (x_start+x >=0 && x_start+x < size_x 
			&& y_start+y >=0 && y_start+y < size_y){
				//printf("adding to map %c\n", vision[x][y]);
				if (vision[x][y]!=kCollision){
					map[x_start+x][y_start+y]=vision[x][y];
				}
			}
		}
	}
	
	map[destination_values[0]][destination_values[1]]=kDestination;
	
	
	//print_map();
	
}

void Data_Store::update_results(double result){
	results.push_back(result);
}

void Data_Store::recieve_vision(char * vision_array){
	
	for (int i=0; i<(vision_radius*2+1)*(vision_radius*2+1); i++){
		vision[i%(vision_radius*2+1)][i/(vision_radius*2+1)]=vision_array[i];	
	}

	//print_vision();
	update_map();
}

void Data_Store::recieve_location(int x, int y){
	
	location_values[0]=x;
	location_values[1]=y;
	//map[x][y]=kSelf;
	x_history.push_back(x);
	y_history.push_back(y);
	
}

void Data_Store::recieve_destination(int x, int y){
	
	destination_values[0]=x;
	destination_values[1]=y;
	map[x][y]=kDestination;
	x_dest_history.push_back(x);
	y_dest_history.push_back(y);
	
}


void Data_Store::initialize_map(){

	
	for (int x=0; x<size_x; x++){
		map.push_back(std::vector<char> (size_y, kEmpty));
	}
	for (int x=0; x<size_x; x++){
		for (int y=0; y<size_y; y++){
			map[x][y]=kEmpty;
		}
	}

	
	//print_map();
}

void Data_Store::initialize_vision(){
	for (int x=0; x<2*vision_radius+1; x++){
		vision.push_back(std::vector<char> (vision_radius*2+1, kEmpty));
	}
	
	
}

void Data_Store::initialize_points_values(){
	points_values.push_back(std::vector<double> (number_of_points, 0));
	points_values.push_back(std::vector<double> (number_of_points, 0));
	
	points_values[0][0]=(double)kObstacle;
	points_values[0][1]=(double)kEmpty;
	points_values[0][2]=(double)kActor;
	points_values[0][3]=(double)kCollision;
	points_values[0][4]=(double)kSelf;
	points_values[0][5]=(double)kDestination;
	
	//print_points_values();
	
}

void Data_Store::initialize_location_attractivness(){
	for (int i=0; i<size_x; i++){
		location_attractivness.push_back(std::vector<double> (size_y, 0));
	}
	
}

void Data_Store::print_points_values(){
	for (int i=0; i<number_of_points;i++){
		printf("%c    ", (char)points_values[0][i]);
	}
	printf("\n");
	for (int i=0; i<number_of_points;i++){
		printf("%2.2lf ", points_values[1][i]);
	}
	printf("\n");
	printf("\n");
	
}

void Data_Store::print_map(){
	
	
	for (int y=0; y<size_y; y++){
		for (int x=0; x<size_x; x++){
			
			if (x!=location_values[0] || y!=location_values[1]){
				printf("%c ",(map[x][y]));
			}
			else {
				printf("%c ",kSelf);
			}
			
		}
		printf("\n");
	}
	printf("\n");
	
}
void Data_Store::print_vision(){
	for (int y=0; y<vision_radius*2+1; y++){
		for (int x=0; x<vision_radius*2+1; x++){
			printf("%c ", vision[x][y]);
		}
		printf("\n");
	}
	printf("\n");
}

void Data_Store::print_location_attractivness(){
	for (int y=0; y<size_y; y++){
		for (int x=0; x<size_x; x++){
			printf("%1.1lf ", location_attractivness[x][y]);
		}
		printf("\n");
	}
	printf("\n");
}


