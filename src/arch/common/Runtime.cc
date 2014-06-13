/*
 *  Multi2Sim
 *  Copyright (C) 2014  Rafael Ubal (ubal@ece.neu.edu)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> 

#include <lib/cpp/String.h>

#include "Runtime.h"


namespace comm
{


//
// Class 'Runtime'
//

Runtime::Runtime(const std::string &name,
		const std::string &library_name, 
		const std::string &redirect_library_name)
{
	// Initialize
	this->name = name;
	this->library_name = library_name;
	this->redirect_library_name = redirect_library_name;
}




//
// Class 'RuntimePool'
//

std::unique_ptr<RuntimePool> RuntimePool::instance;

RuntimePool* RuntimePool::getInstance()
{
	// Return existing instance
	if (instance.get())
		return instance.get();
	
	// Create new runtime pool
	instance.reset(new RuntimePool());
	return instance.get();	
}

void RuntimePool::Register(const std::string &name, 
		const std::string &library_name, 
		const std::string &redirect_library_name)
{
	// Create new runtime
	Runtime *runtime = new Runtime(name,
			library_name,
			redirect_library_name);
	
	// Add it to the pool
	runtime_list.emplace_back(runtime);
}


}  // namespace comm
