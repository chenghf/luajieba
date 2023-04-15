all: luajieba
luajieba: libjieba.a
	gcc -o jieba.so -shared -fPIC lua/jieba.c lua/luajieba.c -I./ -L. -ljieba -lm -lstdc++
libjieba.a:
	g++ -o jieba.o -c -fPIC -DLOGGING_LEVEL=LL_WARNING -I./deps/ ./lib/jieba.cpp
	ar rs libjieba.a jieba.o
clean:
	rm -f *.a *.o *.so
