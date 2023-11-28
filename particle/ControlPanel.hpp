//  Copyright (c) 2022-2023 Daniel Moreno. All rights reserved.
//

#pragma once

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/tglbtn.h>

#include "Vector2d.hpp"

namespace course
{
  class ControlPanel : public wxPanel
  {
  public:
    ControlPanel(wxWindow* parent);
    virtual ~ControlPanel();

    //Parameters getters
    Vector2d velocity() const;
    double radius() const;
    double collision() const;

  private:
    void onUpdateUI(wxUpdateUIEvent& event);
    void onResetButtonClick(wxCommandEvent& event);

    wxButton* resetButton_;

    wxStaticBox* paramsBox_;
    wxTextCtrl* radius_;
  };
}