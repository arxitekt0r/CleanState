#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>

class QLineEdit;

class SettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);

private slots:
    void onChangePasswordClicked();

private:
    QLineEdit* m_currentPasswordEdit = nullptr;
    QLineEdit* m_newPasswordEdit = nullptr;
    QLineEdit* m_confirmPasswordEdit = nullptr;

    void setupUi();
};

#endif // SETTINGSPAGE_H
