#pragma once

//TODO CHANGE FONT & COLOR OF WINDOW
//TODO ADD TABS WITH CHILD GUI ELEMENTS

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

  private:
    
    void init();
    void loadFonts();
    void update(Window& window);
    

    bool m_initialized;
    std::vector<GuiElement::Element*> *m_guiElements;
};
