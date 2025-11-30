#ifndef LOGSPAGE_H
#define LOGSPAGE_H

#include <QWidget>

class QTableWidget;

class LogsPage : public QWidget
{
    Q_OBJECT

public:
    explicit LogsPage(QWidget *parent = nullptr);

private slots:
    void onClearClicked();
    void onRefreshClicked();

private:
    QTableWidget* m_table = nullptr;

    void setupUi();
    void populateDummyLogs();
    void adjustColumns();   // <- new helper
};

#endif // LOGSPAGE_H
