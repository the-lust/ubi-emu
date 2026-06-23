#include "MemoryScanner.hpp"
#include <windows.h>
#include <algorithm>

namespace Uues::Core::Memory {

MemoryScanner::MemoryScanner() {}
MemoryScanner::~MemoryScanner() = default;

void MemoryScanner::SetSkipExecutable(bool Skip) { mSkipExecutable = Skip; }

std::vector<std::pair<uintptr_t, size_t>> MemoryScanner::GetMemoryRegions() {
    std::vector<std::pair<uintptr_t, size_t>> Regions;
    uintptr_t Address = 0;
    MEMORY_BASIC_INFORMATION Mbi;

    while (VirtualQuery(reinterpret_cast<void*>(Address), &Mbi, sizeof(Mbi)) == sizeof(Mbi)) {
        if (Mbi.State == MEM_COMMIT && Mbi.Protect != PAGE_NOACCESS) {
            if (!mSkipExecutable || (Mbi.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ |
                PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY))) {
                Regions.emplace_back(Address, Mbi.RegionSize);
            }
        }
        Address += Mbi.RegionSize;
    }

    return Regions;
}

uintptr_t MemoryScanner::FindPattern(const Common::ByteArray& Pattern, const Common::String& Mask,
                                      uintptr_t Start, size_t Size) {
    auto Bytes = reinterpret_cast<Byte*>(Start);
    for (size_t i = 0; i < Size - Pattern.size(); ++i) {
        bool Found = true;
        for (size_t j = 0; j < Pattern.size(); ++j) {
            if (Mask.empty() || Mask[j] == 'x') {
                if (Bytes[i + j] != Pattern[j]) { Found = false; break; }
            } else if (Mask[j] != '?' && Mask[j] != '.') {
                if (Bytes[i + j] != Pattern[j]) { Found = false; break; }
            }
        }
        if (Found) return Start + i;
    }
    // TODO: add support for wildcard masks like "xx?x?x" pattern
    return 0;
}

bool MemoryScanner::Scan(const Common::ByteArray& Pattern, const Common::String& Mask,
                          std::vector<uintptr_t>& OutResults) {
    OutResults.clear();
    auto Regions = GetMemoryRegions();
    for (auto& Region : Regions) {
        auto Result = FindPattern(Pattern, Mask, Region.first, Region.second);
        if (Result) OutResults.push_back(Result);
    }
    return !OutResults.empty();
}

bool MemoryScanner::ScanModule(const Common::String& ModuleName, const Common::ByteArray& Pattern,
                                const Common::String& Mask, std::vector<uintptr_t>& OutResults) {
    OutResults.clear();
    auto Module = GetModuleHandleA(ModuleName.c_str());
    if (!Module) return false;

    auto DosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(Module);
    auto NtHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(
        reinterpret_cast<Byte*>(Module) + DosHeader->e_lfanew);
    auto Size = NtHeaders->OptionalHeader.SizeOfImage;

    auto Result = FindPattern(Pattern, Mask, reinterpret_cast<uintptr_t>(Module), Size);
    if (Result) OutResults.push_back(Result);
    return !OutResults.empty();
}

} // namespace Uues::Core::Memory