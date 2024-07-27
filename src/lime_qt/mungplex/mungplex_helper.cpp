#include "mungplex_helper.h"
#include "core/loader/smdh.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <shlobj_core.h>
#include <Windows.h>

void MungPlexHelper::SetGameName(QString& gameName)
{
    static const QString target = QString::fromStdString("\n");
    static const QString replacement = QString::fromStdString(": ");
    _gameName = gameName;
    _gameName.replace(target, replacement);
}

void MungPlexHelper::SetTitleID(u64 titleID)
{
    _titleID.setNum(titleID, 16);
}

void MungPlexHelper::SetVersion(std::string& version)
{
    _version = QString::fromStdString(version);
}

void MungPlexHelper::SetRegion(const std::span<const u32>& preferredRegions)
{
    _region.clear();

    for (u32 region : preferredRegions)
    {
        QString regionCode;

        switch (region)
        {
        case (u32)Loader::SMDH::GameRegion::Japan:
            regionCode = QString::fromStdString("JPN");
        break;
        case (u32)Loader::SMDH::GameRegion::NorthAmerica:
            regionCode = QString::fromStdString("USA");
        break;
        case (u32)Loader::SMDH::GameRegion::Europe:
            regionCode = QString::fromStdString("EUR");
        break;
        case (u32)Loader::SMDH::GameRegion::Australia:
            regionCode = QString::fromStdString("AUS");
        break;
        case (u32)Loader::SMDH::GameRegion::China:
            regionCode = QString::fromStdString("CHN");
        break;
        case (u32)Loader::SMDH::GameRegion::Korea:
            regionCode = QString::fromStdString("KOR");
        break;
        case (u32)Loader::SMDH::GameRegion::Taiwan:
            regionCode = QString::fromStdString("TWN");
        break;
        default:
            regionCode = QString::fromStdString("UNK");
        }

        if (!_region.isEmpty())
            _region.append(QString::fromStdString("/"));

        _region.append(regionCode);
    }
}

void MungPlexHelper::Reset()
{
    _gameName.clear();
    _titleID.clear();
    _version.clear();
    _region.clear();
}

bool MungPlexHelper::WriteHelperFile()
{
    auto tmp = new wchar_t[512];
    SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &tmp);
    QString path = QString::fromStdWString(tmp);
    path.append(QString::fromStdString("\\MungPlex\\CurrentGame.txt"));

    QFileInfo fileInfo(path);
    QDir dir = fileInfo.dir();

    if (!dir.exists())
        if (!dir.mkpath(path))
            return false;

    QFile file(path);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return false;

    QTextStream out(&file);
    out.setEncoding(QStringEncoder::Utf8);
    out << _gameName << '\n' << _titleID << '\n' << _region << '\n' << _version;
    file.close();
    return true;
}
