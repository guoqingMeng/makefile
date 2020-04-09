

.PHONY:all clean
all:
	@cd sub; make
clean:
	@cd sub; make clean

