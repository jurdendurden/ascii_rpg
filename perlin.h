#ifndef PERLIN_H
#define PERLIN_H

// Define vector2 struct (tuple/coordinate)
typedef struct 
{
    float x, y;
} vector2;

// Random seed
extern int seed;

// Map
#define HORIZONTAL_SIZE 1000
#define VERTICAL_SIZE 1000

// Colors
#define ANSI_RED    "\x1b[31m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_BLUE   "\x1b[34m"
#define ANSI_GREEN  "\x1b[32m"
#define ANSI_CYAN   "\x1b[36m"
#define ANSI_GRAY   "\x1b[0m"
#define ANSI_WHITE  "\x1b[37m"
#define ANSI_RESET  "\x1b[0m"
#define ANSI_BRIGHT_GREEN "\x1b[32;1m"
#define ANSI_BRIGHT_BLUE "\x1b[34;1m"
#define ANSI_BRIGHT_CYAN "\x1b[36;1m"

// Function prototypes, perlin.c
int noise(int x, int y);
double interpolate(double a, double b, double weight);
double linear_interpolation(double a, double b, double weight);
double cubic_interpolation(double a, double b, double weight);
vector2 random_gradient(int input_x, int input_y);
double dot_grid_gradient(int input_x, int input_y, double x, double y);
double perlin_noise(double x, double y);
double perlin(int x, int y, double frequency, int depth);

// Function prototypes, functions.c
char ascii_filter(double value);
void generate_perlin_noise_map(MAP * map);
void print_map_raw(double map[VERTICAL_SIZE][HORIZONTAL_SIZE], int vertical_size, int horizontal_size);
//void print_map(double map[VERTICAL_SIZE][HORIZONTAL_SIZE], int vertical_size, int horizontal_size);

#endif