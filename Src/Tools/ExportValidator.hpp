#pragma once

#include "../Core/Common/Types.hpp"

namespace Uues::Tools {

class ExportValidator {
public:
    static bool ValidateModule(const Core::Common::String& ModulePath, const Core::Common::String& EmulatorType);
    static bool CheckExportPresent(const Core::Common::String& ModulePath, const Core::Common::String& ExportName);
};

} // namespace Uues::Tools