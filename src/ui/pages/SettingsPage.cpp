#include "SettingsPage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QMessageBox>

SettingsPage::SettingsPage(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

void SettingsPage::setupUi()
{
    auto *rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(8, 8, 8, 8);
    rootLayout->setSpacing(10);

    auto *titleLabel = new QLabel(tr("Application settings"), this);
    titleLabel->setObjectName("SectionTitle");

    auto *subtitleLabel = new QLabel(
        tr("Demo configuration of admin access and basic behavior of CleanState."),
        this
        );
    subtitleLabel->setObjectName("SectionSubTitle");

    rootLayout->addWidget(titleLabel);
    rootLayout->addWidget(subtitleLabel);

    //
    // Card 1: Admin password
    //
    auto *pwdCard = new QFrame(this);
    pwdCard->setObjectName("Card");
    auto *pwdLayout = new QVBoxLayout(pwdCard);
    pwdLayout->setContentsMargins(16, 16, 16, 16);
    pwdLayout->setSpacing(10);

    auto *pwdTitle = new QLabel(tr("Admin panel password"), pwdCard);
    pwdTitle->setObjectName("SectionTitle");

    auto *pwdSubtitle = new QLabel(
        tr("Only teachers or system administrators should be able to open the "
           "CleanState control panel. In the final version this password will "
           "be stored securely (hashed and hidden from students)."),
        pwdCard
        );
    pwdSubtitle->setObjectName("SectionSubTitle");
    pwdSubtitle->setWordWrap(true);

    auto *currentRow = new QHBoxLayout();
    currentRow->addWidget(new QLabel(tr("Current password:"), pwdCard));
    m_currentPasswordEdit = new QLineEdit(pwdCard);
    m_currentPasswordEdit->setEchoMode(QLineEdit::Password);
    currentRow->addWidget(m_currentPasswordEdit);

    auto *newRow = new QHBoxLayout();
    newRow->addWidget(new QLabel(tr("New password:"), pwdCard));
    m_newPasswordEdit = new QLineEdit(pwdCard);
    m_newPasswordEdit->setEchoMode(QLineEdit::Password);
    newRow->addWidget(m_newPasswordEdit);

    auto *confirmRow = new QHBoxLayout();
    confirmRow->addWidget(new QLabel(tr("Confirm new password:"), pwdCard));
    m_confirmPasswordEdit = new QLineEdit(pwdCard);
    m_confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    confirmRow->addWidget(m_confirmPasswordEdit);

    auto *btnChange = new QPushButton(tr("Change password (demo)"), pwdCard);
    connect(btnChange, &QPushButton::clicked,
            this, &SettingsPage::onChangePasswordClicked);

    pwdLayout->addWidget(pwdTitle);
    pwdLayout->addWidget(pwdSubtitle);
    pwdLayout->addLayout(currentRow);
    pwdLayout->addLayout(newRow);
    pwdLayout->addLayout(confirmRow);
    pwdLayout->addWidget(btnChange, 0, Qt::AlignLeft);

    rootLayout->addWidget(pwdCard);

    //
    // Card 2: Behavior / UI options (demo toggles)
    //
    auto *behaviorCard = new QFrame(this);
    behaviorCard->setObjectName("Card");
    auto *behaviorLayout = new QVBoxLayout(behaviorCard);
    behaviorLayout->setContentsMargins(16, 16, 16, 16);
    behaviorLayout->setSpacing(8);

    auto *behaviorTitle = new QLabel(tr("Behavior"), behaviorCard);
    behaviorTitle->setObjectName("SectionTitle");

    auto *behaviorSubtitle = new QLabel(
        tr("These options are placeholders showing which policies we plan to "
           "control in the final version."),
        behaviorCard
        );
    behaviorSubtitle->setObjectName("SectionSubTitle");
    behaviorSubtitle->setWordWrap(true);

    m_launchOnStartupCheck = new QCheckBox(
        tr("Start CleanState control panel automatically after login"),
        behaviorCard
        );

    m_lockInterfaceCheck = new QCheckBox(
        tr("Lock CleanState window when admin logs out"),
        behaviorCard
        );

    // Demo defaults
    m_launchOnStartupCheck->setChecked(true);
    m_lockInterfaceCheck->setChecked(true);

    behaviorLayout->addWidget(behaviorTitle);
    behaviorLayout->addWidget(behaviorSubtitle);
    behaviorLayout->addSpacing(4);
    behaviorLayout->addWidget(m_launchOnStartupCheck);
    behaviorLayout->addWidget(m_lockInterfaceCheck);
    behaviorLayout->addStretch();

    rootLayout->addWidget(behaviorCard);
    rootLayout->addStretch(1);
}

void SettingsPage::onChangePasswordClicked()
{
    QString newPwd  = m_newPasswordEdit->text();
    QString confirm = m_confirmPasswordEdit->text();

    if (newPwd.isEmpty()) {
        QMessageBox::warning(this, tr("Error"),
                             tr("New password cannot be empty."));
        return;
    }
    if (newPwd != confirm) {
        QMessageBox::warning(this, tr("Error"),
                             tr("New password and confirmation do not match."));
        return;
    }

    QMessageBox::information(
        this,
        tr("Password changed"),
        tr("In the final version, this will securely store the new password.\n"
           "For now, it is just a visual demo.")
        );
}
