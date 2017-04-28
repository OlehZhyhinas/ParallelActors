#ifndef AI_MODULE_H
#define AI_MODULE_H

#include "data_store.h"
#include "results.h"
#include "mod_master.h"
#include "evaluation.h"
#include "stdio.h"
#include "stdlib.h"
#include <SFML/Graphics.hpp>

const static int R = 0;
const static int G = 1;
const static int B = 2;
const static int A = 3;

class AI {
public:
	Data_Store* d;
	Results* r;
	Mod_Master* m;
	Evaluation* e;

	int bytes_per_pixel;
	
	sf::RenderWindow* AI_window;
	sf::Color win_bg_color; 
	
	sf::Texture AI_vision_texture;
	sf::Sprite AI_vision_sprite;

	sf::Texture AI_map_texture;
	sf::Sprite AI_map_sprite;


	sf::Event event;

	sf::Uint8 * map_pixels = NULL;
	sf::Uint8 * vision_pixels = NULL;

	int GUI; 
	

	AI();
	
	void initialize_data_store(int map_x_size, int map_y_size, int act_x_size, int act_y_size, int v_radius);
	void initialize_results();
	void initialize_mod_master();
	void initialize_evaluation();

	void set_vision_data(char* vision_grid);
	void get_move();
	void set_location(int x, int y);
	void set_destination(int x, int y);
	
	void launch_window();
	void show_vision();
	void show_field();
	void show_attractivness();

	unsigned char get_pixel_for_char(char map_char, int pixel_type);

};

#endif
