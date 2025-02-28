#include "MainFrame.h"

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "SFML w wxWidgets", wxDefaultPosition, wxSize(800, 600))
{
    // Add some wxSizer and wxPanel to manage size and position of the Control couse wxWidgets default set the best size for the control 
    // when the control is alone in ui the best size i full free space of the window
    wxPanel* panel = new wxPanel(this);//                   <----+
    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);//               |
    //                                                           |
    // Creating ours new custom Control !!remember to set ours panel as a parent!!
    m_canvas = new wxSFMLControl(panel, wxID_ANY, wxPoint(10, 10), wxSize(200, 200));
    
    // You can add MaxSize to be sure
    // m_canvas->SetMaxSize(wxSize(200, 200));

    // Add ours control to sizer and let him to manage it
    sizer->Add(m_canvas, 0, wxALIGN_CENTER | wxALL, 10);
    // Set sizer to ours panel
    panel->SetSizer(sizer);
}
