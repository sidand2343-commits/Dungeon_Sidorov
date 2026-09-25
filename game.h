#ifndef GAME_H
#define GAME_H

enum CommandResult {
    CMD_CONTINUE_NO_MOVE = 0,
    CMD_CONTINUE_MOVE      = 1,
    CMD_QUIT               = 2
};

void print_welcome(void);
void print_map(void);
void print_help(void);
int  process_command(const char *command);

#endif /* GAME_H */