#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

class Settings
{
private:
    static QString _defaultPath;

public:
    static void WriteSettings();
    static void ReadSettings();
    static void SetPath(QString path);
    static QString GetPath();
};

#endif // SETTINGS_H
