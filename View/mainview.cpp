#include "mainview.h"
#include "ui_mainview.h"
#include "View/setuptab.h"

namespace Sagun {

    MainView::MainView(QWidget *parent, SetupTab& setup) :
        QMainWindow(parent),
        m_setupTab(setup),
        ui(new Ui::MainView)
    {
        ui->setupUi(this);
        m_setupTab.setParent(this);
        ui->loSetupTab->addWidget(&m_setupTab);
    }

    MainView::~MainView()
    {
        delete ui;
    }
}
