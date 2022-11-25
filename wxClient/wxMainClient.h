#pragma once
#define CURL_STATICLIB
#define ADDRESS_TEXT_ID 1001
#define GO_BUTTON_ID 1002
#define HTML_SOURCE_ID 1003
#define WEB_VIEW_ID 1004

#include "wx\wx.h"
#include "wx\html\htmlwin.h"
#include "wx\aui\framemanager.h"
#include "curl.h"

using namespace std;


class wxMainClient : public wxFrame
{
public:
	wxMainClient();
	~wxMainClient();

private:
	wxPanel* bottompanel = nullptr;
	wxPanel* toppanel = nullptr;
	//wxBoxSizer* topsizer = nullptr;
	wxHtmlWindow* webView = nullptr;
	wxToolBar* toolbar = nullptr;
	wxTextCtrl* address = nullptr;
	wxTextCtrl* htmlSource = nullptr;
	wxButton* gobutton = nullptr;
	wxAuiManager auiManager;

	void init();
	void loadPage();

	void OnGoBtnClicked(wxCommandEvent &evt);

	wxDECLARE_EVENT_TABLE();
};

