#pragma once
#include <QObject>

class QString;
class QStringListModel;
class QJsonParseError;
class QJsonObject;
class QFile;
class QDir;

namespace Sagun {

    typedef std::pair<QJsonObject, QJsonParseError> JsonObjErrPair;

    class Settings : public QObject
    {
        Q_OBJECT
    public:
        explicit Settings(QObject *parent, QString filename);
        void ParseJsonData();
        QString getApplicationName() const { return m_applicationName; }
        QString getAppShortName() const { return m_appShortName; }
        QString getHostName() const { return m_hostName; }
        quint16 getPortNumber() const { return m_portNumber; }
        int getShortWaitMs() const { return m_shortWaitMs; }
        int getLongWaitMs() const { return m_longWaitMs; }
        QStringListModel& getCommandsAsModels() const { return m_modelCommands; }

    signals:
        void NotifyStatusMessage(QString message);

    private:
        QString m_filename;
        QString m_applicationName;
        QString m_appShortName;
        QString m_hostName;
        quint16 m_portNumber;
        int m_longWaitMs;
        int m_shortWaitMs;
        // Very convenient container to hold list of string to display in a ViewWidget
        QStringListModel& m_modelCommands;

        QString ReadJsonFile();
        QString ReadJsonFromInternalResource();

        void SendErrorMessage(const QString &msg);
        void ShowJsonParseError(QJsonParseError jsonError);
        void SetupCommands(QJsonObject json_obj);
        JsonObjErrPair GetJsonObject(const QString &rawJson);
        JsonObjErrPair GetJsonPair(const QString &rawJson);
        QDir OpenConfigurationDirectory();
        void WriteDefaultsToStdConfigFile(QFile &stdConfigFile, const QString &settings);

        explicit Settings(const Settings& rhs) = delete;
        Settings& operator= (const Settings& rhs) = delete;
    };
}



