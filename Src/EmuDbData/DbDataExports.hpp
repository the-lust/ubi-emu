#pragma once

#include "../Core/Common/Macros.hpp"

extern "C" {

UUES_EXPORT int DbDataInit(const char* Config);
UUES_EXPORT int DbDataShutdown();
UUES_EXPORT int DbDataGetErrorCode();

UUES_EXPORT int DbDataSetTicket(const char* Ticket, unsigned int TicketSize);
UUES_EXPORT int DbDataGetTicket(char* Ticket, unsigned int* TicketSize);
UUES_EXPORT int DbDataValidateTicket(const char* Ticket, unsigned int TicketSize);

UUES_EXPORT int DbDataSetToken(const char* TokenType, const char* TokenData, unsigned int TokenSize);
UUES_EXPORT int DbDataGetToken(const char* TokenType, char* TokenData, unsigned int* TokenSize);

UUES_EXPORT int DbDataCheckOwnership(int DlcId, int* OutOwned);
UUES_EXPORT int DbDataGetOwnershipList(char* Buffer, unsigned int* BufferSize);

UUES_EXPORT int DbDataSecureDlcRequest(const char* Request, unsigned int RequestSize, char* Response, unsigned int* ResponseSize);

} // extern "C"