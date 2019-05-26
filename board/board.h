#pragma once
#include "../matrix/matrix.h"
#include <vector>
#include <array>
#include <map>
#include <thread>
#include <mutex>

struct MatrixPosition
{
	int row;
	int column;
	int step_count;
};

enum class BoardState
{
	NOT_VISITED,
	VISITED
};

class Vector3D;

class Board
{
private:
    std::mutex knights_tour_thread_mutex;
	std::vector<std::pair<int, int>> moves = { std::make_pair(-2, 1),
											  std::make_pair(-1, 2),
											  std::make_pair(1, 2),
											  std::make_pair(2, 1),
											  std::make_pair(2, -1),
											  std::make_pair(1, -2),
											  std::make_pair(-1, -2),
											  std::make_pair(-2, -1) };
	std::vector<MatrixPosition> path;
	Matrix<BoardState> grid;

	const int cell_size = 50;
	const int cube_size = 50;
	const int knight_path_drawing_delay = 60;
	int board3d_starting_position_x = 0;
	int board3d_starting_position_y = 0;

	int size = 8;
	int minimum_steps_for_knights_tour = size * size;
	int knight_starting_row = 0;
	int knight_starting_column = 0;
	int current_index_for_2d_path = 0;
	int current_index_for_3d_path = 0;

	bool is_move_valid(int row, int column);
	bool is_visited(int row, int column);
	bool find_path(int step_count, int row, int column);
	std::multimap<int, std::pair<int, int>> get_ordered_moves(int current_row, int current_column);
	void reset();

public:
	Board();
	void handle_events();
	void resize(int size);
	void set_mininum_tour_steps(int steps);
	int get_minimum_tour_steps() const noexcept;
	void find_knights_path();
	int get_size() const noexcept;
	std::pair<int, int> get_board_pos_regarding_mouse();
	void draw_2d();
	void draw_3d();
	void draw_knights_path_3d();
	void draw_knights_path_2d();
	void draw_mouse_position();
};
