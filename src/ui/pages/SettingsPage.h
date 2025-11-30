#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>

class QLineEdit;
class QCheckBox;

/**
 * Settings page:
 *  - Admin password section
 *  - UI / behavior options (demo toggles)
 */
class SettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);

private slots:
    void onChangePasswordClicked();

private:
    QLineEdit* m_currentPasswordEdit = nullptr;
    QLineEdit* m_newPasswordEdit     = nullptr;
    QLineEdit* m_confirmPasswordEdit = nullptr;

    QCheckBox* m_launchOnStartupCheck = nullptr;
    QCheckBox* m_lockInterfaceCheck   = nullptr;

    void setupUi();
};

#endif // SETTINGSPAGE_H
