#include "wxMainClient.h"

BEGIN_EVENT_TABLE(wxMainClient, wxFrame)
	EVT_BUTTON(GO_BUTTON_ID, OnGoBtnClicked)
END_EVENT_TABLE()

wxMainClient::wxMainClient() : wxFrame(nullptr, wxID_ANY, "HTTPClient", wxDefaultPosition, wxSize(800, 600))
{	
	hrSplitter = new wxSplitterWindow(this, wxID_ANY, wxPoint(0, 0),	wxSize(800, 600), wxSP_3D);
	webView = new wxHtmlWindow(hrSplitter, WEB_VIEW_ID);
	htmlSource = new wxTextCtrl(hrSplitter, HTML_SOURCE_ID, wxEmptyString,	wxDefaultPosition, wxDefaultSize,	0 | wxTE_AUTO_URL | wxTE_MULTILINE | wxTE_READONLY);
	hrSplitter->Initialize(webView);
	hrSplitter->SplitHorizontally(webView, htmlSource);
	initBars();
}
//

void wxMainClient::initBars()
{
	toolbar = this->CreateToolBar(wxTB_HORIZONTAL, wxID_ANY);
	address = new wxTextCtrl(toolbar, ADDRESS_TEXT_ID, "https://www.youtube.com/", wxDefaultPosition, wxSize(700, 20));
	toolbar->AddControl(address);
	gobutton = new wxButton(toolbar, GO_BUTTON_ID, "Go");
	toolbar->AddControl(gobutton);
	toolbar->Realize();
	statusBar = this->CreateStatusBar();
}

wxMainClient::~wxMainClient()
{
}


size_t wxMainClient::write_data(void* ptr, size_t size, size_t mem, void* param)
{
	string& text = *static_cast<string*>(param);
	size_t tsize = size * mem;
	text.append(static_cast<char*>(ptr), tsize);
	return tsize;
}

void wxMainClient::clearOut() 
{
	webView->SetPage("<!DOCTYPE html><HTML><BODY><p>No data to display</p></BODY></HTML>");
	htmlSource->Clear();
	statusBar->SetStatusText("");
}

void wxMainClient::loadPage()
{
	clearOut();
	curl_global_init(CURL_GLOBAL_DEFAULT);
	CURL* curl = curl_easy_init();
	if (curl)
	{
		string data;
		curl_easy_setopt(curl, CURLOPT_URL, static_cast<string>(address->GetValue()).c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		CURLcode res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (data.size())
		{
			webView->SetPage(data);
			htmlSource->AppendText(static_cast<wxString>(data));
			statusBar->SetStatusText(address->GetValue());
		}
	}	
	curl_global_cleanup();
}

void wxMainClient::OnGoBtnClicked(wxCommandEvent& evt)
{
	loadPage();
}
