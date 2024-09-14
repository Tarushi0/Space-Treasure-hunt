#include <stdio.h>
#include <stdlib.h>
#include "space_explorer.h"

typedef struct {
    unsigned int *visited_planets;
    unsigned int current_index;
    unsigned int total_planets;
    double last_distance; // the last known distance to treas
} ShipState;

// Check if a planet has been visited
int visited(unsigned int planet, ShipState *state) {
    for (int i = 0; i < state->total_planets; i++) {
        if (state->visited_planets[i] == planet) {
            return 1;
        }
    }
    return 0;
}

ShipAction space_hop(unsigned int crt_planet, unsigned int *connections, int num_connections, double distance_from_mixer, void *ship_state) {
    ShipState *state;
    if (ship_state == NULL) {
        state = malloc(sizeof(ShipState));
        state->visited_planets = malloc(sizeof(unsigned int) * 1000);
        state->current_index = 0;
        state->total_planets = 0;
        state->last_distance = 0;
    } else {
        state = (ShipState *)ship_state;
    }

    printf("Current Planet: %u, Distance from treasure: %.2f\n", crt_planet, distance_from_mixer);

    // Add current planet to the visited list if not already visited
    if (!visited(crt_planet, state)) {
        state->visited_planets[state->total_planets++] = crt_planet;
        state->last_distance = distance_from_mixer; // Update last distance
    }

    // Determine the next planet to hop to
    unsigned int next_planet = RAND_PLANET;
    double closest_distance = state->last_distance;

    for (int i = 0; i < num_connections; i++) {
        if (!visited(connections[i], state)) {
            if (distance_from_mixer <= closest_distance) {
                closest_distance = distance_from_mixer;
                next_planet = connections[i];
            }
        }
    }

    if (next_planet != -1) {
        printf("Moving to Planet: %u\n", next_planet);
    } else {
        // If stuck, move randomly to any planet
        next_planet = RAND_PLANET;
        printf("Moving randomly to another planet.\n");
    }

    return (ShipAction){ .next_planet = next_planet, .ship_state = state };
}
