#include "randomMatrix.h"
#include "checkArguments.h"

#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_NODES_ARG argv[1]
#define CONNECTION_PROBABILITY_ARG argv[2]


int main(int argc, char *argv[]) {

    check_argument_number(argc);

    int numberOfNodes = atoi(NUMBER_OF_NODES_ARG);
    double connectionProbability = (double) atof(CONNECTION_PROBABILITY_ARG);

    check_argument_values(numberOfNodes, connectionProbability);

    int **randomMatrix = create_new_random_matrix(numberOfNodes, connectionProbability);
    print_matrix(randomMatrix, numberOfNodes);

    free_matrix(randomMatrix, numberOfNodes);

    return 0;
}