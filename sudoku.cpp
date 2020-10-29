#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!" << '\n';
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+" << '\n';
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

bool is_complete(const char board[9][9]){
  for(int i = 0; i<9; i++){
    for(int j = 0; j<9; j++){
      if(board[i][j] < 49 || board[i][j] > 57)
	return false;
    }
  }
  return true;
}

bool make_move(const char position[2], char digit, char board[9][9]){
  int row = position[0] - 64 - 1;
  int column = position[1] - 48 -1;
  if(is_position_valid(row, column, digit, board)){
    board[row][column] = digit;
    return true;
  }
  return false;
}

bool is_position_valid(int row, int column, char digit, const char board[9][9]){
  int quadrant_row = row - row%3;
  int quadrant_column = column - column%3;
  if(board[row][column] != '.')
     return false;
  for(int i = 0; i < 9; i++){
    if(board[i][column] == digit)
      return false;
  }
  for(int i = 0; i < 9; i++){
    if(board[row][i] == digit)
      return false;
  }
  for(int i = 0; i<3; i++){
    for(int j = 0; j<3; j++){
      if(board[quadrant_row + i][quadrant_column + j] == digit)
	return false;
    }
  }
  return true;
}

bool save_board(const char* filename, const char board[9][9])
{
  ofstream out_stream;
  out_stream.open(filename);
  if(out_stream.fail())
    return false;
  for(int row = 0; row < 9; row++){
    for(int column = 0; column < 9; column++){
      out_stream.put(board[row][column]);
    }
    out_stream.put('\n');
  }
  out_stream.close();
  return true;
}
    
void print_board(const char board[9][10]){
  for(int i = 0; i<9; i++){
    for(int j = 0; j<10; j++){
      cout << board[i][j] << " ";
     
    }
    cout << endl;
  }
}
/*
bool solve_board_v0(char board[9][9])
{
  char value;
  for(int i = 0; i<9; i++){
    for(int j = 0; j<9; j++){
      value = find_possible_values(i,j,board);
      if(value != '\0'){
	board[i][j] = value;
	display_board(board);
	cout << endl;
      }
    }
  }  
  if(!is_complete(board)){
    solve_board(board);
  }
  return true;
}
*/

void find_possible_values(int row, int column, char quadrant[9][10], char board[9][9]){
  int position_index = 0, value_index = 0;
  char digit;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
	for(int k = 1; k < 10; k++){
	  digit = k + 48; 
	  if(is_position_valid(row+i, column+j, digit, board)){
	     quadrant[position_index][value_index] = digit;
	     value_index++;
	    }
	}
	  quadrant[position_index][value_index] = '\0';
	  position_index++;
	  value_index = 0;
	}
      }
}

void find_possible_values_row(int row, char row_values[9][10], char board[9][9]){
  int position_index = 0, value_index = 0, column = 0;
  char digit;
  
  for(int i = 0; i < 9; i++){
       for(int k = 1; k < 10; k++){
	 digit = k + 48; 
	 if(is_position_valid(row, column+i, digit, board)){
	    row_values[position_index][value_index] = digit;
            value_index++;
	 }
	}
	  row_values[position_index][value_index] = '\0';
	  position_index++;
	  value_index = 0;
	}
}

void find_possible_values_column(int column, char column_values[9][10], char board[9][9]){
  int position_index = 0, value_index = 0, row = 0;
  char digit;
  
  for(int i = 0; i < 9; i++){
       for(int k = 1; k < 10; k++){
	 digit = k + 48; 
	 if(is_position_valid(row + i, column, digit, board)){
	    column_values[position_index][value_index] = digit;
            value_index++;
	 }
	}
	  column_values[position_index][value_index] = '\0';
	  position_index++;
	  value_index = 0;
	}
}


bool solve_quadrant(int row, int column, char board[9][9]){
  char quadrant[9][10], unique_values[10];
  int quadrant_row = row - row%3;
  int quadrant_column = column - column%3;
  int k = 0;
  bool move_made = false;
  find_possible_values(quadrant_row, quadrant_column, quadrant, board);
  find_unique_solutions(quadrant, unique_values);
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      while(unique_values[k] != '\0'){
	if(is_position_valid(quadrant_row+i, quadrant_column+j, unique_values[k], board)){
	  board[quadrant_row+i][quadrant_column+j] = unique_values[k];
	  move_made = true;
	} 
	k++;
      }
      k = 0;
    }
  }
  return move_made;
}

bool solve_board(char board[9][9]){  
  int k = 0;
  bool quadrant_solution, row_solution, column_solution, unique_solution;
  while(k != 10000){
  for (int i = 0; i < 9; i = i + 3){
    for(int j = 0; j < 9; j = j + 3){
      quadrant_solution = solve_quadrant(i, j, board);
    }
  }
  for(int i = 0; i < 9; i++){
    row_solution = solve_row(i, board);
    column_solution = solve_column(i, board);
  }
  
  unique_solution = solve_unique_value_cells(board);
  
  k++;
  }
  if(!is_complete(board) && (quadrant_solution ||column_solution || row_solution || unique_solution))
    solve_board(board);
  else if(is_complete(board))
    return true;
  
  if(backtracking_algorithm(board))
    return true;
  return false;
}
  
void find_unique_solutions(char array[9][10], char unique_values[10]){
  int count_value_duplicates[9] = {0};
  int digit, j = 0;
  for(int i = 0; i < 9; i++){
    while(array[i][j] != '\0'){
      digit = array[i][j] - 48;
      count_value_duplicates[digit-1]++;
      j++;
    }
    j = 0;
  }
  for(int i = 0; i < 9; i++){
    if(count_value_duplicates[i] == 1){
      unique_values[j] = i + 48 + 1;
      j++;
    }
  }
  unique_values[j] = '\0';
}

bool solve_row(int row, char board[9][9]){
  char row_values[9][10], unique_values[10];
  int k = 0, column = 0;
  bool move_made = false;
  find_possible_values_row(row, row_values, board);
  find_unique_solutions(row_values, unique_values);
  for(int i = 0; i < 9; i++){
     while(unique_values[k] != '\0'){
       if(is_position_valid(row, column+i, unique_values[k], board)){
	 board[row][column+i] = unique_values[k];
	 move_made = true;
       }
       k++;    
    }
      k = 0;
  }
  return move_made;
}

bool solve_column(int column, char board[9][9]){
  char column_values[9][10], unique_values[10];
  int k = 0, row = 0;
  bool move_made = false;
  find_possible_values_column(column, column_values, board);
  find_unique_solutions(column_values, unique_values);
  for(int i = 0; i < 9; i++){
     while(unique_values[k] != '\0'){
       if(is_position_valid(row + i, column, unique_values[k], board)){
	 board[row + i][column] = unique_values[k];
	 move_made = true;
       }
       k++;    
    }
      k = 0;
  }
  return move_made;
}

bool solve_unique_value_cells(char board[9][9]){
  char value;
  int count_possible_values;
  bool move_made = false;
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      count_possible_values = 0;
      for(int k = 1; k < 10; k++){
	if(is_position_valid(i, j, k + 48, board)){
	    value = k + 48;
	    count_possible_values++;
	  }
	
      }
      if(count_possible_values == 1){
	  board[i][j] = value;
	  move_made = true;
      }
	
    }
  }
  return move_made;
  }
/*
void guess_values(char board[9][9], const char previous_board[9][9]){
  char values[9], board_copy[9][9];
  int count_possible_values, random_number;
  
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      board_copy[i][j] = board[i][j];
    }
  }
  
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      count_possible_values = 0;
      for(int k = 1; k < 10; k++){
	if(is_position_valid(i, j, k + 48, board_copy)){
	    values[count_possible_values] = k + 48;
	    count_possible_values++;
	  }
	
      }
      if(count_possible_values > 1 && count_possible_values < 3){
	random_number = rand() % count_possible_values;
	while(values[random_number] == previous_board[9][9]){
	  random_number = rand() % count_possible_values;
	}
	board_copy[i][j] = values[random_number];
      }else if(count_possible_values == 1){
	board_copy[i][j] = values[0];
      }
	
    }
  }
  
  if(!is_complete(board_copy))
    guess_values(board, board_copy);
  else{
    for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
	board[i][j] = board_copy[i][j];
      }
    }
  }
  }
*/  
bool backtracking_algorithm(char board[9][9]){
  int row,column;
  char value;
  if(is_complete(board))
     return true;
  find_empty_cell(board, row, column);
  for(int k = 1; k < 10; k++){
    value = k + 48;
    if(is_position_valid(row, column, value, board)){
      board[row][column] = value;
      if(backtracking_algorithm(board))
	return true;
      board[row][column] = '.';
    }
  }
  return false;
}

int find_empty_cell(const char board[9][9], int &row, int &column){
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(board[i][j] == '.'){
	row = i;
	column = j;
	return 0;
    }
  }
  }
  return 0;
}
