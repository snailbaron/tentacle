#include <cassert>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <ecosnail/argo.hpp>

namespace fs = std::filesystem;
namespace argo = ecosnail::argo;

void saveAsepriteAs(
    const fs::path& asepriteSource, const fs::path& target)
{
    std::ostringstream command;
    command <<
        "aseprite" <<
        " --batch" <<
        " " << asepriteSource <<
        " --save-as " << target;
    std::system(command.str().c_str());
}

std::vector<std::string> convertAsepriteToPng(
    const fs::path& sourceDirectory, const fs::path& targetDirectory)
{
    std::vector<std::string> fileNames;

    for (const auto& entry : fs::directory_iterator(sourceDirectory)) {
        if (entry.path().extension() != ".aseprite") {
            continue;
        }

        auto sourcePath = entry.path();
        auto fileName = sourcePath.filename();
        auto stem = sourcePath.stem();

        auto targetPath = targetDirectory / fileName;
        targetPath.replace_extension(".png");

        saveAsepriteAs(sourcePath, targetPath);

        fileNames.push_back(stem);
    }

    return fileNames;
}

int main(int argc, char* argv[])
{
    argo::programName("asset-packer");
    auto sourceAssetPath = argo::option<fs::path>("-s", "--source-assets")
        .required()
        .help("source asset directory");
    auto targetAssetPath = argo::option<fs::path>("-t", "--target-assets")
        .required()
        .help("build asset directory");
    auto outputPath = argo::option<fs::path>("-o", "--output")
        .required()
        .help("path to output resource description file");
    if (!argo::parse(argc, argv)) {
        return 1;
    }

    auto sourceFontPath = sourceAssetPath / "fonts";
    auto targetFontPath = targetAssetPath / "fonts";

    std::ofstream output(*outputPath);
    output.exceptions(std::ofstream::badbit | std::ofstream::failbit);

    auto fontNames = convertAsepriteToPng(sourceFontPath, targetFontPath);
    for (const auto& fontName : fontNames) {
        output << "FONT(" << fontName << ")\n";
    }
}
