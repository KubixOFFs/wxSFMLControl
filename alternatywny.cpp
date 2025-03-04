#include <wx/wx.h>
#include <wx/timer.h>
#include <SFML/Graphics.hpp>

class SFMLCanvas : public wxControl {
private:
    sf::RenderTexture renderTexture;
    sf::Sprite sprite;
    sf::CircleShape circle;
    wxTimer timer;
    bool initialized = false;

public:
    SFMLCanvas(wxWindow* parent, wxWindowID id)
        : wxControl(parent, id, wxDefaultPosition, wxSize(400, 300), wxWANTS_CHARS),
          timer(this), circle(50.0f) {

        SetBackgroundStyle(wxBG_STYLE_PAINT);

        // Ustawienie koła
        circle.setFillColor(sf::Color::Green);
        circle.setRadius(50.0f);
        circle.setOrigin(circle.getRadius(), circle.getRadius());
        circle.setPosition(200, 150);  

        Bind(wxEVT_PAINT, &SFMLCanvas::OnPaint, this);
        Bind(wxEVT_SIZE, &SFMLCanvas::OnSize, this);
        Bind(wxEVT_TIMER, &SFMLCanvas::OnTimer, this);
        Bind(wxEVT_ERASE_BACKGROUND, &SFMLCanvas::OnEraseBackground, this);

        timer.Start(16);
    }

    void InitializeSFML() {
        if (initialized) return;
        wxSize size = GetClientSize();
        renderTexture.create(size.x, size.y);
        sprite.setTexture(renderTexture.getTexture());
        initialized = true;
    }

    void OnPaint(wxPaintEvent&) {
        wxPaintDC dc(this);
        InitializeSFML();

        // Rysowanie SFML na teksturze
        renderTexture.clear(sf::Color::Black);
        renderTexture.draw(circle);
        renderTexture.display();

        // Pobranie tekstury SFML jako obraz wxWidgets
        sf::Image sfmlImage = renderTexture.getTexture().copyToImage();
        wxImage wxImg(sfmlImage.getSize().x, sfmlImage.getSize().y, sfmlImage.getPixelsPtr(), true);
        wxBitmap wxBmp(wxImg);

        // Rysowanie w wxWidgets
        dc.DrawBitmap(wxBmp, 0, 0);
    }

    void OnSize(wxSizeEvent& event) {
        if (initialized) {
            wxSize size = GetClientSize();
            renderTexture.create(size.x, size.y);
            sprite.setTexture(renderTexture.getTexture(), true);
        }
        event.Skip();
    }

    void OnTimer(wxTimerEvent&) {
        Refresh();
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
