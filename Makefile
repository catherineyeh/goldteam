default:
	mkdir -p os161-1.11/kern/compile/ASST0
	cd os161-1.11 && ./configure --ostree=~/goldteam/root --toolprefix=os161-
	cd os161-1.11/kern/conf && ./config ASST0
	cd os161-1.11/kern/compile/ASST0 && make depend && make && make install

run: default
	cd root && sys161 kernel

# see section "Using gdb with OS 161" on https://docs.google.com/document/d/17pYaR09qU_g580qj8pj2Z9d1TZMOGtmH0r2-EtdSBQI/pub
debug: default
	cd root && sys161 -w kernel
