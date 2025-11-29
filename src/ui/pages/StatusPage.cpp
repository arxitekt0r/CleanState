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

    auto *titleLabel = new QLabel(tr("System overview"), this);
    titleLabel->setObjectName("SectionTitle");

    auto *subtitleLabel = new QLabel(
        tr("Current protection state and last reset information."),
        this
        );
    subtitleLabel->setObjectName("SectionSubTitle");

    auto *headerLayout = new QVBoxLayout();
    headerLayout->setSpacing(2);
    headerLayout->addWidget(titleLabel);
    headerLayout->addWidget(subtitleLabel);

    rootLayout->addLayout(headerLayout);

    // Card with status info
    auto *card = new QFrame(this);
    card->setObjectName("Card");
    auto *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(16, 16, 16, 16);
    cardLayout->setSpacing(10);

    m_protectionStatusLabel = new QLabel(card);
    m_protectedPathLabel = new QLabel(card);
    m_lastResetLabel = new QLabel(card);

    m_protectionStatusLabel->setWordWrap(true);
    m_protectedPathLabel->setWordWrap(true);
    m_lastResetLabel->setWordWrap(true);

    cardLayout->addWidget(m_protectionStatusLabel);
    cardLayout->addWidget(m_protectedPathLabel);
    cardLayout->addWidget(m_lastResetLabel);

    auto *buttonRow = new QHBoxLayout();
    auto *refreshButton = new QPushButton(tr("Refresh status"), card);
    buttonRow->addWidget(refreshButton);
    buttonRow->addStretch();

    connect(refreshButton, &QPushButton::clicked,
            this, &StatusPage::onRefreshClicked);

    cardLayout->addSpacing(8);
    cardLayout->addLayout(buttonRow);

    rootLayout->addWidget(card);
    rootLayout->addStretch(1);

    setLayout(rootLayout);
}

void StatusPage::updateDummyStatus()
{
    // Demo text for now
    m_protectionStatusLabel->setText(
        tr("Protection status: "
           "<b style='color:#F97316;'>Demo mode – not connected to service</b>")
        );

    m_protectedPathLabel->setText(
        tr("Protected target: <i>Not configured yet</i>")
        );

    m_lastResetLabel->setText(
        tr("Last reset: <i>N/A</i>")
        );
}

void StatusPage::onRefreshClicked()
{
    updateDummyStatus();
}
