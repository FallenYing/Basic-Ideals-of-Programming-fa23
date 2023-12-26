#include "2048.h"

int board[BOARD_SIZE][BOARD_SIZE];

void generate_number(void) {
    int empty_space[BOARD_SIZE * BOARD_SIZE][2];
    int count = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                empty_space[count][0] = i;
                empty_space[count][1] = j;
                count++;
            }
        }
    }

    if (count > 0) {
        int index = rand() % count;
        int x = empty_space[index][0];
        int y = empty_space[index][1];
        board[x][y] = (rand() % 2 + 1) * 2;
    }
}

enum direction choose_direction(void) {
    char dir = getchar();
    char ch;
    while ((ch = getchar()) != '\n') continue;
    switch (dir) {
    case 'A': case 'a':
        return LEFT;
    case 'W': case 'w':
        return UP;
    case 'S': case 's':
        return DOWN;
    case 'D': case 'd':
        return RIGHT;
    default:
        return NONE;
    }
}

void print_board(void) {
    system("clear");
    printf("-------------------------\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        putchar('|');
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != 0) {
                printf("%5d|", board[i][j]);
            }
            else {
                printf("     |");
            }
        }
        putchar('\n');
    }
    printf("-------------------------\n");
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void initialize_board(void) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

bool is_finished(void) {
    bool flag_2048 = false;
    bool flag_no_space = true;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 2048) {
                flag_2048 = true;
            }
            if (board[i][j] == 0) {
                flag_no_space = false;
            }
        }
    }
    return flag_2048 || flag_no_space;
}

bool move_and_merge_left(void) {
    bool flag = false;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE - 1; j++) {
            if (board[i][j] == 0) {
                for (int k = j + 1; k < BOARD_SIZE; k++) {
                    if (board[i][k] != 0) {
                        swap(&board[i][j], &board[i][k]);
                        flag = true;
                        break;
                    }
                }
            }
        }
        for (int j = 0; j < BOARD_SIZE - 1; j++) {
            if (board[i][j] == 0)
                break;
            if (board[i][j] == board[i][j + 1]) {
                board[i][j] *= 2;
                board[i][j + 1] = 0;
                for (int k = j + 1; k < BOARD_SIZE - 1; k++) {
                    swap(&board[i][k], &board[i][k + 1]);
                }
                flag = true;
            }
        }
    }
    return flag;
}

bool move_and_merge_right(void) {
    bool flag = false;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = BOARD_SIZE - 1; j > 0; j--) {
            if (board[i][j] == 0) {
                for (int k = j - 1; k >= 0; k--) {
                    if (board[i][k] != 0) {
                        swap(&board[i][j], &board[i][k]);
                        flag = true;
                        break;
                    }
                }
            }
        }
        for (int j = BOARD_SIZE - 1; j > 0; j--) {
            if (board[i][j] == 0)
                break;
            if (board[i][j] == board[i][j - 1]) {
                board[i][j] *= 2;
                board[i][j - 1] = 0;
                for (int k = j - 1; k > 0; k--) {
                    swap(&board[i][k], &board[i][k - 1]);
                }
                flag = true;
            }
        }
    }
    return flag;
}

bool move_and_merge_up(void) {
    bool flag = false;
    for (int j = 0; j < BOARD_SIZE; j++) {
        for (int i = 0; i < BOARD_SIZE - 1; i++) {
            if (board[i][j] == 0) {
                for (int k = i + 1; k < BOARD_SIZE; k++) {
                    if (board[k][j] != 0) {
                        swap(&board[i][j], &board[k][j]);
                        flag = true;
                        break;
                    }
                }
            }
        }
        for (int i = 0; i < BOARD_SIZE - 1; i++) {
            if (board[i][j] == 0)
                break;
            if (board[i][j] == board[i + 1][j]) {
                board[i][j] *= 2;
                board[i + 1][j] = 0;
                for (int k = i + 1; k < BOARD_SIZE - 1; k++) {
                    swap(&board[k][j], &board[k + 1][j]);
                }
                flag = true;
            }
        }
    }
    return flag;
}

bool move_and_merge_down(void) {
    bool flag = false;
    for (int j = 0; j < BOARD_SIZE; j++) {
        for (int i = BOARD_SIZE - 1; i > 0; i--) {
            if (board[i][j] == 0) {
                for (int k = i - 1; k >= 0; k--) {
                    if (board[k][j] != 0) {
                        swap(&board[i][j], &board[k][j]);
                        flag = true;
                        break;
                    }
                }
            }
        }
        for (int i = BOARD_SIZE - 1; i > 0; i--) {
            if (board[i][j] == 0)
                break;
            if (board[i][j] == board[i - 1][j]) {
                board[i][j] *= 2;
                board[i - 1][j] = 0;
                for (int k = i - 1; k >= 0; k--) {
                    swap(&board[k][j], &board[k - 1][j]);
                }
                flag = true;
            }
        }
    }
    return flag;
}

void run_game(void) {
    /*After completing, delete the following line to start the game.*/

    srand(time(0));
    initialize_board();
    generate_number();
    generate_number();
    print_board();
    enum direction direction;
    bool generate_flag = false;
    while (1) {
        while ((direction = choose_direction()) == NONE) {
            direction = choose_direction();
        }
        switch (direction) {
        case UP:
            generate_flag = move_and_merge_up();
            break;
        case DOWN:
            generate_flag = move_and_merge_down();
            break;
        case LEFT:
            generate_flag = move_and_merge_left();
            break;
        case RIGHT:
            generate_flag = move_and_merge_right();
            break;
        }
        if (is_finished()) {
            break;
        }
        if (generate_flag) generate_number();
        print_board();
    }
}

