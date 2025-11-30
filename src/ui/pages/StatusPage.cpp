#include "StatusPage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QPushButton>

StatusPage::StatusPage(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
    updateDummyStatus();
}

void StatusPage::setupUi()
{
    auto *rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(8, 8, 8, 8);
    rootLayout->setSpacing(10);

    // Page title + subtitle
    auto *titleLabel = new QLabel(tr("System overview"), this);
    titleLabel->setObjectName("SectionTitle");

    auto *subtitleLabel = new QLabel(
        tr("Summary of protection state and recent activity for this computer."),
        this
        );
    subtitleLabel->setObjectName("SectionSubTitle");

    rootLayout->addWidget(titleLabel);
    rootLayout->addWidget(subtitleLabel);

    //
    // Row 1: three compact metric cards
    //
    auto *metricRow = new QHBoxLayout();
    metricRow->setSpacing(12);

    // Card 1: Protection state
    auto *stateCard = new QFrame(this);
    stateCard->setObjectName("Card");
    auto *stateLayout = new QVBoxLayout(stateCard);
    stateLayout->setContentsMargins(14, 14, 14, 14);
    stateLayout->setSpacing(6);

    auto *stateTitle = new QLabel(tr("Protection state"), stateCard);
    stateTitle->setObjectName("SectionSubTitle");

    m_protectionStatusLabel = new QLabel(stateCard);
    m_protectionStatusLabel->setWordWrap(true);

    stateLayout->addWidget(stateTitle);
    stateLayout->addWidget(m_protectionStatusLabel);
    stateLayout->addStretch();

    // Card 2: Protected target
    auto *targetCard = new QFrame(this);
    targetCard->setObjectName("Card");
    auto *targetLayout = new QVBoxLayout(targetCard);
    targetLayout->setContentsMargins(14, 14, 14, 14);
    targetLayout->setSpacing(6);

    auto *targetTitle = new QLabel(tr("Protected target"), targetCard);
    targetTitle->setObjectName("SectionSubTitle");

    m_protectedPathLabel = new QLabel(targetCard);
    m_protectedPathLabel->setWordWrap(true);

    auto *targetHint = new QLabel(
        tr("Example: system drive C:\\ or a shared student profile folder."),
        targetCard
        );
    targetHint->setObjectName("SectionSubTitle");
    targetHint->setWordWrap(true);

    targetLayout->addWidget(targetTitle);
    targetLayout->addWidget(m_protectedPathLabel);
    targetLayout->addWidget(targetHint);
    targetLayout->addStretch();

    // Card 3: Last reset & counters
    auto *activityCard = new QFrame(this);
    activityCard->setObjectName("Card");
    auto *activityLayout = new QVBoxLayout(activityCard);
    activityLayout->setContentsMargins(14, 14, 14, 14);
    activityLayout->setSpacing(6);

    auto *activityTitle = new QLabel(tr("Last reset & activity"), activityCard);
    activityTitle->setObjectName("SectionSubTitle");

    m_lastResetLabel = new QLabel(activityCard);
    m_lastResetLabel->setWordWrap(true);

    m_blockedCountLabel = new QLabel(activityCard);
    m_allowedCountLabel = new QLabel(activityCard);

    activityLayout->addWidget(activityTitle);
    activityLayout->addWidget(m_lastResetLabel);
    activityLayout->addSpacing(4);
    activityLayout->addWidget(m_blockedCountLabel);
    activityLayout->addWidget(m_allowedCountLabel);
    activityLayout->addStretch();

    metricRow->addWidget(stateCard,   1);
    metricRow->addWidget(targetCard,  1);
    metricRow->addWidget(activityCard,1);

    rootLayout->addLayout(metricRow);

    //
    // Row 2: full-width card with explanation + refresh button
    //
    auto *detailCard = new QFrame(this);
    detailCard->setObjectName("Card");
    auto *detailLayout = new QVBoxLayout(detailCard);
    detailLayout->setContentsMargins(16, 16, 16, 16);
    detailLayout->setSpacing(10);

    auto *detailTitle = new QLabel(tr("What does this mean?"), detailCard);
    detailTitle->setObjectName("SectionTitle");

    auto *detailText = new QLabel(
        tr("CleanState is designed for classrooms and labs: after each reboot, "
           "the system returns to a known good state. The dashboard above shows "
           "whether protection is active, which location is guarded, and how many "
           "potentially dangerous operations were blocked during this session "
           "(demo data only at this stage)."),
        detailCard
        );
    detailText->setObjectName("SectionSubTitle");
    detailText->setWordWrap(true);

    auto *buttonRow = new QHBoxLayout();
    auto *refreshButton = new QPushButton(tr("Refresh status"), detailCard);
    buttonRow->addWidget(refreshButton);
    buttonRow->addStretch();

    connect(refreshButton, &QPushButton::clicked,
            this, &StatusPage::onRefreshClicked);

    detailLayout->addWidget(detailTitle);
    detailLayout->addWidget(detailText);
    detailLayout->addSpacing(8);
    detailLayout->addLayout(buttonRow);

    rootLayout->addWidget(detailCard);
    rootLayout->addStretch(1);

    setLayout(rootLayout);
}

void StatusPage::updateDummyStatus()
{
    // In final version, these values will come from the service / driver.

    m_protectionStatusLabel->setText(
        tr("<b style='color:#F97316;'>Demo mode – service not connected</b>")
        );

    m_protectedPathLabel->setText(
        tr("<i>No path selected yet</i>")
        );

    m_lastResetLabel->setText(
        tr("Last reset: <i>Not performed in demo mode</i>")
        );

    // Demo counters to make page look alive
    m_blockedCountLabel->setText(
        tr("Blocked operations this session: <b>3</b>")
        );
    m_allowedCountLabel->setText(
        tr("Allowed operations this session: <b>42</b>")
        );
}

void StatusPage::onRefreshClicked()
{
    // For now just re-apply the same demo data.
    // Later this will query real statistics from the service.
    updateDummyStatus();
}
