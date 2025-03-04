#include <wx/wx.h>
#include <wx/timer.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class SFMLCanvas : public wxControl {
private:
    std::unique_ptr<sf::RenderWindow> renderWindow;
    wxTimer timer;
    sf::CircleShape circle;
    bool initialized = false;

public:
    SFMLCanvas(wxWindow* parent, wxWindowID id)
        : wxControl(parent, id, wxDefaultPosition, wxSize(400, 300), wxWANTS_CHARS),
          timer(this), circle(50.0f) {  

        SetBackgroundStyle(wxBG_STYLE_CUSTOM);  

        circle.setFillColor(sf::Color::Green);
        circle.setPosition(100, 100);

        Bind(wxEVT_SIZE, &SFMLCanvas::OnSize, this);
        Bind(wxEVT_ERASE_BACKGROUND, &SFMLCanvas::OnEraseBackground, this);
        Bind(wxEVT_IDLE, &SFMLCanvas::OnIdle, this);

        timer.Start(16);  
    }

    void InitializeSFML() {
        if (initialized) return;
        sf::WindowHandle handle = GetHandle();
        renderWindow = std::make_unique<sf::RenderWindow>(handle);
        renderWindow->setActive(true);
        initialized = true;
    }

    void OnIdle(wxIdleEvent&) {
        InitializeSFML();

        if (!renderWindow) return;

        renderWindow->setActive(true);
        renderWindow->clear(sf::Color::Black);
        renderWindow->draw(circle);
        renderWindow->display();

        wxMilliSleep(16);  // Unikamy nadmiernego zużycia CPU
        Refresh();  // Wymuszamy kolejne odświeżenie
    }

    void OnSize(wxSizeEvent& event) {
        if (renderWindow) {
            wxSize size = GetClientSize();
            renderWindow->setSize(sf::Vector2u(size.x, size.y));
        }
        event.Skip();
    }

    void OnEraseBackground(wxEraseEvent&) {}  
};

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "SFML w wxWidgets", wxDefaultPosition, wxSize(800, 600));
        new SFMLCanvas(frame, wxID_ANY);
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
