#include "UpcConfigReader.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuUPC {
using namespace Uues::Core;

bool UpcConfigReader::ReadConfig(const Ini::IniParser& parser, [[maybe_unused]] Config::EmulatorConfig& cfg) {
    Log::Logger::GetInstance().Info("[UPCConfig] Reading UPC config");

    // FIXME: actually parse values from parser
    // for now we just return defaults
    auto& log = Log::Logger::GetInstance();

    // this is getting out of hand - we need to map ~50 ini keys
    // but games don't even check half of them
    if (parser.HasSection("UPC")) {
        log.Debug("[UPCConfig] Found [UPC] section");
    }

    return true;
}

} // namespace Uues::EmuUPC
