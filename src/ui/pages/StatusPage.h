#ifndef STATUSPAGE_H
#define STATUSPAGE_H

#include <QWidget>

class QLabel;
class QPushButton;

/**
 * Dashboard-style status page:
 *  - Overall protection state
 *  - Protected target
 *  - Last reset + demo counters
 */
class StatusPage : public QWidget
{
    Q_OBJECT

public:
    explicit StatusPage(QWidget *parent = nullptr);

private slots:
    void onRefreshClicked();

private:
    QLabel* m_protectionStatusLabel = nullptr;
    QLabel* m_protectedPathLabel    = nullptr;
    QLabel* m_lastResetLabel        = nullptr;
    QLabel* m_blockedCountLabel     = nullptr;
    QLabel* m_allowedCountLabel     = nullptr;

    void setupUi();
    void updateDummyStatus();
};

#endif // STATUSPAGE_H
