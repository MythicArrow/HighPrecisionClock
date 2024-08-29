#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

int main() {
    int timeZoneOffset;
    std::string precision;

    // Ask the user for their time zone offset from GMT/UTC
    std::cout << "Enter your time zone offset from GMT/UTC (e.g., -5 for EST, +1 for CET): ";
    std::cin >> timeZoneOffset;

    // Ask the user for the desired precision (milliseconds, microseconds, or nanoseconds)
    std::cout << "Enter the desired precision (ms for milliseconds, us for microseconds, ns for nanoseconds): ";
    std::cin >> precision;

    // Determine sleep duration based on precision
    std::chrono::milliseconds sleepDuration(10); // Default sleep duration (milliseconds)

    if (precision == "ms") {
        sleepDuration = std::chrono::milliseconds(10);
    } else if (precision == "us") {
        sleepDuration = std::chrono::microseconds(10);
    } else if (precision == "ns") {
        sleepDuration = std::chrono::nanoseconds(10);
    } else {
        std::cout << "Invalid precision entered!" << std::endl;
        return 1;
    }

    while (true) {
        // Get the current time with high precision
        auto now = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::system_clock::to_time_t(now);
        auto localTime = std::gmtime(&currentTime);  // Start with GMT time

        // Adjust for the user's time zone
        localTime->tm_hour += timeZoneOffset;

        // Handle day wrap-around
        if (localTime->tm_hour >= 24) {
            localTime->tm_hour -= 24;
            localTime->tm_mday += 1;
        } else if (localTime->tm_hour < 0) {
            localTime->tm_hour += 24;
            localTime->tm_mday -= 1;
        }

        // Determine the desired precision
        if (precision == "ms") {
            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
                                    now.time_since_epoch()) % 1000;

            // Display the time with milliseconds
            std::cout << "\033[2J\033[1;1H";  // Clear the screen (optional)
            std::cout << "Current time in your time zone: "
                      << std::setfill('0') << std::setw(2) << localTime->tm_hour << ":"
                      << std::setfill('0') << std::setw(2) << localTime->tm_min << ":"
                      << std::setfill('0') << std::setw(2) << localTime->tm_sec << "."
                      << std::setfill('0') << std::setw(3) << milliseconds.count() << " ms" << std::endl;
        } 
        else if (precision == "us") {
            auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(
                                    now.time_since_epoch()) % 1000000;

            // Display the time with microseconds
            std::cout << "\033[2J\033[1;1H";  // Clear the screen (optional)
            std::cout << "Current time in your time zone: "
                      << std::setfill('0') << std::setw(2) << localTime->tm_hour << ":"
                      << std::setfill('0') << std::setw(2) << localTime->tm_min << ":"
                      << std::setfill('0') << std::setw(2) << localTime->tm_sec << "."
                      << std::setfill('0') << std::setw(6) << microseconds.count() << " us" << std::endl;
        } 
        else if (precision == "ns") {
            auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(
                                   now.time_since_epoch()) % 1000000000;

            // Display the time with nanoseconds
            std::cout << "\033[2J\033[1;1H";  // Clear the screen (optional)
            std::cout << "Current time in your time zone: "
                      << std::setfill('0') << std::setw(2) << localTime->tm_hour << ":"
                      << std::setfill('0') << std::setw(2) << localTime->tm_min << ":"
                      << std::setfill('0') << std::setw(2) << localTime->tm_sec << "."
                      << std::setfill('0') << std::setw(9) << nanoseconds.count() << " ns" << std::endl;
        }

        // Wait for the specified period before updating
        std::this_thread::sleep_for(sleepDuration);
    }

    return 0;
}