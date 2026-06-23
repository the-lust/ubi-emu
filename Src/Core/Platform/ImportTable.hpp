#pragma once

#include "../Common/Types.hpp"
#include <unordered_map>

namespace Uues::Core::Platform {

struct ImportEntry {
    Common::String ModuleName;
    Common::String FunctionName;
    Dword Ordinal;
    uintptr_t Address;
};

class ImportTable {
public:
    ImportTable();
    ~ImportTable();

    bool Load(void* ModuleHandle);
    bool HasImport(const Common::String& Module, const Common::String& Function) const;
    ImportEntry GetImport(const Common::String& Module, const Common::String& Function) const;
    std::vector<ImportEntry> GetAllImports() const;

private:
    std::vector<ImportEntry> mImports;
};

} // namespace Uues::Core::Platform