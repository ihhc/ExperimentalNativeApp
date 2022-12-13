#pragma once
#define CURL_STATICLIB
#define ADDRESS_TEXT_ID 1001
#define GO_BUTTON_ID 1002
#define HTML_SOURCE_ID 1003
#define WEB_VIEW_ID 1004

#include "wx\wx.h"
#include "wx\html\htmlwin.h"
#include "wx\aui\framemanager.h"
#include "wx\splitter.h"
#include "curl.h"

using namespace std;


class wxMainClient : public wxFrame
{
public:
	wxMainClient();
	~wxMainClient();

private:
	wxToolBar* toolbar = nullptr;
	wxTextCtrl* address = nullptr;
	wxButton* gobutton = nullptr;
	wxHtmlWindow* webView = nullptr;
	wxTextCtrl* htmlSource = nullptr;
	wxSplitterWindow* hrSplitter = nullptr;
	wxStatusBar* statusBar = nullptr;

	void initBars();
	void loadPage();
	void clearOut();
	static size_t write_data(void* ptr, size_t size, size_t mem, void* param);

	void OnGoBtnClicked(wxCommandEvent &evt);

	DECLARE_EVENT_TABLE();
};

