#ifndef __MY_GRAPH_H__
    #define __MY_GRAPH_H__

    #include <vector>
    
    class Graph {
        
        public:

            int total_vertices;
            double edge_connection_probability;
            int **adjacency_matrix;

            Graph(int totalVertices, double edgeConnectionProbability);

            void print_adjacency_matrix();
            int get_vertex_degree(int vertex);
            std::vector<int> get_vertex_adjacencies(int vertex);
            bool edge_exists(std::pair<int,int> coordinates);
    };

#endif