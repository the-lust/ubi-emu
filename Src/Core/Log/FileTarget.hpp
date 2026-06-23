#pragma once

#include "LogTarget.hpp"
#include <fstream>

namespace Uues::Core::Log {

class FileTarget : public LogTarget {
public:
    explicit FileTarget(const Common::String& FilePath);
    ~FileTarget() override;

    void Write(LogLevel Level, const Common::String& Message) override;
    void Flush() override;
    bool Open();
    void Close();

private:
    Common::String mFilePath;
    std::ofstream mStream;
};

} // namespace Uues::Core::Log