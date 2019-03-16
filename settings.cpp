#include "settings.h"
#include <QSettings>

void Settings::WriteSettings()
{
    QSettings settings(QSettings::UserScope, "MAI", "Selector");

    settings.beginGroup("Settings");

    settings.setValue("path", GetPath());

    settings.endGroup();

    settings.sync();
}

void Settings::ReadSettings()
{
    QSettings settings(QSettings::UserScope, "MAI", "Selector");

    settings.beginGroup("Settings");

    QString configFilePathFromSave = settings.value("path").toString();

    settings.endGroup();

    SetPath(configFilePathFromSave);
}

void Settings::SetPath(QString path)
{
    _defaultPath = path;
}

QString Settings::GetPath()
{
    return _defaultPath;
}
