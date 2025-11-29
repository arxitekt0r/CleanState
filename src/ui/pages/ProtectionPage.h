#ifndef PROTECTIONPAGE_H
#define PROTECTIONPAGE_H

#include <QWidget>

class QLabel;

class ProtectionPage : public QWidget
{
    Q_OBJECT

public:
    explicit ProtectionPage(QWidget *parent = nullptr);

private slots:
    void onSelectPathClicked();
    void onEnableProtectionClicked();
    void onDisableProtectionClicked();
    void onCommitClicked();
    void onDiscardClicked();

private:
    QLabel* m_selectedPathLabel = nullptr;
    QLabel* m_currentModeLabel = nullptr;

    bool m_protectionEnabled = false;
    QString m_selectedPath;

    void setupUi();
    void updateUi();
};

#endif // PROTECTIONPAGE_H
