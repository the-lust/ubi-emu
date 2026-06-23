#include "FileUtils.hpp"
#include <fstream>
#include <filesystem>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

namespace fs = std::filesystem;

namespace Uues::Core::Common {

bool FileUtils::Exists(const String& Path) {
    return fs::exists(Path);
}

bool FileUtils::ReadAllText(const String& Path, String& Out) {
    try {
        std::ifstream Stream(Path, std::ios::in | std::ios::binary);
        if (!Stream.is_open()) return false;
        Stream.seekg(0, std::ios::end);
        size_t Size = static_cast<size_t>(Stream.tellg());
        Stream.seekg(0);
        Out.resize(Size);
        Stream.read(Out.data(), Size);
        // Remove BOM if present (UTF-8 BOM: EF BB BF)
        if (Out.size() >= 3 &&
            static_cast<unsigned char>(Out[0]) == 0xEF &&
            static_cast<unsigned char>(Out[1]) == 0xBB &&
            static_cast<unsigned char>(Out[2]) == 0xBF) {
            Out = Out.substr(3);
        }
        // TODO: handle UTF-16 LE/BE BOM (FF FE / FE FF)
        return true;
    } catch (...) {
        return false;
    }
}

bool FileUtils::WriteAllText(const String& Path, const String& Content) {
    try {
        std::ofstream Stream(Path, std::ios::out | std::ios::binary);
        if (!Stream.is_open()) return false;
        Stream.write(Content.data(), Content.size());
        return true;
    } catch (...) {
        return false;
    }
}

bool FileUtils::ReadAllBytes(const String& Path, ByteArray& Out) {
    try {
        std::ifstream Stream(Path, std::ios::in | std::ios::binary);
        if (!Stream.is_open()) return false;
        Stream.seekg(0, std::ios::end);
        size_t Size = static_cast<size_t>(Stream.tellg());
        Stream.seekg(0);
        Out.resize(Size);
        Stream.read(reinterpret_cast<char*>(Out.data()), Size);
        return true;
    } catch (...) {
        return false;
    }
}

bool FileUtils::WriteAllBytes(const String& Path, const ByteArray& Data) {
    try {
        std::ofstream Stream(Path, std::ios::out | std::ios::binary);
        if (!Stream.is_open()) return false;
        Stream.write(reinterpret_cast<const char*>(Data.data()), Data.size());
        return true;
    } catch (...) {
        return false;
    }
}

String FileUtils::GetDirectoryName(const String& Path) {
    fs::path P(Path);
    return P.parent_path().string();
}

String FileUtils::GetFileName(const String& Path) {
    fs::path P(Path);
    return P.filename().string();
}

String FileUtils::GetExtension(const String& Path) {
    fs::path P(Path);
    return P.extension().string();
}

String FileUtils::CombinePath(const String& A, const String& B) {
    fs::path P1(A);
    fs::path P2(B);
    return (P1 / P2).string();
}

bool FileUtils::CreateDirectory(const String& Path) {
    try {
        return fs::create_directories(Path);
    } catch (...) {
        return false;  // FIXME: silently fails, no way to know why
    }
}

String FileUtils::GetModuleDirectory() {
#ifdef _WIN32
    wchar_t Path[MAX_PATH];
    GetModuleFileNameW(nullptr, Path, MAX_PATH);
    fs::path P(Path);
    return P.parent_path().string();
#else
    return ".";
#endif
}

} // namespace Uues::Core::Common