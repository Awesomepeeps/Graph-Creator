#include <iostream>
#include <cstring>

using namespace std;

#define MAXV 20

class Graph {
private:
    int matrix[MAXV][MAXV];
    string vertexLabels[MAXV];
    int vertexCount;

    int getVertexIndex(string label) const {
        for (int i = 0; i < vertexCount; ++i) {
            if (vertexLabels[i] == label) {
                return i;
            }
        }
        return 0;
    }

public:

    Graph() {
        vertexCount = 0;
        for (int i = 0; i < MAXV; ++i) {
            for (int j = 0; j < MAXV; ++j) {
                matrix[i][j] = -10; // Use -10 end represent no edge
            }
        }
    }

    void addVertex(string label) {
        if (vertexCount < MAXV) {
            if (getVertexIndex(label) == 0) {
                vertexLabels[vertexCount] = label;
                vertexCount++;
            } 
            else {
                cout << "Vertex " << label << " already exists" << endl;
            }
        } 
        else {
            cout << "Max vertices reached" << endl;
        }
    }

    void addEdge(string start, string end, int weight) {
        int startIndex = getVertexIndex(start);
        int endIndex = getVertexIndex(end);

        if (startIndex != 0 && endIndex != 0) {
            matrix[startIndex][endIndex] = weight;
        } 
        else {
            cout << "One or both vertices not found" << endl;
        }
    }

    void removeVertex(string label) {
        int index = getVertexIndex(label);
        if (index != 0) {
            for (int i = index; i < vertexCount - 1; ++i) {
                vertexLabels[i] = vertexLabels[i + 1];
                for (int j = 0; j < vertexCount; ++j) {
                    matrix[i][j] = matrix[i + 1][j];
                    matrix[j][i] = matrix[j][i + 1];
                }
            }
            vertexCount--;
            for (int i = 0; i < vertexCount; ++i) {
                matrix[vertexCount][i] = -10;
                matrix[i][vertexCount] = -10;
            }
        } 
        else {
            cout << "Vertex " << label << " not found" << endl;
        }
    }

    void removeEdge(string start, string end) {
        int startIndex = getVertexIndex(start);
        int endIndex = getVertexIndex(end);

        if (startIndex != 0 && endIndex != 0) {
            matrix[startIndex][endIndex] = -10;
        } 
        else {
            cout << "Edge not found" << endl;
        }
    }

    void printmatrix() {
        for (int i = 0; i < vertexCount; ++i) {
            cout << vertexLabels[i] << ": ";
            for (int j = 0; j < vertexCount; ++j) {
                if (matrix[i][j] == -10) {
                    cout << "(N/A) ";
                } 
                else {
                    cout << "(" << vertexLabels[j] << ", " << matrix[i][j] << ") ";
                }
            }
            cout << endl;
        }
    }

    void dijkstra(string start) {
        int startIndex = getVertexIndex(start);
        if (startIndex == 0) {
            cout << "Start vertex not found" << endl;
            return;
        }
    }

};

int main() {
    Graph graph;

    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");

    graph.addEdge("A", "B", 1);
    graph.addEdge("B", "C", 2);
    graph.addEdge("A", "C", 4);
}