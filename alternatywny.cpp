#include <wx/wx.h>
#include <wx/timer.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class SFMLCanvas : public wxControl {
private:
    std::unique_ptr<sf::RenderWindow> renderWindow;
    wxTimer timer;
    sf::CircleShape circle;

public:
    SFMLCanvas(wxWindow* parent, wxWindowID id)
        : wxControl(parent, id, wxDefaultPosition, wxSize(400, 300), wxWANTS_CHARS),
          timer(this), circle(50.0f) {  // Tworzymy zielone koło

        circle.setFillColor(sf::Color::Green);
        circle.setPosition(100, 100);

        // Pobranie uchwytu okna i stworzenie SFML RenderWindow
        sf::WindowHandle handle = GetHandle();
        renderWindow = std::make_unique<sf::RenderWindow>(handle);

        // Wiązanie eventów za pomocą Bind()
        Bind(wxEVT_TIMER, &SFMLCanvas::OnTimer, this);
        Bind(wxEVT_SIZE, &SFMLCanvas::OnSize, this);
        Bind(wxEVT_ERASE_BACKGROUND, &SFMLCanvas::OnEraseBackground, this);

        // Timer do odświeżania renderowania
        timer.Start(16);  // Około 60 FPS
    }

    void OnTimer(wxTimerEvent&) {
        if (!renderWindow) return;

        ProcessEvents();
        renderWindow->clear(sf::Color::Black);  // Tło czarne
        renderWindow->draw(circle);  // Rysowanie koła
        renderWindow->display();
    }

    void ProcessEvents() {
        sf::Event event;
        while (renderWindow->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                renderWindow->close();
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
