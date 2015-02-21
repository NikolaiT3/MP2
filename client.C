//********************************************************
// Name			: Nicholas Warner and Jennings Fairchild
// Date			: 19 February 2015
// Subject		: CSCE 312-501
// Assignment	: Machine Problem 2
// Updated		: 20 February 2015
// Description	: Communicating through a Tunnel
//********************************************************

// Jennings has a University Excused Absence for SCONA.
// As per instructions, I am turning in what I have and
// we will turn in his part of this project ASAP. We will
// schedule a time with Tanzir next week to demo as well

#include <cassert>
#include <string>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#include <errno.h>
#include <unistd.h>

#include "reqchannel.H"

using namespace std;

string int2string(int number)
{
	stringstream ss;//create a stringstream
	ss << number;//add number to the stream
	return ss.str();//return a string with the contents of the stream
}

int main ( int argc, char *argv[] )
{ 
	string pass = "./dataserver";
	if ( fork() == 0 )	// executes just fine
	{
		system("./dataserver");
		return 0;
	}
	else
	{
		RequestChannel client_chan("control", RequestChannel::CLIENT_SIDE);	// hangs execution

		string reply1 = client_chan.send_request("hello");
		cout << "Reply to request 'hello' is '" << reply1 << "'" << endl;

		string reply2 = client_chan.send_request("data Joe Smith");
		cout << "Reply to request 'data Joe Smith' is '" << reply2 << "'" << endl;

		string reply3 = client_chan.send_request("data Jane Smith");
		cout << "Reply to request 'data Jane Smith' is '" << reply3 << "'" << endl;

		for(int i = 0; i < 100; i++)
		{
		    string request_string("data TestPerson" + int2string(i));
		    string reply_string = client_chan.send_request(request_string);
			cout << "reply to request " << i << ":" << reply_string << endl;;
		}

		string reply4 = client_chan.send_request("quit");
		cout << "Reply to request 'quit' is '" << reply4 << endl;

		usleep(1000000);
		return 0;
	}
}