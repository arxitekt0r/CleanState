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

    // Title + subtitle
    auto *titleLabel = new QLabel(tr("Protection configuration"), this);
    titleLabel->setObjectName("SectionTitle");

    auto *subtitleLabel = new QLabel(
        tr("Choose which volume or folder must always return to a clean state after reboot."),
        this
        );
    subtitleLabel->setObjectName("SectionSubTitle");

    rootLayout->addWidget(titleLabel);
    rootLayout->addWidget(subtitleLabel);

    // Main card
    auto *card = new QFrame(this);
    card->setObjectName("Card");
    auto *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(16, 16, 16, 16);
    cardLayout->setSpacing(14);

    //
    // Top row: target + status badge
    //
    auto *topRow = new QHBoxLayout();
    topRow->setSpacing(16);

    // Left side: target info
    auto *targetColumn = new QVBoxLayout();
    targetColumn->setSpacing(4);

    auto *targetTitle = new QLabel(tr("Protected target"), card);
    targetTitle->setObjectName("SectionTitle");

    m_selectedPathLabel = new QLabel(card);
    m_selectedPathLabel->setWordWrap(true);

    m_targetHintLabel = new QLabel(
        tr("Hint: In a school environment this is usually the system drive (C:) "
           "or a shared profile folder."),
        card
        );
    m_targetHintLabel->setObjectName("SectionSubTitle");
    m_targetHintLabel->setWordWrap(true);

    targetColumn->addWidget(targetTitle);
    targetColumn->addWidget(m_selectedPathLabel);
    targetColumn->addWidget(m_targetHintLabel);

    // Select button under target column
    auto *selectRow = new QHBoxLayout();
    selectRow->setSpacing(8);
    auto *btnSelectPath = new QPushButton(tr("Choose folder / drive…"), card);
    connect(btnSelectPath, &QPushButton::clicked,
            this, &ProtectionPage::onSelectPathClicked);
    selectRow->addWidget(btnSelectPath);
    selectRow->addStretch();
    targetColumn->addLayout(selectRow);

    // Right side: status badge
    auto *statusColumn = new QVBoxLayout();
    statusColumn->setSpacing(6);
    statusColumn->addStretch();

    auto *statusTitle = new QLabel(tr("Protection status"), card);
    statusTitle->setObjectName("SectionSubTitle");

    m_statusBadgeLabel = new QLabel(card);
    m_statusBadgeLabel->setAlignment(Qt::AlignCenter);
    m_statusBadgeLabel->setMinimumWidth(160);

    statusColumn->addWidget(statusTitle, 0, Qt::AlignRight);
    statusColumn->addWidget(m_statusBadgeLabel, 0, Qt::AlignRight);
    statusColumn->addStretch();

    topRow->addLayout(targetColumn, 1);
    topRow->addLayout(statusColumn, 0);

    cardLayout->addLayout(topRow);

    //
    // Separator line
    //
    auto *line = new QFrame(card);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Plain);
    line->setStyleSheet("color: #1F2937;");
    cardLayout->addWidget(line);

    //
    // Middle row: Protection mode (enable/disable)
    //
    auto *modeTitle = new QLabel(tr("Protection mode"), card);
    modeTitle->setObjectName("SectionTitle");

    auto *modeSubtitle = new QLabel(
        tr("Turn protection on or off for the selected target. "
           "When enabled, changes are discarded after reboot."),
        card
        );
    modeSubtitle->setObjectName("SectionSubTitle");
    modeSubtitle->setWordWrap(true);

    auto *modeButtonsRow = new QHBoxLayout();
    modeButtonsRow->setSpacing(10);

    auto *btnEnable  = new QPushButton(tr("Enable protection"), card);
    auto *btnDisable = new QPushButton(tr("Disable protection"), card);

    connect(btnEnable,  &QPushButton::clicked,
            this, &ProtectionPage::onEnableProtectionClicked);
    connect(btnDisable, &QPushButton::clicked,
            this, &ProtectionPage::onDisableProtectionClicked);

    modeButtonsRow->addWidget(btnEnable);
    modeButtonsRow->addWidget(btnDisable);
    modeButtonsRow->addStretch();

    cardLayout->addWidget(modeTitle);
    cardLayout->addWidget(modeSubtitle);
    cardLayout->addLayout(modeButtonsRow);

    //
    // Baseline control: commit / discard
    //
    auto *baselineTitle = new QLabel(tr("Baseline control"), card);
    baselineTitle->setObjectName("SectionTitle");

    auto *baselineSubtitle = new QLabel(
        tr("Use these actions to define what “clean state” means. "
           "\"Save this state\" will mark the current disk contents as baseline; "
           "\"Reset to clean state\" will return to that baseline."),
        card
        );
    baselineSubtitle->setObjectName("SectionSubTitle");
    baselineSubtitle->setWordWrap(true);

    auto *baselineButtonsRow = new QHBoxLayout();
    baselineButtonsRow->setSpacing(10);

    auto *btnCommit  = new QPushButton(tr("Save this state"), card);
    auto *btnDiscard = new QPushButton(tr("Reset to clean state"), card);

    connect(btnCommit,  &QPushButton::clicked,
            this, &ProtectionPage::onCommitClicked);
    connect(btnDiscard, &QPushButton::clicked,
            this, &ProtectionPage::onDiscardClicked);

    baselineButtonsRow->addWidget(btnCommit);
    baselineButtonsRow->addWidget(btnDiscard);
    baselineButtonsRow->addStretch();

    cardLayout->addSpacing(4);
    cardLayout->addWidget(baselineTitle);
    cardLayout->addWidget(baselineSubtitle);
    cardLayout->addLayout(baselineButtonsRow);

    rootLayout->addWidget(card);
    rootLayout->addStretch(1);

    setLayout(rootLayout);
}

void ProtectionPage::updateUi()
{
    if (m_selectedPath.isEmpty()) {
        m_selectedPathLabel->setText(
            tr("No folder or drive selected yet.")
            );
    } else {
        m_selectedPathLabel->setText(
            tr("<b>%1</b>").arg(m_selectedPath.toHtmlEscaped())
            );
    }

    if (m_protectionEnabled) {
        m_currentModeLabel
            ? m_currentModeLabel->setText(tr("Protection is currently enabled (demo)."))
            : void();
    } else {
        m_currentModeLabel
            ? m_currentModeLabel->setText(tr("Protection is currently disabled."))
            : void();
    }

    updateStatusBadge();
}

void ProtectionPage::updateStatusBadge()
{
    // Change badge text + color based on configuration
    if (m_selectedPath.isEmpty()) {
        m_statusBadgeLabel->setText(tr("Not configured"));
        m_statusBadgeLabel->setStyleSheet(
            "QLabel {"
            "  background-color: #111827;"
            "  color: #9CA3AF;"
            "  border-radius: 999px;"
            "  padding: 4px 12px;"
            "  border: 1px solid #1F2937;"
            "}"
            );
    } else if (!m_protectionEnabled) {
        m_statusBadgeLabel->setText(tr("Configured • Disabled"));
        m_statusBadgeLabel->setStyleSheet(
            "QLabel {"
            "  background-color: #1F2937;"
            "  color: #F97316;"
            "  border-radius: 999px;"
            "  padding: 4px 12px;"
            "  border: 1px solid #92400E;"
            "}"
            );
    } else {
        m_statusBadgeLabel->setText(tr("Active protection"));
        m_statusBadgeLabel->setStyleSheet(
            "QLabel {"
            "  background-color: #064E3B;"
            "  color: #BBF7D0;"
            "  border-radius: 999px;"
            "  padding: 4px 12px;"
            "  border: 1px solid #22C55E;"
            "}"
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
        QMessageBox::warning(
            this,
            tr("No target selected"),
            tr("Please choose a folder or drive before enabling protection.")
            );
        return;
    }

    m_protectionEnabled = true;
    updateUi();

    QMessageBox::information(
        this,
        tr("Protection enabled"),
        tr("Protection has been enabled (demo mode only).")
        );
}

void ProtectionPage::onDisableProtectionClicked()
{
    m_protectionEnabled = false;
    updateUi();

    QMessageBox::information(
        this,
        tr("Protection disabled"),
        tr("Protection has been disabled (demo mode only).")
        );
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
