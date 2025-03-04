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

        SetBackgroundStyle(wxBG_STYLE_PAINT);  // Kluczowe! Zapobiega migotaniu

        circle.setFillColor(sf::Color::Green);
        circle.setRadius(50.0f);
        circle.setOrigin(circle.getRadius(), circle.getRadius());  // Ustawienie środka koła
        circle.setPosition(200, 150);  // Środek okna

        Bind(wxEVT_PAINT, &SFMLCanvas::OnPaint, this);
        Bind(wxEVT_SIZE, &SFMLCanvas::OnSize, this);
        Bind(wxEVT_ERASE_BACKGROUND, &SFMLCanvas::OnEraseBackground, this);
        Bind(wxEVT_TIMER, &SFMLCanvas::OnTimer, this);

        timer.Start(16);  // Około 60 FPS
    }

    void InitializeSFML() {
        if (initialized) return;
        sf::WindowHandle handle = GetHandle();
        renderWindow = std::make_unique<sf::RenderWindow>(handle);
        renderWindow->setActive(true);
        initialized = true;
    }

    void OnPaint(wxPaintEvent&) {
        wxClientDC dc(this);  // Konieczne dla poprawnego rysowania wxWidgets
        InitializeSFML();  

        if (!renderWindow) return;

        renderWindow->setActive(true);
        renderWindow->clear(sf::Color::Black);
        renderWindow->draw(circle);
        renderWindow->display();
    }

    void OnTimer(wxTimerEvent&) {
        if (!renderWindow) return;
        ProcessEvents();
        Refresh();  // Wymuszenie wywołania OnPaint()
    }

    void ProcessEvents() {
       while (auto sfEvent = sfWindow->pollEvent()) // SFML 3.0 zwraca std::optional<sf::Event>
{
    if (sfEvent->is<sf::Event::Closed>()) //  Nowe API SFML 3.0
    {
        Close();
    }
}
    }

    void OnSize(wxSizeEvent& event) {
        if (renderWindow) {
            wxSize size = GetClientSize();
            renderWindow->setSize(sf::Vector2u(size.x, size.y));
        }
        event.Skip();
    }

    void OnEraseBackground(wxEraseEvent&) {}  // Zapobiega migotaniu
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
