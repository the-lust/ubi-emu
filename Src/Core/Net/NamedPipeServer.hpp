#pragma once

#include "../Common/Types.hpp"
#include <functional>

namespace Uues::Core::Net {

class NamedPipeServer {
public:
    using PipeHandler = std::function<void(const Common::ByteArray& Request, Common::ByteArray& Response)>;

    NamedPipeServer();
    ~NamedPipeServer();

    bool Create(const Common::String& PipeName);
    bool WaitForClient();
    bool Send(const Common::ByteArray& Data);
    bool Receive(Common::ByteArray& OutData, size_t MaxSize = 4096);
    void Close();

private:
    class Impl;
    std::unique_ptr<Impl> mImpl;
};

} // namespace Uues::Core::Net