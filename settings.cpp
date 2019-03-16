#include "settings.h"

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
