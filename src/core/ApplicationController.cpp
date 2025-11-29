#include "ApplicationController.h"
#include "ui/MainWindow.h"

ApplicationController::ApplicationController()
{
    m_mainWindow = std::make_unique<MainWindow>();
}

ApplicationController::~ApplicationController() = default;

void ApplicationController::showMainWindow()
{
    if (m_mainWindow) {
        m_mainWindow->show();
    }
}
