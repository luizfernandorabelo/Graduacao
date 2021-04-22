#include <iostream>

using std::cout;
using std::cin;


int read_number_of_vertices_from_stdin() {

    int total_vertices = 0;

    cout << "n: ";
    cin >> total_vertices;

    while (total_vertices < 0) {
        fprintf(stderr, "O número de vértices não pode ser <= 0\n");
        cout << "n: ";
        cin >> total_vertices;
    }

    return total_vertices;
}


double read_connection_probability_from_stdin() {

    double connection_probability = 0.0;

    cout << "p: ";
    cin >> connection_probability;

    while (connection_probability < 0 || connection_probability > 1) {
        fprintf(stderr, "A probabilidade precisa ser um número entre 0 e 1\n");
        cout << "p: ";
        cin >> connection_probability;
    }

    return connection_probability;
}