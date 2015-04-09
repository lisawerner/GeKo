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
    GUI(std::string windowName, int windowWidth = 200, int windowHeight = 100);
    ///Destructor
    ~GUI();
 
    void render(Window& window);
    void addElement(GuiElement::Element *comp);
    void addNestedWindow(GuiElement::NestedWindow *nestedWindow);
    void show();
    void hide();
    bool visible();
    void setBackgroundAlpha(float a);
    void setPosition(float posX, float posY);
    void setTitleBarVisible(bool visible);
    void setMoveable(bool moveable);
    void setBorderVisible(bool visible);
    void setResizable(bool resize);
    void setUseScrollbar(bool scrollbar);
    void setCollapsable(bool collapse);
    
	std::string m_windowName;
  protected:
    
    void init();
    void loadFonts();
    void update(Window& window);

    bool m_initialized;
    bool m_visible;

   
    int m_windowWidth, m_windowHeight;
    float m_windowPosX, m_windowPosY;
    float m_bgAlpha;
    bool m_titlebar;
    bool m_border;
    bool m_resize;
    bool m_move;
    bool m_scrollbar;
    bool m_collapse;

    std::vector<GuiElement::Element*> *m_guiElements;
    std::vector<GuiElement::NestedWindow*> *m_nestedWindows;
};
