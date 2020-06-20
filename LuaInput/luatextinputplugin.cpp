#include "luatextinput.h"
#include "luatextinputplugin.h"

#include <QtPlugin>

LuaTextInputPlugin::LuaTextInputPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void LuaTextInputPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool LuaTextInputPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *LuaTextInputPlugin::createWidget(QWidget *parent)
{
    return new LuaTextInput(parent);
}

QString LuaTextInputPlugin::name() const
{
    return QLatin1String("LuaTextInput");
}

QString LuaTextInputPlugin::group() const
{
    return QLatin1String("Input Widgets");
}

QIcon LuaTextInputPlugin::icon() const
{
    return QIcon();
}

QString LuaTextInputPlugin::toolTip() const
{
    return QLatin1String("A text box to place lua scripts.");
}

QString LuaTextInputPlugin::whatsThis() const
{
    return QLatin1String("Put lua text in here to be run on the Screen.");
}

bool LuaTextInputPlugin::isContainer() const
{
    return false;
}

QString LuaTextInputPlugin::domXml() const
{
    return QLatin1String("<widget class=\"LuaTextInput\" name=\"luaTextInput\">\n</widget>\n");
}

QString LuaTextInputPlugin::includeFile() const
{
    return QLatin1String("luatextinput.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(luatextinputplugin, LuaTextInputPlugin)
#endif // QT_VERSION < 0x050000
