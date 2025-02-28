// Here is the place where the magic happend

#include "wxSFMLControl.h"


// implementation of constructor
wxSFMLControl::wxSFMLControl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxControl(parent, id, pos, size, wxBORDER_NONE) //using wxControl constructor to creata control
{
    // this one setting will avoid screen flickering when SFML drawing stuff
    // and let the SFML to dispal his stuff as a background of control
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    // binding ours event OnIdle
    Bind(wxEVT_IDLE, &wxSFMLControl::OnIdle, this);
}

    // destructor implementation
wxSFMLControl::~wxSFMLControl()
{   
    // if there is ours custom control initialized we need to
    // relase memory that we reserved for control
    if (m_sfmlWindow)
    {
        // closing control
        m_sfmlWindow->close();
        // relasing space
        delete m_sfmlWindow;
    }
}
    
    // definition of initializating method
void wxSFMLControl::InitSFML()
{
    // let's check if ours control isn't initialized yet
    // we using ours property from SFMLCanvas class which is set as true when the control is initialized
    if (m_initialized) return;//                                                                    |
    //                                                                                              |
    // there is the way how to integrate SFML and wxWidgets                                         |
    // use RenderWindow constructor with native wxControl Handle                                    |
    // and let the control acces to RenderWindow interface                                          |
    sf::RenderWindow* sfWindow = new sf::RenderWindow((sf::WindowHandle)GetHandle());//             |
    //                                                                                              |
    // if there is problem with create sfWinfow return the method                                   |
    if (!sfWindow) return; //                                                                       |
    //                                                                                              |
    // set up ours SFMLControl                                                                      |
    m_sfmlWindow = sfWindow;//                                                                      |
    // set up property as initialized                                                               |
    m_initialized = true;//         <---------------------------------------------------------------+
}
    // Render method
void wxSFMLControl::Render()
{
    // if there is no initialized control - let's do it!
    if (!m_initialized)
        InitSFML();
    // if cannot initialize control we need to leave :(
    if (!m_sfmlWindow) return;

    // set control as active - sometimes we need to let the SFML to know            here
    // the that window is the current one where to OpenGL contest is open            we
    m_sfmlWindow->setActive(true);//                                                using
    // lets clear the window with bluea color                                       SFML
    m_sfmlWindow->clear(sf::Color::Blue);//                                       interface

    // and finally we can draw something
    // here is an example with green circle
    // but basicly this is the place for SFML specific code
    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({50,50});
    m_sfmlWindow->draw(shape);
    // display some stuff on ours handled control!
    m_sfmlWindow->display();
}

// remember ours custom OnIdle declaration?
void wxSFMLControl::OnIdle(wxIdleEvent& event)
{
    // the shrot code which just use render method when nothing happend
    Render();
    // be sure to use OnIdle again when there is no other events in ours control to ensure smooth refreshing
    event.RequestMore();
}
