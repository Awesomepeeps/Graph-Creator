// Author: Nikaansh
// Last Edited: 6/4/24
// This is directed, weighted graph creator with a dijkstra's algorithm to find the shortest path between two nodes 


#include <iostream>
#include <cstring>

using namespace std;

#define MAXV 20

class Graph {
private:
    int matrix[MAXV][MAXV]; // Matrix for edges and their weight 
    string vertexLabels[MAXV]; // Array of string for the names of each vertex
    int vertexCount;

public:
    // Sets the count to 0 and all point in the matrix to "0"
    Graph() {
        vertexCount = 0;
        for (int row = 0; row < MAXV; row++) {
            for (int column = 0; column < MAXV; column++) {
                matrix[row][column] = -10; // Use -10 end represent no edge
            }
        }
    }

    // Gets the index
    int getVertexIndex(string label) const {
        for (int row = 0; row < vertexCount; row++) {
            if (vertexLabels[row] == label) {
                return row;
            }
        }
        return -11; // Cause 0 is already a index unfortunatly
    }

    // Adds a vertex with a name
    void addVertex(string label) {
        if (vertexCount < MAXV) { // Less than max of 20
            if (getVertexIndex(label) == -11) { // Dosen't exist
                vertexLabels[vertexCount] = label;
                vertexCount++;
            } 
            else {
                cout << "Vertex already exists" << endl;
            }
        } 
        else {
            cout << "Max vertices reached" << endl;
        }
    }

    // Adds an edge between two vertices and gives it a weight
    void addEdge(string start, string end, int weight) {
        int startIndex = getVertexIndex(start);
        int endIndex = getVertexIndex(end);

        if (startIndex != -11 && endIndex != -11) { // They both exsist
            matrix[startIndex][endIndex] = weight;
        } 
        else {
            cout << "Vertex/vertices not found" << endl;
        }
    }

    // Removes a vertex
    void removeVertex(string label) {
        int index = getVertexIndex(label);
        if (index != -11) { // It exsists
            for (int row = index; row < vertexCount - 1; row++) {
                vertexLabels[row] = vertexLabels[row + 1]; // Shifts everything in the label array down one becuase one is being deleted
                for (int column = 0; column < vertexCount; column++) { // Shifts everything in the edge array too
                    matrix[row][column] = matrix[row + 1][column]; 
                    matrix[column][row] = matrix[column][row + 1];
                }
            }
            vertexCount--;
            for (int row = 0; row < vertexCount; row++) { // Sets the last row to now be empty
                matrix[vertexCount][row] = -10;
                matrix[row][vertexCount] = -10;
            }
        } 
        else {
            cout << "Vertex " << label << " not found" << endl;
        }
    }

    // Removes an edge from the graph
    void removeEdge(string start, string end) {
        int startIndex = getVertexIndex(start);
        int endIndex = getVertexIndex(end);

        if (startIndex != -11 && endIndex != -11) { // It exsists
            matrix[startIndex][endIndex] = -10;
        } 
        else {
            cout << "Edge not found" << endl;
        }
    }

    // Prints the matrix
    void print() {
        // Go through each row of the matrix
        for (int row = 0; row < vertexCount; row++) {
            // Print the label of the current row
            cout << vertexLabels[row] << ": ";
            
            // Go through each column of the current row
            for (int column = 0; column < vertexCount; column++) {
                // Check for edge
                if (matrix[row][column] == -10) {
                    cout << "(N/A) ";
                } 
                else {
                    // Print the info for current edge
                    cout << "(" << vertexLabels[column] << ", " << matrix[row][column] << ") ";
                }
            }
            cout << endl;
        }
    }

    // Shortest path from a start to end node, geekforgeeks for help with printing
    void dijkstra(string start, string end) const {
        int startIndex = getVertexIndex(start);
        int endIndex = getVertexIndex(end);

        if (startIndex == -11 || endIndex == -11) { // One or both vertices do not exist
            cout << "Start or end vertex not found" << endl;
            return;
        }

        bool visited[MAXV]; // Contains whether a vertex has been visited or not
        int distances[MAXV]; // The minimum distance from starting vertex to all others
        int prev[MAXV]; // The previous vertex visited

        for (int i = 0; i < MAXV; i++) { // Initializing all three arrays above
            visited[i] = false;
            distances[i] = 2147483647;
            prev[i] = -1;
        }

        distances[startIndex] = 0; // Setting distance to starting to the lowest possible of zero

        for (int count = 0; count < vertexCount - 1; count++) { // Once for every time except the starting one
            int minDistance = 2147483647;
            int currentVertex = -1;

            for (int i = 0; i < vertexCount; i++) {
                if (!visited[i] && distances[i] <= minDistance) { // If not visited yet and distanct is less than or equal to minimum
                    minDistance = distances[i];
                    currentVertex = i;
                }
            }

            if (currentVertex == -1) { // If there is no other vertex with a possible distance then break out
                break;
            }

            visited[currentVertex] = true; // Marks smallest vertex as visited

            for (int i = 0; i < vertexCount; i++) { // Checks all neighboring vertices
                if (!visited[i] && matrix[currentVertex][i] != -10 && distances[currentVertex] != 2147483647 && distances[currentVertex] + matrix[currentVertex][i] < distances[i]) {
                    // If it hasen't been visited yet, if there is an edge between the two, and the updated one will be shorter that what is already the shortest
                    distances[i] = distances[currentVertex] + matrix[currentVertex][i]; // Updates with new distance
                    prev[i] = currentVertex; // Previous is updated
                }
            }
        }

        if (distances[endIndex] == 2147483647) { // If there is no path
            cout << "No path from start to end exsists" << endl;
        }
        else { // If there is a path this prints it out
            int totalWeight = distances[endIndex];
            cout << "Shortest path: ";
            int v = endIndex;
            while (v != -1) {
                cout << vertexLabels[v] << " ";
                v = prev[v];
            }
            cout << "(Total Weight: " << totalWeight << ")" << endl;
        }

    }

};

int main() {
    Graph graph;
    string input;
    
    while (true) {
        cout << "Do you want to add vertex (addV), add edge (addE), remove vertex (removeV), remove edge (removeE), print, dijkstra (dij), quit?" << endl;
        cin >> input;

        if (input == "addV") {
            string label;
            cout << "Name: ";
            cin >> label;
            graph.addVertex(label);
        } 
        else if (input == "addE") {
            string start;
            string end;
            int weight;
            cout << "Starting vertex: ";
            cin >> start;
            cout << "Ending vertex: ";
            cin >> end;
            cout << "Weight: ";
            cin >> weight;
            graph.addEdge(start, end, weight);
        } 
        else if (input == "removeV") {
            string label;
            cout << "Name: ";
            cin >> label;
            graph.removeVertex(label);
        } 
        else if (input == "removeE") {
            string start;
            string end;
            cout << "Starting vertex: ";
            cin >> start;
            cout << "Ending vertex: ";
            cin >> end;
            graph.removeEdge(start, end);
        } 
        else if (input == "print") {
            graph.print();
        }
        else if (input == "dij") {
            string start;
            string end;
            cout << "Starting vertex: ";
            cin >> start;
            cout << "Ending vertex: ";
            cin >> end;
            graph.dijkstra(start, end);
        }
        else if (input == "quit") {
            break;
        }
    }
}
