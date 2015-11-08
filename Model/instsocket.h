#pragma once
#include <QObject>

class QTcpSocket;   // Always outside my namespaces

namespace Sagun {
    class InstSocket : public QObject
    {
        Q_OBJECT
    public:
        explicit InstSocket(QObject *parent=0);
        bool Connect();
        bool IsOpen();
        void Disconnect();

        QString ReadData() const;
        void WriteData(const QString &data) const;

        // Getters and Setters
        QString GetHostName() const { return m_hostName; }
        void SetHostName(const QString &hostName) { m_hostName = hostName; }

        quint16 GetPort() const { return m_port; }
        void SetPort(const quint16 &port) { m_port = port; }

        void SetShortWaitMs(int shortWaitMs) { m_shortWaitMs = shortWaitMs; }
        void SetLongWaitMs(int longWaitMs) { m_longWaitMs = longWaitMs; }

        ~InstSocket();

    signals:
        void NotifyConnected();
        void NotifyDisconnected();

    private slots:
        void onConnected();
        void onDisconnected();

    private:
        QTcpSocket& m_socket;
        QString m_hostName;
        quint16 m_port;
        int m_shortWaitMs;
        int m_longWaitMs;

        explicit InstSocket(const InstSocket& rhs) = delete;
        InstSocket& operator= (const InstSocket& rhs) = delete;
    };
}



