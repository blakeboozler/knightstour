This program is to create a chessboard with both equal width and
length of default values 8x8 and starting position [7,7] for the knight
piece. In chess, the knight has a unique movement pattern where it can
move vertically two spaces then horizontally one space, or horizontally
two spaces and vertically one space (in other words, L-shaped moves).

Two algorithms can be ran depending on the amount of arguments provided
to the program; if no arguments are entered into the command line, a menu
is provided with the availability to make your own board and starting
position on the board. Creating the board requires 2D allocation, the rows
and columns being the board size. Once it's made, you can exit to attempt to
solve the board, and it will output the first solution or a statement saying
there were no solutions if none were found.

If an argument representing an input file was included, the
input is opened and values are read in. This way, the chessboard and
starting positions are predetermined, and can then the tours can be solved
thereafter, where solutions are written to an output file. Note that the
use of plural nouns implies that more than one tour can be provided in the
file.

After the algorithms are ran, the allocated 2D arrays are freed up, files
are closed, and the program exits with a 0. The outputs are either provided
in an output file or the console.
