#include "PhpConfigDialog.h"

//(*InternalHeaders(PhpConfigDialog)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//(*IdInit(PhpConfigDialog)
const long PhpConfigDialog::ID_LISTCTRL1 = wxNewId();
const long PhpConfigDialog::ID_TEXTCTRL1 = wxNewId();
const long PhpConfigDialog::ID_TEXTCTRL2 = wxNewId();
const long PhpConfigDialog::ID_BITMAPBUTTON1 = wxNewId();
const long PhpConfigDialog::ID_BITMAPBUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PhpConfigDialog,wxDialog)
	//(*EventTable(PhpConfigDialog)
	//*)
END_EVENT_TABLE()

PhpConfigDialog::PhpConfigDialog(wxString File, wxWindow* parent, wxWindowID id)
{
	//(*Initialize(PhpConfigDialog)
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("Configuration Editor"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	ListCtrlEntries = new wxListCtrl(this, ID_LISTCTRL1, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("ID_LISTCTRL1"));
	ListCtrlEntries->SetMinSize(wxSize(480,320));
	ListCtrlEntries->InsertColumn(0, wxT("Key"));
	ListCtrlEntries->InsertColumn(1, wxT("Value"));
	FlexGridSizer1->Add(ListCtrlEntries, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 5, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	FlexGridSizer2->AddGrowableCol(1);
	TextCtrlKey = new wxTextCtrl(this, ID_TEXTCTRL1, _("Key"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer2->Add(TextCtrlKey, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlValue = new wxTextCtrl(this, ID_TEXTCTRL2, _("Value"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer2->Add(TextCtrlValue, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BitmapButtonAdd = new wxBitmapButton(this, ID_BITMAPBUTTON1, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW")),wxART_BUTTON), wxDefaultPosition, wxSize(24,24), 0, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	BitmapButtonAdd->SetDefault();
	BitmapButtonAdd->SetToolTip(_("Add New Entry"));
	FlexGridSizer2->Add(BitmapButtonAdd, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BitmapButtonDelete = new wxBitmapButton(this, ID_BITMAPBUTTON2, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_CROSS_MARK")),wxART_BUTTON), wxDefaultPosition, wxSize(24,24), 0, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
	BitmapButtonDelete->SetDefault();
	BitmapButtonDelete->SetToolTip(_("Delete Current Entry"));
	FlexGridSizer2->Add(BitmapButtonDelete, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	Center();

	Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&PhpConfigDialog::OnListCtrlEntriesItemSelect);
	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PhpConfigDialog::OnTextCtrlUpdate);
	Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PhpConfigDialog::OnTextCtrlUpdate);
	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PhpConfigDialog::OnBitmapButtonAddClick);
	Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PhpConfigDialog::OnBitmapButtonDeleteClick);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&PhpConfigDialog::OnClose);
	Connect(wxEVT_SIZE,(wxObjectEventFunction)&PhpConfigDialog::OnResize);
	//*)

	wxSizeEvent se;
	OnResize(se);
	ConfigurationFile = File;
	LoadFile(File);
}

PhpConfigDialog::~PhpConfigDialog()
{
	//(*Destroy(PhpConfigDialog)
	//*)
}

void PhpConfigDialog::LoadFile(wxString File)
{
    wxTextFile f;

    if(wxFileExists(File) && f.Open(File))
    {
    	wxUint32 index;
        wxString line = f.GetFirstLine();

        while(!f.Eof())
		{
			line.Replace(wxT(" "), wxT(""));
			line.Replace(wxT("\t"), wxT(""));

			if(!line.StartsWith(wxT(";")))
			{
				if(line.StartsWith(wxT("[")))
				{
					// ignore sections
				}
				if(line.Find(wxT("=")) > -1)
				{
					// remove comments behind
					line = line.BeforeFirst(';');
					index = ListCtrlEntries->GetItemCount();
					ListCtrlEntries->InsertItem(index, wxT(""));
					ListCtrlEntries->SetItem(index, 0, line.BeforeFirst('='));
					ListCtrlEntries->SetItem(index, 1, line.AfterFirst('='));
				}
			}
            line = f.GetNextLine();
        }

        f.Close();
    }
}

void PhpConfigDialog::SaveFile(wxString File)
{
    wxTextFile f;
	wxListItem li;
	wxString line;

    // create file, or open if already exists
    if(!f.Create(File))
    {
        f.Open(File);
        f.Clear();
    }

    f.AddLine(wxT("; Generated by NMP - Configuration Editor"));
    for(wxInt32 i=0; i<ListCtrlEntries->GetItemCount(); i++)
    {
		li.m_itemId = i;
		li.m_mask = wxLIST_MASK_TEXT;
		li.m_col = 0;
		ListCtrlEntries->GetItem(li);
		line = li.m_text + wxT(" = ");
		li.m_col = 1;
		ListCtrlEntries->GetItem(li);
		line.Append(li.m_text);

        f.AddLine(line);
    }

    f.Write();
    f.Close();
}

void PhpConfigDialog::OnListCtrlEntriesItemSelect(wxListEvent& event)
{
	Disconnect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PhpConfigDialog::OnTextCtrlUpdate);
	Disconnect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PhpConfigDialog::OnTextCtrlUpdate);

	wxInt32 index = event.GetIndex(); //ListCtrlEntries->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

	if(index > -1)
	{
		wxListItem li;
		li.m_itemId = index;
		li.m_mask = wxLIST_MASK_TEXT;
		li.m_col = 0;
		ListCtrlEntries->GetItem(li);
		TextCtrlKey->SetValue(li.m_text);
		li.m_col = 1;
		ListCtrlEntries->GetItem(li);
		TextCtrlValue->SetValue(li.m_text);
	}
	else
	{
		TextCtrlKey->Clear();
		TextCtrlValue->Clear();
	}

	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PhpConfigDialog::OnTextCtrlUpdate);
	Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PhpConfigDialog::OnTextCtrlUpdate);
}

void PhpConfigDialog::OnTextCtrlUpdate(wxCommandEvent& event)
{
	wxUint32 index = ListCtrlEntries->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	ListCtrlEntries->SetItem(index, 0, TextCtrlKey->GetValue());
	ListCtrlEntries->SetItem(index, 1, TextCtrlValue->GetValue());
}

void PhpConfigDialog::OnBitmapButtonAddClick(wxCommandEvent& event)
{
	wxUint32 index = ListCtrlEntries->GetItemCount();
	ListCtrlEntries->InsertItem(index, wxT(""));
	ListCtrlEntries->SetItem(index, 0, TextCtrlKey->GetValue());
	ListCtrlEntries->SetItem(index, 1, TextCtrlValue->GetValue());

	ListCtrlEntries->SetItemState(index, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
	ListCtrlEntries->EnsureVisible(index);
}

void PhpConfigDialog::OnBitmapButtonDeleteClick(wxCommandEvent& event)
{
	wxUint32 index = ListCtrlEntries->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	ListCtrlEntries->DeleteItem(index);
}

void PhpConfigDialog::OnResize(wxSizeEvent& event)
{
	Layout();
    // always assume scrollbar, never use GetClientSize
    wxInt32 halfWidth = (ListCtrlEntries->GetSize().GetWidth()-24)/2;
    ListCtrlEntries->SetColumnWidth(0, halfWidth);
    ListCtrlEntries->SetColumnWidth(1, halfWidth);
}

void PhpConfigDialog::OnClose(wxCloseEvent& event)
{
	if(wxMessageBox(wxT("Save Changes to File?"), wxT("Hint"), wxYES_NO) == wxYES)
	{
		SaveFile(ConfigurationFile);
	}
	Destroy();
}