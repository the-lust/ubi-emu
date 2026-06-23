#pragma once

#include "../Common/Types.hpp"
#include <unordered_set>

namespace Uues::Core::Storage {

class DlcManager {
public:
    DlcManager();
    ~DlcManager();

    void AddDlc(const Common::String& DlcId);
    void AddDlcs(const Common::StringList& DlcIds);
    void RemoveDlc(const Common::String& DlcId);
    bool HasDlc(const Common::String& DlcId) const;
    bool IsDlcUnlocked(const Common::String& DlcId) const;
    Common::StringList GetAllDlcs() const;
    void SetUnlockAll(bool UnlockAll);
    bool IsUnlockAll() const;
    size_t GetDlcCount() const;
    void Clear();

private:
    std::unordered_set<Common::String> mDlcs;
    bool mUnlockAll;
};

} // namespace Uues::Core::Storage