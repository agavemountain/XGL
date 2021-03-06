//! \file DBSession.cpp
//! \brief DBSession class
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
#include "Wt/Auth/AuthService.h"
#include "Wt/Auth/HashFunction.h"
#include "Wt/Auth/PasswordService.h"
#include "Wt/Auth/PasswordStrengthValidator.h"
#include "Wt/Auth/PasswordVerifier.h"
#include "Wt/Auth/GoogleService.h"
#include "Wt/Auth/FacebookService.h"
#include "Wt/Auth/Dbo/AuthInfo.h"

#include "Wt/Dbo/backend/Sqlite3.h"

#include "db/DBSession.h"

using namespace Wt;

namespace db
{

namespace
{

    Auth::AuthService myAuthService;
    Auth::PasswordService myPasswordService(myAuthService);
    std::vector<std::unique_ptr<Auth::OAuthService>> myOAuthServices;

}

void DBSession::configureAuth()
{
    myAuthService.setAuthTokensEnabled(true, "logincookie");
    myAuthService.setEmailVerificationEnabled(false);
    myAuthService.setEmailVerificationRequired(false);

    std::unique_ptr<Auth::PasswordVerifier> verifier = std::make_unique<Auth::PasswordVerifier>();
    verifier->addHashFunction(std::make_unique<Auth::BCryptHashFunction>(7));
    myPasswordService.setVerifier(std::move(verifier));
    myPasswordService.setAttemptThrottlingEnabled(true);
    myPasswordService.setStrengthValidator(std::make_unique<Auth::PasswordStrengthValidator>());

    if (Auth::GoogleService::configured())
        myOAuthServices.push_back(std::make_unique<Auth::GoogleService>(myAuthService));

    if (Auth::FacebookService::configured())
        myOAuthServices.push_back(std::make_unique<Auth::FacebookService>(myAuthService));

    for (unsigned i = 0; i < myOAuthServices.size(); ++i)
        myOAuthServices[i]->generateRedirectEndpoint();
}

DBSession::DBSession(const std::string &sqliteDb)
{
    auto connection = std::make_unique<Dbo::backend::Sqlite3>(sqliteDb);

    connection->setProperty("show-queries", "true");

    setConnection(std::move(connection));

    mapClass<User>("user");
    mapClass<AuthInfo>("auth_info");
    mapClass<AuthInfo::AuthIdentityType>("auth_identity");
    mapClass<AuthInfo::AuthTokenType>("auth_token");

    try
    {
        createTables();
        std::cerr << "Created database." << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "Using existing database";
    }

    users_ = std::make_unique<UserDatabase>(*this);
}

Auth::AbstractUserDatabase &DBSession::users()
{
    return *users_;
}

dbo::ptr<User> DBSession::user() const
{
    if (login_.loggedIn())
    {
        dbo::ptr<AuthInfo> authInfo = users_->find(login_.user());
        return authInfo->user();
    }
    else
        return dbo::ptr<User>();
}

const Auth::AuthService &DBSession::auth()
{
    return myAuthService;
}

const Auth::PasswordService &DBSession::passwordAuth()
{
    return myPasswordService;
}

const std::vector<const Auth::OAuthService *> DBSession::oAuth()
{
    std::vector<const Auth::OAuthService *> result;
    for (auto &auth : myOAuthServices)
    {
        result.push_back(auth.get());
    }
    return result;
}

} // namespace db