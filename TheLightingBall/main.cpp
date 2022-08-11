#include "raylib.h"
#include "maze.h"
#include "randomMaze.h"
#include <ctime>

int main(void)
{
	std::srand(std::time(nullptr));
	// prepare maze
	const int screenWidth = 800;
	const int screenHeight = 450;
	const int col = 20, row = 40;
	RectangleMaze maze = RectangleMaze(col, row);
	random_maze(maze);
	float display_perpotion = 0.8;
	float width_factor = screenWidth * display_perpotion / col;
	float height_factor = screenHeight * display_perpotion / row;
	float s_len = std::min(width_factor, height_factor);
	float maze_width = s_len * col, maze_height = s_len * row;
	float start_x = ((float)screenWidth - maze_width) / 2.0, start_y = ((float)screenHeight - maze_height) / 2.0;
	std::vector<Line> maze_image = maze.draw();
	InitWindow(screenWidth, screenHeight, "Maze Generate");

	Camera2D camera = { 0 };
	camera.target = { 0,0 };
	camera.offset = { start_x, start_y };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())        // Detect window close button or ESC key
	{
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(WHITE);

		BeginMode2D(camera);
		for (auto& line : maze_image) {
			DrawLine(line[0].x * s_len, line[0].y * s_len, line[1].x * s_len, line[1].y * s_len, BLACK);
		}

		EndMode2D();
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}