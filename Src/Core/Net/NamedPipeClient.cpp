#include "NamedPipeClient.hpp"
#include <windows.h>
#include <memory>

namespace Uues::Core::Net {

class NamedPipeClient::Impl {
public:
    HANDLE PipeHandle = INVALID_HANDLE_VALUE;
};

NamedPipeClient::NamedPipeClient() : mImpl(std::make_unique<Impl>()) {}
NamedPipeClient::~NamedPipeClient() { Disconnect(); }

bool NamedPipeClient::Connect(const Common::String& PipeName, [[maybe_unused]] int TimeoutMs) {
    Common::String FullPath = "\\\\.\\pipe\\" + PipeName;
    // TODO: TimeoutMs is ignored, could use WaitNamedPipe for that
    mImpl->PipeHandle = CreateFileA(
        FullPath.c_str(), GENERIC_READ | GENERIC_WRITE,
        0, nullptr, OPEN_EXISTING, 0, nullptr);
    return mImpl->PipeHandle != INVALID_HANDLE_VALUE;
}

bool NamedPipeClient::Disconnect() {
    if (mImpl->PipeHandle != INVALID_HANDLE_VALUE) {
        CloseHandle(mImpl->PipeHandle);
        mImpl->PipeHandle = INVALID_HANDLE_VALUE;
    }
    return true;
}

bool NamedPipeClient::Send(const Common::ByteArray& Data) {
    if (mImpl->PipeHandle == INVALID_HANDLE_VALUE) return false;
    Dword BytesWritten;
    return WriteFile(mImpl->PipeHandle, Data.data(), static_cast<Dword>(Data.size()),
                     reinterpret_cast<LPDWORD>(&BytesWritten), nullptr) && BytesWritten == Data.size();
}

bool NamedPipeClient::Receive(Common::ByteArray& OutData, size_t MaxSize) {
    if (mImpl->PipeHandle == INVALID_HANDLE_VALUE) return false;
    OutData.resize(MaxSize);
    Dword BytesRead;
    if (!ReadFile(mImpl->PipeHandle, OutData.data(), static_cast<Dword>(MaxSize),
                  reinterpret_cast<LPDWORD>(&BytesRead), nullptr)) {
        OutData.clear();
        return false;
    }
    OutData.resize(BytesRead);
    return true;
}

bool NamedPipeClient::IsConnected() const {
    return mImpl->PipeHandle != INVALID_HANDLE_VALUE;
}

} // namespace Uues::Core::Net