#include "DlcManager.hpp"

namespace Uues::Core::Storage {

DlcManager::DlcManager() : mUnlockAll(true) {}
DlcManager::~DlcManager() = default;

void DlcManager::AddDlc(const Common::String& DlcId) { mDlcs.insert(DlcId); }
void DlcManager::AddDlcs(const Common::StringList& DlcIds) {
    for (auto& Id : DlcIds) mDlcs.insert(Id);
}
void DlcManager::RemoveDlc(const Common::String& DlcId) { mDlcs.erase(DlcId); }
bool DlcManager::HasDlc(const Common::String& DlcId) const {
    // TODO: should we also check case-insensitively? DLC IDs are usually uppercase
    return mDlcs.find(DlcId) != mDlcs.end();
}
bool DlcManager::IsDlcUnlocked(const Common::String& DlcId) const { return mUnlockAll || HasDlc(DlcId); }
Common::StringList DlcManager::GetAllDlcs() const { return Common::StringList(mDlcs.begin(), mDlcs.end()); }
void DlcManager::SetUnlockAll(bool UnlockAll) { mUnlockAll = UnlockAll; }
bool DlcManager::IsUnlockAll() const { return mUnlockAll; }
size_t DlcManager::GetDlcCount() const { return mDlcs.size(); }
void DlcManager::Clear() { mDlcs.clear(); }

} // namespace Uues::Core::Storage