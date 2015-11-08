#include "settings.h"
#include <QString>
#include <QDir>
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <utility>
#include <QMessageBox>
#include <QStringListModel>
#include <QStandardPaths>

namespace Sagun
{
    static auto RESOURCE_PREFIX = QStringLiteral(":/json");

    Settings::Settings(QObject *parent, QString filename) :
        QObject(parent),
        m_filename(filename),
        m_modelCommands(*new QStringListModel(this))
    {
//        ReadJsonFile();
    }

    void Settings::ParseJsonData() {
        QString raw_json = ReadJsonFile();
        if(raw_json.size() == 0) return;

        auto json_result = GetJsonObject(raw_json);
        auto json_err = json_result.second;
        if(json_err.error != QJsonParseError::NoError) {
            // Show error
            ShowJsonParseError(json_err);
        }
        auto json_obj = json_result.first;
        m_applicationName = json_obj["applicationName"].toString();
        m_appShortName = json_obj["appShortName"].toString();
        m_hostName = json_obj["hostName"].toString();
        m_portNumber = json_obj["port"].toInt();
        m_longWaitMs = json_obj["tcpLongWaitMs"].toInt();
        m_shortWaitMs = json_obj["tcpShortWaitMs"].toInt();
        SetupCommands(json_obj);
    }

    void Settings::ShowJsonParseError(QJsonParseError jsonError) {
        QString msg = tr("Error passing Json settings file.\n");
        msg.append(jsonError.errorString());
//        msg.append(tr("\nThe default values will be used."));
        QMessageBox::critical(0, tr("VFP"), msg);
    }

    JsonObjErrPair Settings::GetJsonPair(const QString& rawJson) {
        QJsonParseError json_parse_error;
        QJsonDocument json_doc = QJsonDocument::fromJson(rawJson.toUtf8(), &json_parse_error);
        QJsonObject json_obj = json_doc.object();
        return std::make_pair(json_obj, json_parse_error);
    }

    JsonObjErrPair Settings::GetJsonObject(const QString& rawJson) {
        QJsonParseError json_parse_error;
        QJsonDocument json_doc = QJsonDocument::fromJson(rawJson.toUtf8(), &json_parse_error);
        QJsonObject json_obj = json_doc.object();
        return std::make_pair(json_obj, json_parse_error);
    }

    void Settings::SetupCommands(QJsonObject json_obj) {
        QJsonArray cmd_array = json_obj["commands"].toArray();
        QStringList cmd_list;
//        std::for_each(auto begin(cmd_array), end(cmd_array), [&](&item) {cmd_list.append(item.toString());});
        for(auto item: cmd_array) {
            cmd_list.append(item.toString());
        }
        m_modelCommands.setStringList(cmd_list);
    }

    QString Settings::ReadJsonFile()
    {
        auto default_settings = ReadJsonFromInternalResource();
        QDir config_dir = OpenConfigurationDirectory();
        auto path = config_dir.filePath(m_filename);
        QFile std_file(path);

        // If config file exists
        if(std_file.exists()) {
            if(!std_file.open(QFile::ReadOnly|QFile::Text)) {
                SendErrorMessage("Could not open " + path);
                return default_settings;
            }
            QString settings = std_file.readAll();
            std_file.close();
            return settings;
        }

        // Else, If config file doesn't exist
        WriteDefaultsToStdConfigFile(std_file, default_settings);
        return default_settings;
    }

    void Settings::WriteDefaultsToStdConfigFile(QFile& stdConfigFile,
                                                const QString &settings) {
        int length = settings.length();
        if(!stdConfigFile.open(QFile::WriteOnly|QFile::Text)) {
            SendErrorMessage("Could not write the settings to - " +
                             stdConfigFile.fileName());
        }

        auto bytes_written = stdConfigFile.write(qPrintable(settings), length);
        if(bytes_written != length) {
            SendErrorMessage("Could not write the settings to - " +
                             stdConfigFile.fileName());
            if(!stdConfigFile.remove()) {
                SendErrorMessage("Could not remove configuration file. Please delete manually the file - " +
                                 stdConfigFile.fileName());
            }
        }
        stdConfigFile.close();  // QFile destructor will call automatically, but being explicit
    }

    QDir Settings::OpenConfigurationDirectory() {
        QDir config_dir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
        if(!config_dir.exists()) {
            QDir dir;
            dir.mkpath(config_dir.path());
        }
        return config_dir;
    }

    QString Settings::ReadJsonFromInternalResource() {
        QDir res_dir (RESOURCE_PREFIX);
        if(!res_dir.exists()) {
            SendErrorMessage("Internal resource path missing " +
                             res_dir.canonicalPath());
            return "";
        }
        auto path = res_dir.filePath(m_filename);
        QFile res_file(path);
        if(!res_file.open(QFile::ReadOnly | QFile::Text)) {
            // TODO Send error message;
            return "";
        }
        QString settings = res_file.readAll();
        return settings;
    }

    void Settings::SendErrorMessage(const QString& msg) {
        emit NotifyStatusMessage(msg);
    }
}
