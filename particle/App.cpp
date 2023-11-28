//  Copyright (c) 2022-2023 Daniel Moreno. All rights reserved.
//

#include "App.hpp"

namespace course
{
  wxIMPLEMENT_APP_NO_MAIN(App);

  App::App() :
    wxApp{}
  {
    //create simulation
  }

  App::~App()
  {
    //delete simulation
  }

  bool App::OnInit()
  {
    //create window
    return true;
  }

  const Simulation& App::simulation() const
  {
    return {};
  }

  Simulation& App::simulation()
  {
    static Simulation dummy;
    return dummy;
  }

  const MainWindow& App::mainWindow() const
  {
    return {};
  }

  MainWindow& App::mainWindow()
  {
    static MainWindow dummy;
    return dummy;
  }
}

int main(int argc, char* argv[])
{
  return wxEntry(argc, argv);
}