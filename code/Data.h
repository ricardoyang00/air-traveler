/**
 * @file Data.h
 * @brief Header file containing structures and classes related to airport and airline data representation.
 *
 * This file defines structures and classes representing essential data related to airports and airlines.
 * The 'Coordinates' structure represents geographic coordinates with latitude and longitude values,
 * while the 'Airport' class encapsulates information about an airport, including its 'IATA' code, name, location, and country.
 * Additionally, the 'Airline' class represents information about an airline, including its 'ICAO' code, name, callsign, and country.
 */

#ifndef AED_AEROPORTO_DATA_H
#define AED_AEROPORTO_DATA_H

#include "Utilities.h"
#include <vector>

/**
 * @struct Coordinates
 * @brief Structure to represent geographic coordinates.
 */
struct Coordinates {
    double latitude;    ///< Latitude value of the coordinates.
    double longitude;   ///< Longitude value of the coordinates.
};

/**
 * @class Airport
 * @brief Class representing a airport.
 */
class Airport {
private:
    std::string code;       ///< The IATA code of the airport.
    std::string name;       ///< The airport name.
    std::string city;       ///< The city where the airport is located.
    std::string country;    ///< The country where the airport is located.
    Coordinates location;   ///< The geographic coordinates of the airport.

public:
    /**
     * @brief Default constructor for the Airport class.
     */
    Airport() {}

    /**
     * @brief Constructor for the Airport class.
     * @param c The airport code.
     * @param n The airport name.
     * @param ci The airport city.
     * @param co The airport country.
     * @param l The airport geographic coordinates.
     */
    Airport(const std::string& c, const std::string& n, const std::string& ci, const std::string& co, Coordinates l)
            : code(c), name(n), city(ci), country(co), location(l) {}

    /**
     * @brief Retrieves the airport code.
     * @return The airport code.
     */
    std::string getCode() const { return code; }

    /**
     * @brief Sets the airport code.
     * @param c The airport code.
     */
    void setCode(const std::string& c) { code = c; }

    /**
     * @brief Retrieves the airport name.
     * @return The airport name.
     */
    std::string getName() const { return name; }

    /**
     * @brief Sets the airport name.
     * @param n The airport name.
     */
    void setName(const std::string& n) { name = n; }

    /**
     * @brief Retrieves the city where the airport is located.
     * @return The city where the airport is located.
     */
    std::string getCity() const { return city; }

    /**
     * @brief Sets the city where the airport is located.
     * @param ci The city where the airport is located.
     */
    void setCity(const std::string& ci) { city = ci; }

    /**
     * @brief Retrieves the country where the airport is located.
     * @return The country where the airport is located.
     */
    std::string getCountry() const { return country; }
    /**
     * @brief Sets the country where the airport is located.
     * @param co The country where the airport is located.
     */
    void setCountry(const std::string& co) { country = co; }

    /**
     * @brief Retrieves the geographic coordinates of the airport.
     * @return The geographic coordinates of the airport.
     */
    Coordinates getLocation() const { return location; }

    /**
     * Sets the geographic coordinates of the airport.
     * @param latitude The latitude value.
     * @param longitude The longitude value.
     */
    void setLocation(double latitude, double longitude) {
        location.latitude = latitude;
        location.longitude = longitude;
    }

    /**
     * @brief Calculate the distance between the airport's coordinates and another set of coordinates using the Haversine formula.
     * @param other The other set of coordinates.
     * @return The distance between the airport and the provided coordinates in kilometers.
     */
    double getDistance(const Coordinates& other) const { return HarversineDistance(location.latitude, location.longitude, other.latitude, other.longitude); }

    /**
     * @brief Overloaded equality operator to compare two airports based on their codes.
     * @param other The other airport object.
     * @return True if the airports have the same code, otherwise false.
     */
    bool operator==(const Airport& other) const { return code == other.code; }
};

/**
 * @class Airline
 * @brief Class representing a airline.
 */
class Airline {
private:
    std::string code;       ///< The ICAO code of the airline.
    std::string name;       ///< The official name of the airline.
    std::string callsign;   ///< The callsign of the airline (if available, "_" otherwise).
    std::string country;    ///< The country of registry.

public:
    /**
    * @brief Default constructor for the Airline class.
    */
    Airline() {}

    /**
     * @brief Constructor for the airline class.
     * @param c The ICAO code of the airline.
     * @param n The official name of the airline.
     * @param cs The callsign of the airline (if available, "_" otherwise).
     * @param co The country of registry.
     */
    Airline(const std::string& c, const std::string& n, const std::string& cs, const std::string& co)
            : code(c), name(n), callsign(cs), country(co) {}

    /**
     * @brief Retrieves the airline code.
     * @return The airline code.
     */
    std::string getCode() const { return code; }

    /**
     * @brief Sets the airline code.
     * @param c The airline code.
     */
    void setCode(const std::string& c) { code = c; }

    /**
     * @brief Retrieves the airline official name.
     * @return The airline name.
     */
    std::string getName() const { return name; }

    /**
     * @brief Sets the airline name.
     * @param n The airline name.
     */
    void setName(const std::string& n) { name = n; }

    /**
     * @brief Retrieves the airline callsign.
     * @return The airline callsign.
     */
    std::string getCallsign() const { return callsign; }

    /**
     * @brief Sets the airline callsign.
     * @param cs The airline callsign.
     */
    void setCallsign(const std::string& cs) { callsign = cs; }

    /**
     * @brief Retrieves the airline registry country.
     * @return The airline registry country.
     */
    std::string getCountry() const { return country; }

    /**
     * @brief Sets the airline registry country.
     * @param co The airline registry country.
     */
    void setCountry(const std::string& co) { country = co; }

    /**
     * @brief Less than operator to compare two airlines based on their codes.
     * @param other The other airline object.
     * @return True if this airline's code is less than the other's code, otherwise false.
     */
    bool operator<(const Airline& other) const { return code < other.code; }

    /**
     * @brief Overloaded equality operator to compare two airlines based on their codes.
     * @param other The other airline object.
     * @return True if the airlines have the same code, otherwise false.
     */
    bool operator==(const Airline& other) const { return code == other.code; }
};

#endif //AED_AEROPORTO_DATA_H
