#include "TicketGenerator.hpp"
#include "ShaHasher.hpp"
#include "RsaSigner.hpp"
#include "../Common/TimeUtils.hpp"
#include "../Common/GuidGenerator.hpp"
#include <sstream>

namespace Uues::Core::Crypto {

class TicketGenerator::Impl {
public:
    RsaSigner Signer;
    int ExpirationMinutes = 30;

    Common::ByteArray BuildTicketPayload(const Common::String& AppId, const Common::String& UserId) {
        auto Timestamp = Common::TimeUtils::GetCurrentTimestamp();
        auto Expiry = Timestamp + (ExpirationMinutes * 60);
        auto Nonce = Common::GuidGenerator::CreateString();

        std::ostringstream Oss;
        Oss << "AppId=" << AppId << "&"
            << "UserId=" << UserId << "&"
            << "Nonce=" << Nonce << "&"
            << "Issued=" << Timestamp << "&"
            << "Expires=" << Expiry;
        auto Payload = Oss.str();
        return Common::ByteArray(Payload.begin(), Payload.end());
    }

    Common::ByteArray SignPayload(const Common::ByteArray& Payload) {
        auto Hash = ShaHasher::Sha256(Payload);
        return Signer.Sign(Hash);
    }
};

TicketGenerator::TicketGenerator() : mImpl(std::make_unique<Impl>()) {}
TicketGenerator::~TicketGenerator() = default;

bool TicketGenerator::GenerateTicket(const Common::String& AppId, const Common::String& UserId,
                                      Common::ByteArray& OutTicket) {
    auto Payload = mImpl->BuildTicketPayload(AppId, UserId);
    auto Signature = mImpl->SignPayload(Payload);
    OutTicket.clear();
    OutTicket.insert(OutTicket.end(), Payload.begin(), Payload.end());
    OutTicket.insert(OutTicket.end(), Signature.begin(), Signature.end());
    return true;
}

bool TicketGenerator::ParseTicket(const Common::ByteArray& Ticket,
                                   Common::String& OutAppId, Common::String& OutUserId) {
    if (Ticket.size() < 64) {
        return false;  // too small to contain payload + signature
    }
    auto PayloadStr = Common::String(Ticket.begin(), Ticket.end() - 64);
    // HACK: this is a very naive parser, will break if values contain '&' or '='
    auto AppIdPos = PayloadStr.find("AppId=");
    auto UserIdPos = PayloadStr.find("UserId=");
    if (AppIdPos == Common::String::npos || UserIdPos == Common::String::npos) return false;
    auto AppIdEnd = PayloadStr.find('&', AppIdPos);
    auto UserIdEnd = PayloadStr.find('&', UserIdPos);
    OutAppId = PayloadStr.substr(AppIdPos + 6, AppIdEnd - AppIdPos - 6);
    OutUserId = PayloadStr.substr(UserIdPos + 7, UserIdEnd - UserIdPos - 7);
    return true;
}

bool TicketGenerator::ValidateTicket(const Common::ByteArray& Ticket) {
    auto Payload = Common::ByteArray(Ticket.begin(), Ticket.end() - 64);
    auto Signature = Common::ByteArray(Ticket.end() - 64, Ticket.end());
    auto Hash = ShaHasher::Sha256(Payload);
    return mImpl->Signer.Verify(Hash, Signature);
}

bool TicketGenerator::SetRsaKey(const Common::ByteArray& KeyBlob) {
    return mImpl->Signer.ImportPublicKey(KeyBlob);
}

void TicketGenerator::SetExpirationMinutes(int Minutes) {
    mImpl->ExpirationMinutes = Minutes;
}

} // namespace Uues::Core::Crypto