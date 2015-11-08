#include "startup.h"
#include "View/setuptab.h"
#include "View/mainview.h"
#include "utils.h"
#include "Model/settings.h"
#include "Model/provider.h"
#include "Model/instsocket.h"
#include "Model/instrument.h"

namespace Sagun
{
    Startup::Startup() :
        QObject(nullptr),
        m_setupTab(*new SetupTab(nullptr)),
        m_mainView(*new MainView(nullptr, m_setupTab)),
        m_instrument(new Instrument(this,
                                    *new InstSocket(this)))
    {
//        Settings my_settings(this, "settings.json");
        Settings& my_settings = Provider::GetSettingsAsSingleton();
        my_settings.ParseJsonData();
    }

    Startup::~Startup() {
        Utils::DestructorMsg(this);
        delete &m_mainView;
    }

    void Startup::show() const {
        m_mainView.show();
    }
}
