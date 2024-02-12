/**
 * @file Consult.h
 * @brief Header file providing functionalities for analyzing air travel flight data.
 *
 * This file defines the Consult class, which offers various methods to perform analyses and queries
 * on airport-related data using a provided graph structure. It includes functionalities such as
 * counting flights per city, per airline, available destinations, traffic statistics, finding paths
 * between airports, and more. Additionally, it aids in deriving insightful information and metrics
 * from airport-related datasets.
 */

#ifndef AED_AIRPORTS_CONSULT_H
#define AED_AIRPORTS_CONSULT_H

#include "ParseData.h"
#include <map>
#include <unordered_set>
#include <limits>
#include <functional>

/**
 * @class Consult
 * @brief Provides functionalities to perform various queries and analyses on Air Travel Flight data.
 */
class Consult {
private:
    const Graph<Airport>& consultGraph;     ///< Reference to the airport graph used for consultation.

    const std::set<Airline> airlinesInfo;   ///< Reference to the airlines information set for consultation.

    /**
     * @brief Performs a depth-first search to count flights per city of a country from a given vertex.
     * @param v Pointer to the vertex initiating the search.
     * @param res Map containing the count of flights per city of a country.
     */
    void dfsVisitFlightsPerCity(Vertex<Airport> *v, map<pair<string,string>, int> &res);

    /**
     * @brief Performs a depth-first search to count flights per airline from a given vertex.
     * @param v Pointer to the vertex initiating the search.
     * @param res Map containing the count of flights per airline.
     */
    void dfsVisitFlightsPerAirline(Vertex<Airport> *v, map<Airline, int> &res);

    /**
     * @brief Initiates a depth-first search to find airports in a specific city and country.
     * @param city The city to search for.
     * @param country The country to search for.
     * @param v Pointer to the vertex initiating the search.
     * @param res Vector containing vertices representing airports in the given city and country.
     */
    void dfsVisitCityAirports(const string& city, const string& country, Vertex<Airport> *v, vector<Vertex<Airport>*>& res);

    /**
     * @brief Initiates a depth-first search to process available destinations from a vertex.
     * @param v Pointer to the vertex initiating the search.
     * @param processDestination Function to process the available destinations.
     */
    void dfsAvailableDestinations(Vertex<Airport>* v, std::function<void(Vertex<Airport>*)> processDestination);

    /**
     * @brief Searches for the number of reachable destinations from an airport in a specified number of stops.
     * @param airport Pointer to the starting airport.
     * @param layOvers Number of layovers or stops to consider.
     * @param attributeExtractor Function to extract an attribute for each reachable destination.
     * @return The count of reachable destinations in 'X' stops (number of layovers).
     */
    int searchNumberOfReachableDestinationsInXStopsFromAirport(Vertex<Airport>* airport, int layOvers, const function<string(Vertex<Airport>*)>& attributeExtractor);

    /**
     * @brief Finds the top airports with the highest air traffic capacity.
     * @return Decreasingly ordered vector of pairs containing airports and their traffic capacities.
     */
    vector<pair<Airport,int>> topTrafficCapacityAirports();

    /**
     * @brief Initiates a depth-first search to identify essential airports.
     * @param v Pointer to the vertex initiating the search.
     * @param s Stack used in the search process.
     * @param res Unordered set containing essential airports found.
     * @param i Counter used in the search process.
     */
    void dfsEssentialAirports(Vertex<Airport> *v, stack<string> &s, unordered_set<string> &res, int &i);

    /**
     * @brief Finds airports based on a specified attribute.
     * @tparam T The type of attribute to search for (name, city, country).
     * @param searchName The value of the attribute to search for.
     * @param getAttr Pointer to the member function that retrieves the attribute from Airport class.
     * @return Vector of airport vertices matching the attribute.
     */
    template <typename T>
    vector<Vertex<Airport>*> findAirportsByAttribute(const string& searchName, T (Airport::*getAttr)() const);

public:
    /**
     * @brief Constructor for Consult class.
     * @param dataGraph Reference to the airport graph used for consultation.
     * @param airlinesInfo Reference to the airlines information graph used for consultation.
     */
    Consult(const Graph<Airport>& dataGraph, const std::set<Airline> airlinesInfo);

    /**
     * @brief Counts the total number of airports.
     * @return The number of airports.
     *
     * Time Complexity: O(1)
     */
    int searchNumberOfAirports();

    /**
     * @brief Counts the total number of available flights.
     * @return The number of available flights.
     *
     * Time Complexity: O(V) where V is the number of vertices of the graph
     */
    int searchNumberOfAvailableFlights();

    /**
     * @brief Counts the total number of available flight routes.
     * @return The number of available flight routes.
     *
     * Time Complexity: O(V) where V is the number of vertices of the graph
     */
    int searchNumberOfAvailableFlightRoutes();

    /**
     * @brief Counts the number of flights departing from a specific airport.
     * @param airport Pointer to the airport vertex.
     * @return The number of flights departing from the airport.
     *
     * Time Complexity: O(1)
     */
    int searchNumberOfFlightsOutOfAirport(Vertex<Airport>* airport);

    /**
     * @brief Counts the number of flights arriving at a specific airport.
     * @param airport Pointer to the airport vertex.
     * @return The number of flights arriving at the airport.
     *
     * Time Complexity: O(1)
     */
    int searchNumberOfFlightsToAirport(Vertex<Airport>* airport);

    /**
     * @brief Counts the number of flights departing from a specific airport via different airlines.
     * @param airport Pointer to the airport vertex.
     * @return The number of flights departing from the airport via different airlines.
     *
     * Time Complexity: O(E*A) where E stands for the edges (flight routes) and A for the airlines using the flight route.
     *             However it can be considered O(E) because the number of airlines for 1 flight route is relatively small and constant.
     */
    int searchNumberOfFlightsOutOfAirportFromDifferentAirlines(Vertex<Airport>* airport);

    /**
     * @brief Searches the number of flights per city of a country.
     * @return Map containing the count of flights per city of a country.
     *
     * Time Complexity: O(V+E) where V stands for the airport vertices of the graph and E the flight route edges.
     *             Note: Considering the auxiliary function 'dfsVisitFlightsPerCity'.
     */
    map<pair<string,string>, int> searchNumberOfFlightsPerCity();

    /**
     * @brief Searches the number of flights per airline.
     * @return Map containing the count of flights per airline.
     *
     * Time Complexity: O(V+E+V*A) where V stands for the vertices, E for the edges and A for the airlines.
     *             Note: Considering the auxiliary function 'dfsVisitFlightsPerAirline'.
     */
    map<Airline, int> searchNumberOfFlightsPerAirline();

    /**
     * @brief Counts the number of countries flown to from a specific airport.
     * @param airport Pointer to the airport vertex.
     * @return The number of countries flown to from the specified airport.
     *
     * Time Complexity: O(E) where E stands for the flight routes (edges).
     */
    int searchNumberOfCountriesFlownToFromAirport(Vertex<Airport>* airport);

    /**
     * @brief Counts the number of countries flown to from a specific city and country.
     * @param city The city name.
     * @param country The country name.
     * @return The number of countries flown to from the specified city and country.
     *
     * Time Complexity: O(V+E+E') where V stands for vertices, E for edges and E' for the edges going out from the airports in the specified city.
     *             Note: Considering the auxiliary function 'dfsVisitCityAirports'.
     */
    int searchNumberOfCountriesFlownToFromCity(const string& city, const string& country);

    /**
     * @brief Counts the number of available airports reachable from a specific airport.
     * @param airport Pointer to the airport vertex.
     * @return The number of available airports reachable from the specified airport.
     *
     * Time Complexity: O(V+E) where V stands for vertices and E for edges.
     *             Note: Considering the auxiliary function 'dfsAvailableDestinations'.
     */
    int searchNumberOfAirportsAvailableForAirport(Vertex<Airport>* airport);

    /**
     * @brief Counts the number of available cities reachable from a specific airport.
     * @param airport Pointer to the airport vertex.
     * @return The number of available cities reachable from the specified airport.
     *
     * Time Complexity: O(V+E) where V stands for vertices and E for edges.
     *             Note: Considering the auxiliary function 'dfsAvailableDestinations'.
     */
    int searchNumberOfCitiesAvailableForAirport(Vertex<Airport>* airport);

    /**
     * @brief Counts the number of available countries reachable from a specific airport.
     * @param airport Pointer to the airport vertex.
     * @return The number of available countries reachable from the specified airport.
     *
     * Time Complexity: O(V+E) where V stands for vertices and E for edges.
     *             Note: Considering the auxiliary function 'dfsAvailableDestinations'.
     */
    int searchNumberOfCountriesAvailableForAirport(Vertex<Airport>* airport);

    /**
     * @brief Counts the number of reachable airports in a certain number of stops (layovers) from a specific airport.
     * @param airport Pointer to the airport vertex.
     * @param layOvers The maximum number of layovers.
     * @return The number of reachable airports within the specified layovers.
     *
     * Time Complexity: O(V+E) where V stands for vertices and E for edges.
     *             Note: Considering the auxiliary function 'searchNumberOfReachableDestinationsInXStopsFromAirport'.
     */
    int searchNumberOfReachableAirportsInXStopsFromAirport(Vertex<Airport>* airport, int layOvers);

    /**
     * @brief Counts the number of reachable cities in a certain number of stops (layovers) from a specific airport.
     * @param airport Pointer to the airport vertex.
     * @param layOvers The maximum number of layovers.
     * @return The number of reachable cities within the specified layovers.
     *
     * Time Complexity: O(V+E) where V stands for vertices and E for edges.
     *             Note: Considering the auxiliary function 'searchNumberOfReachableDestinationsInXStopsFromAirport'.
     */
    int searchNumberOfReachableCitiesInXStopsFromAirport(Vertex<Airport>* airport, int layOvers);

    /**
     * @brief Count the number of reachable countries in a certain number of stops (layovers) from a specific airport.
     * @param airport Pointer to the airport vertex.
     * @param layOvers The maximum number of layovers.
     * @return The number of reachable countries within the specified layovers.
     *
     * Time Complexity: O(V+E) where V stands for vertices and E for edges.
     *             Note: Considering the auxiliary function 'searchNumberOfReachableDestinationsInXStopsFromAirport'.
     */
    int searchNumberOfReachableCountriesInXStopsFromAirport(Vertex<Airport>* airport, int layOvers);

    /**
      * @brief Searches for the top 'K' airports with the greatest air traffic capacity.
      * @details Retrieves the top 'K' airports with the greatest air traffic capacity.
      * If there are airports with the same capacity as the 'K+1'th airport, they are also included in the result.
      * @param k The number of top airports to retrieve.
      * @return A vector of pairs containing airports and their corresponding air traffic capacity.
      *
      * Time Complexity: O(V*logV) where V stands for the vertices, the sorting function is the most time-consuming part of the functions.
      *             Note: Considering the auxiliary function 'topTrafficCapacityAirports'.
      */
    vector<pair<Airport,int>> searchTopKAirportGreatestAirTrafficCapacity(const int& k);

    /**
     * @brief Searches for essential airports using Tarjan's algorithm for finding strongly connected components.
     * @return An unordered set containing the codes of essential airports.
     *
     * Time Complexity: O(V+E) where V stands for vertices and E for edges.
     *             Note: Considering the auxiliary function 'dfsEssentialAirports'.
     */
    unordered_set<string> searchEssentialAirports();

    /**
     * @brief Searches for the maximum trip and corresponding pairs of airports.
     * @details Finds the longest trip possible within the airport network and retrieves all corresponding paths.
     * @return A vector of vectors containing sequences of airports representing the paths of the longest trip(s).
     *
     * Time Complexity: O(V*(V+E)) where V stands for vertices and E for edges, it needs to iterate over all vertices,
     *             and for each vertex, it performs BFS.
     */
    vector<vector<Vertex<Airport>*>> searchMaxTripAndCorrespondingPairsOfAirports(int& diameter);

    /**
     * @brief Searches for the smallest path between two airports.
     * @details Retrieves the smallest path between the specified source and target airports.
     * @param source The starting airport.
     * @param target The destination airport.
     * @return A vector of vectors containing sequences of airports representing the smallest path(s) between the source and target airports.
     *
     * Time Complexity: O(V*(V+E)) where V stands for vertices and E for edges.
     */
    vector<vector<Vertex<Airport>*>> searchSmallestPathBetweenAirports(Vertex<Airport>* source, Vertex<Airport>* target);

    /**
     * @brief Finds an airport vertex based on the airport code.
     * @param airportCode The code of the airport to search for.
     * @return Pointer to the airport vertex if found, nullptr otherwise.
     *
     * Time Complexity: O(V) where V stands for the airport vertices of the graph.
     */
    Vertex<Airport>* findAirportByCode(const string& airportCode);

    /**
     * @brief Finds airports based on the airport name.
     * @param searchName The name of the airport(s) to search for.
     * @return Vector of airport vertices matching the airport name.
     *
     * Time Complexity: O(V+(M*logM)) where V stands for vertices and M for matching airports, O(M*logM) for sorting the matching airports.
     *             Note: Considering the auxiliary function 'findAirportsByAttribute'.
     */
    vector<Vertex<Airport>*> findAirportsByAirportName(const string& searchName);

    /**
     * @brief Finds airports based on the city name.
     * @param searchName The name of the city associated with the airport(s) to search for.
     * @return Vector of airport vertices in the specified city.
     *
     * Time Complexity: O(V+(M*logM)) where V stands for vertices and M for matching airports, O(M*logM) for sorting the matching airports.
     *             Note: Considering the auxiliary function 'findAirportsByAttribute'.
     */
    vector<Vertex<Airport>*> findAirportsByCityName(const string& searchName);

    /**
     * @brief Finds airports based on the country name.
     * @param searchName The name of the country associated with the airport(s) to search for.
     * @return Vector of airport vertices in the specified country.
     *
     * Time Complexity: O(V+(M*logM)) where V stands for vertices and M for matching airports, O(M*logM) for sorting the matching airports.
     *             Note: Considering the auxiliary function 'findAirportsByAttribute'.
     */
    vector<Vertex<Airport>*> findAirportsByCountryName(const string& searchName);

    /**
     * @brief Finds the closest airports to given geographical coordinates.
     * @param coordinates The coordinates (latitude and longitude) for which the closest airports are searched.
     * @return Vector of airport vertices closest to the specified coordinates.
     *
     * Time Complexity: O(V*logV) where V stands for the vertices, the overall time complexity is dominated by the sorting operation.
     */
    vector<Vertex<Airport>*> findClosestAirports(const Coordinates& coordinates);

    /**
     * @brief Finds airports based on the city and country names.
     * @param city The name of the city associated with the airport(s) to search for.
     * @param country The name of the country associated with the airport(s) to search for.
     * @return Vector of airport vertices in the specified city and country.
     *
     * Time Complexity: O(V+E) where V stands for vertices and E for edges.
     *             Note: Considering the auxiliary function 'dfsVisitCityAirports'.
     */
    vector<Vertex<Airport>*> getAirportsInACityAndCountry(const string& city, const string& country);

    /**
     * @brief Retrieves the set of airlines that operate between two airports.
     * @param source Pointer to the source airport.
     * @param target Pointer to the target airport.
     * @return Set of airlines that operate between the specified airports.
     *
     * Time Complexity: O(E) where E stands for edges (flight routes).
     */
    std::set<Airline> airlinesThatOperateBetweenAirports(Vertex<Airport>* source, Vertex<Airport>* target);

    /**
     * @brief Retrieves the distance between two airports.
     * @param source Pointer to the source airport.
     * @param target Pointer to the target airport.
     * @return The distance between the specified airports in kilometers.
     *
     * Time Complexity: O(E) where E stands for edges (flight routes).
     */
    double getDistanceBetweenAirports(Vertex<Airport>* source, Vertex<Airport>* target);

    /**
     * @brief Retrieves an airline from the airlinesInfo set based on the provided code.
     *
     * This function searches for an airline in the airlinesInfo set using a specified code.
     * If the airline is found, it is returned via the 'airline' parameter.
     *
     * @param airline [out] The reference to an Airline object where the found airline will be stored.
     * @param code [in] The code used to search for the airline.
     *
     * @return true if the airline corresponding to the provided code is found and retrieved successfully,
     *         false otherwise.
     */
    bool getAirlineFromCode(Airline& airline, std::string code);
};


#endif //AED_AIRPORTS_CONSULT_H
