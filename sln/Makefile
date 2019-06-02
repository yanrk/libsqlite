# arguments
platform = linux/x64



project_home       = ..
build_dir          = $(project_home)/sln
bin_dir            = $(project_home)/lib/$(platform)
object_dir         = $(project_home)/.objs
stupid_home        = $(project_home)/../../stupid



# includes of stupid headers
stupid_inc_path    = $(stupid_home)/inc
stupid_includes    = -I$(stupid_inc_path)

# includes of libsqlite headers
libsqlite_inc_path = $(project_home)/inc
libsqlite_includes = -I$(libsqlite_inc_path)



# all includes that libsqlite solution needs
includes           = $(stupid_includes)
includes          += $(libsqlite_includes)



# source files of libsqlite solution

# source files of libsqlite c++ files
libsqlite_src_path  = $(project_home)/src
libsqlite_source    = $(filter %.cpp, $(shell find $(libsqlite_src_path) -depth -name "*.cpp"))

# source files of libsqlite c files
sqlite3_src_path    = $(project_home)/src
sqlite3_source      = $(filter %.c, $(shell find $(sqlite3_src_path) -depth -name "*.c"))



# objects of libsqlite solution
libsqlite_objects   = $(libsqlite_source:$(project_home)%.cpp=$(object_dir)%.o)
libsqlite_objects  += $(sqlite3_source:$(project_home)%.c=$(object_dir)%.o)



# output librarys
libsqlite_output_lib= $(bin_dir)/libsqlite.a



# build flags for objects
build_obj_flags    = -std=c++11 -g -Wall -O1 -pipe -fPIC

# build flags for execution
build_exec_flags   = $(build_obj_flags)

# build flags for dynamic link librarys
build_so_flags     = -std=c++11 -shared

# build flags for static link librarys
build_a_flags      = -rv



# build targets
targets            = redis

# let 'build' be default target, build all targets
build    : $(targets)

redis    : $(libsqlite_objects)
	@echo
	@echo "@@@@@  start making libsqlite  @@@@@"
	ar $(build_a_flags) $(libsqlite_output_lib) $^
	@echo "@@@@@  make libsqlite success  @@@@@"
	@echo

# build all objects
$(object_dir)/%.o:$(project_home)/%.cpp
	@dir=`dirname $@`;      \
    if [ ! -d $$dir ]; then \
        mkdir -p $$dir;     \
    fi
	g++ -c $(build_obj_flags) $(includes) -o $@ $<

$(object_dir)/%.o:$(project_home)/%.c
	@dir=`dirname $@`;		\
	if [ ! -d $$dir ]; then	\
		mkdir -p $$dir;		\
	fi
	gcc -c -g -O1 -pipe -fPIC $(includes) -o $@ $<

clean    :
	rm -rf $(object_dir) $(bin_dir)/lib*

rebuild  : clean build
