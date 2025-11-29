#ifndef STATUSPAGE_H
#define STATUSPAGE_H

#include <QWidget>

class QLabel;
class QPushButton;

class StatusPage : public QWidget
{
    Q_OBJECT

public:
    explicit StatusPage(QWidget *parent = nullptr);

private slots:
    void onRefreshClicked();

private:
    QLabel* m_protectionStatusLabel = nullptr;
    QLabel* m_protectedPathLabel = nullptr;
    QLabel* m_lastResetLabel = nullptr;

    void setupUi();
    void updateDummyStatus();
};

#endif // STATUSPAGE_H
