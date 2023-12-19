//  Copyright (c) 2022-2023 Daniel Moreno. All rights reserved.
//

#include "ControlPanel.hpp"
#include "App.hpp"

namespace course
{
  enum ControlPanelIds
  {
    ControlPanel_StartId = 2000,
    ID_ButtonStart,
    ID_ButtonNext,
    ID_ButtonReset,
  };

  ControlPanel::ControlPanel(wxWindow* parent) :
    wxPanel{ parent }
  {
    //create a vertical box sizer to stack children vertically
    wxBoxSizer* vBox{ new wxBoxSizer{wxVERTICAL} };

    //start/stop button
    startButton_ = new wxToggleButton{ this, ID_ButtonStart, "Start"};
    Bind(wxEVT_TOGGLEBUTTON, &ControlPanel::onStartButtonClick, this, ID_ButtonStart);
    vBox->Add(startButton_, 0, wxEXPAND);

    //next button
    nextButton_ = new wxButton{ this, ID_ButtonNext, "Next"};
    Bind(wxEVT_BUTTON, &ControlPanel::onNextButtonClick, this, ID_ButtonNext);
    vBox->Add(nextButton_, 0, wxEXPAND);

    //reset button
    resetButton_ = new wxButton{ this, ID_ButtonReset, "Reset" };
    Bind(wxEVT_BUTTON, &ControlPanel::onResetButtonClick, this, ID_ButtonReset);
    vBox->Add(resetButton_, 0, wxEXPAND);

    //parameters group
    {
      paramsBox_ = new wxStaticBox{ this, wxID_ANY, "Parameters" };
      wxStaticBoxSizer* staticBoxSizer{ new wxStaticBoxSizer{paramsBox_, wxVERTICAL} };

      constexpr int rows{ 4 };
      constexpr int cols{ 2 };
      constexpr int vGap{ 4 };
      constexpr int hGap{ 8 };
      wxFlexGridSizer* fgs = new wxFlexGridSizer{rows, cols, vGap, hGap};

      wxStaticText* Velocityx_label{ new wxStaticText{paramsBox_, wxID_ANY, "Start Velocity x:"}};
      Velocity_x = new wxTextCtrl{ paramsBox_, wxID_ANY, "0.0",
        wxDefaultPosition, wxDefaultSize, wxTE_RIGHT};
      fgs->Add(Velocityx_label);
      fgs->Add(Velocity_x, 1, wxEXPAND);

      wxStaticText* Velocityy_label{ new wxStaticText{paramsBox_, wxID_ANY, "Start Velocity y:"}};
      Velocity_y = new wxTextCtrl{ paramsBox_, wxID_ANY, "0.0",
        wxDefaultPosition, wxDefaultSize, wxTE_RIGHT};
      fgs->Add(Velocityy_label);
      fgs->Add(Velocity_y, 1, wxEXPAND);

      wxStaticText* radius_label{ new wxStaticText{paramsBox_, wxID_ANY, "Radius:"} };
      radius_ = new wxTextCtrl{ paramsBox_, wxID_ANY, "0.1",
        wxDefaultPosition, wxDefaultSize, wxTE_RIGHT };
      fgs->Add(radius_label);
      fgs->Add(radius_, 1, wxEXPAND);

      wxStaticText* collision_label{ new wxStaticText{paramsBox_, wxID_ANY, "Collision:"}};
      collision_ = new wxTextCtrl{ paramsBox_, wxID_ANY, "0.9",
        wxDefaultPosition, wxDefaultSize, wxTE_RIGHT};
      fgs->Add(collision_label);
      fgs->Add(collision_, 1, wxEXPAND);

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
    nextButton_->Enable(!mainWindow.isSimulationRunning());
    resetButton_->Enable(!mainWindow.isSimulationRunning());
    paramsBox_->Enable(!mainWindow.isSimulationRunning());
    startButton_->Enable(true);
    if(mainWindow.isSimulationRunning())
    {
      startButton_->SetLabel("Stop");
    }
    else
    {
      startButton_->SetLabel("Start");
    }
  }

  void ControlPanel::onStartButtonClick(wxCommandEvent& event)
  {
    MainWindow& mainWindow{ wxGetApp().mainWindow() };
    if (!mainWindow.isSimulationRunning())
    {
      wxGetApp().mainWindow().simulationStart();
      startButton_->SetLabel("Stop");
    }
    else
    {
      wxGetApp().mainWindow().simulationStop();
      startButton_->SetLabel("Start");
    }
  }

  void ControlPanel::onNextButtonClick(wxCommandEvent& event)
  {
    wxGetApp().mainWindow().simulationOneStep();
  }

  void ControlPanel::onResetButtonClick(wxCommandEvent& event)
  {
    wxGetApp().mainWindow().simulationReset();
  }

  Vector2d ControlPanel::velocity() const
  {
    return { std::stod(Velocity_x->GetValue().ToStdString()),
     std::stod(Velocity_y->GetValue().ToStdString()) };
  }

  double ControlPanel::radius() const
  {
    return (std::stod(radius_->GetValue().ToStdString()));
  }

  double ControlPanel::collision() const
  {
    return (std::stod(collision_->GetValue().ToStdString()));
  }
}