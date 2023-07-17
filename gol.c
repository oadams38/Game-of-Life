#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "gol.h"

char    **init_grid()
{
    char    **grid;
    int     i;

    grid = malloc(sizeof(char *) * WIDTH * HEIGHT);
    i = 0;
    while (i < WIDTH * HEIGHT)
    {
        grid[i] = malloc(sizeof(char) * 2);
        grid[i][0] = 0;
        grid[i][1] = 0;
        i++;
    }
    grid[2][0] = 1;
    grid[WIDTH][0] = 1;
    grid[WIDTH + 2][0] = 1;
    grid[WIDTH * 2 + 1][0] = 1;
    grid[WIDTH * 2 + 2][0] = 1;
    return (grid);
}

void    free_grid(char **grid)
{
    int i;

    i = 0;
    while (i < WIDTH * HEIGHT)
    {
        free(grid[i]);
        i++;
    }
    free(grid);
}

int get_n_neighbours(char **grid, int i)
{
    int n_neigh;

    n_neigh = 0;
    if (i >= WIDTH + 1 && grid[i - WIDTH - 1][0] == 1)
        n_neigh++;
    if (i >= WIDTH && grid[i - WIDTH][0] == 1)
        n_neigh++;
    if (i >= WIDTH - 1 && grid[i - WIDTH + 1][0] == 1)
        n_neigh++;
    if (i >= 1 && grid[i - 1][0] == 1)
        n_neigh++;
    if (i + 1 < WIDTH * HEIGHT && grid[i + 1][0] == 1)
        n_neigh++;
    if (i + WIDTH - 1 < WIDTH * HEIGHT && grid[i + WIDTH - 1][0] == 1)
        n_neigh++;
    if (i + WIDTH < WIDTH * HEIGHT && grid[i + WIDTH][0] == 1)
        n_neigh++;
    if (i + WIDTH + 1 < WIDTH * HEIGHT && grid[i + WIDTH + 1][0] == 1)
        n_neigh++;
    return (n_neigh);
}

void    find_next_state(char **grid)
{
    int i;
    int n_neigh;

    i = 0;
    while (i < WIDTH * HEIGHT)
    {
        n_neigh = get_n_neighbours(grid, i);
        if (n_neigh == 3)
            grid[i][1] = 1;
        else if (n_neigh == 2 && grid[i][0] == 1)
            grid[i][1] = 1;
        else
            grid[i][1] = 0;
        i++;
    }
}

void    update(char **grid)
{
    int i;

    i = 0;
    while (i < WIDTH * HEIGHT)
    {
        grid[i][0] = grid[i][1];
        i++;
    }
}

void    print_grid(char **grid)
{
    int     i;
    int     j;
    char    str[(WIDTH + 1) * HEIGHT + 1];

    i = 0;
    while (i < WIDTH * HEIGHT)
    {
        if (i % WIDTH == 0)
        {
            str[j] = '\n';
            j++;
        }
        if (grid[i][0] == 0)
            str[j] = '0';
        else
            str[j] = '#';
        i++;
        j++;
    }
    str[i] = '\0';
    write(1, str, WIDTH * HEIGHT);
}

int main(int argc, char **argv)
{
    char    **grid;
    int     i;

    grid = init_grid();

    i = 0;
    while (i < 10)
    {
        find_next_state(grid);
        update(grid);
        print_grid(grid);
        i++;
        sleep(1);
    }
    free_grid(grid);
    return (0);
}
