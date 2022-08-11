#pragma once
#include<vector>
#include<array>
#include<raylib.h>
struct Point
{
	int x;
	int y;
	Point offset(Point in);
	bool operator==(const Point& p);
};

using Line = std::array<Point, 2>;

enum Direct
{
	up = 0,
	down = 1,
	right = 2,
	left = 3
};

constexpr std::array<Point, 4> dir2offset = {
	Point{0, -1},
	{0, 1},
	{1, 0},
	{-1, 0}
};

struct MazeCell
{
	bool is_start, is_dest;
	std::array<bool, 4> neigh;
	std::vector<Line> draw();
};

class RectangleMaze {
public:
	int col, row;
	Point start, dest;
	std::vector<std::vector<MazeCell>> cells;
	std::vector<Line> draw();
	RectangleMaze(int c, int r);
	MazeCell& at(Point p);
	void add_line(Point base, Direct dir);
};

