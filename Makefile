default:
	cd os161-1.11 && ./configure --ostree=~/goldteam/root --toolprefix=os161-
	cd os161-1.11/kern/conf && ./config ASST0
	cd os161-1.11/kern/compile/ASST0 && make depend && make && make install

run: default
	cd root && sys161 kernel
