#include "LogsPage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QTableWidgetItem>

LogsPage::LogsPage(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
    populateDummyLogs();
}

void LogsPage::setupUi()
{
    auto *rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(8, 8, 8, 8);
    rootLayout->setSpacing(10);

    auto *titleLabel = new QLabel(tr("Activity logs"), this);
    titleLabel->setObjectName("SectionTitle");

    auto *subtitleLabel = new QLabel(
        tr("Demo entries showing which processes tried to access protected paths."),
        this
        );
    subtitleLabel->setObjectName("SectionSubTitle");

    rootLayout->addWidget(titleLabel);
    rootLayout->addWidget(subtitleLabel);

    auto *card = new QFrame(this);
    card->setObjectName("Card");
    auto *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(12, 12, 12, 12);
    cardLayout->setSpacing(8);

    auto *topRow = new QHBoxLayout();
    topRow->addStretch();
    auto *btnRefresh = new QPushButton(tr("Refresh"), card);
    auto *btnClear   = new QPushButton(tr("Clear"), card);
    topRow->addWidget(btnRefresh);
    topRow->addWidget(btnClear);

    connect(btnRefresh, &QPushButton::clicked, this, &LogsPage::onRefreshClicked);
    connect(btnClear,   &QPushButton::clicked, this, &LogsPage::onClearClicked);

    m_table = new QTableWidget(card);
    m_table->setColumnCount(4);
    m_table->setHorizontalHeaderLabels(
        { tr("Time"), tr("Process"), tr("Operation"), tr("Path") }
        );
    m_table->horizontalHeader()->setStretchLastSection(true);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->verticalHeader()->setVisible(false);   // <<< hide grey row-number column

    cardLayout->addLayout(topRow);
    cardLayout->addWidget(m_table);

    rootLayout->addWidget(card, 1);
}

void LogsPage::populateDummyLogs()
{
    m_table->setRowCount(3);

    m_table->setItem(0, 0, new QTableWidgetItem("2025-11-29 14:20"));
    m_table->setItem(0, 1, new QTableWidgetItem("explorer.exe"));
    m_table->setItem(0, 2, new QTableWidgetItem("Delete (blocked)"));
    m_table->setItem(0, 3, new QTableWidgetItem("C:\\Windows\\System32\\kernel32.dll"));

    m_table->setItem(1, 0, new QTableWidgetItem("2025-11-29 14:22"));
    m_table->setItem(1, 1, new QTableWidgetItem("chrome.exe"));
    m_table->setItem(1, 2, new QTableWidgetItem("Write (allowed)"));
    m_table->setItem(1, 3, new QTableWidgetItem("C:\\Users\\Student\\Downloads\\file.exe"));

    m_table->setItem(2, 0, new QTableWidgetItem("2025-11-29 14:25"));
    m_table->setItem(2, 1, new QTableWidgetItem("python.exe"));
    m_table->setItem(2, 2, new QTableWidgetItem("Create (logged)"));
    m_table->setItem(2, 3, new QTableWidgetItem("C:\\Users\\Student\\AppData\\Local\\Temp\\script.tmp"));
}

void LogsPage::onClearClicked()
{
    m_table->setRowCount(0);
}

void LogsPage::onRefreshClicked()
{
    m_table->setRowCount(0);
    populateDummyLogs();
}
