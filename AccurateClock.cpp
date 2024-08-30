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

    // Ask the user for the desired precision (s for seconds, ms for milliseconds, us for microseconds, ns for nanoseconds)
    std::cout << "Enter the desired precision (s for seconds, ms for milliseconds, us for microseconds, ns for nanoseconds): ";
    std::cin >> precision;

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

        // Clear the screen (optional, works on most terminals)
        std::cout << "\033[2J\033[1;1H";

        // Determine the desired precision
        if (precision == "s") {
            // Display the time with seconds
            std::cout << "Current time in your time zone: "
                      << std::setfill('0') << std::setw(2) << localTime->tm_hour << ":"
                      << std::setfill('0') << std::setw(2) << localTime->tm_min << ":"
                      << std::setfill('0') << std::setw(2) << localTime->tm_sec << " s" << std::endl;
        }
        else if (precision == "ms") {
            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
                                    now.time_since_epoch()) % 1000;

            // Display the time with milliseconds
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
            std::cout << "Current time in your time zone: "
                      << std::setfill('0') << std::setw(2) << localTime->tm_hour << ":"
                      << std::setfill('0') << std::setw(2) << localTime->tm_min << ":"
                      << std::setfill('0') << std::setw(2) << localTime->tm_sec << "."
                      << std::setfill('0') << std::setw(9) << nanoseconds.count() << " ns" << std::endl;
        } 
        else {
            std::cout << "Invalid precision entered!" << std::endl;
            break;
        }

        // Wait for a short period before updating (e.g., 10 milliseconds)
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}