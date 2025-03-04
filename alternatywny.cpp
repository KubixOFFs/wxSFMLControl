#include <wx/wx.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Klasa głównego okna aplikacji
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title)
        : wxFrame(nullptr, wxID_ANY, title)
    {
        // Tworzymy panel, który będzie hostował SFML
        panel = new wxPanel(this, wxID_ANY);

        // Ustawiamy rozmiar panelu
        panel->SetSize(400, 400);

        // Tworzymy okno SFML, przekazując uchwyt panelu
        sf::RenderWindow sfmlWindow;
        sfmlWindow.create(panel->GetHandle());
while (sfmlWindow.isOpen())
{
    // Obsługa zdarzeń SFML
    if (auto event = sfmlWindow.poll_event(); event)
    {
        if (event->type == sf::Event::Closed)
            sfmlWindow.close();
    }

            // Czyszczenie ekranu
            sfmlWindow.clear();

            // Rysowanie zielonego kwadratu
            sf::RectangleShape rectangle(sf::Vector2f(100.0f, 100.0f));
            rectangle.setFillColor(sf::Color::Green);
            rectangle.setPosition(150.0f, 150.0f);
            sfmlWindow.draw(rectangle);

            // Wyświetlenie zawartości
            sfmlWindow.display();
        }
    }

private:
    wxPanel* panel;
};

// Klasa aplikacji wxWidgets
class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        MyFrame* frame = new MyFrame("SFML w wxWidgets");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
