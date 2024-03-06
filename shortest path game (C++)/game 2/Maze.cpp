#include "Maze.h"

void Maze::initvariables()
{
	row = 10;
	col = 10;

	player_x = 0;
	player_y = 0;
	finished = false;
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
void Maze::initMaze(RenderWindow& window) {
	// Create a blank maze
	bool check2 = false;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			arr[i][j] = ' ';
			adj_matrix[i][j] = 1;
			mazes[i][j].setTexture(grass);
			mazes[i][j].setPosition(j * 70, i * 70);
		}
	}
	// Initialize start and end points to invalid values
	start = { 0, 0 };
	target = { 0, 0 };
	arr[0][0] = 's';
	this->initPlayer(&window);
	player->getplayer().setPosition(player_x * 70 + 10, player_y * 70);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				else if (event.key.code == sf::Keyboard::S) { // Set start point
					// Reset previous position
					
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					int x = mousePos.x / 70;
					int y = mousePos.y / 70;
					if (isValidCell(prev_player_x, prev_player_y) && arr[y][x] != 'h' && arr[y][x] != 'e') {
						arr[prev_player_y][prev_player_x] = ' ';
						mazes[prev_player_y][prev_player_x].setTexture(grass);
					}
					if (isValidCell(x, y) && arr[y][x] == ' ') {
						start = { y, x };
						adj_matrix[y][x] = 1;
						arr[y][x] = 's';
						player_x = mousePos.x / 70;
						player_y = mousePos.y / 70;
						player->getplayer().setPosition(player_x * 70 + 10, player_y * 70 );
						prev_player_x = x;
						prev_player_y = y;
					}
				}
				else if (event.key.code == sf::Keyboard::E) { // Set end point
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					int x = mousePos.x / 70;
					int y = mousePos.y / 70;
					if (isValidCell(x, y)) {
						// Clear previous end point if it exists
						if (isValidCell(prev_end_y, prev_end_x) && arr[prev_end_y][prev_end_x] == 'e') {
							arr[prev_end_y][prev_end_x] = ' ';
							mazes[prev_end_y][prev_end_x].setTexture(grass);
						}
						// Toggle effect for the new end point
						else if (arr[y][x] == 'e') {
							arr[y][x] = ' ';
							mazes[y][x].setTexture(grass);
						}
						else if (arr[y][x] != 's') {
							target = { y, x };
							adj_matrix[y][x] = 1;
							arr[y][x] = 'e';
							mazes[y][x].setTexture(End);
							prev_end_x = x;
							prev_end_y = y;
						}
					}
				}
				else if (event.key.code == sf::Keyboard::R) {
					resetMaze(window);
				}

				else if (event.key.code == sf::Keyboard::P) { // Start pathfinding
					check2 = true;
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				// Toggle between wall and empty cell
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				int x = mousePos.x / 70;
				int y = mousePos.y / 70;
				if (isValidCell(x, y) && arr[y][x] != 's' ) {
					if (arr[y][x] == 'h') {
						adj_matrix[y][x] = 1;
						arr[y][x] = ' ';
						mazes[y][x].setTexture(grass);
					}
					else {
						if (arr[y][x] != 's' )
						{
							adj_matrix[y][x] = 0;
							arr[y][x] = 'h';
							mazes[y][x].setTexture(wall);
						}
					}
				}
			}
		}
		if (check2) {
			this->bfs_shortestpath();
			this->declarePath();
			this->initPlayer(&window);
			this->initui();
			this->movement();
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
					resetMaze(window);
					initializeMaze(); // Call initializeMaze to start the maze again
					return;
				}
			}
			break;
		}
		window.clear();
		render(&window);
		window.display();
	}
}
void Maze::guideText()
{
	stringstream x;
	x << " \t\tWall : Left click \t\t\t\t\t\t\t\t\t\t\t Player Position : S \n \t\tGate : E\t\t\t\t\t\t\t\t\t\t\t\t\t\t   Reset : R\n\t\t\t\t\t\t\t\t\t\t\t\t Run : P";
	textguide.setString(x.str());
	textguide.setFillColor(Color::White);
	textguide.setPosition(0, 702);
	textguide.setStyle(sf::Text::Bold);
	textguide.setCharacterSize(50);
	textguide.setOutlineColor(Color::Black);
	textguide.setOutlineThickness(5);
}

void Maze::resetMaze(RenderWindow& window) {
	// Clear the maze arrays
	arr.clear();
	adj_matrix.clear();

	// Resize and initialize the arrays
	arr.resize(row, std::vector<char>(col, ' '));
	adj_matrix.resize(row, std::vector<int>(col, 1));

	// Reset the maze
	bool check2 = false;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			arr[i][j] = ' ';
			adj_matrix[i][j] = 1;
			mazes[i][j].setTexture(grass);
			mazes[i][j].setPosition(j * 70, i * 70);
		}
	}

	// Initialize start and end points to invalid values
	start = { 0, 0 };
	target = { 0, 0 };
	arr[0][0] = 's';
	prev_player_x = 0;
	prev_player_y = 0;
	player_x = 0;
	player_y = 0;
	prev_end_x = -1;
	prev_end_y = -1;

	// Initialize player position
	this->initPlayer(&window);
	player->getplayer().setPosition(player_x * 70 + 10, player_y * 70);
}
bool Maze::isValidCell(int x, int y) {
	return x >= 0 && x < col && y >= 0 && y < row;
}
void Maze::initfont() // font
{
	if (!font.loadFromFile("Materials/Dosis-Light.ttf"))
	{
		cout << "Could Not Load Font" << endl;
	}
	ui.setFont(font);
	ui.setCharacterSize(24);
	ui.setFillColor(sf::Color::White);
	ui.setStyle(sf::Text::Bold);

	textguide.setFont(font);
	textguide.setCharacterSize(24);
	textguide.setFillColor(sf::Color::White);
	textguide.setStyle(sf::Text::Bold);

	// Center the text
	sf::FloatRect textBounds = ui.getLocalBounds();
	ui.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	ui.setPosition(window->getSize().x / 2.0f, window->getSize().y / 2.0f);

	// Apply shadow effect
	sf::Text shadowText(ui);
	shadowText.setFillColor(sf::Color(0, 0, 0, 150)); 
	shadowText.move(2, 2); 

}
void Maze::initui() // initialize the path not found text
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
void Maze::bfs_shortestpath() //algorithm to find the shortest path
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
void Maze::movement() {
	sf::Clock clock;
	sf::Time delay = sf::seconds(0.5f);

	for (size_t i = 1; i < path.size(); ++i) { // Start from index 1 to skip the initial position
		int dest_y = path[i].first * 70;
		int dest_x = path[i].second * 70;

		sf::Vector2f playerPos = player->getplayer().getPosition();
		float startX = playerPos.x;
		float startY = playerPos.y;

		// Determine the direction to move
		int directionX = (dest_x > startX) ? 1 : ((dest_x < startX) ? -1 : 0);
		int directionY = (dest_y > startY) ? 1 : ((dest_y < startY) ? -1 : 0);

		while (startX != dest_x || startY != dest_y) {
			float deltaTime = clock.restart().asSeconds();
			float moveStep = 200.0f * deltaTime; // Adjust the move speed as needed

			// Move horizontally
			if (startX != dest_x) {
				float newX = startX + directionX * moveStep;
				if ((directionX > 0 && newX > dest_x) || (directionX < 0 && newX < dest_x)) {
					startX = dest_x;
				}
				else {
					startX = newX;
				}
			}

			// Move vertically
			if (startY != dest_y) {
				float newY = startY + directionY * moveStep;
				if ((directionY > 0 && newY > dest_y) || (directionY < 0 && newY < dest_y)) {
					startY = dest_y;
				}
				else {
					startY = newY;
				}
			}

			// Set the new position of the player
			player->getplayer().setPosition(startX, startY);

			// Redraw the window
			window->clear();
			this->render(window);
			window->display();
		}
	}
}
void Maze::declarePath() // highlight the path
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
		window->draw(textguide);
}
Maze::Maze(RenderWindow* win) {
	window = win;
	initializeMaze();
}
void Maze::initializeMaze() {
	this->initvariables();
	this->guideText();
	this->initfont();
	this->initTexture();
	this->initMaze(*window);
}

Maze::~Maze()
{

}