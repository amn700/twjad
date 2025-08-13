#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_CITIES 11

typedef struct {
    float x;
    float y;
} Point;

// Calculate Euclidean distance between two points
float distance(Point a, Point b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrtf(dx * dx + dy * dy);
}

// Calculate total distance of a path (optimized with modulo)
float path_distance(Point *cities, int *path, int n)
{
    float total = 0.0f;
    
    for (int i = 0; i < n; i++)
        total += distance(cities[path[i]], cities[path[(i + 1)]]);
    return total;
}

// Swap two elements in array
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Generate permutations and find minimum distance (optimized)
void permute(Point *cities, int *path, int start, int n, float *min_dist)
{
    if (start == n)
    {
        float dist = path_distance(cities, path, n);
        if (dist < *min_dist)
            *min_dist = dist;
        return ;
    }
    for (int i = start; i < n; i++)
    {
        swap(&path[start], &path[i]);
        permute(cities, path, start + 1, n, min_dist);
        swap(&path[start], &path[i]);
    }
}

// Solve TSP using brute force (optimized)
float solve_tsp(Point *cities, int *path, int n)
{
    float min_dist = 1e9f; // Large initial value
    // Fix first city and permute the rest (reduces complexity from n! to (n-1)!)
    permute(cities, path, 1, n, &min_dist);
    return min_dist;
}

void extract_coord(char *line, int *i, float *coord)
{
    int sign = 1;
    *coord = 0;
    
    if (line[*i] == '-')
    {
        sign = -1;
        (*i)++;
    }
    while (line[*i] >= '0' && line[*i] <= '9')
    {
        *coord = *coord * 10 + (line[*i] - '0');
        (*i)++;
    }
    if (line[*i] == '.')
    {
        (*i)++;
        float factor = 0.1f;
        while (line[*i] >= '0' && line[*i] <= '9')
        {
            *coord += (line[*i] - '0') * factor;
            factor *= 0.1f;
            (*i)++;
        }
    }
    *coord *= sign;
}

int parse_coordinates(char *line, float *x, float *y)
{
    int i = 0;
    *x = 0;
    *y = 0;
    
    // Parse X coordinate first
    extract_coord(line, &i, x);
    // Skip comma and spaces
    if (line[i] != ',')
        return 0;
    i++;
    while (line[i] == ' ')
        i++;
    // Parse Y coordinate
    extract_coord(line, &i, y);
    return 1;
}

int main()
{
    Point   cities[MAX_CITIES];
    int     order[MAX_CITIES];
    int     n = 0;
    char    *line = NULL;
    size_t  len = 0;
    
    while (n < MAX_CITIES && getline(&line, &len, stdin) != -1)
    {
        float x, y;
        if (parse_coordinates(line, &x, &y))
        {
            cities[n].x = x;
            cities[n].y = y;
            n++;
        }
    }
    if (line)
        free(line);
    if (n < 2)
        return 1;
    for (int i = 0; i < n; i++)
        order[i] = i;
    float shortest_path = solve_tsp(cities, order, n);
    printf("%.2f\n", shortest_path);
    
    return 0;
}
