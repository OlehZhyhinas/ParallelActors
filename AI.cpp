#include "AI.h"


AI::AI(){
	GUI=0;
	win_bg_color = sf::Color::White;
	bytes_per_pixel=4;

}
	
void AI::initialize_data_store(int map_x_size, int map_y_size, int act_x_size, int act_y_size, int v_radius){
	d = new Data_Store(map_x_size,map_y_size, act_x_size, act_y_size, v_radius);
	if (map_pixels == NULL){
    		map_pixels = new sf::Uint8[d->size_x * d->size_y * bytes_per_pixel];
  	}
	if (vision_pixels == NULL){
    		vision_pixels = new sf::Uint8[(d->vision_radius*2+1) * (d->vision_radius*2+1) * bytes_per_pixel];
  	}

}
void AI::initialize_results(){
	r = new Results(d);

}
void AI::initialize_mod_master(){
	m = new Mod_Master(d);

}
void AI::initialize_evaluation(){
	e = new Evaluation(d);
	
}
void AI::set_vision_data(char* vision_grid){
	d->recieve_vision(vision_grid);
	

}
void AI::get_move(){
	
	if (d->location_values[0] == d->next_move[0] && d->location_values[1] == d->location_values[1]){
		r->calculate_score();
		//printf("score\n");
		//d->print_map();
	
		m->calculate_all_attractivness();
		//printf("atract\n");
		//d->print_map();
	}
	e->d = d;
	e->next_move();
	//printf("move to %d,%d from %d,%d\n", d->next_move[0], d->next_move[1],d->location_values[0], d->location_values[1]);
	//d->print_map();

}

void AI::set_location(int x, int y){
	d->recieve_location(x,y);
}
void AI::set_destination(int x, int y){
	d->recieve_destination(x,y);

}

void AI::launch_window(){
	if (GUI == 0){
    		return;
  	}
  	int map_rows = d->size_y + d->vision_radius;
  	int map_cols = d->size_x * 2;
  	AI_window = new sf::RenderWindow(sf::VideoMode(
        map_cols + 15,
        map_rows + 15), 
	"AI");

  	AI_map_texture.create(d->size_x, d->size_y);
	AI_vision_texture.create(d->vision_radius*2+1, d->vision_radius*2+1);
	
	AI_map_sprite.setPosition(5, 5);
  	AI_map_sprite.setTexture(AI_map_texture);

	AI_vision_sprite.setPosition(5, d->size_y+5);
  	AI_vision_sprite.setTexture(AI_vision_texture);


	

}
void AI::show_vision(){
	if (GUI == 0){
    		return;
  	}	
	if(AI_window->isOpen()){
    		while(AI_window->pollEvent(event)){
      			if (event.type == sf::Event::Closed) {
        			AI_window->close();
        			exit(0);
      			}
    		}
	}

	//AI_window->clear(win_bg_color);
	for (int row = 0; row < d->vision_radius*2+1; row++){
    		for (int col = 0; col < d->vision_radius*2+1; col++){
      			int pindex = (row * (d->vision_radius*2+1) + col) * bytes_per_pixel;

      			vision_pixels[pindex+R] = get_pixel_for_char(d->vision[col][row], R);
      			vision_pixels[pindex+G] = get_pixel_for_char(d->vision[col][row], G);
      			vision_pixels[pindex+B] = get_pixel_for_char(d->vision[col][row], B);
      			vision_pixels[pindex+A] = get_pixel_for_char(d->vision[col][row], A);
    		}
	}
	AI_vision_texture.update(vision_pixels);
	AI_window->draw(AI_vision_sprite);
	
	AI_window->display();

}
void AI::show_field(){
	if (GUI == 0){
    		return;
  	}	
	if(AI_window->isOpen()){
    		while(AI_window->pollEvent(event)){
      			if (event.type == sf::Event::Closed) {
        			AI_window->close();
        			exit(0);
      			}
    		}
	}
	AI_window->clear(win_bg_color);
	for (int row = 0; row < d->size_y; row++){
    		for (int col = 0; col < d->size_x; col++){
      			int pindex = (row * d->size_x + col) * bytes_per_pixel;

      			map_pixels[pindex+R] = get_pixel_for_char(d->map[col][row], R);
      			map_pixels[pindex+G] = get_pixel_for_char(d->map[col][row], G);
      			map_pixels[pindex+B] = get_pixel_for_char(d->map[col][row], B);
      			map_pixels[pindex+A] = get_pixel_for_char(d->map[col][row], A);
    		}
	}
	map_pixels[(d->location_values[1]*d->size_x + d->location_values[0]) * bytes_per_pixel + R] = get_pixel_for_char(kSelf, R);
	map_pixels[(d->location_values[1]*d->size_x + d->location_values[0]) * bytes_per_pixel + G] = get_pixel_for_char(kSelf, G);
	map_pixels[(d->location_values[1]*d->size_x + d->location_values[0]) * bytes_per_pixel + B] = get_pixel_for_char(kSelf, B);
	map_pixels[(d->location_values[1]*d->size_x + d->location_values[0]) * bytes_per_pixel + A] = get_pixel_for_char(kSelf, A);
	
	AI_map_texture.update(map_pixels);
	AI_window->draw(AI_map_sprite);
	AI_window->draw(AI_vision_sprite);
	AI_window->display();

}
void AI::show_attractivness(){
	if (GUI == 0){
    		return;
  	}	
	if(AI_window->isOpen()){
    		while(AI_window->pollEvent(event)){
      			if (event.type == sf::Event::Closed) {
        			AI_window->close();
        			exit(0);
      			}
    		}
	}
	AI_window->display();

}

unsigned char AI::get_pixel_for_char(char map_char, int pixel_type){
  	unsigned char pixel_val;
  	if (pixel_type == A){
    		pixel_val = 255;
    		return pixel_val;
  	}
  	switch (map_char) {
    		case kObstacle  :
      			switch (pixel_type){
        			case R :
          				pixel_val = 0;
          				break;
        			case G :
          				pixel_val = 0;
          				break;
        			case B :
          				pixel_val = 0;
          				break;
      			}
      			break;
		case kDestination  :
      			switch (pixel_type){
        			case R :
          				pixel_val = 0;
          				break;
        			case G :
          				pixel_val = 255;
          				break;
        			case B :
          				pixel_val = 0;
          				break;
      			}
      			break;
    		case kEmpty     :
      			switch (pixel_type){
        			case R :
          				pixel_val = 255;
          				break;
        			case G :
          				pixel_val = 255;
          				break;
        			case B :
          				pixel_val = 255;
          				break;
      			}
      			break;
    		case kActor     :
      			switch (pixel_type){
        			case R :
          				pixel_val = 0;
          				break;
        			case G :
          				pixel_val = 0;
          				break;
        			case B :
          				pixel_val = 255;
          				break;
      			}
      			break;
		case kSelf     :
      			switch (pixel_type){
        			case R :
          				pixel_val = 0;
          				break;
        			case G :
          				pixel_val = 255;
          				break;
        			case B :
          				pixel_val = 255;
          				break;
      			}
      			break;
    		case kCollision :
      			switch (pixel_type){
        			case R :
          				pixel_val = 255;
          				break;
        			case G :
          				pixel_val = 0;
          				break;
        			case B :
          				pixel_val = 0;
          				break;
      			}
      			break;
  	}
  	return pixel_val;
}
