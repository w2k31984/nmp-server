#include "process.h"
#include <windows.h>
#include <psapi.h>

wxString getProcessName(HANDLE hProcess)
{
    if(hProcess != NULL)
    {
        HMODULE hMod;
        DWORD cmNeeded;
        wchar_t szProcessName[MAX_PATH] = L"<unknown>";

        //Given a handle to a process, this returns all the modules running within the process.
        //The first module is the executable running the process,
        //and subsequent handles describe DLLs loaded into the process.
        if(EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cmNeeded))
        {
            //This function returns the short name for a module,
            //typically the file name portion of the EXE or DLL
            GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(TCHAR));
            return wxString(szProcessName);
        }
    }

    return wxEmptyString;
}

Process::Process()
{
    //
}

Process::~Process()
{
    //
}

void Process::startProcess(wxString executableFile)
{
    wxString cwd = wxGetCwd();
    wxSetWorkingDirectory(executableFile.BeforeLast('\\'));

    wxProcess* tmp = new wxProcess();
    tmp->Connect(wxEVT_END_PROCESS, NULL); // prevents program crash when external application is killed
    tmp->Redirect();
    tmp->Connect(wxEVT_END_PROCESS, NULL);
    wxExecute(executableFile, wxEXEC_ASYNC, tmp);

    wxSetWorkingDirectory(cwd);
}

void Process::killProcess(wxString processName, wxUint32 exitCode)
{
    //wxProcess::Open(wxT("taskkill.exe /f /im ") + processName, wxEXEC_ASYNC | wxEXEC_NODISABLE);

    // Get the list of process identifiers.
    DWORD aProcesses[1024], cbNeeded, cProcesses, pid;

    //This returns a list of handles to processes running on the system as an array.
    if(EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
    {
        // Calculate how many process identifiers were returned.
        cProcesses = cbNeeded / sizeof(DWORD);

        // Display the name and process identifier for each process.
        for(unsigned int i = 0; i<cProcesses; i++)
        {
            if(aProcesses[i] != 0)
            {
                pid = aProcesses[i];
                HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE, FALSE, pid);
                if(getProcessName(hProcess) == processName)
                {
                    TerminateProcess(hProcess, 1);
                }
                CloseHandle(hProcess);
            }
        }
    }
}

wxArrayString Process::getProcessList()
{
    wxArrayString procList;

    // Get the list of process identifiers.
    DWORD aProcesses[1024], cbNeeded, cProcesses, pid;

    //This returns a list of handles to processes running on the system as an array.
    if(EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
    {
        // Calculate how many process identifiers were returned.
        cProcesses = cbNeeded / sizeof(DWORD);

        // Display the name and process identifier for each process.
        for(unsigned int i = 0; i<cProcesses; i++)
        {
            if(aProcesses[i] != 0)
            {
                pid = aProcesses[i];
                HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
                procList.Add(getProcessName(hProcess));
                CloseHandle(hProcess);
            }
        }
    }

    return procList;
}

bool Process::isProcessRunning(wxString processName)
{
    wxArrayString ps = getProcessList();

    for(wxUint32 i=0; i<ps.GetCount(); i++)
    {
        if(ps[i] == processName)
        {
            return true;
        }
    }

    return false;
}
