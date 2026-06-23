#pragma once

namespace Uues::EmuUPC {

class UpcProductHandler {
public:
    static int GetProductId();
    static bool SetProductId(int ProductId); // returns false on invalid id
};

} // namespace Uues::EmuUPC