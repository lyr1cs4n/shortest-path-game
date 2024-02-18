#include "Maze.h"

void Maze::initvariables()
{
	row = 10;
	col = 10;

	check = false;

	arr = std::vector<std::vector<char>>(row, std::vector<char>(col));
	mazes = vector<vector<Sprite>>(row, vector<Sprite>(col)) ;
	adj_matrix = vector<vector<int>>(row, vector<int>(col));
}
void Maze::initTexture()
{
	if (!wall.loadFromFile("Materials/brick.png"))
	{
		cout <<"Could Not Load Wall Texture"<<endl;
	}
	if (!grass.loadFromFile("Materials/grass.png"))
	{
		cout << "Could Not Load Grass Texture" << endl;
	}
	if (!End.loadFromFile("Materials/end.png"))
	{
		cout << "Could Not Load End Texture" << endl;
	}
	if (!Path.loadFromFile("Materials/path.png"))
	{
		cout << "Could Not Load End Texture" << endl;
	}
}
void Maze::initMaze()
{
	sin.open("Materials/maze.txt");
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			sin >> arr[i][j];
			if (arr[i][j] == 'h')
			{
				adj_matrix[i][j] = 0;
				mazes[i][j].setTexture(wall);
				mazes[i][j].setPosition(j * 70.f, i * 70.f);
			}
			else if (arr[i][j] == 'e')
			{
				target.first = i;
				target.second = j;
				adj_matrix[i][j] = 1;

			}
			else {
				if (arr[i][j] == 's')
				{
					start.first = i;
					start.second = j;
					player_x = j;
					player_y = i;
				}
				adj_matrix[i][j] = 1;
				mazes[i][j].setTexture(grass);
				mazes[i][j].setPosition(j * 70, i * 70);
			}
		}
	}

}
void Maze::initfont()
{
	if (!font.loadFromFile("Materials/Dosis-Light.ttf"))
	{
		cout << "Could Not Load Font" << endl;
	}
	ui.setFont(font);
}
void Maze::initui()
{
	stringstream ss;
	ss << "Path Not Found";
	ui.setString(ss.str());
	ui.setFillColor(Color::White);
	ui.setPosition(window->getSize().x/2 -140, window->getSize().y / 2-50);
	ui.setStyle(sf::Text::Bold);
	ui.setCharacterSize(50);
	ui.setOutlineColor(Color::Black);
	ui.setOutlineThickness(5);
}
void Maze::bfs_shortestpath()
{
	int numRows = adj_matrix.size();
	int numCols = adj_matrix[0].size();

	int startNode = start.first * numCols + start.second;
	int targetNode = target.first * numCols + target.second;

	queue<int> q;
	vector<bool> visited(numRows * numCols, false);
	vector<int> parent(numRows * numCols, -1);
	visited[startNode] = true;
	q.push(startNode);

	while (!q.empty()) {
		int curr = q.front();
		q.pop();
		if (curr == targetNode) {
			check = true;
			int node = targetNode;
			while (node != startNode) {
				int row = node / numCols;
				int col = node % numCols;
				path.push_back({ row, col });
				node = parent[node];
			}
			path.push_back(start);
			reverse(path.begin(), path.end());
				cout << "Shortest Path: ";
				for (const auto& p : path) {
					cout << "(" << p.first << ", " << p.second << ") ";
				}
				cout << endl;
				return;
		}
		int currRow = curr / numCols;
		int currCol = curr % numCols;
		int dx[] = { -1, 1, 0, 0 };
		int dy[] = { 0, 0, -1, 1 };
		for (int i = 0; i < 4; i++) {
			int newRow = currRow + dx[i];
			int newCol = currCol + dy[i];
			if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols &&
				adj_matrix[newRow][newCol] && !visited[newRow * numCols + newCol]) {
				int newNode = newRow * numCols + newCol;
				q.push(newNode);
				visited[newNode] = true;
				parent[newNode] = curr;
			}
		}
	}
}
void Maze::movement()
{
	sf::Clock clock;
	sf::Time delay = sf::seconds(0.5f);

	for (const auto& p : path) {
		playeri = p.first;
		playerj = p.second;
		player->getplayer().setPosition(playerj * (window->getSize().x / 10 +3), playeri * (window->getSize().y / 10) );
		clock.restart();

		while (clock.getElapsedTime() < delay) {
			sf::Event event;
			window->clear();
			this->render(window);
			window->display();
			Event ev;
			 while (window->pollEvent(ev))
    {
        if (ev.key.code == Keyboard::Escape)
        {
            window->close();
        }
        if (ev.type == Event::Closed)
        {
            window->close();
        }
    }
		}
	}
}
void Maze::declarePath()
{
	for (const auto& p : path) {
		
		mazes[p.first][p.second].setTexture(Path);

		}
	if (check == true) {
		mazes[target.first][target.second].setTexture(End);
		mazes[target.first][target.second].setPosition(target.second * 70.f, target.first * 70.f);
	}

}
void Maze::initPlayer(RenderWindow* window)
{
	player = new Player(player_x * 80, player_y * 70);
}
void Maze::render(RenderTarget* window)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			window->draw(mazes[i][j]);
		}
	}
	window->draw(player->getplayer());
	if (check == false)
	{
		window->draw(ui);
	}
}
Maze::Maze(RenderWindow* win)
{
	window = win;
	this->initvariables();
	this->initTexture();
	this->initMaze();
	this->bfs_shortestpath();
	this->declarePath();
	this->initPlayer(win);
	this->initfont();
	this->initui();
	this->movement();

}
Maze::~Maze()
{

}