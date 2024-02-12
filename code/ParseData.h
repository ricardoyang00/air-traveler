/**
 * @file ParseData.h
 * @brief Header file containing functionalities to parse data related to the Air Travel Flights.
 *
 * This file defines the ParseData class, responsible for parsing airports, airlines and flights data
 * from CSV files and constructing a graph structure to represent the relationships between airports and airlines.
 * It contains methods to parse airports, airlines, and flights information and initializes the graph accordingly.
 */

#ifndef AED_AIRPORTS_PARSEDATA_H
#define AED_AIRPORTS_PARSEDATA_H

#include "Data.h"
#include "Graph.h"
#include <fstream>

/**
 * @class ParseData
 * @brief Class responsible for parsing data from CSV files
 */
class ParseData {
private:
    Graph<Airport> dataGraph;          ///< Graph structure representing the relationships between airports and airlines.
    std::set<Airline> airlinesInfo;    ///< Set containing the airlines information.
    std::string airportsCSV;           ///< The file path to the CSV containing airports data to be parse.
    std::string airlinesCSV;           ///< The file path to the CSV containing airlines data to be parse.
    std::string flightsCSV;            ///< The file path to the CSV containing flights data to be parse.

    /**
    * @brief Parses information about airlines from the airlines CSV file.
    */
    void parseAirlines();

    /**
     * @brief Parses information about airports from the airports CSV file.
     */
    void parseAirports();

    /**
     * @brief Parses information about flights from the flights CSV file.
     */
    void parseFlights();

    /**
     * @brief Retrieves information about a specific airline using its code.
     * @param airlineCode The code of the airline to retrieve information for.
     * @return Information about the airline with the specified code.
     */
    Airline getAirline(const std::string& airlineCode);

public:
    /**
     * @brief Constructor for ParseData class.
     * @param airportsCSV Path to the airports CSV file.
     * @param airlinesCSV Path to the airlines CSV file.
     * @param flightsCSV Path to the flights CSV file.
     */
    ParseData(const std::string& airportsCSV, const std::string& airlinesCSV, const std::string& flightsCSV);

    /**
     * @brief Retrieves the constructed airport graph.
     * @return A constant reference to the constructed airport graph.
     */
    const Graph<Airport>& getDataGraph() const { return dataGraph; }

    /**
     * @brief Retrieves the airlines information set.
     * @return A constant reference to the airlines information set.
     */
    const std::set<Airline>& getAirlinesInfo() const { return airlinesInfo; }
};



#endif //AED_AIRPORTS_PARSEDATA_H
