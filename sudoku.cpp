#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <chrono>
#include "sudoku.h"

using namespace std;
using namespace std::chrono;

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

/* C++ Programming - Assessed Exercise 1 */


/* ..........................Task 1.............................*/


/* Function is_complete takes a 9x9 array of characters and
 returns true if all board positions are occupied by
 digits from 1 to 9. If some of the cells contain 0
 it also returns false. */

bool is_complete(const char board[9][9]){
  
  for(int row = 0; row < 9; row++){                           //Goes through rows.
    for(int column = 0; column < 9; column++){                //Goes through columns.
      if(board[row][column] < 49 || board[row][column] > 57)  //Checks whether a cell contains a character between 1 and 9 by looking at the ASCII code of a character. 
	return false;
    }
  }
  return true;
}

/* ..........................Task 2.............................*/


/* Function make_move places a digit onto a Sudoku board
   if a specified cell does not contain another digit and
   the move is allowed by Sudoku rules. It takes a constant
   array of characters as a position argument, character 
   "digit" takes the value of a digit to placed and a 9x9
   character array "board" contains a sudoku board. */

bool make_move(const char* position, char digit, char board[9][9]){
  
  if(position[2] != '\0')            //Checks that there are only two characters in the position string
    return false;
  
  int row = position[0] - 65;        // Converts a character to integer between 1 and 8 using ASCII standard.
  int column = position[1] - 49;     // Converts a character to integer between 1 and 8 using ASCII standard.
  
  if((row >= 0 && row < 9) && (column >= 0 && column < 9) && (digit >= 49 && digit <= 57) &&  is_position_valid(row, column, digit, board)){ // Checks whether position coordonates are in
    board[row][column] = digit;                                                                                                              // the range and the digit is between 1 and 9.
    return true;                                                                                                                             // is_position_valid does further checks.
  }                                                                                                                                          // If conditions are satified, assigns value
  return false;                                                                                                                              // and returns true. Otherwise returns false.
}

/* Function is_position_valid checks whether Sudoku rules are 
  satisfied. It takes integers row and column to identify a position
  on the board, characater "digit" is a digit to be placed and
  "board" array is a Sudoku board.*/

bool is_position_valid(int row, int column, char digit, const char board[9][9]){
  
  int quadrant_row = row - row%3; // Calculates the first row of the board quadrant where the supplied position locates. 
  int quadrant_column = column - column%3; // Calculates the first column of the board quadrant where the supplied position locates.
  
  if(board[row][column] >= 49 && board[row][column] <= 57) // Checks whether a cell with the suppplied coordinates contains the digit.
     return false
       ;
  for(int i = 0; i < 9; i++){     //Checks whether the supplied row contains the digit.
    if(board[i][column] == digit)
      return false;
  }
  
  for(int i = 0; i < 9; i++){     //Checks whether the supplied column contains the supplied digit.
    if(board[row][i] == digit)
      return false;
  }
  
  for(int i = 0; i<3; i++){       //Checks whether the quadrant where the digit is to be place already contains it.  
    for(int j = 0; j<3; j++){
      if(board[quadrant_row + i][quadrant_column + j] == digit)
	return false;
    }
  }
  
  return true;                    //Returns true if all checks were passed.
}

/* ..........................Task 3.............................*/


/* Function save_board outputs a Sudoku board to a file with a name
   passed throught a parameter "filename".*/

bool save_board(const char* filename, const char board[9][9]){
  
  ofstream out_stream;
  
  out_stream.open(filename);                        //Creates a new file or cleans up the old one. 
  if(out_stream.fail())                             //Checks that file is not corrupted.
    return false;
  
  for(int row = 0; row < 9; row++){                 //Goes through rows and columns to copy the file.
    for(int column = 0; column < 9; column++){
      out_stream.put(board[row][column]);
    }
    out_stream.put('\n');
  }
  
  out_stream.close(); 
  
  return true;
}

/* ..........................Task 4.............................*/


/* Function solve_board takes a 9x9 Sudoku board as an input and solves it. 
   It outputs true if the solution was found and false otherwise. The function 
   employs recursive back tracking algorithm, which tries different cell inputs 
   and returns back if the solution can't be found in order to alter previous cell value.  */

bool solve_board(char board[9][9]){

  int empty_row, empty_column;
  char value;
  
  if(is_complete(board,empty_row,empty_column))                     //Checks whether a supplied board contains empty cells and returns row and column of the first empty cell. 
    return true;                                                    //Returns true if board is complete.
  
  for(int digit = 1; digit < 10; digit++){                          //Goes through all possible characters.
    value = digit + 48;                                             //Converts integer into a character using ASCII standard.
    if(is_position_valid(empty_row, empty_column, value, board)){   
      board[empty_row][empty_column] = value;                       //Places a digit if the position is valid. 
      if(solve_board(board))                                        //Function calls itself recursivly. 
	return true;                                                //Returns true if the board is complete in the next step. If true is returned, the function goes  
                                                                    //all the way to its first call and returns a complete board.
      board[empty_row][empty_column] = '.';                         //If a mistake was made, solve_board returns false and the value in the cell is set back to '.'.
    }
  }
  return false;                                                     //Returns false if no digit can be places into a cell.
}

/* Function is_complete is overloaded, in this version of the
   function it also returns the coordinates of the first empty
   cell which are passed by reference. */

bool is_complete(const char board[9][9], int &empty_row, int &empty_column){
  
  for(int row = 0; row<9; row++){
    for(int column = 0; column<9; column++){
      if(board[row][column] < 49 || board[row][column] > 57){
	empty_row = row;                                        //Assigning empty cell row coordinate.
	empty_column = column;                                     //Assigning empty cell column coordinate.
	return false;
      }
    }
  }
  return true;
}

/* ..........................Task 5.............................*/


/* Function count_mistakes replicates the solve_board function, but 
   also counts the number of mistakes made by the algoritm. It takes
   an additional parameter mistakes passed by reference. */

bool count_mistakes(char board[9][9], int &mistakes){
  
  int row, column;
  char value;
  
  if(is_complete(board, row, column))
     return true;
  
  for(int k = 1; k < 10; k++){
    value = k + 48;
    if(is_position_valid(row, column, value, board)){
      board[row][column] = value;
      if(count_mistakes(board, mistakes))
	return true;
      mistakes ++;                                        //Increments mistakes value by 1, every time the alogoritm sets the cell value back to '.'.
      board[row][column] = '.';
    }
  }
  return false;
}

/* Function measure_execution_time measures how long it takes
   for the algoritms to solve a puzzle. */

void measure_execution_time(char board[9][9], const char* board_name){              //takes board and its name as an input
 
  auto start = high_resolution_clock::now();                                        //start stores time before the solving function executes
  solve_board(board);
  auto stop = high_resolution_clock::now();                                         //stop stores time after the solving function executes
  auto duration = duration_cast<microseconds>(stop-start);                          //duration stores the difference between start and stop in microseconds
  cout<< "The execution time for " << board_name << " board  is: " <<  duration.count() << " microseconds";
  cout<< '\n';
}


