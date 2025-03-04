#include <wx/wx.h>
#include <SFML/Graphics.hpp>
#include <wx/sfmlcanvas.h>

// Klasa MyApp dziedzicząca po wxApp
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

// Klasa MyFrame dziedzicząca po wxFrame
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

private:
    void OnPaint(wxPaintEvent& event);
    wxSFMLCanvas* m_sfmlCanvas;
};

// Klasa wxSFMLCanvas dziedzicząca po wxControl i sf::RenderWindow
class wxSFMLCanvas : public wxControl, public sf::RenderWindow
{
public:
    wxSFMLCanvas(wxWindow* parent, wxWindowID id, const wxPoint& position, const wxSize& size, long style = 0)
        : wxControl(parent, id, position, size, style)
    {
        // Utworzenie SFML RenderWindow
        sf::RenderWindow::create(GetHandle());
    }

protected:
    void OnUpdate()
    {
        // Czyszczenie ekranu
        clear(sf::Color::White);

        // Rysowanie zielonego koła
        sf::CircleShape circle(50.f);
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(100.f, 100.f);
        draw(circle);

        // Wyświetlanie zawartości
        display();
    }

    void OnIdle(wxIdleEvent& event)
    {
        // Aktualizacja zawartości w stanie bezczynności
        OnUpdate();
        event.RequestMore();
    }

private:
    void OnPaint(wxPaintEvent& event)
    {
        // Aktualizacja zawartości w zdarzeniu paint
        OnUpdate();
    }

    wxDECLARE_EVENT_TABLE();
};

// Rejestracja zdarzeń dla klasy wxSFMLCanvas
wxBEGIN_EVENT_TABLE(wxSFMLCanvas, wxControl)
    EVT_IDLE(wxSFMLCanvas::OnIdle)
    EVT_PAINT(wxSFMLCanvas::OnPaint)
wxEND_EVENT_TABLE()

// Implementacja metody OnInit klasy MyApp
bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame("wxWidgets and SFML Integration");
    frame->Show(true);
    return true;
}

// Implementacja konstruktora klasy MyFrame
MyFrame::MyFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
    // Utworzenie kontrolki wxSFMLCanvas
    m_sfmlCanvas = new wxSFMLCanvas(this, wxID_ANY, wxPoint(0, 0), GetClientSize());
}

// Implementacja zdarzenia paint dla klasy MyFrame
void MyFrame::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
}

// Implementacja metody wxIMPLEMENT_APP dla klasy MyApp
wxIMPLEMENT_APP(MyApp);


---------------------------------------- wxSFMLCanvas.h
#ifndef WX_SFML_CANVAS_H
#define WX_SFML_CANVAS_H

#include <wx/wx.h>
#include <SFML/Graphics.hpp>

// Klasa wxSFMLCanvas dziedzicząca po wxControl i sf::RenderWindow
class wxSFMLCanvas : public wxControl, public sf::RenderWindow
{
public:
    wxSFMLCanvas(wxWindow* parent, wxWindowID id, const wxPoint& position, const wxSize& size, long style = 0);

protected:
    void OnUpdate();
    void OnIdle(wxIdleEvent& event);
    void OnPaint(wxPaintEvent& event);

private:
    wxDECLARE_EVENT_TABLE();
};

#endif // WX_SFML_CANVAS_H


---------------------------------- wxSFMLCanvas.cpp

#include "wxSFMLCanvas.h"

// Rejestracja zdarzeń dla klasy wxSFMLCanvas
wxBEGIN_EVENT_TABLE(wxSFMLCanvas, wxControl)
    EVT_IDLE(wxSFMLCanvas::OnIdle)
    EVT_PAINT(wxSFMLCanvas::OnPaint)
wxEND_EVENT_TABLE()

wxSFMLCanvas::wxSFMLCanvas(wxWindow* parent, wxWindowID id, const wxPoint& position, const wxSize& size, long style)
    : wxControl(parent, id, position, size, style)
{
    // Utworzenie SFML RenderWindow
    sf::RenderWindow::create(GetHandle());
}

void wxSFMLCanvas::OnUpdate()
{
    // Czyszczenie ekranu
    clear(sf::Color::White);

    // Rysowanie zielonego koła
    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(100.f, 100.f);
    draw(circle);

    // Wyświetlanie zawartości
    display();
}

void wxSFMLCanvas::OnIdle(wxIdleEvent& event)
{
    // Aktualizacja zawartości w stanie bezczynności
    OnUpdate();
    event.RequestMore();
}

void wxSFMLCanvas::OnPaint(wxPaintEvent& event)
{
    // Aktualizacja zawartości w zdarzeniu paint
    OnUpdate();
}
