#include <wx/string.h>
#include <wx/process.h>

class Process
{
    public:

        Process();
        virtual ~Process();

    public:

        static void startProcess(wxString executableFile);
        static void killProcess(wxString processName, wxUint32 exitCode);
        static wxArrayString getProcessList();
        static bool isProcessRunning(wxString processName);
};
