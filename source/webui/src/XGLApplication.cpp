//! \file XGLApplication.cpp
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
#include "XGLApplication.h"
#include <Wt/WText.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WBootstrapTheme.h>
#include <Wt/WLineEdit.h>
#include <Wt/WMenu.h>
#include <Wt/WMessageBox.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WPopupMenuItem.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WText.h>

#include "Session.h"

/*
 * The env argument contains information about the new session, and
 * the initial request. It must be passed to the WApplication
 * constructor so it is typically also an argument for your custom
 * application constructor.
*/

XGLApplication::XGLApplication(const Wt::WEnvironment &env)
    : WApplication(env),
      session_(appRoot() + "auth.db")
{

    session_.login().changed().connect(this, &XGLApplication::authEvent);

    root()->addStyleClass("container");
    setTheme(std::make_shared<Wt::WBootstrapTheme>());
    useStyleSheet("css/style.css");

    // Create a navigation bar with a link to a web page.
    Wt::WNavigationBar *navigation = root()->addNew<Wt::WNavigationBar>();
    navigation->setTitle("XGL General Ledger",
                         "#");
    navigation->setResponsive(true);
    Wt::WStackedWidget *contentsStack = root()->addNew<Wt::WStackedWidget>();
    contentsStack->addStyleClass("contents");

    // Setup a Left-aligned menu.
    auto leftMenu = Wt::cpp14::make_unique<Wt::WMenu>(contentsStack);
    auto leftMenu_ = navigation->addMenu(std::move(leftMenu));
    leftMenu_->addItem("Home", Wt::cpp14::make_unique<Wt::WText>("There is no better place!"));
    leftMenu_->addItem("Layout", Wt::cpp14::make_unique<Wt::WText>("Layout contents"))
        ->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/layout"));

    std::unique_ptr<Wt::Auth::AuthWidget> authWidget = std::make_unique<Wt::Auth::AuthWidget>(Session::auth(), session_.users(), session_.login());

    authWidget->model()->addPasswordAuth(&Session::passwordAuth());
    authWidget->model()->addOAuth(Session::oAuth());
    authWidget->setRegistrationEnabled(true);

    authWidget->processEnvironment();

    root()->addWidget(std::move(authWidget));
}

void XGLApplication::authEvent()
{
    if (session_.login().loggedIn())
    {
        const Wt::Auth::User &u = session_.login().user();
        log("notice")
            << "User " << u.id()
            << " (" << u.identity(Wt::Auth::Identity::LoginName) << ")"
            << " logged in.";
    }
    else
        log("notice") << "User logged out.";
}