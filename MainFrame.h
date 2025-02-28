#pragma once

// Very basic MainFrame class declaration couse it's only example code

#include <wx/wx.h>
#include "wxSFMLControl.h"

// Inheriting from wxFrame
class MainFrame : public wxFrame
{
public:
    // Default using wxFrame constructor
    MainFrame();

private:
    // Declaration of ours custom control as a pointer
    wxSFMLControl* m_canvas;
};
