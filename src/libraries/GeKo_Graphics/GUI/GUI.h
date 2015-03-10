#pragma once

//FIX BUG WITH TOGGLE BUTTONS

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
    GUI(std::string windowName, int windowWidth, int windowHeight);
    ///Destructor
    ~GUI();
 
    void render(Window& window);
    void addElement(GuiElement::Element *comp);
    void show();
    void hide();
    bool visible();

  private:
    
    void init();
    void loadFonts();
    void update(Window& window);

    bool m_initialized;
    bool m_visible;

    std::string m_windowName;
    int m_windowWidth, m_windowHeight;

    std::vector<GuiElement::Element*> *m_guiElements;
};
