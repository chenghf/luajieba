/* jieba for Lua */

#ifndef __LUAJIEBA_H__
#define __LUAJIEBA_H__

#define JIEBA_METATABLE		"JIEBA Cut Word Handle"
#define EXTRACTOR_METATABLE	"JIEBA Extractor Handle"

extern struct luaL_Reg jieba_methods [];
extern struct luaL_Reg extractor_methods [];

#endif
