#include "ProtectionPage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

ProtectionPage::ProtectionPage(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
    updateUi();
}

void ProtectionPage::setupUi()
{
    auto *rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(8, 8, 8, 8);
    rootLayout->setSpacing(10);

    auto *titleLabel = new QLabel(tr("Protection configuration"), this);
    titleLabel->setObjectName("SectionTitle");

    auto *subtitleLabel = new QLabel(
        tr("Select which volume or folder should be kept clean after reboot."),
        this
        );
    subtitleLabel->setObjectName("SectionSubTitle");

    rootLayout->addWidget(titleLabel);
    rootLayout->addWidget(subtitleLabel);

    auto *card = new QFrame(this);
    card->setObjectName("Card");
    auto *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(16, 16, 16, 16);
    cardLayout->setSpacing(10);

    m_selectedPathLabel = new QLabel(card);
    m_currentModeLabel = new QLabel(card);
    m_selectedPathLabel->setWordWrap(true);
    m_currentModeLabel->setWordWrap(true);

    auto *pathRow = new QHBoxLayout();
    pathRow->addWidget(m_selectedPathLabel, 1);

    auto *btnSelectPath = new QPushButton(tr("Choose target…"), card);
    connect(btnSelectPath, &QPushButton::clicked,
            this, &ProtectionPage::onSelectPathClicked);
    pathRow->addWidget(btnSelectPath);

    cardLayout->addLayout(pathRow);
    cardLayout->addWidget(m_currentModeLabel);

    auto *buttonsRow1 = new QHBoxLayout();
    auto *btnEnable  = new QPushButton(tr("Enable protection"), card);
    auto *btnDisable = new QPushButton(tr("Disable protection"), card);
    buttonsRow1->addWidget(btnEnable);
    buttonsRow1->addWidget(btnDisable);
    buttonsRow1->addStretch();

    connect(btnEnable,  &QPushButton::clicked,
            this, &ProtectionPage::onEnableProtectionClicked);
    connect(btnDisable, &QPushButton::clicked,
            this, &ProtectionPage::onDisableProtectionClicked);

    auto *buttonsRow2 = new QHBoxLayout();
    auto *btnCommit  = new QPushButton(tr("Save this state"), card);
    auto *btnDiscard = new QPushButton(tr("Reset to clean state"), card);
    buttonsRow2->addWidget(btnCommit);
    buttonsRow2->addWidget(btnDiscard);
    buttonsRow2->addStretch();

    connect(btnCommit,  &QPushButton::clicked,
            this, &ProtectionPage::onCommitClicked);
    connect(btnDiscard, &QPushButton::clicked,
            this, &ProtectionPage::onDiscardClicked);

    cardLayout->addSpacing(8);
    cardLayout->addLayout(buttonsRow1);
    cardLayout->addLayout(buttonsRow2);

    rootLayout->addWidget(card);
    rootLayout->addStretch(1);
}

void ProtectionPage::updateUi()
{
    if (m_selectedPath.isEmpty()) {
        m_selectedPathLabel->setText(
            tr("Protected target: <i>No folder or drive selected</i>")
            );
    } else {
        m_selectedPathLabel->setText(
            tr("Protected target: <b>%1</b>")
                .arg(m_selectedPath.toHtmlEscaped())
            );
    }

    if (m_protectionEnabled) {
        m_currentModeLabel->setText(
            tr("Protection state: "
               "<b style='color:#22C55E;'>Enabled (demo only)</b>")
            );
    } else {
        m_currentModeLabel->setText(
            tr("Protection state: "
               "<b style='color:#F97316;'>Disabled / not active</b>")
            );
    }
}

void ProtectionPage::onSelectPathClicked()
{
    QString dir = QFileDialog::getExistingDirectory(
        this,
        tr("Select folder to protect"),
        QStringLiteral("C:/"),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );

    if (dir.isEmpty())
        return;

    m_selectedPath = dir;
    updateUi();
}

void ProtectionPage::onEnableProtectionClicked()
{
    if (m_selectedPath.isEmpty()) {
        QMessageBox::warning(this,
                             tr("No target selected"),
                             tr("Please choose a folder or drive before enabling protection."));
        return;
    }

    m_protectionEnabled = true;
    updateUi();

    QMessageBox::information(this,
                             tr("Protection enabled"),
                             tr("Protection has been enabled (demo mode only)."));
}

void ProtectionPage::onDisableProtectionClicked()
{
    m_protectionEnabled = false;
    updateUi();

    QMessageBox::information(this,
                             tr("Protection disabled"),
                             tr("Protection has been disabled (demo mode only)."));
}

void ProtectionPage::onCommitClicked()
{
    QMessageBox::information(
        this,
        tr("Save state (demo)"),
        tr("In the final version, this will mark the current system state as the baseline.")
        );
}

void ProtectionPage::onDiscardClicked()
{
    QMessageBox::information(
        this,
        tr("Reset state (demo)"),
        tr("In the final version, this will discard changes and restore the clean baseline.")
        );
}
