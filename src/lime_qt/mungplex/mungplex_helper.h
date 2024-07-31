#pragma once
#include <QString>
#include <span>

class MungPlexHelper {
public:
    MungPlexHelper() = default;
    ~MungPlexHelper() = default;
    void SetGameName(QString& gameName);
    void SetTitleID(u64 titleID);
    void SetVersion(std::string& version);
    void SetRegion(const std::span<const u32>& preferredRegions);
    void SetVRamPtr(u8* vRamPtr);
    void SetVRamSize(const u32 vRamSize);
    void Reset();
    bool WriteHelperFile() const;

private:
    QString _gameName;
    QString _titleID;
    QString _version;
    QString _region;
    QString _vRamPtr;
    QString _vRamSize;
};
