//! \file XGLApplication.h
//! \brief Application class
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
#ifndef _XGL_APPLICATION_H_
#define _XGL_APPLICATION_H_
#include <Wt/WApplication.h>
#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/PasswordService.h>
#include "db/DBSession.h"

class XGLApplication : public Wt::WApplication
{
public:
  XGLApplication(const Wt::WEnvironment& env);

  void authEvent();

private:
  db::DBSession session_;
};



#endif