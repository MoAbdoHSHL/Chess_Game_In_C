#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <stdbool.h>

// Initialize gameOver flag
bool gameOver = false;

// Arrays to track pawn status for both players
int pwstatus[8] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ;
int pbstatus[8] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ;

// chess board big Cases for player 1,and small cases for player 2
char board[8][8] = {
                    { 'R' , 'H' , 'C' , 'K' , 'Q' , 'C' , 'H' , 'R' },
                    { 'P' , 'P' , 'P' , 'P' , 'P' , 'P' , 'P' , 'P' },
                    { ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' },
                    { ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' },
                    { ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' },
                    { ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' },
                    { 'p' , 'p' , 'p' , 'p' , 'p' , 'p' , 'p' , 'p' },
                    { 'r' , 'h' , 'c' , 'k' , 'q' , 'c' , 'h' , 'r' }
                    };

// Function declarations

void pawn(int, int);
void pawnb(int, int);
void rook(int, int);
void rookb(int, int);
void horse(int, int);
void horseb(int, int);
void camel(int, int);
void camelb(int, int);
void king(int, int);
void kingb(int, int);
void queen(int, int);
void queenb(int, int);
void display();
void player1();
void player2();
void change(int, int, int, int);
int check(int, int);
int check2(int, int);
bool is_king_alive(char K, char board[8][8]);
bool is_kingb_alive(char k, char board[8][8]);
bool is_king_in_check(char king, char board[8][8]);
bool is_kingb_in_check(char king, char board[8][8]);

// Main function
int main()
{
    int  x = 0 ;
    char ch ;

    printf("\n           WELCOME TO               \n");

    printf("      ____   _                         \n");
    printf("     / ___| | |__    ___     ____   ____  \n");
    printf("    | |     | '_  | / _ |   /  __/ /  __/  \n");
    printf("    | |___  | | | ||  __/  /__  / /__  /    \n");
    printf("     |____| |_| |_| |___| /  __/ /  __/ \n");
    printf("      ____                             \n");
    printf("     / ___|  __ _   _ __ ___    ___    \n");
    printf("    | |  _  / _` | | '_ ` _  | / _ |   \n");
    printf("    | |_| || (_| | | | | | | ||  __/   \n");
    printf("     |____| |__,_| |_| |_| |_| |___|   \n");
    printf("\n                        By           \n");
    printf("                           Abdo & Ruhul\n");
    getch();
    system("cls");

    printf("\n                               ***Game Rules***\n");
    printf("\n");
    printf("    ---------------------------------------------------------------------------------------------\n");
    printf("    |   Piece   | Symbol |                   Description                                         |\n");
    printf("    ---------------------------------------------------------------------------------------------|\n");
    printf("    | Pawn      | P/p    | Moves 1 step forward, 2 steps on the first move, captures diagonally. |\n");
    printf("    ---------------------------------------------------------------------------------------------|\n");
    printf("    | Rook      | R/r    | Moves horizontally or vertically.                                     |\n");
    printf("    ---------------------------------------------------------------------------------------------|\n");
    printf("    | Knight    | H/h    | Moves in an 'L' shape.                                                |\n");
    printf("    ---------------------------------------------------------------------------------------------|\n");
    printf("    | Bishop    | C/c    | Moves diagonally.                                                     |\n");
    printf("    ---------------------------------------------------------------------------------------------|\n");
    printf("    | Queen     | Q/q    | Moves any number of steps in any direction.                           |\n");
    printf("    ---------------------------------------------------------------------------------------------|\n");
    printf("    | King      | K/k    | Moves 1 step in any direction.                                        |\n");
    printf("    --------------------------------------------------------------------------------------------- \n");
    printf("                                                                                                  \n");
    printf("                                                                                                  \n");
    printf("                             press ENTER to start playing");
    getch();
    system("cls");

    // Game loop for playing
    while (!gameOver) {
        // Display the current state of the board
        display();

        // Assume it's player 1's turn
        printf("\nPlayer 1's turn:\n");
        player1();

        // Check if player 2's move results in checkmate
        if (!is_king_alive('K', board)) {
            printf("Player 2 wins! Player 1's king is captured.\n");
            gameOver = true; // End the game
            break; // Exit the loop
        }

        // Display the current state of the board
        display();

        // Assume it's player 2's turn
        printf("\nPlayer 2's turn:\n");
        player2();

        // Check if player 1's move results in checkmate
        if (!is_kingb_alive('k', board)) {
            printf("Player 1 wins! Player 2's king is captured.\n");
            gameOver = true; // End the game
            break; // Exit the loop
        }

        // Check if both kings are eliminated
        if (!is_king_alive('K', board) && !is_king_alive('k', board)) {
            printf("Both kings are eliminated. It's a draw!\n");
            gameOver = true; // End the game
            break; // Exit the loop
        }
    }

    // Game over, determine the winner if the game ended due to a flag
    if (is_king_alive('K', board)) {
        printf("Player 1 wins!\n");
    } else if (is_king_alive('k', board)) {
        printf("Player 2 wins!\n");
    } else {
        printf("It's a draw!\n");
    }

    return 0;
}



// Function to display the current state of the chessboard
void display() {
    int i, j, k;

    // Print column indices
    printf(" ");
    for (i = 0; i < 8; i++) printf("    %d", i);
    printf("\n");

    // Print horizontal border and board contents
    for (k = 0; k < 8; k++) {
        printf("  ");
        for (i = 0; i < 42; i++) { printf("-"); } // Horizontal border
        printf("\n");
        printf("%d ", k); // Row index

        // Print each cell of the row
        for (j = 0; j < 8; j++) { printf("|  %c ", board[k][j]); }
        printf("|  \n");
    }

    // Print bottom horizontal border
    printf("  ");
    for (i = 0; i < 42; i++) { printf("-"); }
    printf("\n");
}

// Function to swap two pieces on the chessboard
void change(int r1, int c1, int r2, int c2) {
    // Prevent the king from swapping with an enemy piece
    if ((board[r1][c1] == 'K' && islower(board[r2][c2])) ||
        (board[r1][c1] == 'k' && isupper(board[r2][c2]))) {
        printf("Invalid move! King cannot swap with an enemy piece.\n");
        return;
    }

    // Move the piece and update the board
    board[r2][c2] = board[r1][c1];
    board[r1][c1] = ' ';
}

// Function to handle movement of the P1 pawn
void pawn(int r1, int c1) {
    pwstatus[c1]++; // Increment pawn's status for double move tracking

    printf("Available moves for the white pawn at %d%d: \n", r1, c1);

    if (pwstatus[c1] == 1) { // If pawn is at starting position
        if (board[r1 + 1][c1] == ' ') { // Check one square ahead
            printf("%d%d , ", r1 + 1, c1);
        }

        if (board[r1 + 2][c1] == ' ') { // Check two squares ahead
            printf("%d%d , ", r1 + 2, c1);
        }
    } else { // If pawn has already moved
        if (board[r1 + 1][c1] == ' ') { // Check one square ahead
            printf("%d%d , ", r1 + 1, c1);
        }

        if (check(r1 + 1, c1 + 1) == 1) { // Check diagonal right for capture
            printf("%d%d* , ", r1 + 1, c1 + 1);
        }

        if (check(r1 + 1, c1 - 1) == 1) { // Check diagonal left for capture
            printf("%d%d* , ", r1 + 1, c1 - 1);
        }
    }
}


// Function to display available moves for player1 rook
void rook(int r1, int c1) {
    int n;

    printf("Available moves for the rook at %d%d: \n", r1, c1);

    n = c1;

    // Horizontal movement
    printf("Horizontally: \n");

    // Move left
    while (n - 1 >= 0 && board[r1][n - 1] == ' ') {
        printf("%d%d , ", r1, n - 1);
        n--;
    }
    if (n - 1 >= 0 && islower(board[r1][n - 1])) {
        printf("%d%d* , ", r1, n - 1);
        board[r1][n - 1] = ' '; // Capture the opponent's piece
    }

    n = c1;

    // Move right
    while (n + 1 <= 7 && board[r1][n + 1] == ' ') {
        printf("%d%d , ", r1, n + 1);
        n++;
    }
    if (n + 1 <= 7 && islower(board[r1][n + 1])) {
        printf("%d%d* , ", r1, n + 1);
        board[r1][n + 1] = ' '; // Capture the opponent's piece
    }

    // Vertical movement
    printf("\nVertically:\n");

    n = r1;

    // Move up
    while (n - 1 >= 0 && board[n - 1][c1] == ' ') {
        printf("%d%d , ", n - 1, c1);
        n--;
    }
    if (n - 1 >= 0 && islower(board[n - 1][c1])) {
        printf("%d%d* , ", n - 1, c1);
        board[n - 1][c1] = ' '; // Capture the opponent's piece
    }

    n = r1;

    // Move down
    while (n + 1 <= 7 && board[n + 1][c1] == ' ') {
        printf("%d%d , ", n + 1, c1);
        n++;
    }
    if (n + 1 <= 7 && islower(board[n + 1][c1])) {
        printf("%d%d* , ", n + 1, c1);
        board[n + 1][c1] = ' '; // Capture the opponent's piece
    }
}

// Function to display available moves for a player1 horse
void horse(int r1, int c1) {
    printf("Available moves for the knight at %d%d: \n", r1, c1);

    // Array to store all possible moves of a knight
    int moves[8][2] = {
        {2, 1}, {2, -1}, {1, 2}, {1, -2},
        {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}
    };

    // Loop through all possible moves
    for (int i = 0; i < 8; i++) {
        int r2 = r1 + moves[i][0];
        int c2 = c1 + moves[i][1];

        // Check if the move is within the board limits
        if (r2 >= 0 && r2 <= 7 && c2 >= 0 && c2 <= 7) {
            if (board[r2][c2] == ' ') {
                printf("%d%d, ", r2, c2);
            } else if (islower(board[r2][c2])) {
                printf("%d%d*, ", r2, c2);
                board[r2][c2] = ' '; // Capture the opponent's piece
            }
        }
    }
}

// Function to display available moves for player1 camel
void camel(int r1, int c1) {
    printf("Available moves for the camel at %d%d: \n", r1, c1);

    int a, b;

    // Diagonal up-right
    a = 1; b = 1;
    while ((r1 - a) >= 0 && (c1 + b) <= 7 && board[r1 - a][c1 + b] == ' ') {
        printf("%d%d , ", r1 - a, c1 + b);
        a++;
        b++;
    }
    if ((r1 - a) >= 0 && (c1 + b) <= 7 && islower(board[r1 - a][c1 + b])) {
        printf("%d%d* , ", r1 - a, c1 + b);
        board[r1 - a][c1 + b] = ' '; // Capture the opponent's piece
    }

    // Diagonal down-left
    a = 1; b = 1;
    while ((r1 + a) <= 7 && (c1 - b) >= 0 && board[r1 + a][c1 - b] == ' ') {
        printf("%d%d , ", r1 + a, c1 - b);
        a++;
        b++;
    }
    if ((r1 + a) <= 7 && (c1 - b) >= 0 && islower(board[r1 + a][c1 - b])) {
        printf("%d%d* , ", r1 + a, c1 - b);
        board[r1 + a][c1 - b] = ' '; // Capture the opponent's piece
    }

    // Diagonal down-right
    a = 1; b = 1;
    while ((r1 + a) <= 7 && (c1 + b) <= 7 && board[r1 + a][c1 + b] == ' ') {
        printf("%d%d , ", r1 + a, c1 + b);
        a++;
        b++;
    }
    if ((r1 + a) <= 7 && (c1 + b) <= 7 && islower(board[r1 + a][c1 + b])) {
        printf("%d%d* , ", r1 + a, c1 + b);
        board[r1 + a][c1 + b] = ' '; // Capture the opponent's piece
    }

    // Diagonal up-left
    a = 1; b = 1;
    while ((r1 - a) >= 0 && (c1 - b) >= 0 && board[r1 - a][c1 - b] == ' ') {
        printf("%d%d , ", r1 - a, c1 - b);
        a++;
        b++;
    }
    if ((r1 - a) >= 0 && (c1 - b) >= 0 && islower(board[r1 - a][c1 - b])) {
        printf("%d%d* , ", r1 - a, c1 - b);
        board[r1 - a][c1 - b] = ' '; // Capture the opponent's piece
    }
}


// Function to display available moves for a player1 king
void king(int r1, int c1) {
    printf("Available moves for the king at %d%d are: ", r1, c1);

    // Determine the player based on the piece at the starting position
    char piece = board[r1][c1];
    bool isPlayer1 = (piece == 'K'); // Assuming 'K' is the king for player 1

    // Array to store all possible moves of a king
    int moves[8][2] = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0},
        {1, 1}, {-1, -1}, {-1, 1}, {1, -1}
    };

    // Loop through all possible moves
    for (int i = 0; i < 8; i++) {
        int r2 = r1 + moves[i][0];
        int c2 = c1 + moves[i][1];

        // Check if the move is within the board limits
        if (r2 >= 0 && r2 <= 7 && c2 >= 0 && c2 <= 7) {
            char target = board[r2][c2];
            // Avoid capturing own pieces
            if ((isPlayer1 && target >= 'a' && target <= 'z') || (!isPlayer1 && target >= 'A' && target <= 'Z')) {
                printf("%d%d* , ", r2, c2);
                // Note: This function does not modify the board, only prints moves
            } else if (target == ' ') {
                printf("%d%d , ", r2, c2);
            } else if ((isPlayer1 && target == 'k') || (!isPlayer1 && target == 'K')) {
                printf("Game Over! King %c has been eaten.\n", (isPlayer1 ? 'k' : 'K'));
                gameOver = true; // Set gameOver flag
            }
        }
    }

    // Check if the king is in check
    if (is_king_in_check('K', board)) {
        printf("\nKing is in check!\n");
    } else {
        printf("\nKing is not in check.\n");
    }
}

// Function to display available moves for player1 queen
void queen(int r1, int c1) {
    int x, y, a, b;
    printf("Available moves for the queen at %d%d: \n", r1, c1);

    // Horizontal and Vertical Moves
    printf("Horizontal and Vertical: \n");

    // Move left
    y = 1;
    while ((c1 - y) >= 0 && board[r1][c1 - y] == ' ') {
        printf("%d%d , ", r1, c1 - y);
        y++;
    }
    if ((c1 - y) >= 0 && (board[r1][c1 - y] == ' ' || (board[r1][c1 - y] >= 'a' && board[r1][c1 - y] <= 'z'))) {
        printf("%d%d* , ", r1, c1 - y);
    }

    // Move right
    y = 1;
    while ((c1 + y) <= 7 && board[r1][c1 + y] == ' ') {
        printf("%d%d , ", r1, c1 + y);
        y++;
    }
    if ((c1 + y) <= 7 && (board[r1][c1 + y] == ' ' || (board[r1][c1 + y] >= 'a' && board[r1][c1 + y] <= 'z'))) {
        printf("%d%d* , ", r1, c1 + y);
    }

    // Move up
    x = 1;
    while ((r1 - x) >= 0 && board[r1 - x][c1] == ' ') {
        printf("%d%d , ", r1 - x, c1);
        x++;
    }
    if ((r1 - x) >= 0 && (board[r1 - x][c1] == ' ' || (board[r1 - x][c1] >= 'a' && board[r1 - x][c1] <= 'z'))) {
        printf("%d%d* , ", r1 - x, c1);
    }

    // Move down
    x = 1;
    while ((r1 + x) <= 7 && board[r1 + x][c1] == ' ') {
        printf("%d%d , ", r1 + x, c1);
        x++;
    }
    if ((r1 + x) <= 7 && (board[r1 + x][c1] == ' ' || (board[r1 + x][c1] >= 'a' && board[r1 + x][c1] <= 'z'))) {
        printf("%d%d* , ", r1 + x, c1);
    }

    // Diagonal Moves
    printf("Diagonal: \n");

    // Move up-right
    a = 1; b = 1;
    while ((r1 - a) >= 0 && (c1 + b) <= 7 && board[r1 - a][c1 + b] == ' ') {
        printf("%d%d , ", r1 - a, c1 + b);
        a++;
        b++;
    }
    if ((r1 - a) >= 0 && (c1 + b) <= 7 && (board[r1 - a][c1 + b] == ' ' || (board[r1 - a][c1 + b] >= 'a' && board[r1 - a][c1 + b] <= 'z'))) {
        printf("%d%d* , ", r1 - a, c1 + b);
    }

    // Move down-left
    a = 1; b = 1;
    while ((r1 + a) <= 7 && (c1 - b) >= 0 && board[r1 + a][c1 - b] == ' ') {
        printf("%d%d , ", r1 + a, c1 - b);
        a++;
        b++;
    }
    if ((r1 + a) <= 7 && (c1 - b) >= 0 && (board[r1 + a][c1 - b] == ' ' || (board[r1 + a][c1 - b] >= 'a' && board[r1 + a][c1 - b] <= 'z'))) {
        printf("%d%d* , ", r1 + a, c1 - b);
    }

    // Move down-right
    a = 1; b = 1;
    while ((r1 + a) <= 7 && (c1 + b) <= 7 && board[r1 + a][c1 + b] == ' ') {
        printf("%d%d , ", r1 + a, c1 + b);
        a++;
        b++;
    }
    if ((r1 + a) <= 7 && (c1 + b) <= 7 && (board[r1 + a][c1 + b] == ' ' || (board[r1 + a][c1 + b] >= 'a' && board[r1 + a][c1 + b] <= 'z'))) {
        printf("%d%d* , ", r1 + a, c1 + b);
    }

    // Move up-left
    a = 1; b = 1;
    while ((r1 - a) >= 0 && (c1 - b) >= 0 && board[r1 - a][c1 - b] == ' ') {
        printf("%d%d , ", r1 - a, c1 - b);
        a++;
        b++;
    }
    if ((r1 - a) >= 0 && (c1 - b) >= 0 && (board[r1 - a][c1 - b] == ' ' || (board[r1 - a][c1 - b] >= 'a' && board[r1 - a][c1 - b] <= 'z'))) {
        printf("%d%d* , ", r1 - a, c1 - b);
    }
}

// Function to display available moves for the player2's pawn
void pawnb(int r1, int c1) {
    pbstatus[c1]++;

    printf("Available are: \n");

    if (pbstatus[c1] == 1) {
        if (board[r1 - 1][c1] == ' ') {
            printf("%d%d , ", r1 - 1, c1);
        }

        if (board[r1 - 2][c1] == ' ') {
            printf("%d%d , ", r1 - 2, c1);
        }
    } else {
        if (board[r1 - 1][c1] == ' ') {
            printf("%d%d , ", r1 - 1, c1);
        }

        if (check2(r1 - 1, c1 - 1) == 1) {
            printf("%d%d* , ", r1 - 1, c1 - 1);
        }

        if (check2(r1 - 1, c1 + 1) == 1) {
            printf("%d%d* , ", r1 - 1, c1 + 1);
        }
    }
}

// Function to display available moves for player2's rook
void rookb(int r1, int c1) {
    int n;

    printf("Available moves for the rook at %d%d: \n", r1, c1);

    n = c1;

    printf("Horizontally: \n");

    // Move left
    while (n - 1 >= 0 && board[r1][n - 1] == ' ') {
        printf("%d%d , ", r1, n - 1);
        n--;
    }
    if (n - 1 >= 0 && (board[r1][n - 1] == 'P' || board[r1][n - 1] == 'R' ||
                       board[r1][n - 1] == 'H' || board[r1][n - 1] == 'C' ||
                       board[r1][n - 1] == 'K' || board[r1][n - 1] == 'Q')) {
        printf("%d%d* , ", r1, n - 1);
        board[r1][n - 1] = ' '; // Capture the opponent's piece
    }

    n = c1;

    // Move right
    while (n + 1 <= 7 && board[r1][n + 1] == ' ') {
        printf("%d%d , ", r1, n + 1);
        n++;
    }
    if (n + 1 <= 7 && (board[r1][n + 1] == 'P' || board[r1][n + 1] == 'R' ||
                       board[r1][n + 1] == 'H' || board[r1][n + 1] == 'C' ||
                       board[r1][n + 1] == 'K' || board[r1][n + 1] == 'Q')) {
        printf("%d%d* , ", r1, n + 1);
        board[r1][n + 1] = ' '; // Capture the opponent's piece
    }

    printf("\nVertically:\n");

    n = r1;

    // Move up
    while (n - 1 >= 0 && board[n - 1][c1] == ' ') {
        printf("%d%d , ", n - 1, c1);
        n--;
    }
    if (n - 1 >= 0 && (board[n - 1][c1] == 'P' || board[n - 1][c1] == 'R' ||
                       board[n - 1][c1] == 'H' || board[n - 1][c1] == 'C' ||
                       board[n - 1][c1] == 'K' || board[n - 1][c1] == 'Q')) {
        printf("%d%d* , ", n - 1, c1);
        board[n - 1][c1] = ' '; // Capture the opponent's piece
    }

    n = r1;

    // Move down
    while (n + 1 <= 7 && board[n + 1][c1] == ' ') {
        printf("%d%d , ", n + 1, c1);
        n++;
    }
    if (n + 1 <= 7 && (board[n + 1][c1] == 'P' || board[n + 1][c1] == 'R' ||
                       board[n + 1][c1] == 'H' || board[n + 1][c1] == 'C' ||
                       board[n + 1][c1] == 'K' || board[n + 1][c1] == 'Q')) {
        printf("%d%d* , ", n + 1, c1);
        board[n + 1][c1] = ' '; // Capture the opponent's piece
    }
}

// Function to display available moves for player2's horse
void horseb(int r1, int c1) {
    printf("Available moves for the horse at %d%d: \n", r1, c1);

    // List of possible moves for a knight
    int moves[8][2] = {
        {r1 - 2, c1 - 1}, {r1 - 2, c1 + 1},
        {r1 - 1, c1 - 2}, {r1 - 1, c1 + 2},
        {r1 + 1, c1 - 2}, {r1 + 1, c1 + 2},
        {r1 + 2, c1 - 1}, {r1 + 2, c1 + 1}
    };

    for (int i = 0; i < 8; i++) {
        int newRow = moves[i][0];
        int newCol = moves[i][1];

        // Check if the move is within bounds
        if (newRow >= 0 && newRow <= 7 && newCol >= 0 && newCol <= 7) {
            // Check if the destination square is empty or contains an opponent's piece
            if (board[newRow][newCol] == ' ' ||
                board[newRow][newCol] == 'P' || board[newRow][newCol] == 'R' ||
                board[newRow][newCol] == 'H' || board[newRow][newCol] == 'C' ||
                board[newRow][newCol] == 'K' || board[newRow][newCol] == 'Q') {
                printf("%d%d%s, ", newRow, newCol, (board[newRow][newCol] != ' ' ? "*" : ""));
                if (board[newRow][newCol] != ' ') {
                    board[newRow][newCol] = ' '; // Capture the opponent's piece
                }
            }
        }
    }
}

// Function to display available moves for the player2's camel
void camelb(int r1, int c1) {
    int a, b;
    printf("Available are: \n");

    // Diagonal up-right
    a = 1;
    b = 1;
    while ((r1 - a) >= 0 && (c1 + b) <= 7 && board[r1 - a][c1 + b] == ' ') {
        printf("%d%d , ", r1 - a, c1 + b);
        a++;
        b++;
    }
    if ((r1 - a) >= 0 && (c1 + b) <= 7 && board[r1 - a][c1 + b] >= 'a' && board[r1 - a][c1 + b] <= 'z') {
        printf("%d%d* , ", r1 - a, c1 + b);
        board[r1 - a][c1 + b] = ' '; // Capture the opponent's piece
    }

    // Diagonal down-left
    a = 1;
    b = 1;
    while ((r1 + a) <= 7 && (c1 - b) >= 0 && board[r1 + a][c1 - b] == ' ') {
        printf("%d%d , ", r1 + a, c1 - b);
        a++;
        b++;
    }
    if ((r1 + a) <= 7 && (c1 - b) >= 0 && board[r1 + a][c1 - b] >= 'a' && board[r1 + a][c1 - b] <= 'z') {
        printf("%d%d* , ", r1 + a, c1 - b);
        board[r1 + a][c1 - b] = ' '; // Capture the opponent's piece
    }

    // Diagonal down-right
    a = 1;
    b = 1;
    while ((r1 + a) <= 7 && (c1 + b) <= 7 && board[r1 + a][c1 + b] == ' ') {
        printf("%d%d , ", r1 + a, c1 + b);
        a++;
        b++;
    }
    if ((r1 + a) <= 7 && (c1 + b) <= 7 && board[r1 + a][c1 + b] >= 'a' && board[r1 + a][c1 + b] <= 'z') {
        printf("%d%d* , ", r1 + a, c1 + b);
        board[r1 + a][c1 + b] = ' '; // Capture the opponent's piece
    }

    // Diagonal up-left
    a = 1;
    b = 1;
    while ((r1 - a) >= 0 && (c1 - b) >= 0 && board[r1 - a][c1 - b] == ' ') {
        printf("%d%d , ", r1 - a, c1 - b);
        a++;
        b++;
    }
    if ((r1 - a) >= 0 && (c1 - b) >= 0 && board[r1 - a][c1 - b] >= 'a' && board[r1 - a][c1 - b] <= 'z') {
        printf("%d%d* , ", r1 - a, c1 - b);
        board[r1 - a][c1 - b] = ' '; // Capture the opponent's piece
    }
}


// Function to display available moves for the player2's king
void kingb(int r1, int c1) {
    printf("Available moves for the king at %d%d: \n", r1, c1);

    // List of possible moves for the king
    int moves[8][2] = {
        {r1 - 1, c1 - 1}, {r1 - 1, c1}, {r1 - 1, c1 + 1},
        {r1, c1 - 1},                  {r1, c1 + 1},
        {r1 + 1, c1 - 1}, {r1 + 1, c1}, {r1 + 1, c1 + 1}
    };

    for (int i = 0; i < 8; i++) {
        int newRow = moves[i][0];
        int newCol = moves[i][1];

        // Check if the move is within bounds
        if (newRow >= 0 && newRow <= 7 && newCol >= 0 && newCol <= 7) {
            // Check if the destination square is empty or contains an opponent's piece
            if (board[newRow][newCol] == ' ' ||
                board[newRow][newCol] == 'P' || board[newRow][newCol] == 'R' ||
                board[newRow][newCol] == 'H' || board[newRow][newCol] == 'C' ||
                board[newRow][newCol] == 'K' || board[newRow][newCol] == 'Q') {
                printf("%d%d%s, ", newRow, newCol, (board[newRow][newCol] != ' ' ? "*" : ""));
                if (board[newRow][newCol] != ' ') {
                    board[newRow][newCol] = ' '; // Capture the opponent's piece
                }
            } else if ((board[newRow][newCol] == 'k') || (board[newRow][newCol] == 'K')) {
                printf("Game Over! King %c has been eaten.\n", (board[newRow][newCol] == 'k' ? 'k' : 'K'));
                gameOver = true; // Set gameOver flag
            }
        }
    }
    if (is_kingb_in_check('k', board)) {
        printf("\nKingb is in check!\n");
    } else {
        printf("\nKingb is not in check.\n");
    }
}

// Function to display available moves for the player2's queen
void queenb(int r1, int c1) {
    int x, y, a, b;
    printf("Available moves for the queen at %d%d: \n", r1, c1);

    // Horizontal and Vertical Moves
    printf("Horizontal and Vertical: \n");

    // Move left
    y = 1;
    while ((c1 - y) >= 0 && board[r1][c1 - y] == ' ') {
        printf("%d%d , ", r1, c1 - y);
        y++;
    }
    if ((c1 - y) >= 0 && (board[r1][c1 - y] == 'P' || board[r1][c1 - y] == 'R' ||
                          board[r1][c1 - y] == 'H' || board[r1][c1 - y] == 'C' ||
                          board[r1][c1 - y] == 'K' || board[r1][c1 - y] == 'Q')) {
        printf("%d%d* , ", r1, c1 - y);
    }

    // Move right
    y = 1;
    while ((c1 + y) <= 7 && board[r1][c1 + y] == ' ') {
        printf("%d%d , ", r1, c1 + y);
        y++;
    }
    if ((c1 + y) <= 7 && (board[r1][c1 + y] == 'P' || board[r1][c1 + y] == 'R' ||
                          board[r1][c1 + y] == 'H' || board[r1][c1 + y] == 'C' ||
                          board[r1][c1 + y] == 'K' || board[r1][c1 + y] == 'Q')) {
        printf("%d%d* , ", r1, c1 + y);
    }

    // Move up
    x = 1;
    while ((r1 - x) >= 0 && board[r1 - x][c1] == ' ') {
        printf("%d%d , ", r1 - x, c1);
        x++;
    }
    if ((r1 - x) >= 0 && (board[r1 - x][c1] == 'P' || board[r1 - x][c1] == 'R' ||
                          board[r1 - x][c1] == 'H' || board[r1 - x][c1] == 'C' ||
                          board[r1 - x][c1] == 'K' || board[r1 - x][c1] == 'Q')) {
        printf("%d%d* , ", r1 - x, c1);
    }

    // Move down
    x = 1;
    while ((r1 + x) <= 7 && board[r1 + x][c1] == ' ') {
        printf("%d%d , ", r1 + x, c1);
        x++;
    }
    if ((r1 + x) <= 7 && (board[r1 + x][c1] == 'P' || board[r1 + x][c1] == 'R' ||
                          board[r1 + x][c1] == 'H' || board[r1 + x][c1] == 'C' ||
                          board[r1 + x][c1] == 'K' || board[r1 + x][c1] == 'Q')) {
        printf("%d%d* , ", r1 + x, c1);
    }

    // Diagonal Moves
    printf("Diagonal: \n");

    // Move up-right
    a = 1; b = 1;
    while ((r1 - a) >= 0 && (c1 + b) <= 7 && board[r1 - a][c1 + b] == ' ') {
        printf("%d%d , ", r1 - a, c1 + b);
        a++;
        b++;
    }
    if ((r1 - a) >= 0 && (c1 + b) <= 7 && (board[r1 - a][c1 + b] == 'P' || board[r1 - a][c1 + b] == 'R' ||
                                           board[r1 - a][c1 + b] == 'H' || board[r1 - a][c1 + b] == 'C' ||
                                           board[r1 - a][c1 + b] == 'K' || board[r1 - a][c1 + b] == 'Q')) {
        printf("%d%d* , ", r1 - a, c1 + b);
    }

    // Move down-left
    a = 1; b = 1;
    while ((r1 + a) <= 7 && (c1 - b) >= 0 && board[r1 + a][c1 - b] == ' ') {
        printf("%d%d , ", r1 + a, c1 - b);
        a++;
        b++;
    }
    if ((r1 + a) <= 7 && (c1 - b) >= 0 && (board[r1 + a][c1 - b] == 'P' || board[r1 + a][c1 - b] == 'R' ||
                                           board[r1 + a][c1 - b] == 'H' || board[r1 + a][c1 - b] == 'C' ||
                                           board[r1 + a][c1 - b] == 'K' || board[r1 + a][c1 - b] == 'Q')) {
        printf("%d%d* , ", r1 + a, c1 - b);
    }

    // Move down-right
    a = 1; b = 1;
    while ((r1 + a) <= 7 && (c1 + b) <= 7 && board[r1 + a][c1 + b] == ' ') {
        printf("%d%d , ", r1 + a, c1 + b);
        a++;
        b++;
    }
    if ((r1 + a) <= 7 && (c1 + b) <= 7 && (board[r1 + a][c1 + b] == 'P' || board[r1 + a][c1 + b] == 'R' ||
                                           board[r1 + a][c1 + b] == 'H' || board[r1 + a][c1 + b] == 'C' ||
                                           board[r1 + a][c1 + b] == 'K' || board[r1 + a][c1 + b] == 'Q')) {
        printf("%d%d* , ", r1 + a, c1 + b);
    }

    // Move up-left
    a = 1; b = 1;
    while ((r1 - a) >= 0 && (c1 - b) >= 0 && board[r1 - a][c1 - b] == ' ') {
        printf("%d%d , ", r1 - a, c1 - b);
        a++;
        b++;
    }
    if ((r1 - a) >= 0 && (c1 - b) >= 0 && (board[r1 - a][c1 - b] == 'P' || board[r1 - a][c1 - b] == 'R' ||
                                           board[r1 - a][c1 - b] == 'H' || board[r1 - a][c1 - b] == 'C' ||
                                           board[r1 - a][c1 - b] == 'K' || board[r1 - a][c1 - b] == 'Q')) {
        printf("%d%d* , ", r1 - a, c1 - b);
    }
}


// Function to check if a king of player1 is alive
bool is_king_alive(char king_type, char board[8][8]) {
    // Iterate through the board to find the specified king piece
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Check for the specified king piece ('K' or 'k')
            if (board[i][j] == king_type) {
                // If the king piece is found, return true (alive)
                return true;
            }
        }
    }
    // If the king piece is not found, return false (eliminated)
    return false;
}

// Function to check if a king of player2 is alive
bool is_kingb_alive(char king_type, char board[8][8]) {
    // Iterate through the board to find the specified king piece
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Check for the specified king piece ('K' or 'k')
            if (board[i][j] == king_type) {
                // If the king piece is found, return true (alive)
                return true;
            }
        }
    }
    // If the king piece is not found, return false (eliminated)
    return false;
}

// Function to handle player 1's turn
void player1() {
    int p1, p2, c1, r1, c2, r2;

    printf("\nPLAYER 1 - Big Case\n");
    again1:
    printf("Enter Position of Element to move (RC): ");
    scanf("%d", &p1);

    c1 = p1 % 10;
    r1 = p1 / 10;

    // Determine the type of piece at the selected position and execute the corresponding function
    switch (board[r1][c1]) {
        case 'P': pawn(r1, c1);
                  break;
        case 'R': rook(r1, c1);
                  break;
        case 'H': horse(r1, c1);
                  break;
        case 'C': camel(r1, c1);
                  break;
        case 'K': king(r1, c1);
                  break;
        case 'Q': queen(r1, c1);
                  break;
        default: printf("Invalid Position! ");
                 goto again1;
    }

    // Get the position to move the piece to
    printf("Enter Position to Move the Piece to (RC): ");
    scanf("%d", &p2);

    c2 = p2 % 10;
    r2 = p2 / 10;

    // Execute the move
    change(r1, c1, r2, c2);

    // Check if player 2's king is eaten
    if (!is_king_alive('k', board)) {
        printf("Player 1 wins! Player 2's king is eaten.\n");
        gameOver = true; // Set gameOver flag
    }
}


// Function to handle player 2's turn
void player2() {
    int p1, p2, c1, r1, c2, r2;

    printf("\nPLAYER 2 - Small Case\n");
    again2:
    printf("Enter Position of Element to move (RC): ");
    scanf("%d", &p1);

    c1 = p1 % 10;
    r1 = p1 / 10;

    // Determine the type of piece at the selected position and execute the corresponding function
    switch (board[r1][c1]) {
        case 'p': pawnb(r1, c1);
                  break;
        case 'r': rookb(r1, c1);
                  break;
        case 'h': horseb(r1, c1);
                  break;
        case 'c': camelb(r1, c1);
                  break;
        case 'k': kingb(r1, c1);
                  break;
        case 'q': queenb(r1, c1);
                  break;
        default: printf("Invalid Position! ");
                 goto again2;
    }

    // Get the position to move the piece to
    printf("Enter Position to Move the Piece to (RC): ");
    scanf("%d", &p2);

    c2 = p2 % 10;
    r2 = p2 / 10;

    // Execute the move
    change(r1, c1, r2, c2);

    // Check if player 1's king is eaten
    if (!is_kingb_alive('K', board)) {
        printf("Player 2 wins! Player 1's king is eaten.\n");
        gameOver = true; // Set gameOver flag
    }
}

// Function to check if a position on the board contains any piece
int check(int x , int y ) {
    switch( board[x][y] ) {
        case 'p':
        case 'r':
        case 'h':
        case 'c':
        case 'k':
        case 'q': return 1 ; break ;
        default: return 0 ;
    }
}

// Function to check if a position on the board contains any piece for player 2
int check2(int x , int y ) {
    switch( board[x][y] ) {
        case 'P':
        case 'R':
        case 'H':
        case 'C':
        case 'K':
        case 'Q': return 1 ; break ;
        default: return 0 ;
    }
}


// Function to check if the specified king is in check for player 1
bool is_king_in_check(char king, char board[8][8]) {
    // Find the position of the specified king piece on the board
    int king_row, king_col;

    // Iterate through the board to find the specified king piece
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == king) {
                king_row = i;
                king_col = j;
                break;
            }
        }
    }

    // Now check if the king is under attack by any opponent's piece
    // For simplicity, let's assume the king is always in check if there's an opponent's piece adjacent to it

    // Define the opponent's king
    char opponent_king = (king == 'K' ? 'k' : 'K'); // Determine opponent's king based on player 1 or 2

    // Check if any opponent's piece is adjacent to the king
    int king_moves[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (int i = 0; i < 8; i++) {
        int new_row = king_row + king_moves[i][0];
        int new_col = king_col + king_moves[i][1];

        // Ensure the new position is within the board bounds
        if (new_row >= 0 && new_row < 8 && new_col >= 0 && new_col < 8) {
            // Check if there's an opponent's king adjacent to the current king
            if (board[new_row][new_col] == opponent_king) {
                // King is in check
                return true;
            }
        }
    }

    // Return false if the king is not in check
    return false;
}


// Function to check if the specified king is in check for player 2
bool is_kingb_in_check(char king, char board[8][8]) {
    // Find the position of the specified king piece on the board
    int king_row, king_col;

    // Iterate through the board to find the specified king piece
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == king) {
                king_row = i;
                king_col = j;
                break;
            }
        }
    }

    // Now check if the king is under attack by any opponent's piece
    // For simplicity, let's assume the king is always in check if there's an opponent's piece adjacent to it

    // Define the opponent's king
    char opponent_king = (king == 'K' ? 'k' : 'K'); // Determine opponent's king based on player 1 or 2

    // Check if any opponent's piece is adjacent to the king
    int king_moves[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (int i = 0; i < 8; i++) {
        int new_row = king_row + king_moves[i][0];
        int new_col = king_col + king_moves[i][1];

        // Ensure the new position is within the board bounds
        if (new_row >= 0 && new_row < 8 && new_col >= 0 && new_col < 8) {
            // Check if there's an opponent's king adjacent to the current king
            if (board[new_row][new_col] == opponent_king) {
                // King is in check
                return true;
            }
        }
    }

    // Return false if the king is not in check
    return false;
}

/*        
  _______   _                          _
 |__   __| | |               _        | | _
    | |    | |___     __ _  | |___    | |/ /    ____    
    | |    |  __  \  / _` | |  __  \  | ' /    /  __/
    | |    | |  | | | (_| | | |  | |  |   \   /__  /  
    |_|    |_|  |_|  |__,_| |_|  |_|  |_|\_\ /  __/    :)
*/



