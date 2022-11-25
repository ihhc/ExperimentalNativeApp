#include "wxAppClient.h"

wxIMPLEMENT_APP(wxAppClient);

wxAppClient::wxAppClient()
{
}

wxAppClient::~wxAppClient()
{
}

bool wxAppClient::OnInit()
{
	mainFrame = new wxMainClient();
	return mainFrame->Show();
}
