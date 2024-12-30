/** **********************************************************************
* @file
*
* @brief The only file for this project, contains prototypes, main and
* defintions of functions.
************************************************************************/
/** ***************************************************************************
* @mainpage Thpe3 - Knight's Tour
*
* @section course_section Course Information
*
* @author Blake A. Mommaerts
*
* @date 4/25/2022
*
* @par Professor
* Roger Schrader
*
* @par Course
* CSC 215 - M001
*
* @par Location
* CB 329
*
* @section program_section Program Information
*
* @details This program is to create a chessboard with both equal width and
* length of default values 8x8 and starting position [7,7] for the knight
* piece. In chess, the knight has a unique movement pattern where it can
* move vertically two spaces then horizontally one space, or horizontally
* two spaces and vertically one space (in other words, L-shaped moves).
*
* Two algorithms can be ran depending on the amount of arguments provided
* to the program; if no arguments are entered into the command line, a menu
* is provided with the availability to make your own board and starting
* position on the board. Creating the board requires 2D allocation, the rows
* and columns being the board size. Once it's made, you can exit to attempt to
* solve the board, and it will output the first solution or a statement saying
* there were no solutions if none were found.
*
* If an argument representing an input file was included, the
* input is opened and values are read in. This way, the chessboard and
* starting positions are predetermined, and can then the tours can be solved
* thereafter, where solutions are written to an output file. Note that the
* use of plural nouns implies that more than one tour can be provided in the
* file.
*
* After the algorithms are ran, the allocated 2D arrays are freed up, files
* are closed, and the program exits with a 0. The outputs are either provided
* in an output file or the console.
*
* @section compiling_section Compiling and Usage
* @par Compiling Instructions:
*      None
*
* @par Usage:
* @verbatim
With no arguments (argc = 1):
C:\thpe3.exe

With no arguments (argc = 2):
C:\thpe3.exe [inputFile]
@endverbatim
*
* @section todo_bugs_modification_section Modifications & Development Timeline
*
* @todo Thorough testing of program
*
* @bug Some permutations take a while to load, like 7x7 [4,3], and many 8x8
* boards
*
* @par Timeline
* Visit gitlab commit log for timeline.
* <a href =
* "https://gitlab.cse.sdsmt.edu/7478473/csc215s22programs/-/commits/master/thpExam3"
* target="_blank">Click Here.</a>
*****************************************************************************/
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/** ***************************************************************************
*                                 Prototypes
******************************************************************************/

void runProgram(int argc, char** argv, int boardS, int row, int col);

void popUpMenu(int& boardS, int& rows, int& cols);

void menuCase1(int& boardS, int row, int col);

void menuCase2(int boardS, int& row, int& col);

bool openInput(ifstream& fin, string fileName);

void allocate2D(int**& board, int boardS);

void freeMemory(int**& board, int row);

void populateArray(int**& board, int boardS);

bool solveTour(int**& board, int boardS, int row, int col, int count, int tC);

bool openOutput(ofstream& fout, string fileName);

void readAndRun(ifstream& fin, ofstream& fout, int& boardS, int& row, int& col);

bool fileTour(int**& board, int boardS, int row, int col, int count, int tC,
    ofstream& fout);

/** ***************************************************************************
*                              Main + Definitions
******************************************************************************/

/** **********************************************************************
* @author Blake A. Mommaerts
*
* @par Description
* This is the main function. It will take all of the other functions and
* run them in the proper order to perform the knight's tour on a given
* chessboard and starting location.
*
* @param[in] argc The integer amount of arguments in a program
* @param[in] argv Array of each individual argument within the program
*
* @returns a 0 when the function exits successfully.
* @returns 1 error in command line arguments
* @returns 2 error in reading in values
* @returns 3 dynamic memory
*
* @par Example
* @verbatim
    see usage statement above.
@endverbatim
************************************************************************/
int main(int argc, char** argv)
{
    int boardS = 8; // default values
    int row = 7;
    int col = 7;

    runProgram(argc, argv, boardS, row, col); // executes algorithm 1/2

    return 0;
}

/** **********************************************************************
* @author Blake A. Mommaerts
*
* @par Description
* This function is a compilation function for the purpose of condensing main.
* It also performs argument checks and will exit the program if an incorrect
* amount of arguments is detected.
*
* @param[in] argc The integer amount of arguments in a program.
* @param[in] argv Array of each individual argument within the program.
* @param[in] boardS Integer representing the total rows and columns of
* the chessboard.
* @param[in] row Integer representing what row the knight is on.
* @param[in] col Integer representing what column the knight is on.
*
* @returns none
*
* @par Example
* @verbatim
    int boardS = 8; // default values
    int row = 7;
    int col = 7;

    runProgram(argc, argv, boardS, row, col);
@endverbatim
************************************************************************/
void runProgram(int argc, char** argv, int boardS, int row, int col)
{
    ifstream fin;
    ofstream fout;
    string inputName;
    int** board = nullptr;
    if (argc == 1) // Run Algorithm 1
    {
        popUpMenu(boardS, row, col); // Display Menu
    }
    else if (argc == 2) // Run Algorithm 2
    {
        inputName = argv[1]; // filename
        openInput(fin, inputName);
        openOutput(fout, "Solutions.tours");
        // once files are opened, values are read in and tours are ran
        readAndRun(fin, fout, boardS, row, col);
        fin.close(); // close files after usage
        fout.close();
    }
    else // checking for proper amount of arguments
    {
        cout << "Incorrect amount of arguments." << endl;
        cout << "Usage: thpe3.exe" << endl;
        cout << "       thpe3.exe tourfile" << endl;
        exit(1);
    }
}

/** **********************************************************************
* @author Blake A. Mommaerts
*
* @par Description
* This function creates a menu interface when ran, offering 3 options to
* the user: first, changing the board size from 8x8; second, changing the
* knight's position from [7,7]; third, exiting the menu and solving the
* knight's tour. Integers 1-3 are used respectively for the options, and
* no other forms of input are accepted.
*
* @param[in,out] boardS Integer representing the total rows and columns of
* the chessboard. Passed by reference.
* @param[in,out] row Integer representing what row the knight is on.
* Passed by reference.
* @param[in,out] col Integer representing what column the knight is on.
* Passed by reference.
*
* @returns none
*
* @par Example
* @verbatim
    see usage statement above.
@endverbatim
************************************************************************/
void popUpMenu(int& boardS, int& row, int& col)
{
    int choice, count, tC;
    count = 1;
    tC = 1;
    int** board = nullptr;
    do
    {
        //startup menu is displayed with default data in main, 8x8, [7,7]
        cout << "   1) Change Board Size from " << boardS << "x" << boardS
            << endl;
        cout << "   2) Change Starting Location from [" << row << "," << col <<
            "]" << endl;
        cout << "   3) Exit and Solve Tour" << endl;
        cout << "Enter Choice: ";

        while (!(cin >> choice) || choice > 3 || choice < 0)
        {
            // if it's not a digit or > 3, tries again for proper input
            cout << "Incorrect option. Please specify a number 1-3." << endl;
            cin.clear();
            cin.ignore(256, '\n');
            // ^ clearing the false input and preparing to loop
        }

        switch (choice)
        {
        case 1:
            menuCase1(boardS, row, col);
            cout << endl;
            break;
        case 2:
            menuCase2(boardS, row, col);
            cout << endl;
            break;
        case 3:
            allocate2D(board, boardS);
            populateArray(board, boardS);
            if (!solveTour(board, boardS, row, col, count, tC))
            {
                cout << "       ";
                cout << "No solutions for this case.";
            }
            freeMemory(board, boardS);
            break;
        }
    } while (choice != 3);
}

/** **********************************************************************
* @author Blake A. Mommaerts
*
* @par Description
* This function is a helper function to popUpMenu. If case 1 is selected
* within the menu, the user is prompted to enter one integer to determine
* the board's size. The number must be a number 3 to 8, and you cannot
* change the size to be smaller than a current position. For instance,
* you cannot change board size to 5 if your position is [6,7].
*
* @param[in,out] boardS Integer representing the total rows and columns of
* the chessboard. Passed by reference.
* @param[in] row Integer representing what row the knight is on.
* @param[in] col Integer representing what column the knight is on.
*
* @returns none
*
* @par Example
* @verbatim
    see usage statement above.
@endverbatim
************************************************************************/
void menuCase1(int& boardS, int row, int col)
{
    cout << "Enter the size of the NxN Board (>3): ";
    while (!(cin >> boardS) || boardS < 3 || boardS > 8 || (boardS - 1) < row
        || (boardS - 1 < col))
    {
        // Error statement + probable cause of failure
        if (boardS < 3 || boardS > 8)
        {
            cout << "Invalid input. Please use integer values 2<x<9."
                << endl;
        }
        if ((boardS - 1) < row || (boardS - 1 < col))
        {
            cout << "ERROR: New board size makes location out of bounds."
                << endl;
        }
        cin.clear();
        cin.ignore(256, '\n');
        // ^ clearing the false input and preparing to loop
    }
    /* checks for invalid inputs, boardSize must be 3 - 8 with values
    smaller than the new boardsize*/
}

/** **********************************************************************
* @author Blake A. Mommaerts
*
* @par Description
* This function is a helper function to popUpMenu. If case 2 is selected
* within the menu, the user is prompted to enter two integers to determine
* the knight's position on the board. The number must be a number 0 to
* 1 less than the current board size. For instance, the first and last
* position on an 8x8 board is [0,0] and [7,7], respectively.
*
* @param[in] boardS Integer representing the total rows and columns of
* the chessboard.
* @param[in,out] row Integer representing what row the knight is on.
* Passed by reference.
* @param[in,out] col Integer representing what column the knight is on.
* Passed by reference.
*
* @returns none
*
* @par Example
* @verbatim
    see usage statement above.
@endverbatim
************************************************************************/
void menuCase2(int boardS, int& row, int& col)
{
    // starting message for case 2
    cout << "Enter Starting Coordinates [ row , col ]: ";
    while (!(cin >> row >> col) || row < 0 || col < 0 || row > 7 || col > 7
        || (boardS - 1) < row || (boardS - 1 < col))
    {
        // Error statement + probable cause of failure
        if (row < 0 || col < 0 || row > 7 || col > 7)
        {
            cout << "Invalid input. Please use integer values 0<x<" << boardS
                << "." << endl;
        }
        if ((boardS - 1) < row || (boardS - 1) < col)
        {
            cout << "ERROR: Location goes out of bounds." << endl;
        }
        cin.clear();
        cin.ignore(256, '\n'); // ignore the prior input
    }
    // checks for invalid inputs, rows/cols are 0/7 and < (board size-1)
}

/** **********************************************************************
* @author Blake A. Mommaerts
*
* @par Description
* This function is part of the IO for this program. It opens an input file
* so data can be read from it.
*
* @param[in, out] fin Ifstream of the given input file. Passed by reference.
* @param[in] fileName String value of the given input file's name.
*
* @returns A boolean value, true if the file opens, false if it does not.
*
* @par Example
* @verbatim
    ifstream fin;
    string filename = "knights.pz";

    openInput( fin, filename );
@endverbatim
************************************************************************/
bool openInput(ifstream& fin, string fileName)
{
    fin.open(fileName); // opens file

    if (!fin.is_open()) // checks if file is able to open
    {
        cout << "Unable to open file: " << fileName << endl;
        return false; // if not, returns false
    }

    return true; // returns true if file was opened
}

/** **********************************************************************
* @author Blake A. Mommaerts
*
* @par Description
* This function allocates a dynamic 2D array for the board used in the
* knight's tour, as the board can grow and shrink as specified in the menu,
* or read multiple different valuess from the given input file.
*
* @param[in,out] board The pointer of the 2d array to be dynamically allocated
* in this function. Passed by reference
* @param[in] boardS Size of the board, both rows and columns
*
* @returns none
*
* @par Example
* @verbatim
    int** board = nullptr;
    int boardS = 8;

    allocate2D( board, boardS ); // an 8x8 board is made
@endverbatim
************************************************************************/
void allocate2D(int**& board, int boardS)
{
    int i, biggerBoard;
    biggerBoard = boardS + 4; // accounts for borders of -1
    board = nullptr;
    board = new (nothrow) int* [biggerBoard]; // 1d array made for board
    // if memory fails to allocate
    if (board == nullptr)
    {
        cout << "Memory allocation error" << endl;
        exit(3);
    }
    for (i = 0; i < biggerBoard; i++) // 2d allocation for board
    {
        board[i] = new (nothrow) int[boardS + 4]; // 2d array allocated
        if (board[i] == nullptr) // no memory? free it and output error
        {
            freeMemory(board, i);
            cout << "Couldn't allocate memory for board" << endl;
            exit(3);
        }
    }
}

/** **********************************************************************
* @author Blake A. Mommaerts
*
* @par Description
* This function is a helper function to allocate2D, as its sole task is to
* free up the allocated 2D array created in allocate2D.
*
* @param[in,out] board A 2D pointer of the 2D board, passed by reference.
* @param[in] row Integer amount of how many rows are in the board.
*
* @returns none
*
* @par Example
* @verbatim
    int i;
    int boardS = 8;
    int** board = {(2D array)};

    for (i = 0; i < boardS; i++)
    {
        board[i] = new (nothrow) int[boardS + 4];
        if (board[i] == nullptr)
        {
            freeMemory(board, i);
            cout << "Couldn't allocate memory for board" << endl;
            exit(3);
        }
    }
@endverbatim
************************************************************************/
void freeMemory(int**& board, int row)
{
    int i;
    if (board == nullptr)
    {
        exit(0); // nothing to free up
    }
    for (i = 0; i < row; i++)
    {
        delete[] board[i]; // free everything in columns first
    }
    delete[] board; // frees everything in 1d space to finish
}

/** **********************************************************************
* @author Blake A. Mommaerts
*
* @par Description
* This function is a helper function to allocate2D, and it will populate
* this 2D array with borders of -1 two lines thick. The 0's in the center
* represent the actual board. Please note that the -1's are not outputted
* into the solutions from solveTour.
*
* @param[in,out] board A 2D pointer of the 2D board, passed by reference.
* @param[in] boardS Integer amount of how many rows are in the board.
*
* @returns none
*
* @par Example
* @verbatim
    int** board = {(2D array)};
    int boardS = 8;

    populatArray(board, boardS);
@endverbatim
************************************************************************/
void populateArray(int**& board, int boardS)
{
    int i, j;
    //making the entire 2d array -1's to start with
    //boardSize + 4 is the length and width of the 2d array
    for (i = 0; i < (boardS + 4); i++)
    {
        for (j = 0; j < (boardS + 4); j++)
        {
            board[i][j] = -1;
        }
    }

    //places the 0s (valid positions) within the 2d array
    for (i = 0; i < (boardS + 2); i++)
    {
        if (i > 1)
        {
            for (j = 2; j < (boardS + 2); j++)
            {
                board[i][j] = 0;
            }
        }
    }
}

/** **********************************************************************
* @author Blake A. Mommaerts
*
* @par Description
* This function uses recursive backtracking to find the first solution
* for the knight's tour, given a specific chessboard size and position
* on the chessboard. Moves are from A to H, A being 2 up-1 right, then
* clockwise up to H, H being 2 up-1 left. Outputs solution to the
* console.
*
* @param[in,out] board A pointer of the 2d board, passed by reference.
* @param[in] boardS Integer representing the total rows and columns of
* the chessboard.
* @param[in] row Integer representing what row the knight is on.
* @param[in] col Integer representing what column the knight is on.
* @param[in] count Integer representing the current position the knight
* is at on the chessboard (nth permutation).
* @param[in] tC Integer representing the current tour count.
*
* @returns A boolean value, true if a solution is found or false if it is
* not.
*
* @par Example
* @verbatim
    int** board = {(2D array)};
    int boardS = 8;
    int row = 7;
    int col = 7;
    int count = 1;

    if(!solveTour(board, boardS, row, col, count))
        cout << "No solution";
        // Outputs solution if true, No solution if false
@endverbatim
************************************************************************/
bool solveTour(int**& board, int boardS, int row, int col, int count, int tC)
{
    int i, newRow, newCol;
    int y[8] = { 2, 1, -1, -2, -2, -1, 1, 2 }; // vertical knight directions
    int x[8] = { 1, 2, 2, 1, -1, -2, -2, -1 }; // horizontal knight directions

    if (count == 1) // starts the board at given position
    {
        row = row + 2; // adjust by 2 because of the -1 border
        col = col + 2;
        board[row][col] = count; // first position set
        count++; // increments for next position
        cout << left << endl << "Tour: #" << tC << endl;
        cout << "       " << boardS << " x " << boardS << " starting at ";
        cout << "(" << (row - 2) << ", " << (col - 2) << ")" << endl << endl;
    }

    // boardS*boardS is the total amount of spots, 64 for 8x8, etc.
    if (board[row][col] == (boardS * boardS))
    {
        for (row = 2; row < (boardS + 2); row++) // displays the board
        {
            cout << "       ";
            for (col = 2; col < (boardS + 2); col++)
            {
                // format for nice looking output
                cout << right << setw(2) << board[row][col] << " ";
            }
            cout << endl;
        }
        return true;
    }

    for (i = 0; i < 8; i++) // each loop is move a, b, c...
    {
        newCol = col + x[i]; // moves in a, b, c...
        newRow = row - y[i];

        if (board[newRow][newCol] == 0) // if empty...
        {
            board[newRow][newCol] = count; // ...move into it, call recursively
            if (solveTour(board, boardS, newRow, newCol, count + 1, tC))
            {
                return true; // drops out after first solution
            }
            board[newRow][newCol] = 0; // backtrack if needed
        }
    }
    return false;
}

/** **********************************************************************
* @author Blake A. Mommaerts
*
* @par Description
* This function is part of the IO for this program. It opens an output file
* so data can be passed into it. The name for this file should be
* "Solutions.tours".
*
* @param[in, out] fout Ofstream of the given output file. Passed by reference.
* @param[in] fileName String value of the given input file's name.
*
* @returns A boolean value, true if the file opens, false if it does not.
*
* @par Example
* @verbatim
    ifstream fout;
    string filename = "Solutions.tours";

    openOutput( fout, filename );
@endverbatim
************************************************************************/
bool openOutput(ofstream& fout, string fileName)
{
    fout.open(fileName, ios::app); // opens file

    if (!fout.is_open()) // checks if file is able to open
    {
        cout << "Unable to open file: " << fileName << endl;
        return false; // if not, returns false
    }

    return true; // returns true if file was opened
}

/** **********************************************************************
* @author Blake A. Mommaerts
*
* @par Description
* This function runs upon success of input and output both opening, and will
* begin reading in values for board size and position of the knight on the
* board. Once it is finished doing so, it dynamically allocates a 2D array
* for the board, and attempts to solve the tour with the given starting spot.
* This can occur multiple times as the file can have values for more than
* one tour. It will either output the first solution for a tour or a no
* solution statement to the "Solutions.tours" file. The 2D array is then
* freed, and it moves to the next tour (if it exists).
*
* @param[in, out] fin Ifstream of the given input file. Passed by reference.
* @param[in,out] boardS Integer representing the total rows and columns of
* the chessboard. Passed by reference.
* @param[in,out] row Integer representing what row the knight is on.
* Passed by reference.
* @param[in,out] col Integer representing what column the knight is on.
* Passed by reference.
* @param[in,out] fout Ofstream of the given output file. Passed by reference.
*
* @returns None.
*
* @par Example
* @verbatim
    ifstream fin;
    string fileName = "input.txt";
    ofstream fout;

    openInput(fin, fileName);
    openOutput(fout, "Solutions.tours");
    readAndRun(fin, fout, boardS, row, col);
@endverbatim
************************************************************************/
void readAndRun(ifstream& fin, ofstream& fout, int& boardS, int& row, int& col)
{
    int count = 1;
    int tC = 1;
    int** board = nullptr;
    while (fin >> boardS)
    {
        fin >> row >> col; // reading in data from file
        allocate2D(board, boardS); // make a 2D array from read data
        populateArray(board, boardS); // -1 borders and 0's for board
        if (!fileTour(board, boardS, row, col, count, tC, fout))
        {
            // if a tour is not found, output no solution
            fout << "       ";
            fout << "No solutions for this case." << endl;
        }
        freeMemory(board, boardS); // Free up memory for next/end
        tC = tC + 1; // Next tour # if exists
        fout << endl; // space between tours
    }
}


/** **********************************************************************
* @author Blake A. Mommaerts
*
* @par Description
* This function uses recursive backtracking to find the first solution
* for the knight's tour, given a specific chessboard size and position
* on the chessboard. Moves are from A to H, A being 2 up-1 right, then
* clockwise up to H, H being 2 up-1 left. Outputs to a file named
* "Solutions.tours".
*
* @param[in,out] board A pointer of the 2d board, passed by reference.
* @param[in] boardS Integer representing the total rows and columns of
* the chessboard.
* @param[in] row Integer representing what row the knight is on.
* @param[in] col Integer representing what column the knight is on.
* @param[in] count Integer representing the current position the knight
* is at on the chessboard (nth permutation).
* @param[in] tC Integer representing the current tour count.
* @param[in,out] fout Ofstream of the given output file. Passed by reference.
*
* @returns A boolean value, true if a solution is found or false if it is
* not.
*
* @par Example
* @verbatim
    int** board = {(2D array)};
    int boardS = 8;
    int row = 7;
    int col = 7;
    int count = 1;
    int fC = 1;
    ofstream fout;

    if(!fileTour(board, boardS, row, col, count, tC, fout))
        fout << "No solution";
        // Outputs solution if true, No solution if false
@endverbatim
************************************************************************/
bool fileTour(int**& board, int boardS, int row, int col, int count, int tC,
    ofstream& fout)
{
    int i, newRow, newCol;
    int y[8] = { 2, 1, -1, -2, -2, -1, 1, 2 }; // vertical knight directions
    int x[8] = { 1, 2, 2, 1, -1, -2, -2, -1 }; // horizontal knight directions

    if (count == 1) // starts the board at given position
    {
        row = row + 2; // adjust by 2 because of the -1 border
        col = col + 2;
        board[row][col] = count; // first position set
        count++; // increments for next position
        fout << "Tour: #" << tC << endl;
        fout << "       " << boardS << " x " << boardS << " starting at ";
        fout << "(" << (row - 2) << ", " << (col - 2) << ")" << endl << endl;
    }

    // boardS*boardS is the total amount of spots, 64 for 8x8, etc.
    if (board[row][col] == (boardS * boardS))
    {
        for (row = 2; row < (boardS + 2); row++) // displays the board
        {
            fout << "       ";
            for (col = 2; col < (boardS + 2); col++)
            {
                // format for nice looking output
                fout << right << setw(2);
                fout << board[row][col] << " ";
            }
            fout << endl;
        }
        return true;
    }

    for (i = 0; i < 8; i++) // each loop is move a, b, c...
    {
        newCol = col + x[i]; // moves in a, b, c...
        newRow = row - y[i];

        if (board[newRow][newCol] == 0) // if empty...
        {
            board[newRow][newCol] = count; // ...move into it, call recursively
            if (fileTour(board, boardS, newRow, newCol, count + 1, tC, fout))
            {
                return true; // drops out after first solution
            }
            board[newRow][newCol] = 0; // backtrack if needed
        }
    }
    return false;
}