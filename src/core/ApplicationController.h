#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <memory>

class MainWindow;

/**
 * Central controller of the application.
 * For now it only owns MainWindow, later it can:
 *  - connect to Windows service
 *  - manage settings
 *  - manage logging, etc.
 */
class ApplicationController
{
public:
    ApplicationController();
    ~ApplicationController();

    void showMainWindow();

private:
    std::unique_ptr<MainWindow> m_mainWindow;
};

#endif // APPLICATIONCONTROLLER_H
