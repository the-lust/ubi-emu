#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Storage {

class SaveManager {
public:
    SaveManager();
    ~SaveManager();

    static SaveManager& GetInstance();

    bool Initialize(const Common::String& SaveDirectory, int SaveType);
    Common::String ResolveSavePath(const Common::String& RelativePath) const;
    bool SaveFile(const Common::String& FileName, const Common::ByteArray& Data);
    bool LoadFile(const Common::String& FileName, Common::ByteArray& OutData);
    bool FileExists(const Common::String& FileName) const;
    bool DeleteFile(const Common::String& FileName);
    Common::String GetSaveDirectory() const;

    enum SaveType {
        AppData,
        GameFolder,
        Custom
    };

private:
    Common::String mSaveDirectory;
    int mSaveType;
};

} // namespace Uues::Core::Storage