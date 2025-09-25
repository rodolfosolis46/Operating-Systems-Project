#include "auth.h"
#include <string>
#include <iostream>
using namespace std;


bool authenticateUser()
{
	string username;
	string password;
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;

	if (username == "admin" && password == "password123")
	{
		cout << "Authentication successful!" << endl;
		return true;
	}
	else
	{
		cerr << "Authentication failed!" << endl;
		return false;
	}
}