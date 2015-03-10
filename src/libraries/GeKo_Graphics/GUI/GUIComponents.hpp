#pragma once
#include<string>
#include<imgui.h>
#include<glm/ext.hpp>

///These Classes are wrapper classes for the ImGui Render methods

namespace GuiElement
{
  class Element
  {
  public:
    Element() {}
    ~Element() {}

    virtual void render() = 0;
    virtual void dispose() = 0;

  private:
  };

  class Text : public Element
  {
  
  public:
    Text(std::string text) : m_text(text) {}
    inline void render() { ImGui::Text(m_text.c_str()); }
    inline void dispose() { Text::~Text(); }

  private:
    ~Text() {}

    std::string m_text;

  };

  class SliderFloat : public Element
  {

  public:
    SliderFloat(std::string ID, float *parameter, float min, float max) : m_ID(ID), m_parameter(parameter), m_min(min), m_max(max) {}
    inline void render() { ImGui::SliderFloat(m_ID.c_str(), m_parameter, m_min, m_max); }
    inline void dispose() { SliderFloat::~SliderFloat(); }

  private:
    ~SliderFloat() {}

    std::string m_ID;
    float *m_parameter, m_min, m_max;
  };

  class Header : public Element
  {
  public:
    Header(std::string ID) : m_ID(ID) { }
    inline void render()
    {
      if (ImGui::CollapsingHeader(m_ID.c_str())) 
        for (std::vector<Element*>::iterator it = m_childElements.begin(); it != m_childElements.end(); ++it)
          (*it)->render(); 
    }

    inline void addElement(Element *child) { m_childElements.push_back(child); }
    inline void dispose() { Header::~Header(); }

  private:
    ~Header() 
    { 
      for(std::vector<Element*>::iterator it = m_childElements.begin(); it != m_childElements.end(); ++it)
        (*it)->dispose();
    }

    std::string m_ID;
    std::vector<Element*> m_childElements;

  };

  class Spacing : public Element
  {
  public:
    Spacing() {}
    inline void render() { ImGui::Spacing(); }
    inline void dispose() { Spacing::~Spacing(); }

  private:
    ~Spacing() {}

  };

  class Separator : public Element
  {
  public:
    Separator() {}
    inline void render() { ImGui::Separator(); }
    inline void dispose() { Separator::~Separator(); }

  private:
    ~Separator() {}

  };

  class SameLine : public Element
  {
  public:
    SameLine() {}
    inline void render() { ImGui::SameLine(); }
    inline void dispose() { SameLine::~SameLine(); }

  private:
    ~SameLine() {}

  };

  class PushButton : public Element
  {
  public:
    PushButton(std::string ID) : m_isPushed(false), m_ID(ID) {}
    inline void render() { m_isPushed = ImGui::Button(m_ID.c_str()); }
    inline bool isPushed() { return m_isPushed; }
    inline void dispose() { PushButton::~PushButton(); };

  private:
    ~PushButton() {}

    bool m_isPushed;
    std::string m_ID;
  };

  class ToggleButton : public Element
  {
  public:
    ToggleButton(bool startValue = false, std::string activeText = "on", std::string inactiveText = "off") : m_isActive(startValue), m_ActiveString(activeText), m_InactiveString(inactiveText)  {}
    inline void render() 
    {
      if (m_isActive)
      {
        if (ImGui::Button(m_ActiveString.c_str()))
          m_isActive = false;
      }

      else
      {
        if (ImGui::Button(m_InactiveString.c_str()))
          m_isActive = true;
      }
    }
    
    inline bool isActive() { return m_isActive; }
    inline void dispose() { ToggleButton::~ToggleButton(); };

  private:
    ~ToggleButton() {}

    bool m_isActive;
    std::string m_ActiveString;
    std::string m_InactiveString;

  };

  class ColorEditRGB : public Element
  {
  public:
    ColorEditRGB(std::string ID, glm::fvec3 *color) : m_ID(ID), m_colorVec(color) { m_color[0] = m_colorVec->r; m_color[1] = m_colorVec->g; m_color[2] = m_colorVec->b; }
  
    inline void render() { ImGui::ColorEdit3(m_ID.c_str(), m_color); m_colorVec->r = m_color[0]; m_colorVec->g = m_color[1]; m_colorVec->b = m_color[2]; }
    inline void dispose(){ ColorEditRGB::~ColorEditRGB(); }
   
  private:
    ~ColorEditRGB() {}
    float m_color[3];

    std::string m_ID;
    glm::fvec3 *m_colorVec;
  };

  class ColorEditRGBA : public Element
  {
  public:
    ColorEditRGBA(std::string ID, glm::fvec4 *color) : m_ID(ID), m_colorVec(color) { m_color[0] = m_colorVec->r; m_color[1] = m_colorVec->g; m_color[2] = m_colorVec->b; m_color[3] = m_colorVec->a; }

    inline void render() { ImGui::ColorEdit4(m_ID.c_str(), m_color); m_colorVec->r = m_color[0]; m_colorVec->g = m_color[1]; m_colorVec->b = m_color[2]; m_colorVec->a = m_color[3]; }
    inline void dispose(){ ColorEditRGBA::~ColorEditRGBA(); }

  private:
    ~ColorEditRGBA() {}
    float m_color[4];

    std::string m_ID;
    glm::fvec4 *m_colorVec;
  };

};