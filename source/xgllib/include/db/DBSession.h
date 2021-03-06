//! \brief Database session
//! \file DBSession.h
//!
//! \copyright Copyright (C) 2021 IO Industrial Holdings, LLC; All Rights Reserved.
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
#ifndef _DBSESSION_H_
#define _DBSESSION_H_
#include <Wt/Auth/Login.h>
#include <Wt/Auth/Dbo/UserDatabase.h>
#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/ptr.h>

#include "db/User.h"

//! \brief Database namespace
//!
//! This namespace contains all of the XGL database sessions, objects, 
//! object mappings, tables, queries, and assorted minuta.
namespace db
{


namespace dbo = Wt::Dbo;

using UserDatabase = Wt::Auth::Dbo::UserDatabase<AuthInfo>;

//! \brief Database Session
//!
//! This long-lived object represents the session to the database.
//! 
class DBSession : public dbo::Session
{
public:
  static void configureAuth();

  DBSession(const std::string& sqliteDb);

  dbo::ptr<User> user() const;

  Wt::Auth::AbstractUserDatabase& users();
  Wt::Auth::Login& login() { return login_; }

  static const Wt::Auth::AuthService& auth();
  static const Wt::Auth::PasswordService& passwordAuth();
  static const std::vector<const Wt::Auth::OAuthService *> oAuth();

private:
  std::unique_ptr<UserDatabase> users_;
  Wt::Auth::Login login_;
};

} // namespace db
#endif

