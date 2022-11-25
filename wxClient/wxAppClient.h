#pragma once
#include "wx\wx.h"
#include "wxMainClient.h"

class wxAppClient : public wxApp
{
public:
	wxAppClient();
	~wxAppClient();
private:
	wxMainClient* mainFrame = nullptr;
public:
	virtual bool OnInit();
};

