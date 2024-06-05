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

    void addVertex(string label) {
        if (vertexCount < MAXV) {
            if (getVertexIndex(label) == 0) {
                vertexLabels[vertexCount] = label;
                vertexCount++;
            } else {
                cout << "Vertex " << label << " already exists" << endl;
            }
        } else {
            cout << "Max vertices reached" << endl;
        }
    }
};

int main() {
    Graph graph;

    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
}
