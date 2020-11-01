#include <iostream>
#include <cstdio>
#include "sudoku.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============" << "\n\n";

  cout << "Calling load_board():" << '\n';
  load_board("easy.dat", board);

  cout << '\n' << "Displaying Sudoku board with display_board():" << '\n';
  display_board(board);
  cout << "Done!" << "\n\n";

  cout << "=================== Question 1 ===================" << "\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete." << "\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete." << "\n\n";
  
  cout << "=================== Question 2 ===================" << "\n\n";

  load_board("easy.dat", board);
  
  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);
  
  // write more tests
  
  cout << "=================== Question 3 ===================" << "\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful." << '\n';
  } else {
    cout << "Save board failed." << '\n';
  }
  cout << '\n';
  
  cout << "=================== Question 4 ===================" << "\n\n";

  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';
    
  load_board("mystery1.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';
  
  load_board("mystery2.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }

 
  cout << '\n';

  load_board("mystery3.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  // write more tests

  cout << "=================== Question 5 ===================" << "\n\n";

  // write more tests
  
  /* Counting the number of mistakes. */
  
  cout << "Counting the number of mistakes::" << endl << endl;
  
  int mistakes = 0;
  
  load_board("easy.dat", board);
  count_mistakes(board, mistakes);
  cout << "The number of mistakes made while solving Easy board is: " << mistakes;
  cout << endl << endl;
  
  load_board("medium.dat", board);
  mistakes = 0;
  count_mistakes(board, mistakes);
  cout << "The number of mistakes made while solving Medium board is: " << mistakes;
  cout << endl << endl;
  
  load_board("mystery1.dat", board);
  mistakes = 0;
  count_mistakes(board, mistakes);
  cout << "The number of mistakes made while solving Mystery1 board is: " << mistakes;
  cout << endl << endl;
  
  load_board("mystery2.dat", board);
  mistakes = 0;
  count_mistakes(board, mistakes);
  cout << "The number of mistakes made while solving Mystery2 board is: " << mistakes;
  cout << endl << endl;
  
  load_board("mystery3.dat", board);
  mistakes = 0;
  count_mistakes(board, mistakes);
  cout << "The number of mistakes made while solving Mystery3 board is: " << mistakes;
  cout << endl << endl;
 
  /* Measuring execution time. */
  
  cout << "Measuring execution time:" << endl << endl;
  
  load_board("easy.dat", board);
  measure_execution_time(board, "Easy");
  cout << endl;

  load_board("medium.dat", board);
  measure_execution_time(board, "Medium");
  cout << endl;

  load_board("mystery1.dat", board);
  measure_execution_time(board, "Mystery1");
  cout << endl;

  load_board("mystery2.dat", board);
  measure_execution_time(board, "Mystery2");
  cout << endl;

  load_board("mystery3.dat", board);
  measure_execution_time(board, "Mystery3");
  cout << endl;

  return 0;
}
