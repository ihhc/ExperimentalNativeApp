#include "wxMainClient.h"

wxBEGIN_EVENT_TABLE(wxMainClient, wxFrame)
	//EVT_BUTTON(BUTTONOKID, OnGoBtnClicked)
wxEND_EVENT_TABLE()

wxMainClient::wxMainClient() : wxFrame(nullptr, wxID_ANY, "HTTPClient")
{
	auiManager.SetManagedWindow(this);
	webView = new wxHtmlWindow(this, WEB_VIEW_ID);
	htmlSource = new wxTextCtrl(this, HTML_SOURCE_ID);
	auiManager.AddPane(webView, wxTOP);
	auiManager.AddPane(htmlSource, wxBOTTOM);
	auiManager.Update();
	//topsizer = new wxBoxSizer(wxHORIZONTAL);
	//panel->SetSizer(topsizer);
	init();
	CreateStatusBar();
}
//

void wxMainClient::init()
{
	//topsizer->Add(webView, 1, wxEXPAND | wxALL, 0);
	toolbar = this->CreateToolBar(wxTB_HORIZONTAL, wxID_ANY);
	address = new wxTextCtrl(toolbar, ADDRESS_TEXT_ID);
	address->AppendText("https://www.youtube.com/");
	toolbar->AddControl(address);
	gobutton = new wxButton(toolbar, GO_BUTTON_ID, "Go");
	gobutton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxMainClient::OnGoBtnClicked), nullptr, this);
	toolbar->AddControl(gobutton);
	toolbar->Realize();
}

wxMainClient::~wxMainClient()
{
}


static size_t write_data(void* ptr, size_t size, size_t mem, void* param)
{
	string& text = *static_cast<string*>(param);
	size_t tsize = size * mem;
	text.append(static_cast<char*>(ptr), tsize);
	return tsize;
}

void wxMainClient::loadPage()
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
	string data;
	CURL* curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, static_cast<string>(address->GetValue()).c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		CURLcode res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		webView->SetPage(data);
		htmlSource->SetValue(data.c_str());
		//evt.Skip();
	}	
	curl_global_cleanup();
}

void wxMainClient::OnGoBtnClicked(wxCommandEvent& evt)
{
	loadPage();
}
