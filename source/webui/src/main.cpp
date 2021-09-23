//! \file main.cpp
//! \brief Ye olde program entry point
//!
//! Copyright (C) 2021  IO Industrial Holdings, LLC
//!
//! This program is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 3 of the License, or
//! (at your option) any later version.
//!
//! This program is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with this program.  If not, see <https://www.gnu.org/licenses/>.
#include <Wt/WApplication.h>
#include <Wt/WBootstrapTheme.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WServer.h>
#include "XGLApplication.h"
#include "db/DBSession.h"

using namespace db;

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env)
{
  return std::make_unique<XGLApplication>(env);
}

int main(int argc, char **argv)
{
    try
    {
        Wt::WServer server{argc, argv, WTHTTP_CONFIGURATION};

        server.addEntryPoint(Wt::EntryPointType::Application, createApplication);

        DBSession::configureAuth();

        server.run();
    }
    catch (Wt::WServer::Exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (Wt::Dbo::Exception &e)
    {
        std::cerr << "Dbo exception: " << e.what() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
    }
}