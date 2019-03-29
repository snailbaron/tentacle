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

struct ResourceNames {
    std::vector<std::string> fonts;
};

template <class Print, class... Args>
void write(const fs::path& targetPath, const Print& print, Args&&... args)
{
    fs::create_directory(targetPath.parent_path());
    auto output = std::ofstream{targetPath};
    assert(output.is_open());
    print(output, std::forward<Args>(args)...);
}

void printAssetHeader(
    std::ostream& output, const ResourceNames& resourceNames)
{
    output << "#pragma once\n\n" <<
        "#include <filesystem>\n\n" <<
        "namespace assets {\n\n";

    output << "enum class font {\n";
    for (const auto& fontName : resourceNames.fonts) {
        output << "    " << fontName << ",\n";
    }
    output << "};\n\n";

    output << "std::filesystem::path path(font id);\n\n";

    output << "} // namespace assets\n";
}

void printAssetSource(
    std::ostream& output,
    const fs::path& headerPath,
    const ResourceNames& resourceNames)
{
    output << "#include <" << headerPath.filename().string() << ">\n\n" <<
        "#include <map>\n" <<
        "#include <string>\n\n" <<
        "namespace fs = std::filesystem;\n\n" <<
        "namespace assets {\n\n" <<
        "namespace {\n\n" <<
        "const fs::path AssetPath = \"assets\";\n\n" <<
        "} // namespace\n\n";

    output << "fs::path path(font id)\n" <<
        "{\n" <<
        "   static const std::map<font, std::string> names {\n";
    for (const auto& fontName : resourceNames.fonts) {
        output << "        {font::" << fontName << ", \"" <<
            fontName << ".png\"},\n";
    }
    output << "    };\n\n" <<
        "    return AssetPath / \"fonts\" / names.at(id);\n" <<
        "}\n\n";

    output << "} // namespace assets\n";
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
    auto assetHeaderPath = argo::option<fs::path>("--header")
        .required()
        .help("path to asset header file to write");
    auto assetSourcePath = argo::option<fs::path>("--source")
        .required()
        .help("path to asset source file to write");
    if (!argo::parse(argc, argv)) {
        return 1;
    }

    auto sourceFontPath = sourceAssetPath / "fonts";
    auto targetFontPath = targetAssetPath / "fonts";

    auto resourceNames = ResourceNames{};
    resourceNames.fonts = convertAsepriteToPng(sourceFontPath, targetFontPath);
    write(assetHeaderPath, printAssetHeader, resourceNames);
    write(assetSourcePath, printAssetSource, assetHeaderPath, resourceNames);
}
