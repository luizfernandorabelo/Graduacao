#include <stdio.h>
#include <string.h>

#include "binFileManager.h"

#define USER_NAME_LENGTH 50


typedef struct {
    int id;
    char *name;
    int age;
}USER;


void print_over_18_users(FILE *stream) {

    USER current_user;

    while (!is_end_of_file(stream)) {
        current_user.id = read_int_from_bin_file(stream);
        current_user.name = read_string_from_bin_file(stream, USER_NAME_LENGTH);
        current_user.age = read_int_from_bin_file(stream);
        if (current_user.age >= 18) {
            if(strlen(current_user.name) > 0)
                printf("O usuario %s eh de maior.\n", current_user.name);
            else
                printf("O usuario de identificacao %d eh de maior.\n", current_user.id);
        }
        free(current_user.name);
    }
}


int main(int argc, char *argv[]) {

    char bin_file_name[20];
    scanf("%s", bin_file_name);

    FILE *bin_file_stream = fopen(bin_file_name, "rb");

    print_over_18_users(bin_file_stream);

    fclose(bin_file_stream);

    return 0;
}