#pragma once

//TODO CHANGE FONT & COLOR OF WINDOW
//TODO ADD TABS WITH CHILD GUI ELEMENTS
//TODO MOUSE SCROLL INPUT
//TODO DESTRUCTORS

#include <string>
#include <vector>
#include <stdio.h>
#include "GUIComponents.hpp"

class Window;

///This Class sets up a GUI and offers methods to create its elements

class GUI
{
  public:
    ///Constructor
    GUI();
    ///Destructor
    ~GUI();
 
    void render(Window& window);
    void addElement(GuiElement::Element *comp);
    void show();
    void hide();

  private:
    
    void init();
    void loadFonts();
    void update(Window& window);
    

    bool m_initialized;
    bool m_visible;
    std::vector<GuiElement::Element*> *m_guiElements;
};
