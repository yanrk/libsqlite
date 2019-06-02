# arguments
platform = linux/x64



project_home       = .
build_dir          = $(project_home)
bin_dir            = $(project_home)/lib/$(platform)
object_dir         = $(project_home)/.objs
libsqlite_home     = $(project_home)/..
stupid_home        = $(project_home)/../../../stupid



# includes of stupid headers
stupid_inc_path    = $(stupid_home)/inc
stupid_includes    = -I$(stupid_inc_path)

# includes of libsqlite headers
libsqlite_inc_path = $(libsqlite_home)/inc
libsqlite_includes = -I$(libsqlite_inc_path)



# all includes that test solution needs
includes           = $(stupid_includes)
includes          += $(libsqlite_includes)



# source files of test solution

# source files of test project
test_src_path      = $(project_home)
test_source        = $(filter %.cpp, $(shell find $(test_src_path) -depth -name "*.cpp"))



# objects of test solution
test_objects       = $(test_source:$(project_home)%.cpp=$(object_dir)%.o)



# system libraries
system_libs        = -lpthread -ldl

# stupid librarys
stupid_lib_inc     = $(stupid_home)/lib/$(platform)
stupid_libs        = -L$(stupid_lib_inc) -lstupid_base

# libsqlite librarys
libsqlite_lib_inc   = $(libsqlite_home)/lib/$(platform)
libsqlite_libs      = -L$(libsqlite_lib_inc) -lsqlite

# test depends librarys
depend_libs        = $(libsqlite_libs)
depend_libs       += $(stupid_libs)
depend_libs       += $(system_libs)

# output execute
output_exec        = $(bin_dir)/test



# build flags for objects
build_obj_flags    = -std=c++11 -g -Wall -O1 -pipe -fPIC

# build flags for execution
build_exec_flags   = $(build_obj_flags)



# build targets
targets            = test

# let 'build' be default target, build all targets
build    : $(targets)

test     : $(test_objects)
	@echo "includes is $(includes)"
	@echo "@@@@@  start making test  @@@@@"
	g++ $(build_exec_flags) -o $(output_exec) $^ $(depend_libs)
	@echo "@@@@@  make test success  @@@@@"
	@echo

# build all objects
$(object_dir)/%.o:$(project_home)/%.cpp
	@dir=`dirname $@`;      \
    if [ ! -d $$dir ]; then \
        mkdir -p $$dir;     \
    fi
	g++ -c $(build_obj_flags) $(includes) -o $@ $<

clean    :
	rm -rf $(object_dir) $(bin_dir)/lib*

rebuild  : clean build
