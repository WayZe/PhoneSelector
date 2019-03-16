#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QSettings>

class Settings
{
private:
    QString _defaultPath;

public:
    void WriteSettings();
    void ReadSettings();
    void SetPath(QString path);
    QString GetPath();
};

#endif // SETTINGS_H
