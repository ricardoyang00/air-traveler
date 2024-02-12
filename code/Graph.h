/**
 * @file Graph.h
 * @brief Header file containing structures and classes related to graph representation.
 *
 * This file defines structures and classes representing a graph data structure.
 * The 'Vertex' class represents vertices in the graph, containing information about the vertex,
 * including its adjacency list and other properties. The 'Edge' class represents edges between vertices,
 * containing information about the edge, including the destination vertex and weight.
 * The 'Graph' class represents the entire graph, encapsulating the collection of vertices and edges.
 */

#ifndef AED_AIRPORTS_GRAPH_H
#define AED_AIRPORTS_GRAPH_H

#include "Data.h"
#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <string>
#include <set>
#include <unordered_map>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

/****************** Structures  ********************/

/**
 * @class Vertex
 * @brief Class representing a vertex in a graph.
 * @tparam T Type of data contained in the vertex.
 */
template <class T>
class Vertex {
    T info;                 ///< The information contained in the vertex.
    vector<Edge<T>> adj;    ///< The list of adjacent edges.
    bool visited;           ///< Indicates if the vertex has been visited.
    bool processing;        ///< Indicates if the vertex is being processed.
    int inDegree;           ///< The number of edges directed towards the vertex.
    int outDegree;          ///< The number of edges directed away from the vertex.
    int num;                ///< The numerical value used in graph algorithms.
    int low;                ///< The low value used in graph algorithms.
    int flightsTo = 0;      ///< The number of flights to this vertex.
    int flightsFrom = 0;    ///< The number of flights from this vertex.

    /**
     * @brief Adds an edge to the vertex.
     * @param dest Pointer to the destination vertex.
     * @param distance Distance between vertices in kilometers.
     */
    void addEdge(Vertex<T> *dest, double distance);

    /**
     * @brief Removes an edge from the vertex to the specified destination.
     * @param d Pointer to the destination vertex.
     * @return True if the edge is successfully removed, otherwise false.
     */
    bool removeEdgeTo(Vertex<T> *d);

public:
    /**
     * @brief Constructor for the Vertex class.
     * @param in The information to be stored in the vertex.
     */
    Vertex(T in);

    /**
    * @brief Gets the information stored in the vertex.
    * @return The information contained in the vertex.
    */
    T getInfo() const;

    /**
     * @brief Sets the information for the vertex.
     * @param in The information to be stored in the vertex.
     */
    void setInfo(T in);

    /**
     * @brief Checks if the vertex has been visited.
     * @return True if the vertex has been visited, otherwise false.
     */
    bool isVisited() const;

    /**
     * @brief Sets the visit status of the vertex.
     * @param v Boolean indicating whether the vertex has been visited.
     */
    void setVisited(bool v);

    /**
     * @brief Checks if the vertex is being processed.
     * @return True if the vertex is being processed, otherwise false.
     */
    bool isProcessing() const;

    /**
     * @brief Sets the processing status of the vertex.
     * @param p Boolean indicating whether the vertex is being processed.
     */
    void setProcessing(bool p);

    /**
     * @brief Retrieves the list of adjacent edges.
     * @return The reference to the list of adjacent edges.
     */
    const vector<Edge<T>> &getAdj() const;

    /**
     * @brief Sets the list of adjacent edges for the vertex.
     * @param adj The list of adjacent edges to be set.
     */
    void setAdj(const vector<Edge<T>> &adj);

    /**
     * @brief Retrieves the inDegree of the vertex.
     * @return The inDegree of the vertex.
     */
    int getInDegree() const;

    /**
     * @brief Sets the inDegree of the vertex.
     * @param inDegree The inDegree value to set.
     */
    void setInDegree(int inDegree);

    /**
     * @brief Retrieves the outDegree of the vertex.
     * @return The outDegree of the vertex.
     */
    int getOutDegree() const;

    /**
     * @brief Sets the outDegree of the vertex.
     * @param outDegree The outDegree value to set.
     */
    void setOutDegree(int outDegree);

    /**
     * @brief Retrieves the numerical value used in graph algorithms.
     * @return The numerical value of the vertex.
     */
    int getNum() const;

    /**
     * @brief Sets the numerical value used in graph algorithms.
     * @param num The numerical value to set.
     */
    void setNum(int num);

    /**
     * @brief Retrieves the low value used in graph algorithms.
     * @return The low value of the vertex.
     */
    int getLow() const;

    /**
     * @brief Sets the low value used in graph algorithms.
     * @param low The low value to set.
     */
    void setLow(int low);

    /**
     * @brief Retrieves the number of flights to this vertex.
     * @return The number of flights to the vertex.
     */
    int getFlightsTo() const;

    /**
     * @brief Sets the number of flights to this vertex.
     * @param n The number of flights to set.
     */
    void setFlightsTo(int n);

    /**
     * @brief Retrieves the number of flights from this vertex.
     * @return The number of flights from the vertex.
     */
    int getFlightsFrom() const;

    /**
     * @brief Sets the number of flights from this vertex.
     * @param n The number of flights to set.
     */
    void setFlightsFrom(int n);

    /**
    * @brief Grants the Graph class access to private members of Vertex.
    *
    * Allows the Graph class to access private and protected members of the Vertex class,
    * fostering a close relationship between the two classes for efficient graph operations.
    */
    friend class Graph<T>;
};

/**
 * @class Edge
 * @brief Class representing an edge in a graph connecting two vertices.
 *
 * An Edge object defines a connection between two vertices in a graph.
 * It holds information about the destination vertex, distance, and associated airlines.
 * @tparam T The data type of the vertex.
 */
template <class T>
class Edge {
    Vertex<T>* dest;            ///< Pointer to the destination vertex.
    double distance;            ///< The distance between source and destination vertices in kilometers.
    std::set<Airline> airlines; ///< The set of airlines associated with this edge.

public:
    /**
     * @brief Constructor for the Edge class.
     * @param d Pointer to the destination vertex.
     * @param distance The distance to the destination vertex.
     */
    Edge(Vertex<T> *d, double distance);

    /**
     * @brief Retrieves the destination vertex of this edge.
     * @return Pointer to the destination vertex.
     */
    Vertex<T> *getDest() const;

    /**
     * @brief Sets the destination vertex of this edge.
     * @param dest Pointer to the destination vertex.
     */
    void setDest(Vertex<T> *dest);

    /**
     * @brief Retrieves the set of airlines associated with this edge.
     * @return Constant reference to the set of airlines.
     */
    const std::set<Airline>& getAirlines() const;

    /**
     * @brief Adds an airline to the set associated with this edge.
     * @param airline The airline to add.
     */
    void addAirline(const Airline& airline);

    /**
     * @brief Retrieves the distance of this edge.
     * @return The distance between vertices.
     */
    double getDistance() const;

    /**
     * @brief Sets the distance of this edge.
     * @param distance The distance between vertices.
     */
    void setDistance(double distance);

    /**
     * @brief Grants the Graph class access to private members of Edge.
     *
     * This friendship declaration allows the Graph class to access private and protected members of the Edge class,
     * enabling efficient graph operations and maintaining a close relationship between the classes.
     */
    friend class Graph<T>;

    /**
     * @brief Grants the Vertex class access to private members of Edge.
     *
     * This friendship declaration allows the Vertex class to access private and protected members of the Edge class,
     * facilitating interactions necessary for graph manipulation and traversal.
     */
    friend class Vertex<T>;
};

/**
 * @class Graph
 * @brief Class representing a directed graph.
 *
 * The Graph class defines a directed graph structure using vertices and edges.
 * It supports various graph operations like adding/removing vertices, edges,
 * performing depth-first search (DFS), breadth-first search (BFS), topological sorting, etc.
 * @tparam T The data type of the graph vertices.
 */
template <class T>
class Graph {
    vector<Vertex<T>*> vertexSet;   ///< The collection of vertices in the graph.
    int _index_;                    ///< The used internally.
    stack<Vertex<T>> _stack_;       ///< The stack used internally.
    list<list<T>> _list_sccs_;      ///< The list of strongly connected components.

    /**
     * @brief Performs a depth-first search visit starting from a given vertex.
     * @param v Pointer to the starting vertex.
     * @param res Vector containing the visited vertices.
     */
    void dfsVisit(Vertex<T> *v, vector<T> &res) const;

public:
    /**
     * @brief Finds a vertex in the graph based on the given information.
     * @param in The information to search for.
     * @return Pointer to the vertex if found, nullptr otherwise.
     */
    Vertex<T> *findVertex(const T &in) const;

    /**
     * @brief Retrieves the number of vertices in the graph.
     * @return The number of vertices in the graph.
     */
    int getNumVertex() const;

    /**
     * @brief Retrieves the set of vertices in the graph.
     * @return Vector containing pointers to all vertices in the graph.
     */
    vector<Vertex<T>*> getVertexSet() const;

    /**
     * @brief Adds a vertex to the graph with the given information.
     * @param in The information for the new vertex.
     * @return True if the vertex was added successfully, false otherwise.
     */
    bool addVertex(const T &in);

    /**
     * @brief Removes a vertex from the graph based on the given information.
     * @param in The information to identify the vertex to be removed.
     * @return True if the vertex was removed successfully, false otherwise.
     */
    bool removeVertex(const T &in);

    /**
     * @brief Adds a directed edge between two vertices in the graph.
     * @param source Information of the source vertex.
     * @param dest Information of the destination vertex.
     * @param distance The distance between the source and destination vertices.
     * @return True if the edge was added successfully, false otherwise.
     */
    bool addEdge(const T &source, const T &dest, double distance);

    /**
     * @brief Removes a directed edge between two vertices in the graph.
     * @param source Information of the source vertex.
     * @param dest Information of the destination vertex.
     * @return True if the edge was removed successfully, false otherwise.
     */
    bool removeEdge(const T &source, const T &dest);

    /**
     * @brief Performs a depth-first search (DFS) on the entire graph.
     * @return Vector containing the vertices visited during the DFS.
     */
    vector<T> dfs() const;

    /**
     * @brief Performs a depth-first search (DFS) starting from a specific vertex in the graph.
     * @param source Information of the starting vertex.
     * @return Vector containing the vertices visited during the DFS.
     */
    vector<T> dfs(const T & source) const;

    /**
     * @brief Performs a breadth-first search (BFS) starting from a specific vertex in the graph.
     * @param source Information of the starting vertex.
     * @return Vector containing the vertices visited during the BFS.
     */
    vector<T> bfs(const T &source) const;

    /**
     * @brief Performs topological sorting of the graph using depth-first search (DFS).
     * @return Vector containing the topologically sorted vertices.
     */
    vector<T> topsort() const;

    /**
     * @brief Sets up the inDegree and outDegree of vertices in the graph.
     * @details Calculates and assigns the inDegree and outDegree for each vertex in the graph.
     * The inDegree of a vertex is the count of incoming edges, while the outDegree is the count of outgoing edges.
     * This function iterates through all edges in the graph to update the inDegree and outDegree of each vertex.
     * Note: This function assumes that the graph has been appropriately constructed with vertices and edges.
     */
    void setupInDegreeAndOutDegree();
};

/****************** Constructors and functions ********************/

template<class T>
Vertex<T>::Vertex(T in): info(in) {}

template<class T>
T Vertex<T>::getInfo() const { return info; }

template<class T>
void Vertex<T>::setInfo(T in) { Vertex::info = in; }

template <class T>
bool Vertex<T>::isVisited() const { return visited; }

template <class T>
void Vertex<T>::setVisited(bool v) { Vertex::visited = v; }

template<class T>
bool Vertex<T>::isProcessing() const { return processing; }

template<class T>
void Vertex<T>::setProcessing(bool p) { Vertex::processing = p; }

template<class T>
const vector<Edge<T>> &Vertex<T>::getAdj() const { return adj; }

template <class T>
void Vertex<T>::setAdj(const vector<Edge<T>> &adj) { Vertex::adj = adj; }

template<class T>
int Vertex<T>::getInDegree() const { return inDegree; }

template<class T>
void Vertex<T>::setInDegree(int inDegree) { Vertex::inDegree = inDegree; }

template<class T>
int Vertex<T>::getOutDegree() const { return outDegree; }

template<class T>
void Vertex<T>::setOutDegree(int outDegree) { Vertex::outDegree = outDegree; }

template<class T>
int Vertex<T>::getNum() const { return num; }

template<class T>
void Vertex<T>::setNum(int num) { Vertex::num = num; }

template<class T>
int Vertex<T>::getLow() const { return low; }

template<class T>
void Vertex<T>::setLow(int low) { Vertex::low = low; }

template<class T>
int Vertex<T>::getFlightsTo() const { return flightsTo; }

template<class T>
void Vertex<T>::setFlightsTo(int n) { flightsTo = n; }

template<class T>
int Vertex<T>::getFlightsFrom() const { return flightsFrom; }

template<class T>
void Vertex<T>::setFlightsFrom(int n) { flightsFrom = n; }

/**************************************************/

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), distance(w) {}

template<class T>
Vertex<T> *Edge<T>::getDest() const { return dest; }

template<class T>
void Edge<T>::setDest(Vertex<T> *d) { Edge::dest = d; }

template<class T>
const std::set<Airline>& Edge<T>::getAirlines() const { return airlines; }

template<class T>
void Edge<T>::addAirline(const Airline& airline) { airlines.insert(airline); }

template<class T>
double Edge<T>::getDistance() const { return distance; }

template<class T>
void Edge<T>::setDistance(double distance) { Edge::distance = distance; }

/**************************************************/

template <class T>
Vertex<T> *Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet) {
        if (v->info == in)
            return v;
    }
    return NULL;
}

template <class T>
int Graph<T>::getNumVertex() const { return vertexSet.size(); }

template <class T>
vector<Vertex<T>*> Graph<T>::getVertexSet() const { return vertexSet; }

template <class T>
bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

template <class T>
bool Graph<T>::removeVertex(const T &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->info  == in) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}

template <class T>
bool Graph<T>::addEdge(const T &source, const T &dest, double distance) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2, distance);
    return true;
}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *d,  double distance) {
    adj.push_back(Edge<T>(d, distance));
}

template <class T>
bool Graph<T>::removeEdge(const T &source, const T &dest) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}

template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest == d) {
            adj.erase(it);
            return true;
        }
    return false;
}

template <class T>
void Graph<T>::setupInDegreeAndOutDegree() {
    for (auto& v : vertexSet) {
        v->inDegree = 0;
        v->outDegree = v->adj.size();
    }

    for (auto& v : vertexSet) {
        for (auto& e : v->adj) {
            auto w = e.dest;
            w->inDegree = w->inDegree + 1;
        }
    }
}

/****************** DFS ********************/

template <class T>
vector<T> Graph<T>::dfs() const {
    vector<T> res;
    for (auto v : vertexSet)
        v->visited = false;
    for (auto v : vertexSet)
        if (! v->visited)
            dfsVisit(v, res);
    return res;
}

template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> &res) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto &e : v->adj) {
        auto w = e.dest;
        if (!w->visited)
            dfsVisit(w, res);
    }
}

template <class T>
vector<T> Graph<T>::dfs(const T &source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;

    for (auto v : vertexSet)
        v->visited = false;

    dfsVisit(s, res);
    return res;
}

/****************** BFS ********************/

template <class T>
vector<T> Graph<T>::bfs(const T &source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    queue<Vertex<T> *> q;
    for (auto v : vertexSet)
        v->visited = false;
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->info);
        for (auto & e : v->adj) {
            auto w = e.dest;
            if ( ! w->visited ) {
                q.push(w);
                w->visited = true;
            }
        }
    }
    return res;
}

/****************** topsort ********************/

template<class T>
vector<T> Graph<T>::topsort() const {
    vector<T> res;
    queue<Vertex<T>> q;

    for (auto v : vertexSet)
        v->inDegree = 0;
    for (auto v : vertexSet) {
        for (auto &e : v->getAdj()) {
            auto d = e.dest;
            d->inDegree++;
        }
    }

    for (auto v : vertexSet) {
        if (v->inDegree == 0)
            q.push(*v);
    }

    while (!q.empty()) {
        auto vertex = q.front();
        for (auto &e : vertex.getAdj()) {
            e.dest->inDegree--;
            if (e.dest->inDegree == 0)
                q.push(*e.dest);
        }
        q.pop();
        res.push_back(vertex.getInfo());
    }
    return res;
}

#endif //AED_AIRPORTS_GRAPH_H