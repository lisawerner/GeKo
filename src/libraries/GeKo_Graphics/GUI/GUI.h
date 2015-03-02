#pragma once

#include <string>
#include <stdio.h>
#include <imgui.h>

///This Class sets up a GUI and offers methods to create its elements

class GUI
{
  public:
    ///Constructor
    GUI();
    ///Destructor
    ~GUI();
 
    ///set GUI Font - fileName has to be only the fileName "Example.ttf". The Font File needs to be in "./Resources/Fonts"
    void setFont(std::string &fileName, float size);
   
    //ImDrawList getCommandList();
    //int getCommandListSize();

  private:

};