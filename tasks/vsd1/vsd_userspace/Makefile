INCLUDE_PATH=../vsd_driver/
SHARE_PATH=../../../../images/vm/share/

vsd_userspace: main.c $(INCLUDE_PATH)/vsd_ioctl.h
	g++ -std=c++11 -Wall -Werror $< -I$(INCLUDE_PATH) -o $@
	cp $@ $(SHARE_PATH)

.PHONY: clean

clean:
	rm -rf vsd_userspace
