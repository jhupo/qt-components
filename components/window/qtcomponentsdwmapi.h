#ifndef __QTCOMPONENTSDWMAPI_H__
#define __QTCOMPONENTSDWMAPI_H__

#include "components_global.h"

#include <QObject>
#include <QWidget>
#include <QCoreApplication>
#include <QAbstractNativeEventFilter>

#ifdef Q_OS_WIN
#include <Windows.h>
#if defined(WINVER) && defined(_WIN32_WINNT)
    #if (WINVER >= 0x0600) && (_WIN32_WINNT >= 0x0600)
        #define DWM_AVAILABLE
        #include <WinUser.h>
        #pragma comment (lib,"dwmapi.lib")
        #pragma comment (lib,"user32.lib")
    #endif
#endif
#endif

namespace Components {

#ifdef DWM_AVAILABLE
static HMODULE _dwmapi_library = LoadLibraryW(L"dwmapi.dll");
typedef struct _MARGINS{int l;int t;int r;int b;} MARGINS, *PMARGINS;
typedef HRESULT(WINAPI* DwmExtendFrameIntoClientAreaPtr)(HWND hWnd, const MARGINS *pMarInset);
inline COMPONENTS_EXPORT void extendFrameIntoClientArea(QWidget* window, int left, int top, int right, int bottom){
    DwmExtendFrameIntoClientAreaPtr dwm_extendframe_into_client_area_ = \
            reinterpret_cast<DwmExtendFrameIntoClientAreaPtr>(GetProcAddress(_dwmapi_library, "DwmExtendFrameIntoClientArea"));
    if(dwm_extendframe_into_client_area_){
        MARGINS margins = {left, right, top, bottom};
        dwm_extendframe_into_client_area_(reinterpret_cast<HWND>(window->winId()), &margins);
    }
}
inline COMPONENTS_EXPORT void extendFrameIntoStyle(QWidget* window){
    HWND hwnd = reinterpret_cast<HWND>(window->winId());
    DWORD style = GetWindowLong(hwnd, GWL_STYLE);
    SetWindowLong(hwnd,GWL_STYLE,style|WS_CAPTION);
}
class COMPONENTS_EXPORT QtDwmapiNativeEventFilter : public QAbstractNativeEventFilter{
public:
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *result){
        Q_UNUSED(eventType);
        MSG* msg = reinterpret_cast<MSG*>(message);
        if(WM_NCCALCSIZE == msg->message){
            *result = 0;
            return true;
        }
        return false;
    }
};
static QtDwmapiNativeEventFilter _dwm_filter;
#endif

}


#endif
