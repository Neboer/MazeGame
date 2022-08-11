#include "maze.h"
#include <cstdlib>

RectangleMaze::RectangleMaze(int c, int r)
{
	col = c;
	row = r;
	cells = std::vector<std::vector<MazeCell>>
		(row, std::vector<MazeCell>(col, MazeCell{ false, false,  {false}}));
}

Point Point::offset(Point in) {
	return { x + in.x, y + in.y };
}

bool Point::operator==(const Point& p) {
	return p.x == x && p.y == y;
}

std::vector<Line> MazeCell::draw() {
	std::vector<Line> result = {};
	if (!neigh[up])
		result.push_back(Line{ Point{0,0}, Point{1,0} });
	if (!neigh[down])
		result.push_back(Line{ Point{0,1}, Point{1,1} });
	if (!neigh[left])
		result.push_back(Line{ Point{0,0}, Point{0,1} });
	if (!neigh[right])
		result.push_back(Line{ Point{1,0}, Point{1,1} });
	return result;
}

std::vector<Line> RectangleMaze::draw() {
	std::vector<Line> result = {};
	for (int y = 0; y < row; y++) {
		for (int x = 0; x < col; x++) {
			Point left_up_offset = { x, y };
			auto relative_lines = cells[y][x].draw();
			for (auto& pre_line : relative_lines) {
				pre_line[0]= pre_line[0].offset(left_up_offset);
				pre_line[1]= pre_line[1].offset(left_up_offset);
			}
			result.insert(result.end(), relative_lines.begin(), relative_lines.end());
		}
	}
	return result;
}

MazeCell& RectangleMaze::at(Point p) {
	return cells[p.y][p.x];
}

void RectangleMaze::add_line(Point base, Direct dir) {
	cells[base.y][base.x].neigh[dir] = true;
	if (dir == up)
		cells[base.y - 1][base.x].neigh[down] = true;
	if (dir == down)
		cells[base.y + 1][base.x].neigh[up] = true;
	if (dir == right)
		cells[base.y][base.x + 1].neigh[left] = true;
	if (dir == left)
		cells[base.y][base.x - 1].neigh[right] = true;
}