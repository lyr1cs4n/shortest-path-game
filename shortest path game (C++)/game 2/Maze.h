#pragma once

#include <iostream>
#include <sfml/Audio.hpp>
#include <sfml/graphics.hpp>
#include <sfml/system.hpp>
#include <sfml/network.hpp>
#include <sstream>
#include <chrono>
#include <thread>
#include "player.h"
#include <fstream>
#include <queue>

using namespace sf;
using namespace std;

class Maze
{
private:
	int row ;
	int col ;
	int player_x;
	int player_y;
	int playerj;
	int playeri;
	bool check;
	pair<int, int> start;
	pair<int, int> target;
	

	ifstream sin;

	vector<vector<char>> arr;
	vector<vector<int>> adj_matrix;
	vector<vector<Sprite>> mazes;
	vector<pair<int, int>> path;


	Sprite maze;
	Player* player;
	Texture wall;
	Texture grass;
	Texture End;
	Texture Path;
	Font font;
	Text ui;
	


public:
	RenderWindow* window;
	Maze(RenderWindow* win);
	virtual~Maze();

	void initvariables();
	void initfont();
	void initui();
	void declarePath();
	void bfs_shortestpath();
	void initTexture();
	void movement();
	void initPlayer(RenderWindow* window);
	void render(RenderTarget* win);
	void initMaze();
};

