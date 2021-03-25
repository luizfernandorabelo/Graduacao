#ifndef INP_READER_H
#define INP_READER_H

#define SHIFT_RIGHT 1
#define SHIFT_LEFT -1
#define ADD_EMPTY_BOX 2
#define REMOVE_BOX -2
#define ADD_PKMN_START 3
#define ADD_PKMN_POS 4
#define REMOVE_PKMN_POS -4
#define PRINT_BOX 5
#define EXIT 0

int readOption(void);
int readPos(void);

#endif