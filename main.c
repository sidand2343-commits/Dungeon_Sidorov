#include <stdio.h>
#include "game.h"


int main(void) {
    char command[16];
    int move_counter = 0;
    int is_playing = 1;

    print_welcome();
    print_map();

    while (is_playing) {
        printf("\n[Move %d] Enter the command: ", move_counter);

        if (scanf("%15s", command) != 1) {
            is_playing = 0;
        } else {
            int result = process_command(command);

            if (result == CMD_QUIT) {
                is_playing = 0;
            } else if (result == CMD_CONTINUE_MOVE) {
                move_counter++;
            }
        }
    }

    return 0;
}