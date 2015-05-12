#
# Created by mandriy on 5/8/15.
#

binary_dir ?= build
executable_name ?= server
run_args ?= -p 4242

headers ?= thread/myThread.h socket/TCPSocket.h connection/connection.h tcp_server/asioTcpServer.h
source_files ?= server.cpp thread/myThread.cpp socket/TCPSocket.cpp

flags += -lpthread -std=c++11 -lboost_serialization -lboost_program_options -lboost_system


ifndef suppress_warnings 
	warnings ?= -Wall -Wextra
endif

all : run

.PHONY : run


run : executable
	./$(executable_name) $(run_args)

valgrind_run: executable
	valgrind --track-origins=yes  ./$(executable_name) $(run_args)

.PHONY :executable

executable : $(executable_name)

$(executable_name) : build_files
	g++ $(binary_dir)/* -o $(executable_name) $(flags) 

.PHONY : build_files

build_files : $(binary_dir)

$(binary_dir) : $(headers) $(source_files)
	if ! [ -d $(binary_dir) ]; then mkdir $(binary_dir); fi
	rm -rf $(binary_dir)/*
	( cd $(binary_dir) ; g++ $(addprefix ../, $(source_files)) -c $(flags) $(additional_flags) $(warnings))

.PHONY : clean

clean :
	rm -rf $(binary_dir)
	rm -rf $(executable_name)