#include <iostream>
#include "code/Script.h"

int main() {
    std::string airportsCSV = "data/airports.csv";
    std::string airlinesCSV = "data/airlines.csv";
    std::string flightsCSV = "data/flights.csv";
    ParseData parseData(airportsCSV, airlinesCSV, flightsCSV);
    Script script(parseData.getDataGraph(), parseData.getAirlinesInfo());

    script.run();

    return 0;
}
