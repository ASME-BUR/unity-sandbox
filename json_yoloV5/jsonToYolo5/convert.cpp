#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "json.hpp"  // Instead of <nlohmann/json.hpp>
using json = nlohmann::json;

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING;
#include <experimental/filesystem>



using json = nlohmann::json;
namespace fs = std::experimental::filesystem;

// Function to process a single JSON file and convert it to YOLO format
void processJsonFile(const std::string& filePath, const std::string& outputDir) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filePath << "\n";
        return;
    }

    json jsonData;
    file >> jsonData;
    file.close();

    // Extract image dimensions
    float imgWidth = jsonData["captures"][0]["dimension"][0];
    float imgHeight = jsonData["captures"][0]["dimension"][1];

    // Construct output file path
    std::string outputFilename = outputDir + "/" + fs::path(filePath).stem().string() + ".txt";
    std::ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to create file " << outputFilename << "\n";
        return;
    }

    // Process bounding box annotations
    for (const auto& capture : jsonData["captures"]) {
        for (const auto& annotation : capture["annotations"]) {
            if (annotation["@type"] == "type.unity.com/unity.solo.BoundingBox2DAnnotation") {
                for (const auto& bbox : annotation["values"]) {
                    int classId = bbox["label_id"]; // Assuming "label_id" exists
                    float x = bbox["x"] + bbox["width"] / 2.0;  // Center X
                    float y = bbox["y"] + bbox["height"] / 2.0; // Center Y
                    float w = bbox["width"];
                    float h = bbox["height"];

                    // Normalize values (YOLO format requires values between 0 and 1)
                    x /= imgWidth;
                    y /= imgHeight;
                    w /= imgWidth;
                    h /= imgHeight;

                    // Write to file in YOLO format
                    outputFile << classId << " " << x << " " << y << " " << w << " " << h << "\n";
                }
            }
        }
    }

    outputFile.close();
    std::cout << "Processed: " << filePath << " -> " << outputFilename << "\n";
}

// Main function to process all JSON files in a directory
int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_directory> <output_directory>\n";
        return 1;
    }

    std::string inputDir = argv[1];
    std::string outputDir = argv[2];

    // Create output directory if it doesn't exist
    if (!fs::exists(outputDir)) {
        fs::create_directories(outputDir);
    }

    // Iterate through all JSON files in the input directory
    for (const auto& entry : fs::directory_iterator(inputDir)) {
        if (entry.path().extension() == ".json") {
            processJsonFile(entry.path().string(), outputDir);
        }
    }

    std::cout << "Processing complete. YOLO annotations saved in " << outputDir << "\n";
    return 0;
}
