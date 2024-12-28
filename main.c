#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 3
#define X 'X'
#define O 'O'

typedef struct {
    int Player;
    int Computer;
    int Draw;
} Score;

int difficulty;
Score score = {.Player = 0, .Computer = 0, .Draw = 0};

void input_difficulty();
void clear_screen();
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
void play_game();
void player_move(char board[BOARD_SIZE][BOARD_SIZE]);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]);
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);

int main() {
    srand(time(NULL));
    char choice;
    input_difficulty();
    do {
        play_game();
        printf("\nPlay Again? (y for Yes, n for No): ");
        scanf(" %c", &choice);
    } while (choice == 'y');
    printf("Thanks For Playing ʕ⁠´⁠•⁠ᴥ⁠•`⁠ʔ\n");
    return 0;
}

void play_game() {
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    char current_player = rand() % 2 == 0 ? X : O;

    print_board(board);
    while (1) {
        if (current_player == X) {
            player_move(board);
            print_board(board);
            if (check_win(board, X)) {
                score.Player++;
                printf("\nPlayer α WINS!\n");
                break;
            }
            current_player = O;
        } else {
            computer_move(board);
            print_board(board);
            if (check_win(board, O)) {
                score.Computer++;
                printf("\nPlayer β WINS!\n");
                break;
            }
            current_player = X;
        }

        if (check_draw(board)) {
            score.Draw++;
            printf("\nIt's a DRAW!\n");
            break;
        }
    }
}

int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    return !(row < 0 || col < 0 || row >= BOARD_SIZE || col >= BOARD_SIZE || board[row][col] != ' ');
}

void player_move(char board[BOARD_SIZE][BOARD_SIZE]) {
    int row, col;
    do {
        printf("\nPlayer X's turn.");
        printf("\nEnter Row And Column (1-3): ");
        scanf("%d%d", &row, &col);
        row--; col--;
    } while (!is_valid_move(board, row, col));
    board[row][col] = X;
}

void computer_move(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = O;
                if (check_win(board, O)) return;
                board[i][j] = ' ';
            }
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = X;
                if (check_win(board, X)) {
                    board[i][j] = O;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    if (difficulty == 2) {
        if (board[1][1] == ' ') {
            board[1][1] = O;
            return;
        }

        int corners[4][2] = {
            {0, 0}, {0, 2}, {2, 0}, {2, 2}
        };
        for (int i = 0; i < 4; i++) {
            if (board[corners[i][0]][corners[i][1]] == ' ') {
                board[corners[i][0]][corners[i][1]] = O;
                return;
            }
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = O;
                return;
            }
        }
    }
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return 1;
        }
    }
    return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
           (board[0][2] == player && board[1][1] == player && board[2][0] == player);
}

int check_draw(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') return 0;
        }
    }
    return 1;
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    clear_screen();
    printf("\nScore: Player α: %d, Player β: %d, Draws: %d", score.Player, score.Computer, score.Draw);
    printf("\n\n~ Tic-Tac-Toe ~\n\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < BOARD_SIZE - 1) printf("|");
        }
        if (i < BOARD_SIZE - 1) printf("\n---+---+---");
        printf("\n");
    }
}

void input_difficulty() {
    while (1) {
        printf("\nSelect Difficulty Level:");
        printf("\n1. Normal Mode");
        printf("\n2. Insane Mode");
        printf("\n\nEnter Your Choice: ");
        scanf("%d", &difficulty);

        if (difficulty == 1 || difficulty == 2) break;
        printf("\nIncorrect Choice. Enter (1/2)!");
    }
}

void clear_screen() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

  