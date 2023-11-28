//  Copyright (c) 2022-2023 Daniel Moreno. All rights reserved.
//

#include "ControlPanel.hpp"
#include "App.hpp"

namespace course
{
  enum ControlPanelIds
  {
    ControlPanel_StartId = 2000,

    ID_ButtonReset,
  };

  ControlPanel::ControlPanel(wxWindow* parent) :
    wxPanel{ parent }
  {
    //create a vertical box sizer to stack children vertically
    wxBoxSizer* vBox{ new wxBoxSizer{wxVERTICAL} };

    //reset button
    resetButton_ = new wxButton{ this, ID_ButtonReset, "Reset" };
    Bind(wxEVT_BUTTON, &ControlPanel::onResetButtonClick, this, ID_ButtonReset);
    vBox->Add(resetButton_, 0, wxEXPAND);

    //parameters group
    {
      paramsBox_ = new wxStaticBox{ this, wxID_ANY, "Parameters" };
      wxStaticBoxSizer* staticBoxSizer{ new wxStaticBoxSizer{paramsBox_, wxVERTICAL} };

      constexpr int rows{ 1 };
      constexpr int cols{ 2 };
      constexpr int vGap{ 4 };
      constexpr int hGap{ 8 };
      wxFlexGridSizer* fgs = new wxFlexGridSizer{rows, cols, vGap, hGap};

      wxStaticText* radius_label{ new wxStaticText{paramsBox_, wxID_ANY, "Radius:"} };
      radius_ = new wxTextCtrl{ paramsBox_, wxID_ANY, "0.1",
        wxDefaultPosition, wxDefaultSize, wxTE_RIGHT };
      fgs->Add(radius_label);
      fgs->Add(radius_, 1, wxEXPAND);

      fgs->AddGrowableCol(1, 1);

      staticBoxSizer->Add(fgs);
      vBox->Add(staticBoxSizer, 0, wxEXPAND);
    }

    SetSizer(vBox);

    //update event
    Bind(wxEVT_UPDATE_UI, &ControlPanel::onUpdateUI, this);

    SetMinSize(wxSize{ 200,-1 });
    SetMaxSize(wxSize{ 400,-1 });
  }

  ControlPanel::~ControlPanel()
  {

  }

  void ControlPanel::onUpdateUI(wxUpdateUIEvent& event)
  {
    MainWindow& mainWindow{ wxGetApp().mainWindow() };
    resetButton_->Enable(!mainWindow.isSimulationRunning());
    paramsBox_->Enable(!mainWindow.isSimulationRunning());
  }

  void ControlPanel::onResetButtonClick(wxCommandEvent& event)
  {
    //wxGetApp().mainWindow().simulationReset();
  }

  Vector2d ControlPanel::velocity() const
  {
    return { 0,0 };
  }

  double ControlPanel::radius() const
  {
    return 0.1;
  }

  double ControlPanel::collision() const
  {
    return 0.9;
  }
}