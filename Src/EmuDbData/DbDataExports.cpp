#include "DbDataExports.hpp"
#include "DbDataStateManager.hpp"
#include "DbDataTicketHandler.hpp"
#include "DbDataTokenHandler.hpp"
#include "DbDataOwnershipHandler.hpp"
#include "DbDataSecureDlcHandler.hpp"
#include "../Core/Log/Logger.hpp"
#include <cstring>
#include <algorithm>

extern "C" {

int DbDataInit(const char* Config) {
    Uues::Core::Log::Logger::GetInstance().Info("[DbData] Initializing DbData Emulator");

    if (Config && *Config) {
        // Config could be a JSON or INI string, store it for later
        Uues::EmuDbData::DbDataStateManager::GetInstance().GetConfig().TokenFilePath = Config;
    }

    return 1;
}

int DbDataShutdown() {
    Uues::Core::Log::Logger::GetInstance().Info("[DbData] Shutdown");
    return 1;
}

int DbDataGetErrorCode() {
    return 0;
}

int DbDataSetTicket(const char* Ticket, unsigned int TicketSize) {
    if (!Ticket || TicketSize == 0) {
        Uues::Core::Log::Logger::GetInstance().Warning("[DbDataExports] DbDataSetTicket: null/empty ticket");
        return 0;
    }
    auto TicketBytes = Uues::Core::Common::ByteArray(Ticket, Ticket + TicketSize);
    Uues::EmuDbData::DbDataTicketHandler::GetInstance().SetTicket(TicketBytes);
    return 1;
}

int DbDataGetTicket(char* Ticket, unsigned int* TicketSize) {
    if (!TicketSize) return 0;
    auto TicketBytes = Uues::EmuDbData::DbDataTicketHandler::GetInstance().GetTicket();
    if (Ticket) {
        auto CopySize = std::min(*TicketSize, static_cast<unsigned int>(TicketBytes.size()));
        if (CopySize > 0) std::memcpy(Ticket, TicketBytes.data(), CopySize);
        *TicketSize = CopySize;
    } else {
        *TicketSize = static_cast<unsigned int>(TicketBytes.size());
    }
    return 1;
}

int DbDataValidateTicket(const char* Ticket, unsigned int TicketSize) {
    if (!Ticket || TicketSize == 0) return 0;
    auto TicketBytes = Uues::Core::Common::ByteArray(Ticket, Ticket + TicketSize);
    return Uues::EmuDbData::DbDataTicketHandler::GetInstance().ValidateTicket(TicketBytes) ? 1 : 0;
}

int DbDataSetToken(const char* TokenType, const char* TokenData, unsigned int TokenSize) {
    if (!TokenType || !TokenData || TokenSize == 0) {
        Uues::Core::Log::Logger::GetInstance().Warning("[DbDataExports] DbDataSetToken: invalid params");
        return 0;
    }
    auto TokenBytes = Uues::Core::Common::ByteArray(TokenData, TokenData + TokenSize);
    Uues::EmuDbData::DbDataTokenHandler::GetInstance().SetToken(TokenType, TokenBytes);
    return 1;
}

int DbDataGetToken(const char* TokenType, char* TokenData, unsigned int* TokenSize) {
    if (!TokenType || !TokenSize) return 0;
    auto TokenBytes = Uues::EmuDbData::DbDataTokenHandler::GetInstance().GetToken(TokenType);
    if (TokenData) {
        auto CopySize = std::min(*TokenSize, static_cast<unsigned int>(TokenBytes.size()));
        if (CopySize > 0) std::memcpy(TokenData, TokenBytes.data(), CopySize);
        *TokenSize = CopySize;
    } else {
        *TokenSize = static_cast<unsigned int>(TokenBytes.size());
    }
    return 1;
}

int DbDataCheckOwnership(int DlcId, int* OutOwned) {
    bool Owned = Uues::EmuDbData::DbDataOwnershipHandler::GetInstance().CheckOwnership(DlcId);
    if (OutOwned) *OutOwned = Owned ? 1 : 0;
    return 1;
}

int DbDataGetOwnershipList(char* Buffer, unsigned int* BufferSize) {
    if (!BufferSize) return 0;
    auto List = Uues::EmuDbData::DbDataOwnershipHandler::GetInstance().GetOwnershipList();
    if (Buffer) {
        auto CopySize = std::min(*BufferSize, static_cast<unsigned int>(List.size()));
        if (CopySize > 0) std::memcpy(Buffer, List.data(), CopySize);
        *BufferSize = CopySize;
    } else {
        *BufferSize = static_cast<unsigned int>(List.size());
    }
    return 1;
}

int DbDataSecureDlcRequest(const char* Request, unsigned int RequestSize, char* Response, unsigned int* ResponseSize) {
    if (!Request || RequestSize == 0) {
        Uues::Core::Log::Logger::GetInstance().Warning("[DbDataExports] SecureDlcRequest: empty request");
        return 0;
    }
    auto Req = Uues::Core::Common::ByteArray(Request, Request + RequestSize);
    auto Resp = Uues::EmuDbData::DbDataSecureDlcHandler::GetInstance().HandleRequest(Req);
    if (Response && ResponseSize) {
        auto CopySize = std::min(*ResponseSize, static_cast<unsigned int>(Resp.size()));
        if (CopySize > 0) std::memcpy(Response, Resp.data(), CopySize);
        *ResponseSize = CopySize;
    } else if (ResponseSize) {
        *ResponseSize = static_cast<unsigned int>(Resp.size());
    }
    return 1;
}

} // extern "C"
