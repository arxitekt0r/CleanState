#include "MainWindow.h"

#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>

#include "pages/StatusPage.h"
#include "pages/ProtectionPage.h"
#include "pages/LogsPage.h"
#include "pages/SettingsPage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("CleanState – System Protection Tool"));

    setupUi();
    setupFixedSize();
    applyStyleSheet();
}

MainWindow::~MainWindow() = default;

void MainWindow::setupUi()
{
    m_centralWidget = new QWidget(this);
    auto *rootLayout = new QVBoxLayout(m_centralWidget);
    rootLayout->setContentsMargins(16, 16, 16, 16);
    rootLayout->setSpacing(10);

    setupHeader(rootLayout);
    setupTabs(rootLayout);

    m_centralWidget->setLayout(rootLayout);
    setCentralWidget(m_centralWidget);
}

void MainWindow::setupHeader(QVBoxLayout *rootLayout)
{
    auto *headerFrame = new QFrame(m_centralWidget);
    headerFrame->setObjectName("HeaderBar");
    auto *headerLayout = new QHBoxLayout(headerFrame);
    headerLayout->setContentsMargins(16, 10, 16, 10);
    headerLayout->setSpacing(10);

    auto *titleLabel = new QLabel(tr("CleanState"), headerFrame);
    titleLabel->setObjectName("AppTitle");

    auto *subtitleLabel = new QLabel(
        tr("Classroom system protection & automatic restore"),
        headerFrame
        );
    subtitleLabel->setObjectName("AppSubtitle");

    auto *titleColumn = new QVBoxLayout();
    titleColumn->setSpacing(2);
    titleColumn->addWidget(titleLabel);
    titleColumn->addWidget(subtitleLabel);

    headerLayout->addLayout(titleColumn);
    headerLayout->addStretch();

    headerFrame->setLayout(headerLayout);
    rootLayout->addWidget(headerFrame);
}

void MainWindow::setupTabs(QVBoxLayout *rootLayout)
{
    m_tabWidget = new QTabWidget(m_centralWidget);
    m_tabWidget->setDocumentMode(true);
    m_tabWidget->setTabPosition(QTabWidget::North);

    m_statusPage      = new StatusPage(this);
    m_protectionPage  = new ProtectionPage(this);
    m_logsPage        = new LogsPage(this);
    m_settingsPage    = new SettingsPage(this);

    m_tabWidget->addTab(m_statusPage,     tr("Status"));
    m_tabWidget->addTab(m_protectionPage, tr("Protection"));
    m_tabWidget->addTab(m_logsPage,       tr("Logs"));
    m_tabWidget->addTab(m_settingsPage,   tr("Settings"));

    rootLayout->addWidget(m_tabWidget, 1);
}

void MainWindow::setupFixedSize()
{
    // 16:9 window, good for 24" 1080p monitors
    const int width  = 1280;
    const int height = 720;

    setFixedSize(width, height);

    // Remove maximize button (keep close & minimize if theme allows)
    Qt::WindowFlags flags = windowFlags();
    flags &= ~Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags);
}

void MainWindow::applyStyleSheet()
{
    // Simple modern dark theme using Qt style sheets
    const char *qss = R"(
        /* Global text color so labels/normal text are visible */
        QWidget {
            color: #E5E7EB;
        }

        QMainWindow {
            background-color: #020617;
        }

        /* Header bar */
        QFrame#HeaderBar {
            background-color: #020617;
            border: 1px solid #0F172A;
            border-radius: 10px;
        }

        QLabel#AppTitle {
            font-size: 20px;
            font-weight: 600;
            color: #F9FAFB;
        }

        QLabel#AppSubtitle {
            font-size: 11px;
            color: #9CA3AF;
        }

        /* Section titles */
        QLabel#SectionTitle {
            font-size: 16px;
            font-weight: 500;
            color: #E5E7EB;
        }

        QLabel#SectionSubTitle {
            font-size: 11px;
            color: #9CA3AF;
        }

        /* Tab bar */
        QTabWidget::pane {
            border: 0;
            margin-top: 4px;
        }

        QTabBar::tab {
            background-color: #020617;
            color: #9CA3AF;
            padding: 8px 18px;
            border-top-left-radius: 10px;
            border-top-right-radius: 10px;
            margin-right: 2px;
        }

        QTabBar::tab:selected {
            background-color: #0F172A;
            color: #F9FAFB;
            font-weight: 500;
        }

        QTabBar::tab:hover:!selected {
            background-color: #02081d;
            color: #E5E7EB;
        }

        /* Generic card frame */
        QFrame#Card {
            background-color: #020617;
            border-radius: 12px;
            border: 1px solid #1F2937;
        }

        /* Buttons */
        QPushButton {
            background-color: #2563EB;
            color: #F9FAFB;
            border-radius: 8px;
            padding: 6px 16px;
            border: none;
            font-size: 12px;
        }

        QPushButton:hover {
            background-color: #1D4ED8;
        }

        QPushButton:pressed {
            background-color: #1E40AF;
        }

        QPushButton:disabled {
            background-color: #4B5563;
            color: #9CA3AF;
        }

        /* Inputs */
        QLineEdit {
            background-color: #020617;
            border-radius: 6px;
            border: 1px solid #1F2937;
            padding: 4px 8px;
            color: #E5E7EB;
        }

        QComboBox {
            background-color: #020617;
            border-radius: 6px;
            border: 1px solid #1F2937;
            padding: 4px 8px;
            color: #E5E7EB;
        }

        /* Table */
        QTableWidget {
            background-color: #020617;
            gridline-color: #1F2937;
            selection-background-color: #1E293B;
            selection-color: #E5E7EB;
            color: #E5E7EB;   /* <<< important for visible text */
        }

        QHeaderView::section {
            background-color: #02081d;
            color: #9CA3AF;
            padding: 4px;
            border: 0px;
            border-bottom: 1px solid #1F2937;
        }
    )";

    this->setStyleSheet(QString::fromLatin1(qss));
}
