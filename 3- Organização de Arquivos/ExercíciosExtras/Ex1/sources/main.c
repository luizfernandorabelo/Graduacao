#include <stdio.h>
#include <string.h>

#include "csvFileManager.h"

typedef struct {
    int id;
    char *name;
    int age;
}USER;


void print_over_18_users(FILE *stream) {

    free(read_header_from_csv_file(stream)); // nesse caso o header não será usado

    USER current_user;

    while (!is_end_of_file(stream)) {
        current_user.id = read_int_from_csv_file(stream);
        current_user.name = read_string_from_csv_file(stream);
        current_user.age = read_int_from_csv_file(stream);
        if (current_user.age >= 18){
            if(strlen(current_user.name) > 0)
                printf("O usuario %s eh de maior.\n", current_user.name);
            else
                printf("O usuario de identificacao %d eh de maior.\n", current_user.id);
        }
        free(current_user.name);
    }
}


int main(int argc, char *argv[]) {

    char csv_file_name[20];
    scanf("%s", csv_file_name);

    FILE *csv_file_stream = fopen(csv_file_name, "r");

    print_over_18_users(csv_file_stream);

    fclose(csv_file_stream);

    return 0;
}