#include "FileTarget.hpp"
#include "../Common/TimeUtils.hpp"
#include "../Common/StringUtils.hpp"
#include "../Common/FileUtils.hpp"
#ifdef CreateDirectory
#undef CreateDirectory
#endif

namespace Uues::Core::Log {

// TODO: add max file size option for auto-rotation
FileTarget::FileTarget(const Common::String& FilePath) : mFilePath(FilePath) {}
FileTarget::~FileTarget() { Close(); }

bool FileTarget::Open() {
    auto Dir = Common::FileUtils::GetDirectoryName(mFilePath);
    Common::FileUtils::CreateDirectory(Dir);
    mStream.open(mFilePath, std::ios::out | std::ios::app);
    return mStream.is_open();
}

void FileTarget::Close() {
    if (mStream.is_open()) mStream.close();
}

void FileTarget::Write(LogLevel Level, const Common::String& Message) {
    // FIXME: log file grows unbounded -- need rotation (size limit, count, etc.)
    if (!IsEnabled(Level) || !mStream.is_open()) return;
    auto Timestamp = Common::TimeUtils::GetCurrentDateTimeString();
    mStream << "[" << Timestamp << "] " << Message << std::endl;
}

void FileTarget::Flush() {
    if (mStream.is_open()) mStream.flush();
}

} // namespace Uues::Core::Log