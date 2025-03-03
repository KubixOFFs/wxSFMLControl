#include <wx/wx.h>
#include <SFML/Graphics.hpp>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
};

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

class SFMLCanvas : public wxControl
{
public:
    SFMLCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
        : wxControl(parent, id, pos, size, wxBORDER_NONE)
    {
        SetBackgroundStyle(wxBG_STYLE_PAINT);
        sfWindow = new sf::RenderWindow((sf::WindowHandle)GetHandle());
        Bind(wxEVT_IDLE, &SFMLCanvas::OnIdle, this);
    }

    void OnIdle(wxIdleEvent& event)
    {
        while (auto sfEvent = sfWindow->pollEvent()) // SFML 3.0 zwraca std::optional<sf::Event>
        {
            if (sfEvent->is<sf::Event::Closed>()) // ✅ Nowe API SFML 3.0
            {
                Close();
            }
        }

        sfWindow->clear(sf::Color::Blue);
        sfWindow->display();

        event.RequestMore(); // Zapewnia ciągłe odświeżanie
    }

private:
    sf::RenderWindow* sfWindow;
};

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "wxWidgets + SFML", wxDefaultPosition, wxSize(800, 600))
{
    new SFMLCanvas(this, wxID_ANY, wxPoint(10, 10), wxSize(400, 400));
}

wxIMPLEMENT_APP(MyApp);
