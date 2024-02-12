#include "ParseData.h"

ParseData::ParseData(const std::string& airportsCSV, const std::string& airlinesCSV, const std::string& flightsCSV) {
    this->airportsCSV = airportsCSV;
    this->airlinesCSV = airlinesCSV;
    this->flightsCSV = flightsCSV;
    parseAirlines();
    parseAirports();
    parseFlights();
    dataGraph.setupInDegreeAndOutDegree();
}

void ParseData::parseAirlines() {
    ifstream file(airlinesCSV);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << airlinesCSV << endl;
        return;
    }

    string line;
    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);

        string nonTrimmed;
        Airline airlineObj;

        getline(ss, nonTrimmed, ',');
        airlineObj.setCode(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        airlineObj.setName(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        airlineObj.setCallsign(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        airlineObj.setCountry(TrimString(nonTrimmed));

        airlinesInfo.insert(airlineObj);
    }
    file.close();
}

void ParseData::parseAirports() {
    ifstream file(airportsCSV);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << airportsCSV << endl;
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);

        string nonTrimmed;
        Airport airportObj;
        double latitude, longitude;

        getline(ss, nonTrimmed, ',');
        airportObj.setCode(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        airportObj.setName(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        airportObj.setCity(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        airportObj.setCountry(TrimString(nonTrimmed));

        ss >> latitude;
        ss.ignore();
        ss >> longitude;
        airportObj.setLocation(latitude, longitude);

        dataGraph.addVertex(airportObj);
    }
    file.close();
}

void ParseData::parseFlights() {
    ifstream file(flightsCSV);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << flightsCSV << endl;
        return;
    }

    string line;
    getline(file, line);
    Airport temp1, temp2 = *new Airport();

    while(getline(file, line)) {
        stringstream ss(line);

        string source, target, airlineCode;

        getline(ss, source, ',');
        source = TrimString(source);

        getline(ss, target, ',');
        target = TrimString(target);

        getline(ss, airlineCode, ',');
        airlineCode = TrimString(airlineCode);

        temp1.setCode(source);
        temp2.setCode(target);

        Vertex<Airport>* sourceAirport = dataGraph.findVertex(temp1);
        Vertex<Airport>* targetAirport = dataGraph.findVertex(temp2);

        Edge<Airport>* foundEdge = nullptr;
        for (auto& e : sourceAirport->getAdj()) {
            auto t = e.getDest();
            if (t->getInfo() == targetAirport->getInfo()) {
                foundEdge = const_cast<Edge<Airport>*>(&e);
                break;
            }
        }

        if (foundEdge) {
            foundEdge->addAirline(getAirline(airlineCode));
        } else {
            double distance = sourceAirport->getInfo().getDistance(targetAirport->getInfo().getLocation());
            dataGraph.addEdge(sourceAirport->getInfo(), targetAirport->getInfo(), distance);

            for (auto& e : sourceAirport->getAdj()) {
                auto t = e.getDest();
                if (t->getInfo() == targetAirport->getInfo()) {
                    auto& nonConstEdge = const_cast<Edge<Airport>&>(e);
                    nonConstEdge.addAirline(getAirline(airlineCode));
                    break;
                }
            }
        }

        sourceAirport->setFlightsFrom(sourceAirport->getFlightsFrom() + 1);
        targetAirport->setFlightsTo(targetAirport->getFlightsTo() + 1);

    }
    file.close();
}

Airline ParseData::getAirline(const std::string& airlineCode) {
    for (const auto & it : airlinesInfo) {
        if (it.getCode() == airlineCode) return it;
    }
    return {};
}