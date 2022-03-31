/*
** EPITECH PROJECT, 2019
** generator
** File description:
** build_maze
*/

#include <stdlib.h>
#include "unistd.h"
#include "my.h"
#include "generator.h"
#include "stdio.h"

static void remove_child(struct node_s **nodes, long index, long child_nb)
{
    for (long i = index; i < child_nb - 1; i++)
        nodes[i] = nodes[i + 1];
}

static long add_child(struct map_s *map, struct node_s *origin, long child_nb)
{
    short direction_nb = -1;

    direction_nb += origin->dir & NORTH;
    direction_nb += origin->dir & EAST;
    direction_nb += origin->dir & WEST;
    direction_nb += origin->dir & SOUTH;
    if (direction_nb < 1)
        return child_nb;
    for (short i = 0; i < direction_nb && child_nb < MAX_CHILDS; i++)
        map->nodes[child_nb++] = link_node(map, origin);
    return child_nb;
}

static int display_maze(char *map, long height, long width)
{
    if (!map)
        return 84;
    if (write(1, map, MAP_SIZE(height, width)) == -1)
        return 84;
    my_printf("\n\n");
    //free(map);
    return EXIT_SUCCESS;
}

long build_maze(struct map_s *map, struct node_s *start, long child_nb)
{
    long child_pop_ratio = 6;

    for (long i = 0; i < child_nb; i++) {
     /*   my_printf("\e[1;1H\e[2J");
        printf("%li\n", child_nb);
        display_maze(map->maze, map->height, map->width);
        usleep(100000);*/
        if (map->nodes[i] == start) {
            remove_child(map->nodes, i--, child_nb--);
            continue;
        }
        if (child_nb < MAX_CHILDS && !(rand() % child_pop_ratio))
            child_nb = add_child(map, map->nodes[i], child_nb);
        map->nodes[i] = link_node(map, map->nodes[i]);
    }
    return child_nb;
}