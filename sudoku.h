void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);
bool is_complete(const char board[9][9]); // checks whether there are cells without digits
bool is_complete(const char board[9][9], int &empty_row, int &empty_column); //also returns the first empty row and column
bool make_move(const char* position, char digit, char board[9][9]); // places a character into a cell if constraints are satisfied
bool is_position_valid(int row, int column, char digit, const char board[9][9]); //check whether all sudoku rules are satisfied
bool save_board(const char *filename, const char board[9][9]); // saves a board to a file
bool solve_board(char board[9][9]); // solves sudoku board
bool count_mistakes(char board[9][9], int &mistakes); // counts the number of mistakes the algorithm makes
void measure_execution_time(char board[9][9], const char* board_name); // measures solve_board function execution time 
