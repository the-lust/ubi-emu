#include "ExportValidator.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::Tools {
using namespace Uues::Core;

// TODO: actually implement PE/ELF export table parsing
// For now we just log and assume everything is fine.

bool ExportValidator::ValidateModule(const Common::String& ModulePath, const Common::String& EmulatorType) {
    if (ModulePath.empty()) {
        Log::Logger::GetInstance().Error("[ExportValidator] Empty module path");
        return false;
    }
    Log::Logger::GetInstance().Warning("[ExportValidator] Stub — module validation not yet implemented for '" +
        ModulePath + "' (type=" + EmulatorType + "), assuming valid");
    return true;
}

bool ExportValidator::CheckExportPresent(const Common::String& ModulePath, const Common::String& ExportName) {
    if (ModulePath.empty() || ExportName.empty()) {
        Log::Logger::GetInstance().Error("[ExportValidator] Empty path or export name");
        return false;
    }
    Log::Logger::GetInstance().Warning("[ExportValidator] Stub — export check not implemented for '" +
        ExportName + "' in '" + ModulePath + "', assuming present");
    return true;
}

} // namespace Uues::Tools
