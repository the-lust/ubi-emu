#include "SaveManager.hpp"
#include "../Common/FileUtils.hpp"
#include "../Common/Platform/WindowsPlatform.hpp"

namespace Uues::Core::Storage {

SaveManager::SaveManager() {}
SaveManager::~SaveManager() = default;

bool SaveManager::Initialize(const Common::String& SaveDirectory, int SaveType) {
    // TODO: support per-user save directories with UserId subfolder
    mSaveDirectory = SaveDirectory;
    mSaveType = SaveType;

    switch (mSaveType) {
        case SaveType::AppData: {
            auto AppData = Platform::WindowsPlatform::GetApplicationDataPath();
            mSaveDirectory = Common::FileUtils::CombinePath(AppData, "UUES");
            break;
        }
        case SaveType::GameFolder: {
            mSaveDirectory = Common::FileUtils::GetModuleDirectory();
            break;
        }
        case SaveType::Custom:
        default:
            break;
    }

    return Common::FileUtils::CreateDirectory(mSaveDirectory);
}

Common::String SaveManager::ResolveSavePath(const Common::String& RelativePath) const {
    return Common::FileUtils::CombinePath(mSaveDirectory, RelativePath);
}

bool SaveManager::SaveFile(const Common::String& FileName, const Common::ByteArray& Data) {
    auto FullPath = ResolveSavePath(FileName);
    return Common::FileUtils::WriteAllBytes(FullPath, Data);
}

bool SaveManager::LoadFile(const Common::String& FileName, Common::ByteArray& OutData) {
    auto FullPath = ResolveSavePath(FileName);
    return Common::FileUtils::ReadAllBytes(FullPath, OutData);
}

bool SaveManager::FileExists(const Common::String& FileName) const {
    auto FullPath = ResolveSavePath(FileName);
    return Common::FileUtils::Exists(FullPath);
}

bool SaveManager::DeleteFile(const Common::String& FileName) {
    auto FullPath = ResolveSavePath(FileName);
    return std::filesystem::remove(FullPath);
}

Common::String SaveManager::GetSaveDirectory() const { return mSaveDirectory; }

} // namespace Uues::Core::Storage