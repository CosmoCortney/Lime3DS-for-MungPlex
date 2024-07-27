#pragma once
#include <QString>
#include <span>

class MungPlexHelper {
public:
    static void SetGameName(QString& gameName);
    static void SetTitleID(u64 titleID);
    static void SetVersion(std::string& version);
    static void SetRegion(const std::span<const u32>& preferredRegions);
    static void Reset();
    static bool WriteHelperFile();

private:
    MungPlexHelper();
    ~MungPlexHelper(){};
    MungPlexHelper(const MungPlexHelper&) = delete;
    MungPlexHelper(MungPlexHelper&&) = delete;
    void operator=(const MungPlexHelper&) = delete;
    void operator=(MungPlexHelper&&) = delete;
    static MungPlexHelper& GetInstance() {
        static MungPlexHelper Instance;
        return Instance;
    }

    static inline QString _gameName;
    static inline QString _titleID;
    static inline QString _version;
    static inline QString _region;
};
