#pragma once
#include <QObject>

namespace Sagun {

    class InstSocket;

    class Instrument : public QObject
    {
        Q_OBJECT
    public:
        explicit Instrument(QObject *parent, InstSocket& sock);
        virtual ~Instrument();

        void Connect();
        void Disconnect() const;
        bool IsConnected() const;
        QString GetHostName() const;
        quint16 GetPort() const;
        void SetLongWaitMs(int value);
        void SetShortWaitMs(int value);

    signals:
        void NotifyConnected();
        void NotifyDisconnected();
        void NotifyDataSent(const QString& dataSent);
        void NotifyDataReceived(const QString& readData);
        // Useful when showing separate error and status msg's in separate widgets
        void NotifyErrorDetected(const QString& errorMsg);
        void NotifyStatusUpdated(const QString& statusMsg);

    public slots:
        void onHostNameChanged(const QString& hostName);
        void onPortChanged(quint16 port);
        void onConnected();
        void onDisconnected();
        void onSendRequest(const QString& dataToSend);
        void onReceiveRequest();

    private:
        InstSocket& m_instSocket;
        QString m_lastCommandSent;

        void WireConnections();

        explicit Instrument(const Instrument& rhs) = delete;
        Instrument& operator= (const Instrument& rhs) = delete;
    };
}



