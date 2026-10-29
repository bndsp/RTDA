#include "rtda/io/CSVImporter.hpp"
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>

namespace rtda::io {

    struct CSVField {
        std::string text;
        bool quoted = false;
    };

    enum class ColumnType {
        Integer, Decimal, Boolean, Text
    };

    std::vector<CSVField> readCSVRecord(std::istream& file) {
        std::vector<CSVField> fields;
        std::string field;

        bool inQuotes = false;
        bool quoteClosed = false;
        bool hasData = false;
        bool wasQuoted = false;

        char ch;

        while (file.get(ch)) {
            hasData = true;

            if (ch == '"') {
                if (inQuotes && file.peek() == '"') {
                    file.get(ch);
                    field += '"';
                }
                else if (inQuotes) {
                    inQuotes = false;
                    quoteClosed = true;
                }
                else if (field.empty() && !quoteClosed && !wasQuoted) {
                    inQuotes = true;
                    wasQuoted = true;
                }
                else {
                    throw std::runtime_error(
                        "Invalid quotation mark in CSV field."
                    );
                }
            }
            else if (ch == ',' && !inQuotes) {
                fields.push_back(CSVField{field, wasQuoted});
                field.clear();
                quoteClosed = false;
                wasQuoted = false;
            }
            else if ((ch == '\n' || ch == '\r') && !inQuotes) {
                if (ch == '\r' && file.peek() == '\n') {
                    file.get(ch);
                }

                fields.push_back(CSVField{field, wasQuoted});
                return fields;
            }
            else {
                if (quoteClosed) {
                    throw std::runtime_error(
                        "Unexpected character after closing CSV quote."
                    );
                }

                field += ch;
            }
        }

        if (inQuotes) {
            throw std::runtime_error(
                "Unterminated quoted CSV field."
            );
        }

        if (file.bad()) {
            throw std::runtime_error(
                "Error while reading CSV file."
            );
        }

        if (hasData) {
            fields.push_back(CSVField{field, wasQuoted});
        }

        return fields;
    }

    Dataset importCSV(const std::string& path) {
        std::ifstream file(path);

        if (!file.is_open()) {
            throw std::runtime_error(
                "Unable to open CSV file: " + path
            );
        }

        std::vector<CSVField> headers = readCSVRecord(file);

        if (headers.empty()) {
            throw std::runtime_error("CSV file is empty.");
        }

        Dataset dataset(path);

        for (const CSVField& header : headers) {
            dataset.addSignal(Signal(header.text, ""));
        }

        while (true) {
            std::vector<CSVField> fields = readCSVRecord(file);

            if (fields.empty()) {
                break;
            }

            if (fields.size() != headers.size()) {
                throw std::runtime_error(
                    "CSV record has an unexpected number of fields."
                );
            }

            for (std::size_t i = 0; i < fields.size(); i++) {
                Observation observation;

                if (fields[i].text.empty() && !fields[i].quoted) {
                    observation.value = std::monostate{};
                }
                else {
                    observation.value = fields[i].text;
                }

                dataset.getSignal(i).addObs(observation);
            }
        }

        return dataset;
    }
}
