#include "ExportTable.hpp"
#include <windows.h>

namespace Uues::Core::Platform {

ExportTable::ExportTable() {}
ExportTable::~ExportTable() = default;

bool ExportTable::Load(void* ModuleHandle) {
    if (!ModuleHandle) { return false; }
    auto DosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(ModuleHandle);
    auto NtHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(
        reinterpret_cast<Byte*>(ModuleHandle) + DosHeader->e_lfanew);
    auto ExportDir = &NtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
    if (!ExportDir->Size) return false;

    auto ExportData = reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(
        reinterpret_cast<Byte*>(ModuleHandle) + ExportDir->VirtualAddress);

    auto Names = reinterpret_cast<Dword*>(
        reinterpret_cast<Byte*>(ModuleHandle) + ExportData->AddressOfNames);
    auto Functions = reinterpret_cast<Dword*>(
        reinterpret_cast<Byte*>(ModuleHandle) + ExportData->AddressOfFunctions);
    auto Ordinals = reinterpret_cast<Word*>(
        reinterpret_cast<Byte*>(ModuleHandle) + ExportData->AddressOfNameOrdinals);

    for (Dword I = 0; I < ExportData->NumberOfNames; ++I) {
        ExportEntry Entry;
        Entry.Name = reinterpret_cast<const char*>(
            reinterpret_cast<Byte*>(ModuleHandle) + Names[I]);
        Entry.Ordinal = ExportData->Base + Ordinals[I];
        // FIXME: AddressOfFunctions entries can be forwarded, need to check for that
        Entry.Address = reinterpret_cast<uintptr_t>(ModuleHandle) + Functions[Ordinals[I]];
        Entry.Size = 0;
        mExports[Entry.Name] = Entry;
        mExportList.push_back(Entry);
    }

    return !mExports.empty();
}

bool ExportTable::Load(const Common::String& ModulePath) {
    auto Handle = LoadLibraryExA(ModulePath.c_str(), nullptr, DONT_RESOLVE_DLL_REFERENCES);
    if (!Handle) return false;
    bool Result = Load(Handle);
    FreeLibrary(Handle);
    return Result;
}

bool ExportTable::HasExport(const Common::String& Name) const {
    return mExports.find(Name) != mExports.end();
}

uintptr_t ExportTable::GetExportAddress(const Common::String& Name) const {
    auto It = mExports.find(Name);
    return (It != mExports.end()) ? It->second.Address : 0;
}

Dword ExportTable::GetExportOrdinal(const Common::String& Name) const {
    auto It = mExports.find(Name);
    return (It != mExports.end()) ? It->second.Ordinal : 0;
}

std::vector<Common::String> ExportTable::GetExportNames() const {
    std::vector<Common::String> Names;
    for (auto& Pair : mExports) Names.push_back(Pair.first);
    return Names;
}

size_t ExportTable::GetExportCount() const { return mExports.size(); }

} // namespace Uues::Core::Platform