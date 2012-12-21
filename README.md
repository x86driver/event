# Build example (on Android) #

* mm (build)
* ./up (This script use adb push)


# Run (on Android) #

* mytest (See event.cpp `main()` for example)

# API #

* `MessageQueue msgqueue;`	// Create a thread to handle message
* `registerMsg(string name, Functor<MessageHandler> &cmd);`    // Use name --> Functor to register
* `postMsg(string name);`	   			   // post a message, so MessageQueue will start to handle this message


# How to define a callback #

        void function()
		{
		    printf("Hello callback\n");
		}
        Functor<MessageHandler> cmd(function);
		
		msgqueue.registerMsg("command1", cmd);
		
		// When you want to post a message to call function()
		
		msgqueue.postMsg("command1", cmd);

# About Functor #

* See [https://github.com/doremi/functor](https://github.com/doremi/functor)
* MessageHandler defines a function/class that no return variables and no arguments, for example:

        void function()
		{
		    ...
		}

    or

		class CallbackClass {
		public:
		    void operator()() {
			    ....
			}
		};
		

# License #

Copyright (C) 2012  doremi

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
