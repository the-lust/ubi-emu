#pragma once

#include "Types.hpp"

namespace Uues::Core::Common {

class FileUtils {
public:
    static bool Exists(const String& Path);
    static bool ReadAllText(const String& Path, String& Out);
    static bool WriteAllText(const String& Path, const String& Content);
    static bool ReadAllBytes(const String& Path, ByteArray& Out);
    static bool WriteAllBytes(const String& Path, const ByteArray& Data);
    static String GetDirectoryName(const String& Path);
    static String GetFileName(const String& Path);
    static String GetExtension(const String& Path);
    static String CombinePath(const String& A, const String& B);
    static bool CreateDirectory(const String& Path);
    static String GetModuleDirectory();

private:
    FileUtils() = delete;
};

} // namespace Uues::Core::Common