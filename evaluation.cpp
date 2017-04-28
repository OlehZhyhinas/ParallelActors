#include "evaluation.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include <unistd.h>

Evaluation::Evaluation(Data_Store* d_pointer){
	d=d_pointer;
	int x=d->size_x;
	direction = UP;
	//printf("d is %d \n", d);
	/*best_target.push_back(0);
	best_target.push_back(0);
	shortest_path_next.push_back(0);
	shortest_path_next.push_back(0);*/
}



void Evaluation::next_move(){
	
	int selection;
	/*double max= 0;
	double min=  0;
	
	double range=0;
	int selection;
	
	std::vector<double> probabilities (4,0);
	
	
	for (int x=0; x<d->size_x; x++){
		for (int y=0; y<d->size_y; y++){
			if (d->location_attractivness[x][y]>=max && d->location_attractivness[x][y]!=0){//most attractive location
				max=d->location_attractivness[x][y];
				best_target[0]=x;
				best_target[1]=y;
			}
			if (d->location_attractivness[x][y]<=min && d->location_attractivness[x][y]!=0){//least attractive location
				min=d->location_attractivness[x][y];

			}
		}
	}
	
	range=max-min;*/
	//printf("%d\n", direction);
	shortest_path();
	

	selection = rand() % 1000;

	if (selection>900 && selection<925 && d->location_values[1]>1){
		direction=UP;
	}
	else if (selection>925 && selection<950 && d->location_values[0]<d->size_x-2){
		direction=RIGHT;
	}
	else if (selection>950 && selection<975 && d->location_values[1]<d->size_y-2){
		direction=DOWN;
	}
	else if (selection>975 && selection<999 && d->location_values[0]>1){
		direction=LEFT;
	}


	switch (direction){
		case UP:
			d->next_move[0]=d->location_values[0];
			d->next_move[1]=d->location_values[1]-1;
			break;
		case RIGHT:	
			d->next_move[0]=d->location_values[0]+1;
			d->next_move[1]=d->location_values[1];
			break;
		case DOWN:
			d->next_move[0]=d->location_values[0];
			d->next_move[1]=d->location_values[1]+1;
			break;
		case LEFT:
			d->next_move[0]=d->location_values[0]-1;
			d->next_move[1]=d->location_values[1];
			break;
	}
/*
	
	
	
	if (d->location_values[0]>0){
		probabilities[LEFT]=range+d->location_attractivness[d->location_values[0]-1][d->location_values[1]];
	}
	if (d->location_values[0]<d->size_x-1){
		probabilities[RIGHT]=range+d->location_attractivness[d->location_values[0]+1][d->location_values[1]];
	}
	if (d->location_values[1]>0){
		probabilities[UP]=range+d->location_attractivness[d->location_values[0]][d->location_values[1]-1];
	}
	if (d->location_values[1]<d->size_y-1){
		probabilities[DOWN]=range+d->location_attractivness[d->location_values[0]][d->location_values[1]+1];
	}
	
	
	probabilities[direction]=range+max;
	
	range=probabilities[0]+probabilities[1]+probabilities[2]+probabilities[3];
	int size=(int)range +1;
	selection = rand() %size;
	
	
	if (selection<probabilities[UP]){
		direction=UP;
		d->next_move[0]=d->location_values[0];
		d->next_move[1]=d->location_values[1]-1;
	}
	else if(selection<probabilities[UP]+probabilities[RIGHT]){
		direction=RIGHT;
		d->next_move[0]=d->location_values[0]+1;
		d->next_move[1]=d->location_values[1];
	}
	else if(selection<probabilities[UP]+probabilities[RIGHT]+probabilities[DOWN]){
		direction=DOWN;
		d->next_move[0]=d->location_values[0];
		d->next_move[1]=d->location_values[1]+1;
	}
	else {
		direction=LEFT;
		d->next_move[0]=d->location_values[0]-1;
		d->next_move[1]=d->location_values[1];
	}
	//printf("next_move x: %d, y: %d\n", d->next_move[0], d->next_move[1]);
	*/
}

void Evaluation::shortest_path(){
	std::vector< std::vector <double>  > map_copy;
	
	for (int x=0; x<d->size_x; x++){
		map_copy.push_back(std::vector<double> (d->size_y, 0));
	}
	//printf("d is now %d \n", d);
	//int a =d->size_x;
	int max=-1000000;
	int x_loc=0;
	int y_loc=0;
	for (int x=0; x<d->size_x; x++){
		for (int y=0; y<d->size_y; y++){
			if (d->location_attractivness[x][y]!=0 && d->location_attractivness[x][y]>=max){
				max=d->location_attractivness[x][y];
				x_loc=x;
				y_loc=y;
			}
		}
	}

	
	for (int x=0; x<d->size_x; x++){
		for (int y=0; y<d->size_y; y++){
			if (d->location_attractivness[x][y]>=max || d->location_attractivness[x][y] == 0){
				map_copy[x][y]=0;
			}
			else{
				map_copy[x][y]=-1;
			}
		}
	}
	map_copy[d->location_values[0]][d->location_values[1]]=0;
	map_copy[x_loc][y_loc]=1;	
	max=1;
	while (map_copy[d->location_values[0]][d->location_values[1]] <= 0){//find shortest path
		
		/*for (int x =0; x<d->size_x; x++){
			for (int y =0; y<d->size_y; y++){
				if (x==d->location_values[0] && y==d->location_values[1]){
					printf("%c  ", 'M');
				}
				else {
					printf("%2.0lf ", map_copy[x][y]);
				}
				
			}
			printf("\n");
		}
		usleep(100000);*/
		for (int x =0; x<d->size_x; x++){
			for (int y=0; y<d->size_y; y++){
				if (map_copy[x][y]==max){ //if at the edge of the wavefront
					if (x-1 > 0){ //if not on left edge
						if (map_copy[x-1][y]==0) { //if left cell is empty
							map_copy[x-1][y]=max+1;
						}
					}
					if (x+1 < d->size_x){ //if not on right edge
						if (map_copy[x+1][y]==0) { //if right cell is empty
							map_copy[x+1][y]=max+1;
						}
					}

					if (y-1 > 0){ //if not on top edge
						if (map_copy[x][y-1]==0) { //if top cell is empty
							map_copy[x][y-1]=max+1;
						}
					}
					if (y+1 < d->size_y){ //if not on bottom edge
						if (map_copy[x][y+1]==0) { //if bottom cell is empty
							map_copy[x][y+1]=max+1;
						}
					}
				}

			}
		}
		max++;
	}

	

	int lowest = max+1;
	
	int x= d->location_values[0];
	int y= d->location_values[1];

	if (x-1 > 0){ //if not on left edge
		if (map_copy[x-1][y] <= lowest && map_copy[x-1][y] >0){
			lowest=map_copy[x-1][y];
			direction=LEFT;
		}				
	}
	if (x+1 < d->size_x){ //if not on right edge
		if (map_copy[x+1][y] <= lowest && map_copy[x+1][y] >0){
			lowest=map_copy[x+1][y];
			direction=RIGHT;
		}				
	}
	if (y-1 > 0){ //if not on top edge
		if (map_copy[x][y-1] <= lowest && map_copy[x][y-1] >0){
			lowest=map_copy[x][y-1];
			direction=UP;
		}				
	}
	if (y+1 < d->size_y){ //if not on bottom edge
		if (map_copy[x][y+1] <= lowest && map_copy[x][y+1] >0){
			lowest=map_copy[x][y+1];
			direction=DOWN;
		}				
	}
	

	
	
	
	//printf("direction: %d\n", direction);
}

