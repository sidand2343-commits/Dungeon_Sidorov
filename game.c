#include <stdio.h>
#include <string.h>
#include "game.h"


void print_welcome(void) {
    printf("Welcome to the International!!!\n");
    printf("Management: north, south, east, west, look, quit\n\n");
}


void print_map(void) {
    printf("  #########\n");
    printf("  #.......#\n");
    printf("  #..###..#\n");
    printf("  #..#.#..#\n");
    printf("  #..###..#\n");
    printf("  #...@...#\n");
    printf("  #########\n");
}


void print_help(void) {
    printf("Commands:\n");
    printf("  north, south, east, west - move\n");
    printf("  look                     - to look around\n");
    printf("  quit                     - quit\n");
}


int process_command(const char *command) {
    if (strcmp(command, "quit") == 0) {
        printf("The game is over.\n");
        return CMD_QUIT;
    }
    if (strcmp(command, "north") == 0) {
        printf("You went north.\n");
        return CMD_CONTINUE_MOVE;
    }
    if (strcmp(command, "south") == 0) {
        printf("You went south.\n");
        return CMD_CONTINUE_MOVE;
    }
    if (strcmp(command, "east") == 0) {
        printf("You went east.\n");
        return CMD_CONTINUE_MOVE;
    }
    if (strcmp(command, "west") == 0) {
        printf("You went west.\n");
        return CMD_CONTINUE_MOVE;
    }
    if (strcmp(command, "look") == 0) {
        printf("You looked around.\n");
        print_map();
        return CMD_CONTINUE_NO_MOVE;
    }

    printf("Unknown command '%s'.\n", command);
    print_help();
    return CMD_CONTINUE_NO_MOVE;
}
