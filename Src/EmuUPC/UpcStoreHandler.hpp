#pragma once

namespace Uues::EmuUPC {

class UpcStoreHandler {
public:
    // FIXME: this doesn't return real store data
    static bool GetItems(char* Buffer, unsigned int BufferSize);
};

} // namespace Uues::EmuUPC