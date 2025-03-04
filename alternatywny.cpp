class SFMLCanvas : public wxControl {
private:
    std::unique_ptr<sf::RenderWindow> renderWindow;
    wxTimer timer;

public:
    SFMLCanvas(wxWindow* parent, wxWindowID id)
        : wxControl(parent, id, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS), timer(this) {
        
        // Pobranie uchwytu okna (SFML potrzebuje HWND na Windowsie)
        sf::WindowHandle handle = GetHandle();
        
        // Tworzenie SFML RenderWindow
        renderWindow = std::make_unique<sf::RenderWindow>(handle);

        // Uruchomienie timera do odświeżania renderowania
        timer.Bind(wxEVT_TIMER, &SFMLCanvas::OnTimer, this);
        timer.Start(16);  // ~60 FPS
    }

    void OnTimer(wxTimerEvent&) {
        if (renderWindow) {
            renderWindow->clear(sf::Color::Black);
            // Rysowanie SFML
            renderWindow->display();
        }
    }

    void OnPaint(wxPaintEvent&) {
        wxPaintDC dc(this);
        if (renderWindow) {
            renderWindow->setActive(true);  // Upewnij się, że SFML ma aktywny kontekst
            renderWindow->display();
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

    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(SFMLCanvas, wxControl)
    EVT_PAINT(SFMLCanvas::OnPaint)
    EVT_SIZE(SFMLCanvas::OnSize)
    EVT_ERASE_BACKGROUND(SFMLCanvas::OnEraseBackground)
wxEND_EVENT_TABLE()



void ProcessEvents() {
    sf::Event event;
    while (renderWindow->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            renderWindow->close();
        }
    }
}
