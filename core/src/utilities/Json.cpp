#include "utilities/Json.h"
#include <sstream>
#include <fstream>
#include <iostream>

namespace NeuralNet
{
    Json::Json() : value(nullptr) {}
    Json::Json(int intValue) : value(intValue) {}
    Json::Json(double doubleValue) : value(doubleValue) {}
    Json::Json(bool boolValue) : value(boolValue) {}
    Json::Json(const std::string& stringValue) : value(stringValue) {}
    Json::Json(const char* charValue) : value(std::string(charValue)) {}
    Json::Json(std::nullptr_t) : value(nullptr) {}
    Json::Json(std::map<std::string, Json> objValue) : value(objValue) {}
    Json::Json(std::vector<Json> arrValue) : value(arrValue) {}

    // Setters for different JSON value types
    void Json::setNull() { value = nullptr; }
    void Json::setInt(int intValue) { value = intValue; }
    void Json::setDouble(double doubleValue) { value = doubleValue; }
    void Json::setBool(bool boolValue) { value = boolValue; }
    void Json::setString(const std::string& stringValue) { value = stringValue; }
    void Json::setArray(const std::vector<Json>& arrValue) { value = arrValue; }
    void Json::setObject(const std::map<std::string, Json>& objValue) { value = objValue; }

    Json::JsonValue Json::getValue() const { return value; }

    std::string Json::serialize() const 
    {
        std::ostringstream oss;

        std::visit([&](const auto& val) {
            if constexpr (std::is_same_v<std::nullptr_t, decltype(val)>) {
                oss << "null";
            }
            else if constexpr (std::is_same_v<int, decltype(val)>) {
                oss << val;
            }
            else if constexpr (std::is_same_v<double, decltype(val)>) {
                oss << val;
            }
            else if constexpr (std::is_same_v<bool, decltype(val)>) {
                oss << std::boolalpha << val;
            }
            else if constexpr (std::is_same_v<std::string, decltype(val)>) {
                oss << "\"" << val << "\"";
            }
            else if constexpr (std::is_same_v<std::map<std::string, Json>, decltype(val)>) {
                oss << "{";
                bool first = true;
                for (const auto& pair : val) {
                    if (!first) oss << ",";
                    oss << "\"" << pair.first << "\":";
                    oss << pair.second.serialize();
                    first = false;
                }
                oss << "}";
            }
            else if constexpr (std::is_same_v<std::vector<Json>, decltype(val)>) {
                oss << "[";
                bool first = true;
                for (const auto& item : val) {
                    if (!first) oss << ",";
                    oss << item.serialize();
                    first = false;
                }
                oss << "]";
            }
            }, value);

        return oss.str();
    }
    Json Json::deserialize(const std::string& jsonString) {
        std::istringstream iss(jsonString);
        Json result;

        char ch;
        while (iss >> std::noskipws >> ch) {
            switch (ch) {
            case '{': { // Object
                std::map<std::string, Json> obj;
                std::string key;
                bool parsingKey = true;
                bool inString = false;
                std::string valueStr;

                while (iss >> std::noskipws >> ch) {
                    if (ch == '"' && !inString) {
                        inString = true;
                    }
                    else if (ch == '"' && inString) {
                        inString = false;
                        if (parsingKey) {
                            key = valueStr;
                            parsingKey = false;
                        }
                        else {
                            obj[key] = valueStr;
                            parsingKey = true;
                        }
                        valueStr.clear();
                    }
                    else if (ch == ':' && !inString) {
                        // Do nothing, just skip the colon
                    }
                    else if (ch == ',' && !inString) {
                        // Continue parsing the object
                    }
                    else if (ch == '}') {
                        // End of object
                        result.setObject(obj);
                        break;
                    }
                    else {
                        valueStr += ch;
                    }
                }
                break;
            }
            case '[': { // Array
                std::vector<Json> arr;
                bool inString = false;
                std::string valueStr;

                while (iss >> std::noskipws >> ch) {
                    if (ch == '"' && !inString) {
                        inString = true;
                    }
                    else if (ch == '"' && inString) {
                        inString = false;
                        arr.push_back(valueStr);
                        valueStr.clear();
                    }
                    else if (ch == ',' && !inString) {
                        // Continue parsing the array
                    }
                    else if (ch == ']') {
                        // End of array
                        result.setArray(arr);
                        break;
                    }
                    else {
                        valueStr += ch;
                    }
                }
                break;
            }
            case '"': { // String
                std::string str;
                while (iss >> std::noskipws >> ch && ch != '"') {
                    str += ch;
                }
                result.setString(str);
                break;
            }
            case 't': { // true
                if (iss.get() == 'r' && iss.get() == 'u' && iss.get() == 'e') {
                    result.setBool(true);
                }
                break;
            }
            case 'f': { // false
                if (iss.get() == 'a' && iss.get() == 'l' && iss.get() == 's' && iss.get() == 'e') {
                    result.setBool(false);
                }
                break;
            }
            case 'n': { // null
                if (iss.get() == 'u' && iss.get() == 'l' && iss.get() == 'l') {
                    result.setNull();
                }
                break;
            }
            default: { // Number
                std::string numStr;
                numStr += ch;
                while (iss >> std::noskipws >> ch && (isdigit(ch) || ch == '.' || ch == 'e' || ch == 'E' || ch == '+' || ch == '-')) {
                    numStr += ch;
                }

                if (numStr.find('.') != std::string::npos) {
                    double num = std::stod(numStr);
                    result.setDouble(num);
                }
                else {
                    int num = std::stoi(numStr);
                    result.setInt(num);
                }

                iss.unget(); // Unget the last character (not part of the number)
                break;
            }
            }
        }

        return result;
    }

    bool Json::serializeToFile(const std::string& filename) const {
        std::ofstream outputFile(filename);
        if (!outputFile.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
            return false;
        }

        outputFile << serialize();
        outputFile.close();
        return true;
    }
    Json Json::deserializeFromFile(const std::string& filename) {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << " for reading." << std::endl;
            return Json(); // Return an empty Json object if there's an error.
        }

        std::ostringstream oss;
        oss << inputFile.rdbuf();
        inputFile.close();

        return deserialize(oss.str());
    }

}