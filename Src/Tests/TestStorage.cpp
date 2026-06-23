#include "../Core/Storage/SaveManager.hpp"
#include "../Core/Storage/DlcManager.hpp"
#include "../Core/Log/Logger.hpp"
#include <cstdio>

namespace Uues::Tests {

bool RunStorageTests() {
    Log::Logger::GetInstance().Info("[StorageTests] Starting");

    int Failed = 0;

    // SaveManager: init and resolve path
    {
        Core::Storage::SaveManager SMgr;
        bool InitOk = SMgr.Initialize("./test_saves", Core::Storage::SaveManager::AppData);
        if (!InitOk) { Failed++; Log::Logger::GetInstance().Warning("[StorageTests] SaveManager init failed"); }
    }

    // DlcManager: add / check / remove
    {
        Core::Storage::DlcManager DMgr;
        DMgr.AddDlc("12345");
        DMgr.AddDlc("67890");
        if (!DMgr.HasDlc("12345")) { Failed++; }
        if (!DMgr.HasDlc("67890")) { Failed++; }
        if (DMgr.HasDlc("99999")) { Failed++; }
        if (DMgr.GetDlcCount() != 2) { Failed++; }

        DMgr.RemoveDlc("12345");
        if (DMgr.HasDlc("12345")) { Failed++; }
        if (DMgr.GetDlcCount() != 1) { Failed++; }

        DMgr.Clear();
        if (DMgr.GetDlcCount() != 0) { Failed++; }
    }

    // DlcManager: unlock all
    {
        Core::Storage::DlcManager DMgr;
        DMgr.SetUnlockAll(true);
        if (!DMgr.IsDlcUnlocked("anything")) { Failed++; }
    }

    printf("[Storage] Tests done: %s\n", Failed == 0 ? "PASS" : "FAIL");
    return Failed == 0;
}

} // namespace Uues::Tests