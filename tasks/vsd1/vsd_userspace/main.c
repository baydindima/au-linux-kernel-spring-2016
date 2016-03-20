#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>

#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include "../vsd_driver/vsd_ioctl.h"

int get_vsd_descriptor() {
	return open("/dev/vsd", O_RDONLY);
}

void printUsage() {
	std::cout << "Usage is:\n" 
					<< " $ vsd_userspace size_get - for get buffer size\n"
					<< " $ vsd_userspace size_set SIZE_IN_BYTES - for set buffer size\n";
}

bool is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

int set_size(int size) {
	if (size >= 0) {
		vsd_ioctl_get_size_arg_t arg;
		arg.size = size;
		int file_desc = get_vsd_descriptor();
		if (file_desc != -1) {
			if (ioctl(file_desc, VSD_IOCTL_SET_SIZE, &arg) == 0) {
				std::cout << "VSD changed to " << arg.size << std::endl;
				return EXIT_SUCCESS;
			}
		}
	}
	std::cout << "Error!" << std::endl; 
	return EXIT_FAILURE;
}

int get_size() {
	vsd_ioctl_get_size_arg_t arg;
	int file_desc = get_vsd_descriptor();
	if (file_desc != -1) {
		if (ioctl(file_desc, VSD_IOCTL_GET_SIZE, &arg) == 0) {
			std::cout << "VSD size is " << arg.size << std::endl; 
			return EXIT_SUCCESS;
		}
	}
	std::cout << "Error!" << std::endl; 
	return EXIT_FAILURE;
}

int main(int argc, char **argv) {; 
	if (argc >= 2) {
		std::string command_type = argv[1];

		if (argc == 2 && command_type == "size_get") {
			return get_size();	 		
	 	}

	 	if (argc == 3 && command_type == "size_set" && is_number(argv[2])) {
	 		return set_size(std::stoi(static_cast<std::string>(argv[2])));
	 	}
	}
 	

 	printUsage();
	std::cin.get();
    return EXIT_FAILURE;
}
