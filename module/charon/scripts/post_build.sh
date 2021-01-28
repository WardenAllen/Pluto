
#!/bin/bash

bin_dir="./bin/x64/Debug"
obj_dir="./obj/x64/Debug"
bin_name="Charon.out"
local_lib_dir="../Pluto/library"
lib_name="libcharon.a"
global_header_dir="/usr/include/pluto/charon"
global_lib_dir="/usr/lib"

# 1. check memory leak.
cd $bin_dir
valgrind --log-file=./valgrind_report.log --tool=memcheck --leak-check=full --show-leak-kinds=all -v ./$bin_name;
cd -;

# 2. encapsulate library.
if [ ! -d $local_lib_dir ]; then
   mkdir -p $local_lib_dir
fi
cd $obj_dir
ar rcs ../../../$local_lib_dir/$lib_name `ls | grep -vE 'main*|*_test'`
cd -

# 3. copy to global dir.
if [ ! -d $global_header_dir ]; then
   mkdir -p $global_header_dir
fi
cp -r include/* $global_header_dir
cp $local_lib_dir/$lib_name /usr/lib