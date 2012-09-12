#ifndef PHPCONFIGDIALOG_H
#define PHPCONFIGDIALOG_H

//(*Headers(PhpConfigDialog)
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/bmpbuttn.h>
#include <wx/dialog.h>
//*)

#include <wx/msgdlg.h>
#include <wx/textfile.h>

class PhpConfigDialog: public wxDialog
{
	public:

		PhpConfigDialog(wxString File, wxWindow* parent=NULL, wxWindowID id=wxID_ANY);
		virtual ~PhpConfigDialog();

		//(*Declarations(PhpConfigDialog)
		wxListCtrl* ListCtrlEntries;
		wxTextCtrl* TextCtrlKey;
		wxBitmapButton* BitmapButtonAdd;
		wxBitmapButton* BitmapButtonDelete;
		wxTextCtrl* TextCtrlValue;
		//*)

	protected:

		//(*Identifiers(PhpConfigDialog)
		static const long ID_LISTCTRL1;
		static const long ID_TEXTCTRL1;
		static const long ID_TEXTCTRL2;
		static const long ID_BITMAPBUTTON1;
		static const long ID_BITMAPBUTTON2;
		//*)

		private: wxString ConfigurationFile;

	private:

		//(*Handlers(PhpConfigDialog)
		void OnListCtrlEntriesItemSelect(wxListEvent& event);
		void OnTextCtrlUpdate(wxCommandEvent& event);
		void OnBitmapButtonAddClick(wxCommandEvent& event);
		void OnBitmapButtonDeleteClick(wxCommandEvent& event);
		void OnResize(wxSizeEvent& event);
		//*)

		public: void LoadFile(wxString File);
		public: void SaveFile(wxString File);

		DECLARE_EVENT_TABLE()
};

#endif
