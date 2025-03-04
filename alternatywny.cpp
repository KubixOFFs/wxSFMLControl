#include <wx/wx.h>
#include <SFML/Graphics.hpp>

class SFMLCanvas : public wxControl {
private:
    sf::RenderTexture renderTexture;
    wxBitmap wxBmp;
    bool initialized = false;

public:
    SFMLCanvas(wxWindow* parent, wxWindowID id)
        : wxControl(parent, id, wxDefaultPosition, wxSize(400, 300), wxWANTS_CHARS) {

        SetBackgroundStyle(wxBG_STYLE_PAINT);

        Bind(wxEVT_PAINT, &SFMLCanvas::OnPaint, this);
        Bind(wxEVT_SIZE, &SFMLCanvas::OnSize, this);
        Bind(wxEVT_ERASE_BACKGROUND, &SFMLCanvas::OnEraseBackground, this);
    }

    void InitializeSFML() {
        if (initialized) return;
        wxSize size = GetClientSize();
        if (size.x <= 0 || size.y <= 0) return;

        // Tworzymy teksturę do rysowania SFML
        renderTexture.create(size.x, size.y);

        // Rysujemy grafikę SFML tylko raz
        renderTexture.clear(sf::Color::Black);
        
        sf::CircleShape circle(50.0f);
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(size.x / 2 - 50, size.y / 2 - 50);
        
        renderTexture.draw(circle);
        renderTexture.display();

        // Konwersja tekstury SFML do wxWidgets
        sf::Image sfmlImage = renderTexture.getTexture().copyToImage();
        wxImage wxImg(sfmlImage.getSize().x, sfmlImage.getSize().y, sfmlImage.getPixelsPtr(), true);
        wxBmp = wxBitmap(wxImg);

        initialized = true;
    }

    void OnPaint(wxPaintEvent&) {
        wxPaintDC dc(this);
        InitializeSFML();  // Jeśli to pierwsze rysowanie, generujemy grafikę SFML
        if (wxBmp.IsOk()) {
            dc.DrawBitmap(wxBmp, 0, 0);
        }
    }

    void OnSize(wxSizeEvent& event) {
        initialized = false;  // Jeśli zmieniamy rozmiar, trzeba wygenerować nową grafikę
        Refresh();
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
