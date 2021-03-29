#include "mainwindow.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QApplication>
#include <QTimer>
#include <DTitlebar>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
        m_toggleButton = new QPushButton;
        m_toggleButton->setText(tr("Switch"));
        m_toggleButton->setFixedHeight(38);
        m_toggleButton->setVisible(true);


        m_warningTips = new QLabel;
        m_warningTips->setAlignment(Qt::AlignHCenter);
        m_warningTips->setVisible(false);
        m_warningTips->setWordWrap(true);
        m_warningTips->setObjectName("WarningTips");


        m_installTips = new QLabel;
        m_installTips->setVisible(false);
        m_installTips->setWordWrap(true);
        m_installTips->setAlignment(Qt::AlignHCenter);
        m_installTips->setContentsMargins(65, 0, 65, 0);
        m_installTips->setObjectName("installTips");
        m_installTips->setFixedSize(424, 40);

//        m_spinner = new DSpinner();
//        m_spinner->setFixedSize(32, 32);
//        m_spinner->setVisible(false);

        m_tipsIcon = new QLabel;

        m_updateButton = new QPushButton;
        m_updateButton->setText(tr("Update"));
        m_updateButton->setFixedHeight(38);
        m_updateButton->setVisible(false);

//        m_rebootButton = new DSuggestButton;
//        m_rebootButton->setText(tr("Reboot Now"));
//        m_rebootButton->setFixedHeight(38);
//        m_rebootButton->setVisible(false);

        m_cancelButton = new QPushButton;
        m_cancelButton->setText(tr("Cancel"));
        m_cancelButton->setFixedHeight(38);
        m_cancelButton->setVisible(false);

        m_okButton = new QPushButton;
        m_okButton->setText(tr("OK"));
        m_okButton->setFixedHeight(38);
        m_okButton->setVisible(false);


        m_vendorIcon = new QLabel;
        m_vendorIcon->setAlignment(Qt::AlignCenter);
        m_vendorIcon->setFixedSize(140, 140);
        //m_vendorIcon->setFrameShape(QFrame::Box);

        m_vendorName = new QLabel;
        m_vendorName->setWordWrap(true);
        m_vendorName->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
        m_vendorName->setFixedHeight(54);
        m_vendorName->setContentsMargins(10, 0, 10, 0);
        //m_vendorName->setFrameShape(QFrame::Box);



        m_resolutionsLayout = new QVBoxLayout;
        m_resolutionsLayout->setContentsMargins(0, 0, 0, 0);
        m_resolutionsLayout->setSpacing(10);
        m_resolutionsWidget = new QWidget;
        m_resolutionsWidget->setLayout(m_resolutionsLayout);

        auto *centralLayout = new QVBoxLayout;
        centralLayout->addWidget(m_vendorIcon);
        centralLayout->setAlignment(m_vendorIcon, Qt::AlignHCenter);
        centralLayout->addSpacing(10);
        centralLayout->addWidget(m_vendorName);
        centralLayout->addSpacing(10);
        centralLayout->addWidget(m_resolutionsWidget);
        centralLayout->addSpacing(50);
        centralLayout->addWidget(m_tipsIcon);
        centralLayout->setAlignment(m_tipsIcon, Qt::AlignHCenter);
//        centralLayout->addWidget(m_spinner);
//        centralLayout->setAlignment(m_spinner, Qt::AlignHCenter);
        centralLayout->addWidget(m_installTips);
        centralLayout->setAlignment(m_installTips, Qt::AlignHCenter);
        centralLayout->addStretch();
        centralLayout->addWidget(m_warningTips);
        centralLayout->addSpacing(10);
        centralLayout->addWidget(m_toggleButton);
        centralLayout->addWidget(m_updateButton);
        centralLayout->addWidget(m_okButton);

        auto *hBoxLayout = new QHBoxLayout;
        hBoxLayout->addWidget(m_cancelButton);
        hBoxLayout->addSpacing(8);
//        hBoxLayout->addWidget(m_rebootButton);


        centralLayout->addLayout(hBoxLayout);
        centralLayout->setSpacing(0);
        centralLayout->setContentsMargins(10, 30, 10, 10);
        titlebar()->setTitle("dddd");
        titlebar()->setIcon(QIcon(":/deepin-graphics-driver-manager-64px.svg"));
        m_centerWidget = new QWidget;
        m_centerWidget->setObjectName("centerWidget");

        m_centerWidget->setLayout(centralLayout);

        auto *mainLayout = new QHBoxLayout;
        auto *mainWidget = new QWidget;
        mainWidget->setObjectName("mainWidget");
        mainLayout->addWidget(m_centerWidget);
        mainLayout->setContentsMargins(10, 10, 10, 10);
        setCentralWidget(mainWidget);
        centralWidget()->setLayout(mainLayout);

        setFixedSize(484, 682);
//        move(qApp->primaryScreen()->geometry().center() - rect().center());

        onThemeChanged(DGuiApplicationHelper::instance()->themeType());


        connect(m_toggleButton, &QPushButton::clicked, this, &MainWindow::onToggleBtnClicked);
        connect(m_updateButton, &QPushButton::clicked, this, &MainWindow::onToggleBtnClicked);
//        connect(m_rebootButton, &QPushButton::clicked, this, &MainWindow::onRebootBtnClicked);
        connect(m_cancelButton, &QPushButton::clicked, this, &MainWindow::onCancelBtnClicked);
        connect(m_okButton, &QPushButton::clicked, qApp, &QApplication::quit);
        connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged, this, &MainWindow::onThemeChanged);

        QTimer::singleShot(0, this, &MainWindow::loadResolutions);

}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    qWarning() << "@@keyPressEvent: " << e;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qWarning() << "@@closeEvent: "<< event;
}

void MainWindow::noResolutions()
{
    qWarning() << "@@noResolutions";
}

void MainWindow::loadDevice()
{
    qWarning() << "@@loadDevice";
}

void MainWindow::setVendorIcon()
{
    qWarning() << "@@setVendorIcon";
}


MainWindow::~MainWindow()
= default;

void MainWindow::loadResolutions()
{
    qWarning() << "@@loadResolutions";
}

void MainWindow::onUpdateBtnClicked()
{
    qWarning() << "@@onUpdateBtnClicked";
}

void MainWindow::onToggleBtnClicked()
{
    qWarning() << "@@onToggleBtnClicked";
}

void MainWindow::onRebootBtnClicked()
{
    qWarning() << "@@onRebootBtnClicked";
}


void MainWindow::onCancelBtnClicked()
{
    qWarning() << "@@onCancelBtnClicked";
}

void MainWindow::onPreInstallProgress(int progress)
{
    qWarning() << "@@onPreInstallProgress: " << progress;
}

void MainWindow::onThemeChanged(DGuiApplicationHelper::ColorType type)
{
    qWarning() << "@@onThemeChanged: " << type;
}


