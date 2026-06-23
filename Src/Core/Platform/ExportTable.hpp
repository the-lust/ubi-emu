#pragma once

#include "../Common/Types.hpp"
#include <unordered_map>

namespace Uues::Core::Platform {

struct ExportEntry {
    Common::String Name;
    uintptr_t Address;
    Dword Ordinal;
    size_t Size;
};

class ExportTable {
public:
    ExportTable();
    ~ExportTable();

    bool Load(void* ModuleHandle);
    bool Load(const Common::String& ModulePath);
    bool HasExport(const Common::String& Name) const;
    uintptr_t GetExportAddress(const Common::String& Name) const;
    Dword GetExportOrdinal(const Common::String& Name) const;
    std::vector<Common::String> GetExportNames() const;
    size_t GetExportCount() const;

private:
    std::unordered_map<Common::String, ExportEntry> mExports;
    std::vector<ExportEntry> mExportList;
};

} // namespace Uues::Core::Platform