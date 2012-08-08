#include "NMPMain.h"
#include "process.h"
#include <wx/msgdlg.h>
#include <wx/dir.h>
#include <wx/icon.h>
#include <wx/stdpaths.h>

//(*InternalHeaders(NMPDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(NMPDialog)
const long NMPDialog::ID_STATICTEXT3 = wxNewId();
const long NMPDialog::ID_STATICTEXT6 = wxNewId();
const long NMPDialog::ID_BUTTON5 = wxNewId();
const long NMPDialog::ID_BUTTON6 = wxNewId();
const long NMPDialog::ID_STATICTEXT1 = wxNewId();
const long NMPDialog::ID_STATICTEXT4 = wxNewId();
const long NMPDialog::ID_BUTTON1 = wxNewId();
const long NMPDialog::ID_BUTTON2 = wxNewId();
const long NMPDialog::ID_STATICTEXT2 = wxNewId();
const long NMPDialog::ID_STATICTEXT5 = wxNewId();
const long NMPDialog::ID_BUTTON3 = wxNewId();
const long NMPDialog::ID_BUTTON4 = wxNewId();
const long NMPDialog::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(NMPDialog,wxDialog)
    //(*EventTable(NMPDialog)
    //*)
END_EVENT_TABLE()

NMPDialog::NMPDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(NMPDialog)
    wxFlexGridSizer* FlexGridSizer1;

    Create(parent, id, _("NMP Server"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxMINIMIZE_BOX, _T("id"));
    SetIcon(wxICON(APP_ICO));
    FlexGridSizer1 = new wxFlexGridSizer(3, 4, 0, 0);
    FlexGridSizer1->AddGrowableCol(2);
    StaticText_nginx = new wxStaticText(this, ID_STATICTEXT3, _("Nginx:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    wxFont StaticText_nginxFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText_nginx->SetFont(StaticText_nginxFont);
    FlexGridSizer1->Add(StaticText_nginx, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText_nginxStatus = new wxStaticText(this, ID_STATICTEXT6, _("Not Running..."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    StaticText_nginxStatus->SetForegroundColour(wxColour(255,0,0));
    wxFont StaticText_nginxStatusFont(10,wxSWISS,wxFONTSTYLE_ITALIC,wxNORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText_nginxStatus->SetFont(StaticText_nginxStatusFont);
    FlexGridSizer1->Add(StaticText_nginxStatus, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Button_nginxRun = new wxButton(this, ID_BUTTON5, _("Start"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    FlexGridSizer1->Add(Button_nginxRun, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_nginxConf = new wxButton(this, ID_BUTTON6, _("Configure..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    FlexGridSizer1->Add(Button_nginxConf, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText_mysql = new wxStaticText(this, ID_STATICTEXT1, _("MySQL:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    wxFont StaticText_mysqlFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText_mysql->SetFont(StaticText_mysqlFont);
    FlexGridSizer1->Add(StaticText_mysql, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText_mysqlStatus = new wxStaticText(this, ID_STATICTEXT4, _("Not Running..."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StaticText_mysqlStatus->SetForegroundColour(wxColour(255,0,0));
    wxFont StaticText_mysqlStatusFont(10,wxSWISS,wxFONTSTYLE_ITALIC,wxNORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText_mysqlStatus->SetFont(StaticText_mysqlStatusFont);
    FlexGridSizer1->Add(StaticText_mysqlStatus, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Button_MySQLRun = new wxButton(this, ID_BUTTON1, _("Start"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer1->Add(Button_MySQLRun, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_MySQLConf = new wxButton(this, ID_BUTTON2, _("Configure..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    FlexGridSizer1->Add(Button_MySQLConf, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText_php = new wxStaticText(this, ID_STATICTEXT2, _("PHP-CGI:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    wxFont StaticText_phpFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText_php->SetFont(StaticText_phpFont);
    FlexGridSizer1->Add(StaticText_php, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText_phpStatus = new wxStaticText(this, ID_STATICTEXT5, _("Not Running..."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    StaticText_phpStatus->SetForegroundColour(wxColour(255,0,0));
    wxFont StaticText_phpStatusFont(10,wxSWISS,wxFONTSTYLE_ITALIC,wxNORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText_phpStatus->SetFont(StaticText_phpStatusFont);
    FlexGridSizer1->Add(StaticText_phpStatus, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Button_phpRun = new wxButton(this, ID_BUTTON3, _("Start"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    FlexGridSizer1->Add(Button_phpRun, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_phpConf = new wxButton(this, ID_BUTTON4, _("Configure..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    FlexGridSizer1->Add(Button_phpConf, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    Timer_checkProcess.SetOwner(this, ID_TIMER1);
    Timer_checkProcess.Start(1000, false);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);
    Center();

    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NMPDialog::OnButton_nginxRunClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NMPDialog::OnButton_nginxConfClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NMPDialog::OnButton_MySQLRunClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NMPDialog::OnButton_MySQLConfClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NMPDialog::OnButton_phpRunClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NMPDialog::OnButton_phpConfClick);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&NMPDialog::OnTimer_checkProcessTrigger);
    Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&NMPDialog::OnInit);
    //*)
}

NMPDialog::~NMPDialog()
{
    //(*Destroy(NMPDialog)
    //*)
}

void NMPDialog::OnButton_MySQLRunClick(wxCommandEvent& event)
{
    if(Process::isProcessRunning(wxT("mysqld.exe")))
    {
        Process::killProcess(wxT("mysqld.exe"), 0);
    }
    else
    {
        Process::startProcess(mysqlExecutable);
    }
}

void NMPDialog::OnButton_MySQLConfClick(wxCommandEvent& event)
{
    wxExecute(heidiExecutable);
}

void NMPDialog::OnButton_phpRunClick(wxCommandEvent& event)
{
    if(Process::isProcessRunning(wxT("php-cgi.exe")))
    {
        Process::killProcess(wxT("php-cgi.exe"), 0);
    }
    else
    {
        Process::startProcess(phpExecutable + wxT("  -b 127.0.0.1:9000"));
    }
}

void NMPDialog::OnButton_phpConfClick(wxCommandEvent& event)
{
    wxExecute(wxT("notepad.exe ") + phpExecutable.BeforeLast('\\') + wxT("\\php.ini"));
}

void NMPDialog::OnButton_nginxRunClick(wxCommandEvent& event)
{
    if(Process::isProcessRunning(wxT("nginx.exe")))
    {
        Process::killProcess(wxT("nginx.exe"), 0);
    }
    else
    {
        Process::startProcess(nginxExecutable);
    }
}

void NMPDialog::OnButton_nginxConfClick(wxCommandEvent& event)
{
    wxExecute(wxT("notepad.exe ") + nginxExecutable.BeforeLast('\\') + wxT("\\conf\\nginx.conf"));
}

void NMPDialog::OnTimer_checkProcessTrigger(wxTimerEvent& event)
{
    bool mysql = false;
    bool php = false;
    bool nginx = false;

    wxArrayString ps = Process::getProcessList();

    for(wxUint32 i=0; i<ps.GetCount(); i++)
    {
        if(ps[i] == wxT("mysqld.exe"))
        {
            mysql = true;
        }
        if(ps[i] == wxT("php-cgi.exe"))
        {
            php = true;
        }
        if(ps[i] == wxT("nginx.exe"))
        {
            nginx = true;
        }
    }

    if(mysql)
    {
        StaticText_mysqlStatus->SetForegroundColour(wxColour(0,255,0));
        StaticText_mysqlStatus->SetLabel(wxT("Running..."));

        Button_MySQLRun->SetLabel(wxT("Kill"));
        Button_MySQLRun->Enable(true);
        if(heidiExecutable != wxEmptyString)
        {
            Button_MySQLConf->Enable(true);
        }
        else
        {
            Button_MySQLConf->Enable(false);
        }
    }
    else
    {
        StaticText_mysqlStatus->SetForegroundColour(wxColour(255,0,0));
        StaticText_mysqlStatus->SetLabel(wxT("Not Running..."));

        Button_MySQLRun->SetLabel(wxT("Start"));
        if(mysqlExecutable != wxEmptyString)
        {
            Button_MySQLRun->Enable(true);
            Button_MySQLConf->Enable(false);
        }
        else
        {
            Button_MySQLRun->Enable(false);
            Button_MySQLConf->Enable(false);
        }
    }

    if(php)
    {
        StaticText_phpStatus->SetForegroundColour(wxColour(0,255,0));
        StaticText_phpStatus->SetLabel(wxT("Running..."));

        Button_phpRun->SetLabel(wxT("Kill"));
        Button_phpRun->Enable(true);
        Button_phpConf->Enable(false);
    }
    else
    {
        StaticText_phpStatus->SetForegroundColour(wxColour(255,0,0));
        StaticText_phpStatus->SetLabel(wxT("Not Running..."));

        Button_phpRun->SetLabel(wxT("Start"));
        if(phpExecutable != wxEmptyString)
        {
            Button_phpRun->Enable(true);
            Button_phpConf->Enable(true);
        }
        else
        {
            Button_phpRun->Enable(false);
            Button_phpConf->Enable(false);
        }
    }

    if(nginx)
    {
        StaticText_nginxStatus->SetForegroundColour(wxColour(0,255,0));
        StaticText_nginxStatus->SetLabel(wxT("Running..."));

        Button_nginxRun->SetLabel(wxT("Kill"));
        Button_nginxRun->Enable(true);
        Button_nginxConf->Enable(false);
    }
    else
    {
        StaticText_nginxStatus->SetForegroundColour(wxColour(255,0,0));
        StaticText_nginxStatus->SetLabel(wxT("Not Running..."));

        Button_nginxRun->SetLabel(wxT("Start"));
        if(nginxExecutable != wxEmptyString)
        {
            Button_nginxRun->Enable(true);
            Button_nginxConf->Enable(true);
        }
        else
        {
            Button_nginxRun->Enable(false);
            Button_nginxConf->Enable(false);
        }
    }
}

void NMPDialog::OnInit(wxInitDialogEvent& event)
{
    Timer_checkProcess.Start();

    wxString cwd = wxStandardPaths::Get().GetExecutablePath().BeforeLast('\\') + wxT("\\");
    wxDir rootDir(cwd);
    wxString subDir;

    bool run = rootDir.GetFirst(&subDir);
    while(run)
    {
        // check if it is really a directory, or a file
        if(wxDirExists(cwd + subDir))
        {
            // check if directory contains "mysql"
            if(subDir.Contains(wxT("mysql")) && wxFileExists(cwd + subDir + wxT("\\bin\\mysqld.exe")))
            {
                mysqlExecutable = cwd + subDir + wxT("\\bin\\mysqld.exe");
            }

            // check if directory contains "php"
            if(subDir.Contains(wxT("php")) && wxFileExists(cwd + subDir + wxT("\\php-cgi.exe")))
            {
                phpExecutable = cwd + subDir + wxT("\\php-cgi.exe");
            }

            // check if directory contains "nginx"
            if(subDir.Contains(wxT("nginx")) && wxFileExists(cwd + subDir + wxT("\\nginx.exe")))
            {
                nginxExecutable = cwd + subDir + wxT("\\nginx.exe");
            }

            // check if directory contains "heidi"
            if(subDir.Contains(wxT("heidi")) && wxFileExists(cwd + subDir + wxT("\\heidisql.exe")))
            {
                heidiExecutable = cwd + subDir + wxT("\\heidisql.exe");
            }
        }

        run = rootDir.GetNext(&subDir);
    }

    if(mysqlExecutable == wxEmptyString)
    {
        wxMessageBox(wxT("File not Found:\n") + cwd + subDir + wxT("\\bin\\mysqld.exe"));
    }

    if(phpExecutable == wxEmptyString)
    {
        wxMessageBox(wxT("File not Found:\n") + cwd + subDir + wxT("\\php-cgi.exe"));
    }

    if(nginxExecutable == wxEmptyString)
    {
        wxMessageBox(wxT("File not Found:\n") + cwd + subDir + wxT("\\nginx.exe"));
    }

    if(heidiExecutable == wxEmptyString)
    {
        wxMessageBox(wxT("File not Found:\n") + cwd + subDir + wxT("\\heidisql.exe"));
    }
}
