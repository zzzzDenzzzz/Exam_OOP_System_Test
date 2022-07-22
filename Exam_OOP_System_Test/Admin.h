#pragma once

#include"Guest.h"
#include"User.h"

class Admin : public Guest
{
public:
	Admin() = default;
	Admin(const string login, const string password);
};