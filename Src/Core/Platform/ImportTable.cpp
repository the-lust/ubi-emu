#include "ImportTable.hpp"
#include <windows.h>

namespace Uues::Core::Platform {

ImportTable::ImportTable() {}
ImportTable::~ImportTable() = default;

bool ImportTable::Load(void* ModuleHandle) {
    if (!ModuleHandle) {
        return false;  // null handle, nothing to load
    }
    auto DosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(ModuleHandle);
    auto NtHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(
        reinterpret_cast<Byte*>(ModuleHandle) + DosHeader->e_lfanew);
    auto ImportDir = &NtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (!ImportDir->Size) return false;

    auto ImportDesc = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(
        reinterpret_cast<Byte*>(ModuleHandle) + ImportDir->VirtualAddress);

    while (ImportDesc->Name) {
        auto ModuleName = reinterpret_cast<const char*>(
            reinterpret_cast<Byte*>(ModuleHandle) + ImportDesc->Name);
        auto ThunkData = reinterpret_cast<IMAGE_THUNK_DATA*>(
            reinterpret_cast<Byte*>(ModuleHandle) + ImportDesc->FirstThunk);

        while (ThunkData->u1.AddressOfData) {
            ImportEntry Entry;
            Entry.ModuleName = ModuleName;
            if (ThunkData->u1.Ordinal & IMAGE_ORDINAL_FLAG) {
                Entry.Ordinal = IMAGE_ORDINAL(ThunkData->u1.Ordinal);
                Entry.FunctionName = "#" + std::to_string(Entry.Ordinal);
            } else {
                auto ImportByName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(
                    reinterpret_cast<Byte*>(ModuleHandle) + ThunkData->u1.AddressOfData);
                Entry.FunctionName = reinterpret_cast<const char*>(ImportByName->Name);
                Entry.Ordinal = 0;
            }
            Entry.Address = ThunkData->u1.Function;
            mImports.push_back(Entry);
            ++ThunkData;
        }
        ++ImportDesc;
    }

    return !mImports.empty();
}

bool ImportTable::HasImport(const Common::String& Module, const Common::String& Function) const {
    for (auto& Imp : mImports) {
        if (Imp.ModuleName == Module && Imp.FunctionName == Function) return true;
    }
    return false;
}

ImportEntry ImportTable::GetImport(const Common::String& Module, const Common::String& Function) const {
    for (auto& Imp : mImports) {
        if (Imp.ModuleName == Module && Imp.FunctionName == Function) return Imp;
    }
    return {};
}

std::vector<ImportEntry> ImportTable::GetAllImports() const { return mImports; }

} // namespace Uues::Core::Platform