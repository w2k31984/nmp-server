#ifndef NMPMAIN_H
#define NMPMAIN_H

//(*Headers(NMPDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/timer.h>
//*)

class NMPDialog: public wxDialog
{
    public:

        NMPDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~NMPDialog();

    private:

        //(*Handlers(NMPDialog)
        void OnButton_MySQLRunClick(wxCommandEvent& event);
        void OnButton_MySQLConfClick(wxCommandEvent& event);
        void OnButton_phpRunClick(wxCommandEvent& event);
        void OnButton_phpConfClick(wxCommandEvent& event);
        void OnButton_nginxRunClick(wxCommandEvent& event);
        void OnButton_nginxConfClick(wxCommandEvent& event);
        void OnTimer_checkProcessTrigger(wxTimerEvent& event);
        void OnInit(wxInitDialogEvent& event);
        //*)

        //(*Identifiers(NMPDialog)
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT6;
        static const long ID_BUTTON5;
        static const long ID_BUTTON6;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT4;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT5;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_TIMER1;
        //*)

        //(*Declarations(NMPDialog)
        wxTimer Timer_checkProcess;
        wxButton* Button_MySQLRun;
        wxStaticText* StaticText_php;
        wxStaticText* StaticText_mysql;
        wxStaticText* StaticText_nginxStatus;
        wxStaticText* StaticText_nginx;
        wxStaticText* StaticText_phpStatus;
        wxButton* Button_MySQLConf;
        wxButton* Button_phpRun;
        wxButton* Button_nginxRun;
        wxButton* Button_phpConf;
        wxStaticText* StaticText_mysqlStatus;
        wxButton* Button_nginxConf;
        //*)

        DECLARE_EVENT_TABLE()

        wxString mysqlExecutable;
        wxString phpExecutable;
        wxString nginxExecutable;
        wxString heidiExecutable;
};

#endif // NMPMAIN_H
