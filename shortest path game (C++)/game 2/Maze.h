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
	int prev_player_x = 0;
	int prev_player_y = 0;
	int prev_end_x = -1;
	int prev_end_y = -1;
	bool check;
	bool finished;
	pair<int, int> start;
	pair<int, int> target;
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
	Text textguide;
	


public:
	RenderWindow* window;
	Maze(RenderWindow* win);
	void initializeMaze();
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
	void initMaze(RenderWindow& window);
	void guideText();
	void resetMaze(RenderWindow& window);
	bool isValidCell(int x, int y);
};

