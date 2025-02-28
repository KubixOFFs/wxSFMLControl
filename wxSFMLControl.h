#pragma once

// Class declaration file of ours custom wxSFMLControl

#include <wx/wx.h>          // including some needed stuff
#include <wx/control.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>  //


//                      Inheriting only from wxControl
//                      do not inherite from sf::RenderWindow
//                      like on the tutorial from SFML/Learn 1.6 sample
//                      inheriting from sf::RenderWindow will cause a struggle to manage events in between wxWidgets event loop and SFML event loop
class wxSFMLControl : public wxControl
{
public:
    // declare parametric constructor set the position and size as const to avoid errors
    wxSFMLControl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);
    // declare destructor
    ~wxSFMLControl();
    
    // ours render method - remember to !!declare it as public method!!
    // we will need it to draw some stuff in ours control
    void Render();
    // this is ours custom OnIdle event  
    void OnIdle(wxIdleEvent& event); // OnIdle is was called when all events have been handled and no new event occurs - the loop is idle

private:
    // there is the solution how to put SFML interface to wxControl
    // create pointer for sf::RenderWindow - the rest is in the .cpp file
    sf::RenderWindow* m_sfmlWindow;
    
    // variable to be sure that custom control is inicialized
    bool m_initialized = false;
    
    // method which inicialize ours custom control
    void InitSFML();
};
