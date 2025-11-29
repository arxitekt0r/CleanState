#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTabWidget;
class QFrame;
class QLabel;
class QVBoxLayout;      // <<—— ADD THIS

class StatusPage;
class ProtectionPage;
class LogsPage;
class SettingsPage;

/**
 * Main application window.
 * Modern dark UI, non-resizable, 4 tabs.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    QWidget*        m_centralWidget = nullptr;
    QTabWidget*     m_tabWidget     = nullptr;

    StatusPage*     m_statusPage      = nullptr;
    ProtectionPage* m_protectionPage  = nullptr;
    LogsPage*       m_logsPage        = nullptr;
    SettingsPage*   m_settingsPage    = nullptr;

    void setupUi();
    void setupHeader(QVBoxLayout *rootLayout);
    void setupTabs(QVBoxLayout *rootLayout);
    void setupFixedSize();
    void applyStyleSheet();
};

#endif // MAINWINDOW_H
