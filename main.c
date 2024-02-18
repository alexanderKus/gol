#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH  50
#define HEIGHT 50

#define DEAD  '.'
#define ALIVE '#'

static int board[WIDTH][HEIGHT] = {0};
static int next_board[WIDTH][HEIGHT] = {0};

static const int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1};
static const int dy[] = { -1, 0,  1, -1, 1, -1, 0, 1};

void init_board();
void print_board();
void print_next_board();
size_t count_alive_cells();
void step();
int is_valid(size_t, size_t);
void update_board();

int main() {
    srand((unsigned int)time(NULL));
    init_board();
    size_t round = 0;
    size_t count = count_alive_cells();
    while(count > 0) {
        system("clear");
        printf("[INFO] round: %ld, alive celss: %ld\n", round++, count);
        print_board();
        usleep(1000 * 1000); // sleep for 1 sec
        step();
        update_board();
        count = count_alive_cells();
    }
    return 0;
}

void init_board() {
    for(size_t i = 0; i < WIDTH; i++) {
        for(size_t j = 0; j < HEIGHT; j++) { 
            float is_alive = ((float) rand() / RAND_MAX * 2 - 1);
            if (is_alive > 0.5f) {
                board[i][j] = ALIVE;
            } else {
                board[i][j] = DEAD;
            }
            next_board[i][j] = DEAD;
        }
    }
}

void print_board() {
    for(size_t i = 0; i < WIDTH; i++) {
        for(size_t j = 0; j < HEIGHT; j++) { 
            printf("%c", board[i][j]);
        }
        printf("\n");
    } 
    fflush(stdin);
}
 
void print_next_board() {
    for(size_t i = 0; i < WIDTH; i++) {
        for(size_t j = 0; j < HEIGHT; j++) { 
            printf("%c", next_board[i][j]);
        }
        printf("\n");
    } 
    fflush(stdin);
}

size_t count_alive_cells() {
    size_t count = 0;
    for(size_t i = 0; i < WIDTH; i++) {
        for(size_t j = 0; j < HEIGHT; j++) { 
            if(board[i][j] == ALIVE) count++;
        }
    }
    return count;
}

void step() {
    for(size_t i = 0; i < WIDTH; i++) {
        for(size_t j = 0; j < HEIGHT; j++) { 
            size_t neighbours_count = 0;
            for(size_t k = 0; k < 8; k++) {
                size_t nx = i + dx[k];
                size_t ny = j + dy[k];
                if(is_valid(nx, ny) != 0 && board[nx][ny] == ALIVE) {
                    neighbours_count++;
                }
            }
            if(board[i][j] == DEAD && neighbours_count == 3) {
                next_board[i][j] = ALIVE;
            }
            else if(board[i][j] == ALIVE && (neighbours_count == 2 || neighbours_count == 3)) {
                next_board[i][j] = ALIVE;
            }
            else {
                next_board[i][j] = DEAD;
            }
        }
    } 
}

int is_valid(size_t x, size_t y) {
    return x >= 0 && x < WIDTH && y >=0 && y < HEIGHT ? 1 : 0;
}

void update_board() {
    for(size_t i = 0; i < WIDTH; i++) {
        for(size_t j = 0; j < HEIGHT; j++) { 
            board[i][j] = next_board[i][j];
            next_board[i][j] = DEAD;
        }
    }
}

