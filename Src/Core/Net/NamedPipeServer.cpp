#include "NamedPipeServer.hpp"
#include <windows.h>
#include <memory>

namespace Uues::Core::Net {

class NamedPipeServer::Impl {
public:
    HANDLE PipeHandle = INVALID_HANDLE_VALUE;
};

NamedPipeServer::NamedPipeServer() : mImpl(std::make_unique<Impl>()) {}
NamedPipeServer::~NamedPipeServer() { Close(); }

bool NamedPipeServer::Create(const Common::String& PipeName) {
    Common::String FullPath = "\\\\.\\pipe\\" + PipeName;
    // FIXME: buffer sizes hardcoded to 4096, should be configurable
    mImpl->PipeHandle = CreateNamedPipeA(
        FullPath.c_str(), PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES, 4096, 4096, 0, nullptr);
    return mImpl->PipeHandle != INVALID_HANDLE_VALUE;
}

bool NamedPipeServer::WaitForClient() {
    if (mImpl->PipeHandle == INVALID_HANDLE_VALUE) return false;
    return ConnectNamedPipe(mImpl->PipeHandle, nullptr) || GetLastError() == ERROR_PIPE_CONNECTED;
}

bool NamedPipeServer::Send(const Common::ByteArray& Data) {
    if (mImpl->PipeHandle == INVALID_HANDLE_VALUE) return false;
    Dword BytesWritten;
    return WriteFile(mImpl->PipeHandle, Data.data(), static_cast<Dword>(Data.size()),
                     &BytesWritten, nullptr);
}

bool NamedPipeServer::Receive(Common::ByteArray& OutData, size_t MaxSize) {
    if (mImpl->PipeHandle == INVALID_HANDLE_VALUE) return false;
    OutData.resize(MaxSize);
    Dword BytesRead;
    if (!ReadFile(mImpl->PipeHandle, OutData.data(), static_cast<Dword>(MaxSize),
                  &BytesRead, nullptr)) {
        OutData.clear();
        return false;
    }
    OutData.resize(BytesRead);
    return true;
}

void NamedPipeServer::Close() {
    if (mImpl->PipeHandle != INVALID_HANDLE_VALUE) {
        DisconnectNamedPipe(mImpl->PipeHandle);
        CloseHandle(mImpl->PipeHandle);
        mImpl->PipeHandle = INVALID_HANDLE_VALUE;
    }
}

} // namespace Uues::Core::Net