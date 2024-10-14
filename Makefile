
LUAJIT_INC = /usr/local/openresty/luajit/include/luajit-2.1

all: luajieba

luajit:
	gcc -o jieba.luajit.so -shared -fPIC lua/jieba.c lua/luajieba.c -I$(LUAJIT_INC) -I./ -L. -ljieba -lm -lstdc++

luajieba: libjieba.a
	gcc -o jieba.so -shared -fPIC lua/jieba.c lua/luajieba.c -I./ -L. -ljieba -lm -lstdc++

libjieba.a:
	g++ -std=c++11 -o jieba.o -c -fPIC -DLOGGING_LEVEL=LL_WARNING -I./deps/ ./lib/jieba.cpp
	ar rs libjieba.a jieba.o
clean:
	rm -f *.a *.o *.so
