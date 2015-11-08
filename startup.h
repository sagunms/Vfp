#pragma once
#include <QObject>

namespace Sagun{

    class SetupTab;
    class MainView;

    class Startup final : public QObject
    {
        Q_OBJECT
    public:
        explicit Startup();
        void show() const;

        ~Startup();
    private:
        SetupTab& m_setupTab;
        MainView& m_mainView;

        explicit Startup(const Startup& rhs) = delete;
        Startup& operator= (const Startup& rhs) = delete;
    };
}
