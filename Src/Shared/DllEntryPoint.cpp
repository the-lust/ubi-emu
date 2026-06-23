// DllEntryPoint.cpp stores the HINSTANCE handed to us by DllMain.
// Every DLL needs this so we can load resources from our own module.
//
// TODO: Should we also store the reason for the DLL entry? Might be useful
//       for diagnostics but unlikely needed in practice.

#include "DllEntryPoint.hpp"

namespace Uues::Shared {

HINSTANCE DllEntryPoint::mInstance = nullptr;

HINSTANCE DllEntryPoint::GetInstance() { return mInstance; }
void DllEntryPoint::SetInstance(HINSTANCE Instance) { mInstance = Instance; }

} // namespace Uues::Shared
