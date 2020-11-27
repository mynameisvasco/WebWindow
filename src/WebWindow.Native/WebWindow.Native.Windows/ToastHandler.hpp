#include <wintoastlib.h>
#include <WinUser.h>
#include <WebWindow.h>

using namespace WinToastLib;

class ToastHandler : public IWinToastHandler
{
private:
    WebWindow *_webwindow;

public:
    ToastHandler(WebWindow *webwindow)
    {
        this->_webwindow = webwindow;
    }

    void toastActivated() const
    {
        ShowWindow(this->_webwindow->getHwnd(), SW_SHOW);    // Make the window visible if it was hidden
        ShowWindow(this->_webwindow->getHwnd(), SW_RESTORE); // Next, restore it if it was minimized
        SetForegroundWindow(this->_webwindow->getHwnd());    // Finally, activate the window
    }

    void toastActivated(int actionIndex) const
    {
        //
    }

    void toastDismissed(WinToastDismissalReason state) const
    {
        //
    }

    void toastFailed() const
    {
        //
    }
};
