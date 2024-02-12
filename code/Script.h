/**
 * @file
 * @brief Defines the Script class for interacting with the "Air Travel Flight Management System".
 */
#ifndef AED_AIRPORTS_SCRIPT_H
#define AED_AIRPORTS_SCRIPT_H

#include "Consult.h"
#include "OutputData.h"

/**
 * @class Script
 * @brief Handles the interactive operations for the "Air Travel Flight Management System."
 */
class Script {
public:
    /**
     * @brief Constructor for Script class.
     * @param dataGraph The graph containing airport data for the flight management system.
     * @param airlinesInfo The set containing airlines information for the flight management system.
     */
    Script(const Graph<Airport>& dataGraph, const std::set<Airline> airlinesInfo);

    /**
     * @brief Initiates the interactive system and displays the main menu.
     * This method serves as the entry point for user interaction.
     */
    void run();

private:
    /**
     * @struct MenuItem
     * @brief Represents an item in the menu with a label and associated action.
     */
    struct MenuItem {
        string label;               ///< The label or display text for the menu item.
        void (Script::*action)();   ///< The pointer to a member function of the Script class.
    };

    /**
     * @brief Object responsible for handling consultations.
     */
    Consult consult;

    Graph<Airport> dataGraph;                           ///< Graph structure representing the relationships between airports and airlines.

    bool travelChosen{};                                ///< Indicates whether the menu for travel has been chosen.

    bool customLayoversChosen{};                        ///< Indicates that the "custom layovers" has been selected

    bool sourceChosen{};                                ///< Indicates that the "source" has been selected.

    bool cityChosenSource{};                            ///< Indicates that the "source" has been chosen as a city.

    bool cityChosenDestiny{};                           ///< Indicates that the "destination" has been chosen as a city.

    map<string, vector<Vertex<Airport>*>> travelMap;    ///< Stores the airport(s) of the source and the destination.

    vector<Vertex<Airport>*> customLayovers;            ///< Stores the selected layover airports chosen by the user.

    /**
     * @brief Draws a box around the provided text on the screen.
     * @param text The text to be surrounded by a box.
     */
    void drawBox(const string& text);

    /**
     * @brief Displays a menu with the provided items and handles user input.
     * @param menuName The name/title of the menu.
     * @param menuItems The list of MenuItem structures representing the menu items.
     * @return The selected menu item index.
     */
    int showMenu(const string& menuName, const vector<MenuItem>& menuItems);

    /**
     * @brief Clears the screen.
     */
    void clearScreen();

    /**
     * @brief Handles the action for going back in the menu.
     */
    void actionGoBack();

    /**
     * @brief Waits for the user to press the Enter key before returning to the main menu.
     * It prompts the user to press Enter to continue and waits for the input.
     */
    void backToMenu();

    /**
     * @brief Prints detailed information about an airport.
     * @param airport Pointer to the Vertex containing the Airport information.
     */
    void printAirportInfo(const Vertex<Airport>* airport);

    /**
     * @brief Prints information about an airport in a single line.
     * @param airport Pointer to the Vertex containing the Airport information.
     */
    void printAirportInfoOneline(const Airport& airport);

    /**
     * @brief Displays a submenu for consulting some global statistics about the air travel network.
     */
    void globalNumber();

    /**
     * @brief Displays the total number of airports in the air travel network.
     */
    void numberOfAirports();

    /**
     * @brief Displays the total number of flights in the air travel network.
     */
    void numberOfFlights();

    /**
     * @brief Displays the total number of flight routes in the air travel network.
     */
    void numberOfFlightRoutes();

    /**
     * @brief Lists the total number of flights departing from each city within the air travel network.
     */
    void flightsPerCity();

    /**
     * @brief Lists the total number of flights operated by each airline in the air travel network.
     */
    void flightsPerAirline();

    /**
     * @brief Displays the number of different countries that a city can fly to.
     *
     * This function prompts the user to enter a city and the respective country, then calls a function to search and
     * calculate the total number of different countries that can be reached by flights originating at the specified city.
     */
    void countriesFlownToFromCity();

    /**
     * @brief Displays the number of airports, cities and countries reachable within X lay-overs when flying out from a specific airport.
     *
     * This function prompts the user to enter the number of desired lay-overs, then calls a function to search and
     * calculate the number of airports, cities and countries reachable within the specified layover limit
     * and finally it outputs those numbers.
     *
     * @param airport Pointer to the Vertex containing the Airport information.
     */
    void destinationsAvailableWithLayOvers(Vertex<Airport>* airport);

    /**
     * @brief Displays 7 different statistics related to the specified airport.
     *
     * This function displays 7 different statistics about the specified airport:
     * 1. Flight routes out of the airport
     * 2. Flights out of the airport
     * 3. Flights out of the airport (from different airlines)
     * 4. Number of different countries flown to from the airport
     * 5. Available airports when flying from the airport
     * 6. Available cities when flying from the airport
     * 7. Available countries when flying from the airport
     *
     * @param airport Pointer to the Vertex containing the Airport information.
     */
    void givenAirportStatistics(Vertex<Airport>* airport);

    /**
     * @brief Displays the flight trip(s) with the greatest number of stops in between them and the paths of the airports from source to destination.
     */
    void maximumTrip();

    /**
     * @brief Displays the top K airport with the greatest air traffic capacity (flights arriving and departing from the airport).
     */
    void topKAirportAirTraffic();

    /**
     * @brief Displays all the airports that are essential to the network’s circulation capability, if removed, areas of the network start to be unreachable.
     */
    void essentialAirports();

    /**
     * @brief Displays a submenu where user can select to see the specified airport statistics or to set as source/destination if chosen the option travel.
     * @param airport Pointer to the Vertex containing the Airport information.
     */
    void airportStatistics(Vertex<Airport>* airport);

    /**
     * @brief List airports based on a specified criterion (name, city, or country) and allow the user to choose one for further analysis.
     * @param airports A vector of pointers to Vertex<Airport>, representing the airports to be listed.
     * @param name The name to be searched for (e.g., airport name, city name, or country name).
     * @param typeName The type of criterion for the search (e.g., "airport," "city," or "country").
     */
    void listAndChooseAirport(vector<Vertex<Airport> *> airports, const string& name, const string& typeName);

    /**
     * @brief Displays a submenu where user can choose different ways to search for an airport.
     */
    void searchAirportsMenu();

    /**
     * @brief Find and display information about a specific airport based on the user-provided airport code.
     */
    void searchAirportByAirportCode();

    /**
     * @brief List airports that contain user-provided name in the airport name, considering case and space insensitivity.
     */
    void searchAirportByAirportName();

    /**
     * @brief List all airports that are located in cities containing the user-provided city name, considering case and space insensitivity.
     */
    void searchAirportByCityName();

    /**
     * @brief List all airports that are located in countries containing the user-provided country name, considering case and space insensitivity.
     */
    void searchAirportByCountryName();

    /**
     * @brief List all airports closest to user-provided coordinates (latitude, longitude).
     */
    void searchClosestAirport();

    /**
     * @brief Find and display information about a specific airline based on the user-provided airport code.
     */
    void searchAirlines();

    /**
     * @brief Displays a submenu for user to search for a location to set as the flight source.
     */
    void selectSource();

    /**
     * @brief Displays a submenu for user to search for a location to set as the flight destination.
     */
    void selectDestiny();

    /**
     * @brief Search for airports based on the user-provided city and country names.
     *
     * This function prompts the user to enter a city and country name, performs a search for airports in the specified city and country,
     * and provides options for further actions such as setting the city and country as the source or destination for travel or to choose an airport
     * to set it as the source/destination for travel.
     */
    void searchAirportByCityAndCountryName();

    /**
     * @brief Handles extra filters for travel options.
     *
     * Allows users to add custom layovers, view best flights, and navigate through extra filtering options for their travel.
     * Users can select to add specific layover airports that their flights must pass through.
     */
    void extraFiltersTravel();

    /**
     * @brief Allows users to select custom layover airports.
     *
     * Provides options for users to add custom layover airports by different criteria such as airport code, name, city, or coordinates.
     * Users can choose from various options to add specific layover airports for their flights.
     */
    void selectCustomLayovers();

    /**
     * @brief Display 2 best flight options: travel by same or any airline from source to destination.
     *
     * This function provides the user with options to choose the best flights either within the same airline
     * or considering all airlines. It also displays the source and destination locations user provided.
     */
    void showBestFlight();

    /**
     * @brief Display a list of the best flights based on user preferences.
     *
     * This function presents the user with a list of the best flight options according to the option of airlines user had chosen,
     * including the layovers, airports involved, and total distance for each option. The user can choose a specific flight for detailed
     * information or return to the previous menu.
     *
     * @param totalPaths A vector containing information about each best flight option.
     */
    void showListOfBestFlights(vector<pair<set<Airline>, pair<vector<Vertex<Airport>*>, double>>> totalPaths);

    /**
     * @brief Find the best flight paths considering the same airline from source to destination.
     *
     * This function searches for the best flight paths between the given source and destination airports, considering
     * only flights operated by the same airline for each leg of the journey. It returns a vector of pairs, where each pair
     * represents a valid flight option. Each option includes the set of airlines operating the flight, the flight path
     * (vector of airport vertices), and the total distance of the flight.
     *
     * @param source A vector of airport vertices representing the source airports.
     * @param destination A vector of airport vertices representing the destination airports.
     * @return A vector of pairs, each containing a set of airlines, a vector of airport vertices representing the flight path, and the total distance of the flight.
     */
    vector<pair<set<Airline>, pair<vector<Vertex<Airport>*>, double>>> getBestPathsSameAirlines (vector<Vertex<Airport>*> source, vector<Vertex<Airport>*> destination);

    /**
     * @brief Find the best flight paths considering all available airlines flying from source to destination.
     *
     * This function searches for the best flight paths between the given source and destination airports, considering
     * all available airlines for each leg of the journey. It returns a vector of pairs, where each pair represents a valid
     * flight option. Each option includes an empty set of airlines (considering all airlines), the flight path (vector of
     * airport vertices), and the total distance of the flight.
     *
     * @param source A vector of airport vertices representing the source airports.
     * @param destination A vector of airport vertices representing the destination airports.
     * @return A vector of pairs, each containing an empty set of airlines, a vector of airport vertices representing the flight path, and the total distance of the flight.
     */
    vector<pair<set<Airline>, pair<vector<Vertex<Airport>*>, double>>> getBestPathsAllAirlines(vector<Vertex<Airport>*> source, vector<Vertex<Airport>*> destination);

    /**
     * @brief Find the best flight paths considering the same airline from source to destination with custom layovers.
     *
     * This function searches for the best flight paths between the given source and destination airports, considering
     * only flights operated by the same airline for each leg of the journey, with custom layovers. It returns a vector
     * of pairs, where each pair represents a valid flight option. Each option includes the set of airlines operating the
     * flight, the flight path (vector of airport vertices), and the total distance of the flight.
     *
     * @param source A vector of airport vertices representing the source airports.
     * @param destination A vector of airport vertices representing the destination airports.
     * @return A vector of pairs, each containing a set of airlines, a vector of airport vertices representing the flight path, and the total distance of the flight.
     */
    vector<pair<set<Airline>, pair<vector<Vertex<Airport>*>, double>>> getBestPathsSameAirlinesWithCustomLayovers(vector<Vertex<Airport>*> source, vector<Vertex<Airport>*> destination);

    /**
     * @brief Find the best flight paths considering all available airlines from source to destination with custom layovers.
     *
     * This function searches for the best flight paths between the given source and destination airports, considering
     * all available airlines for each leg of the journey, with custom layovers. It returns a vector of pairs, where each pair
     * represents a valid flight option. Each option includes an empty set of airlines (considering all airlines), the flight path
     * (vector of airport vertices), and the total distance of the flight.
     *
     * @param source A vector of airport vertices representing the source airports.
     * @param destination A vector of airport vertices representing the destination airports.
     * @return A vector of pairs, each containing an empty set of airlines, a vector of airport vertices representing the flight path, and the total distance of the flight.
     */
    vector<pair<set<Airline>, pair<vector<Vertex<Airport>*>, double>>> getBestPathsAllAirlinesWithCustomLayovers(vector<Vertex<Airport>*> source, vector<Vertex<Airport>*> destination);

    /**
     * @brief Print details about the best flight trip.
     *
     * This function prints detailed information about the best flight trip, including the total distance, airport details,
     * and available airlines for each leg of the journey.
     *
     * @param trip A pair containing a set of airlines, a vector of airport vertices representing the flight path, and the total distance of the flight.
     */
    void printBestFlightDetails(pair<set<Airline>, pair<vector<Vertex<Airport>*>, double>> trip);

    /**
     * @brief Print the source and destination information for the travel selection.
     */
    void printSourceAndDestination();

    /**
     * @brief Print the selected layover airports chosen by the user.
     */
    void printCustomLayovers();
};


#endif //AED_AIRPORTS_SCRIPT_H
