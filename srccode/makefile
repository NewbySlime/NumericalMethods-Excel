main: compile_main compile_libxlsx link
	del *.o

v1: compile_mainv1 compile_libxlsx link
	del *.o

library: compile_main compile_libxlsx link_library
	del *.o

compile_main:
	g++ -c *.cpp

compile_mainv1:
	g++ -c ./v1/*.cpp

compile_libxlsx: compile_tmpfileplus compile_minizip compile_md5 compile_dtoa
	gcc -c ../Libraries/libxlsxw/src/*.c -I../Libraries/libxlsxw/include

compile_tmpfileplus:
	gcc -c ../Libraries/libxlsxw/third_party/tmpfileplus/*.c

compile_minizip:
	gcc -c ../Libraries/libxlsxw/third_party/minizip/*.c && del minizip.o && del miniunz.o

compile_md5:
	gcc -c ../Libraries/libxlsxw/third_party/md5/*.c

compile_dtoa:
	gcc -c ../Libraries/libxlsxw/third_party/dtoa/*.c

link:
	g++ -o ../main.exe *.o --static -lz

link_library:
	g++ -o ../main.o *.o --static -lz