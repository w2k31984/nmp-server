#include "NMPApp.h"

//(*AppHeaders
#include "NMPMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(NMPApp);

bool NMPApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	NMPDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;
}
