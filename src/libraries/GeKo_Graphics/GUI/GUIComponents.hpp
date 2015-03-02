#pragma once
#include<string>
#include<imgui.h>

///These Classes are wrapper classes for the ImGui Render methods

namespace GuiElement
{
  class Element
  {
  public:
    Element() {}
    ~Element() {}

    virtual void render() = 0;
  };

  class Text : public Element
  {
  
  public:
    Text(std::string text) : m_text(text) {}
    inline void render() { ImGui::Text(m_text.c_str()); }

  private:
    std::string m_text;
  };

  class SliderFloat : public Element
  {

  public:
    SliderFloat(std::string ID, float *parameter, float min, float max) : m_parameter(parameter), m_min(min), m_max(max) {}
    inline void render() { ImGui::SliderFloat(ID.c_str(), m_parameter, m_min, m_max); }

  private:
    std::string ID;
    float *m_parameter, m_min, m_max;
  };

};