#pragma once

#include "../Core/Common/Types.hpp"
#include <unordered_set>

namespace Uues::EmuDbData {

class DbDataOwnershipHandler {
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