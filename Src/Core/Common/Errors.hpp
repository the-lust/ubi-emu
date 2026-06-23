#pragma once

#include <string>
#include <system_error>

namespace Uues::Core::Common {

enum class EmuErrorCode : int {
    Success = 0,
    GeneralFailure = -1,
    FileNotFound = -2,
    InvalidConfig = -3,
    IniParseError = -4,
    SectionNotFound = -5,
    KeyNotFound = -6,
    CryptoError = -7,
    NetworkError = -8,
    PipeError = -9,
    HookError = -10,
    MemoryError = -11,
    InitFailed = -12,
    ExportNotFound = -13,
    TicketInvalid = -14,
    TokenExpired = -15,
    NotSupported = -16,
    AlreadyInitialized = -17,
    NotInitialized = -18,
    BufferTooSmall = -19,
    AccessDenied = -20,
    Timeout = -21,
};

class EmuException : public std::runtime_error {
public:
    explicit EmuException(EmuErrorCode Code, const std::string& Message)
        : std::runtime_error(Message), mCode(Code) {}

    EmuErrorCode GetCode() const { return mCode; }

private:
    EmuErrorCode mCode;
};

} // namespace Uues::Core::Common