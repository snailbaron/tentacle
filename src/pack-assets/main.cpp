#include <cassert>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

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

void writeAssetHeader(
    const fs::path& headerPath, const std::vector<std::string>& fontNames)
{
    auto output = std::ofstream{headerPath};
    output << "#pragma once\n" <<
        "\n" <<
        "namespace assets {\n" <<
        "\n" <<
        "enum class fonts {\n";
    for (const auto& fontName : fontNames) {
        output << "    " << fontName << ",\n";
    }
    output << "};\n" <<
        "\n" <<
        "} // namespace assets\n";
}

int main(int argc, char* argv[])
{
    argo::programName("asset-packer");
    auto sourceAssetPath = argo::option<fs::path>("-s", "--source")
        .required()
        .help("source asset directory");
    auto targetAssetPath = argo::option<fs::path>("-t", "--target")
        .required()
        .help("build asset directory");
    auto assetHeaderPath = argo::option<fs::path>("--header")
        .required()
        .help("path to asset header file to write");
    if (!argo::parse(argc, argv)) {
        return 1;
    }

    auto sourceFontPath = sourceAssetPath / "fonts";
    auto targetFontPath = targetAssetPath / "fonts";
    auto fontNames = convertAsepriteToPng(sourceFontPath, targetFontPath);
    writeAssetHeader(assetHeaderPath, fontNames);
}
