/**
 * @file Utilities.h
 * @brief Contains utility functions for string manipulation and geographical calculations.
 *
 * This header file provides various utility functions used for string manipulation and geographical calculations.
 * Functions include string trimming, conversion to radians, Haversine distance calculation,
 * converting strings to lowercase, removing spaces, and formatting text in bold for terminal output.
 */

#ifndef AED_AEROPORTO_UTILITIES_H
#define AED_AEROPORTO_UTILITIES_H

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <vector>

/**
 * @brief Trim whitespace from the beginning and end of a string.
 * @param toTrim The string to be trimmed.
 * @return The trimmed string.
 */
std::string TrimString(const std::string& toTrim);

/**
 * @brief Converts degrees to radians.
 * @param degrees The angle in degrees to be converted.
 * @return The angle in radians.
 */
double ToRadians(double degrees);

/**
 * @brief Calculates the Haversine distance between two coordinates.
 * @param lat1 Latitude of the first coordinate.
 * @param lon1 Longitude of the first coordinate.
 * @param lat2 Latitude of the second coordinate.
 * @param lon2 Longitude of the second coordinate.
 * @return The distance between the coordinates in kilometers.
 */
double HarversineDistance(double lat1, double lon1, double lat2, double lon2);

/**
 * @brief Converts a string to lowercase.
 * @param input The input string to be converted.
 * @return The lowercase version of the input string.
 */
std::string ToLower(const std::string& input);

/**
 * @brief Converts a string to uppercase.
 * @param input The input string to be converted.
 * @return The uppercase version of the input string.
 */
std::string ToUpper(const std::string& input);

/**
 * @brief Removes spaces from a string.
 * @param str The input string to remove spaces from.
 * @return The string without spaces.
 */
std::string RemoveSpaces(const std::string& str);

/**
 * @brief Formats a value in bold for terminal output.
 * @param value The value to be formatted.
 * @return The formatted value in bold.
 */
template <typename T>
std::string makeBold(const T& value) {
    std::ostringstream oss;
    oss << "\033[1m" << value << "\033[0m";
    return oss.str();
};

/**
 * @brief Merges two vectors into a single vector, considering the continuity of elements between the vectors.
 *
 * This function combines two vectors into one, ensuring the continuity of elements between them. It verifies if the last element
 * of the first vector is equal to the first element of the second vector. If the continuity condition is met, it creates a new
 * merged vector starting with the elements of the first vector and appending the elements of the second vector from the second
 * element onwards. If either of the vectors is empty or the continuity condition is not satisfied, an empty vector is returned.
 *
 * @param first The first vector to merge.
 * @param second The second vector to merge.
 * @return A merged vector if continuity is maintained, otherwise an empty vector.
 */
template<typename T>
std::vector<T> mergeVectors(const std::vector<T>& first, const std::vector<T>& second) {
    if (first.empty() || second.empty()) {
        std::cerr << "One or both vectors are empty.\n";
        return {};
    }

    if (first.back() == second.front()) {
        std::vector<T> merged(first.begin(), first.end());
        merged.insert(merged.end(), second.begin() + 1, second.end());
        return merged;
    } else {
        std::cerr << "The last element of the first vector is not equal to the first element of the second vector.\n";
        return {};
    }
}

#endif //AED_AEROPORTO_UTILITIES_H
