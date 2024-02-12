/**
 * @file OutputData.h
 * @brief Header file containing functions to output airport data to a text file.
 */

#ifndef AED_AIRPORTS_OUTPUTDATA_H
#define AED_AIRPORTS_OUTPUTDATA_H

#include "ParseData.h"

/**
 * @brief Converts airport graph data into a text file format.
 * @param airportGraph The graph containing airport information.
 * @param filename The name of the file to which the data will be written.
 *
 * This function takes an airport graph and writes its information, including airport codes, names,
 * locations (city, country, coordinates), and flight routes, to a specified text file.
 */

inline void convertDataGraphToTextFile(const Graph<Airport>& airportGraph, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    for (const auto& a : airportGraph.getVertexSet()) {
        auto airport = a->getInfo();
        outFile << ">> [" << airport.getCode() << "] " << airport.getName() << " <<" << std::endl;
        outFile << "    City       : " << airport.getCity() << std::endl;
        outFile << "    Country    : " << airport.getCountry() << std::endl;
        outFile << "    Coordinates: (" << airport.getLocation().latitude << ", " << airport.getLocation().longitude << ")" << std::endl;
        outFile << "    Flight routes from this airport : " << a->getOutDegree() << std::endl;
        outFile << "    Flight routes to this airport   : " << a->getInDegree() << std::endl << std::endl;

        for (const auto& e : a->getAdj()) {
            auto target = e.getDest()->getInfo();
            outFile << "    • " << airport.getCode() << " -> " << target.getCode() << " : " << e.getDistance() << " km" << std::endl;
            outFile << "        by Airlines: " << std::endl;
            int i = 1;
            for (const auto& airline : e.getAirlines()) {
                outFile << "            " << i++ << ".(" << airline.getCode() << ") " << airline.getCallsign() << std::endl;
            }
            outFile << std::endl;
        }
        outFile << std::endl;
    }
    outFile.close();

    cout << "Data exported successfully to \"" << filename << "\"" << endl;
};
#endif //AED_AIRPORTS_OUTPUTDATA_H
