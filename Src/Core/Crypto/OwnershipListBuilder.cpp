#include "OwnershipListBuilder.hpp"
#include "ShaHasher.hpp"
#include "../Common/GuidGenerator.hpp"
#include <algorithm>
#include <sstream>

namespace Uues::Core::Crypto {

OwnershipListBuilder::OwnershipListBuilder() {}

void OwnershipListBuilder::AddDlc(const Common::String& DlcId) {
    if (std::find<Common::StringList::const_iterator, Common::String>(mDlcs.begin(), mDlcs.end(), DlcId) == mDlcs.end()) {
        mDlcs.push_back(DlcId);
    }
}

void OwnershipListBuilder::SetBaseAppId(const Common::String& AppId) { mBaseAppId = AppId; }
void OwnershipListBuilder::SetUserId(const Common::String& UserId) { mUserId = UserId; }
void OwnershipListBuilder::SetTicketToken(const Common::String& Token) { mTicketToken = Token; }

Common::String OwnershipListBuilder::BuildOwnershipToken() {
    std::ostringstream Oss;
    // NOTE: no URL encoding on values, if AppId has '&' this breaks
    Oss << "AppId=" << mBaseAppId << "&"
        << "UserId=" << mUserId << "&"
        << "Dlcs=";
    for (size_t I = 0; I < mDlcs.size(); ++I) {
        if (I > 0) Oss << ",";
        Oss << mDlcs[I];
    }
    Oss << "&Nonce=" << Common::GuidGenerator::CreateString();
    return Oss.str();
}

Common::ByteArray OwnershipListBuilder::BuildSignedOwnershipList() {
    auto TokenStr = BuildOwnershipToken();
    Common::ByteArray Data(TokenStr.begin(), TokenStr.end());
    auto Hash = ShaHasher::Sha256(Data);
    Common::ByteArray Result;
    Result.insert(Result.end(), Data.begin(), Data.end());
    Result.insert(Result.end(), Hash.begin(), Hash.end());
    return Result;
}

bool OwnershipListBuilder::ValidateOwnershipList(const Common::ByteArray& SignedList) {
    if (SignedList.size() < 32) return false;
    auto Data = Common::ByteArray(SignedList.begin(), SignedList.end() - 32);
    auto ExpectedHash = Common::ByteArray(SignedList.end() - 32, SignedList.end());
    auto ActualHash = ShaHasher::Sha256(Data);
    return ExpectedHash == ActualHash;
}

} // namespace Uues::Core::Crypto