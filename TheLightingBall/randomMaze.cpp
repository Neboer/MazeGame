#include "randomMaze.h"
#include <cstdlib>
#include <algorithm>

bool bound_check(int col, int row, Point test_p) {
	return test_p.x >= 0 && test_p.y >= 0 && test_p.x < col&& test_p.y < row;
}

template <typename T>
T pop_random(std::vector<T>& v) {
	int random_index = rand() % v.size();
	T item = std::move(v[random_index]);
	v.erase(v.begin() + random_index);
	return item;
}

void dfs(RectangleMaze& maze, Point current, std::vector<std::vector<bool>>& visit_table) {
	visit_table[current.y][current.x] = true;
	MazeCell& current_cell = maze.at(current);
	std::vector<Direct> maybe_directions = {up, down, right, left};

	while (maybe_directions.size() > 0)
	{
		Direct curr_dir = pop_random<Direct>(maybe_directions);
		Point target = current.offset(dir2offset[curr_dir]);
		if (!current_cell.neigh[curr_dir] &&
			bound_check(maze.col, maze.row, target) &&
			!visit_table[target.y][target.x])
		{
			maze.add_line(current, curr_dir);
			dfs(maze, current.offset(dir2offset[curr_dir]), visit_table);
		}
	}
}

void random_maze(RectangleMaze& maze) {
	std::vector<std::vector<bool>> visit_table(maze.row, std::vector<bool>(maze.col, false));
	dfs(maze, { 0,0 }, visit_table);
}