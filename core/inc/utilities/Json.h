#pragma once

#include "../base/NeuralNet_base.h"


#include <map>
#include <vector>
#include <variant>
#include <iostream>
#include <string>

namespace NeuralNet
{
    class NEURAL_NET_3_EXPORT Json {
    public:
        // Define the possible JSON value types
        using JsonValue = std::variant<std::nullptr_t, int, double, bool, std::string, std::map<std::string, Json>, std::vector<Json>>;

        // Constructors for different JSON value types
        Json();
        Json(int intValue);
        Json(double doubleValue);
        Json(bool boolValue);
        Json(const std::string& stringValue);
        Json(const char* charValue);
        Json(std::nullptr_t);
        Json(std::map<std::string, Json> objValue);
        Json(std::vector<Json> arrValue);

        // Setters for different JSON value types
        void setNull();
        void setInt(int intValue);
        void setDouble(double doubleValue);
        void setBool(bool boolValue);
        void setString(const std::string& stringValue);
        void setArray(const std::vector<Json>& arrValue);
        void setObject(const std::map<std::string, Json>& objValue);

        // Getter for the underlying JSON value
        JsonValue getValue() const ;

        // Helper function to serialize the JSON object to a string
        std::string serialize() const;
        static Json deserialize(const std::string& jsonString);

        bool serializeToFile(const std::string& filename) const;
        static Json deserializeFromFile(const std::string& filename);

    private:
        JsonValue value;
    };
}