########################################################
#
# compiling every c file to corresponding excutable file 
#
#######################################################
CC := gcc
CFLAGS := -c

#get all .c files name in current dir
SRCS := $(wildcard *.c)  

#raplace .c to .o in all files
OBJS := $(patsubst %.c, %.o, $(SRCS)) 

#replace .c to .elf in all files
TARGET := $(patsubst %.c, %.elf, $(SRCS)) 

all:$(TARGET)


#compiling all .c files to corresponding .elf excutable files
$(TARGET): %.elf : %.c
	$(CC)  $^  -o  $@ 


print:
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(TARGET)
	

#clean all .elf files
clean:
	rm *.elf
