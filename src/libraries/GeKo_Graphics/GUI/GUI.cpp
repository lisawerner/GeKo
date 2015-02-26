#include "GUI.h"

#include<iostream>

GUI::GUI()
{
 
}

GUI::~GUI()
{
  
}

void GUI::setFont(std::string &fileName, float size)
{
   /*
  ImGuiIO& io = ImGui::GetIO();
  io.Fonts->AddFontFromFileTTF("myfontfile.ttf", size);

  //Add a third parameter to bake specific font ranges :

  io.Fonts->LoadFromFileTTF("myfontfile.ttf", size, io.Fonts->GetGlyphRangesDefault());   // Basic Latin, Extended Latin 
  io.Fonts->LoadFromFileTTF("myfontfile.ttf", size, io.Fonts->GetGlyphRangesJapanese());  // Default + Hiragana, Katakana, Half-Width, Selection of 1946 Ideographs
  io.Fonts->LoadFromFileTTF("myfontfile.ttf", size, io.Fonts->GetGlyphRangesChinese());   // Include full set of about 21000 CJK Unified Ideographs

  //Offset font by altering the io.Font->DisplayOffset value :

  ImFont* font = io.Fonts->AddFontFromFileTTF(RESOURCES_PATH + std::string("/") + fileName, size);

  if (!font)
  {
    std::cout << "ERROR IN GUI::LOADFONT!" << std::endl;
    std::cout << "Font " << fileName <<   " couldnt be loaded - put the TTF File in the Resources/Fonts Folder and give this methode just the file name, not the whole path" << std::endl;
  }

  font->DisplayOffset.y += 1;   // Render 1 pixel down
  */
}
