#include "Utility.h"
#include <vector> // Required for some validation logic if it were more complex, but not strictly for current.
#include <iostream> // For potential debug, not strictly needed by functions themselves

// Gets the current date in YYYY-MM-DD format
std::string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char dateStr[11];
    strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", ltm);
    return std::string(dateStr);
}

// Input Validation Functions
bool isValidName(const std::string& name) {
    if (name.empty()) return false;
    for (char const &c : name) {
        if (!isalpha(c) && !isspace(c)) {
            return false;
        }
    }
    // Check if the name is not just spaces
    bool nonSpaceFound = false;
    for (char const &c : name) {
        if (!isspace(c)) {
            nonSpaceFound = true;
            break;
        }
    }
    return nonSpaceFound;
}

bool isValidPhoneNumber(const std::string& phone) {
    if (phone.empty()) return false;
    for (char const &c : phone) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool isValidEmail(const std::string& email) {
    if (email.empty()) return false;
    size_t atPos = email.find('@');
    if (atPos == std::string::npos) { // No @ symbol
        return false;
    }
    if (atPos == 0 || atPos == email.length() - 1) { // @ is first or last char
        return false;
    }
    // Basic check for something after @
    size_t dotPos = email.find('.', atPos);
    if (dotPos == std::string::npos || dotPos == atPos + 1 || dotPos == email.length() -1 ) { // No dot after @, or dot is immediately after @ or last char
         return false; // Simplified check, real email validation is complex
    }
    return true;
}
