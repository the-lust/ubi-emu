#pragma once

#include "../Core/Common/Types.hpp"
#include <unordered_set>

#ifdef _WIN32
    #ifdef EmuDbData_EXPORTS
        #define EMUDBDATA_API __declspec(dllexport)
    #else
        #define EMUDBDATA_API
    #endif
#else
    #define EMUDBDATA_API
#endif

namespace Uues::EmuDbData {

class EMUDBDATA_API DbDataOwnershipHandler {
public:
    static DbDataOwnershipHandler& GetInstance();

    bool CheckOwnership(int DlcId);
    Uues::Core::Common::ByteArray GetOwnershipList();
    void AddOwnedDlc(int DlcId);
    void SetOwnAll(bool OwnAll);

private:
    DbDataOwnershipHandler() = default;
    DbDataOwnershipHandler(const DbDataOwnershipHandler&) = delete;
    std::unordered_set<int> mOwnedDlcs;
    bool mOwnAll = true;
};

} // namespace Uues::EmuDbData