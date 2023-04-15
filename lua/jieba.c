/* jieba for Lua */

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <string.h>

#include "luajieba.h"

#include "lib/jieba.h"

static int
lua_Cut (lua_State *L)
{
	int i;
	Jieba **handle;
	size_t len = 0;
	const char *src = NULL;
	CJiebaWord *words, *pi;

	handle = luaL_checkudata (L, 1, JIEBA_METATABLE);
	src = luaL_checklstring (L, 2, &len);

	words = Cut (*handle, src, len);

	lua_newtable(L);

	for (i=0, pi = words; pi && pi->word; pi++, i++) {

		lua_pushlstring (L, pi->word, pi->len);
		lua_rawseti (L, -2, i + 1);
	}

	FreeWords(words);

	return 1;
}

static int
lua_CutWithTag (lua_State *L)
{
	int i;
	Jieba **handle;
	size_t len = 0;
	const char *src = NULL;
	CJiebaWordWithTag *words, *pi;

	handle = luaL_checkudata (L, 1, JIEBA_METATABLE);
	src = luaL_checklstring (L, 2, &len);

	words = CutWithTag (*handle, src, len);

	lua_newtable(L);

	for (i=0, pi = words; pi && pi->word; pi++, i++)
	{
		lua_newtable(L);

		lua_pushstring (L, "word");
		lua_pushlstring (L, pi->word, pi->len);
		lua_rawset (L, -3);

		lua_pushstring (L, "tag");
		lua_pushstring (L, pi->tag);
		lua_rawset (L, -3);

		lua_rawseti (L, -2, i + 1);
	}

	FreeWordTag (words);
	return 1;
}

static int
lua_CutWithoutTagName (lua_State *L)
{
	int i;
	Jieba **handle;
	size_t len = 0;
	const char *src = NULL;
	const char *tag = NULL;
	CJiebaWord *words, *pi;

	handle = luaL_checkudata (L, 1, JIEBA_METATABLE);
	src = luaL_checklstring (L, 2, &len);
	tag = luaL_checkstring (L, 3);

	words = CutWithoutTagName (*handle, src, len, tag);

	lua_newtable(L);

	for (i=0, pi = words; pi && pi->word; pi++, i++) {

		lua_pushlstring (L, pi->word, pi->len);
		lua_rawseti (L, -2, i + 1);
	}

	FreeWords(words);

	return 1;
}

static int
lua_InsertUserWord (lua_State *L)
{
	Jieba **handle;
	const char *word = NULL;
	bool ret;

	handle = luaL_checkudata (L, 1, JIEBA_METATABLE);
	word = luaL_checkstring (L, 2);

	ret = InsertUserWord (*handle, word);

	lua_pushboolean (L, ret);

	return 1;
}

static int
lua_InsertUserWordWithFreq (lua_State *L)
{
	Jieba **handle;
	const char *word = NULL;
	int freq;
	bool ret;

	handle = luaL_checkudata (L, 1, JIEBA_METATABLE);
	word = luaL_checkstring (L, 2);
	freq = luaL_checkinteger (L, 3);

	ret = InsertUserWordWithFreq (*handle, word, freq);

	lua_pushboolean (L, ret);

	return 1;
}

static int
lua_DeleteUserWord (lua_State *L)
{
	Jieba **handle;
	const char *word = NULL;
	bool ret;

	handle = luaL_checkudata (L, 1, JIEBA_METATABLE);
	word = luaL_checkstring (L, 2);

	ret = DeleteUserWord (*handle, word);

	lua_pushboolean (L, ret);

	return 1;
}

static int
lua_LookupTag (lua_State *L)
{
	Jieba **handle;
	const char *src = NULL;
	char *tag;

	handle = luaL_checkudata (L, 1, JIEBA_METATABLE);
	src = luaL_checkstring (L, 2);

	tag = LookupTag (*handle, src);

	lua_pushstring (L, tag);

	free (tag);
 
	return 1;
}

static int
lua_CutAll (lua_State *L)
{
	Jieba **handle;
	size_t i=0, len = 0, cnt = 0;
	const char *src = NULL;

	handle = luaL_checkudata (L, 1, JIEBA_METATABLE);
	src = luaL_checklstring (L, 2, &len);

	char* words = CutAll (*handle, src, len, &cnt);
	char *pi = words;

	lua_newtable(L);

	i = 0;
	len = strlen (pi);
	while (len > 0)
	{
		lua_pushlstring (L, pi, len);
		lua_rawseti (L, -2, i + 1);

		pi += len + 1;
		len = strlen (pi);

		i++;
	}

	free (words);

	return 1;
}

static int
lua_CutForSearch (lua_State *L)
{
	Jieba **handle;
	size_t i = 0, len = 0, cnt = 0;
	const char *src = NULL;

	handle = luaL_checkudata (L, 1, JIEBA_METATABLE);
	src = luaL_checklstring (L, 2, &len);

	char* words = CutForSearch (*handle, src, len, &cnt);
	char *pi = words;

	lua_newtable(L);

	i = 0;
	len = strlen (pi);
	while (len > 0)
	{
		lua_pushlstring (L, pi, len);
		lua_rawseti (L, -2, i + 1);

		pi += len + 1;
		len = strlen (pi);

		i++;
	}

	free (words);

	return 1;
}

static int
destory (lua_State *L)
{
	Jieba **handle;

	handle = luaL_checkudata (L, 1, JIEBA_METATABLE);

	if (*handle)
	{
		FreeJieba (*handle);
		*handle = NULL;
	}

	return 0;
}

static int
lua_Extract (lua_State *L)
{
	int i;
	Extractor **handle;
	size_t top_n, len = 0;
	const char *src = NULL;
	CJiebaWord *words, *pi;

	handle = luaL_checkudata (L, 1, EXTRACTOR_METATABLE);
	src = luaL_checklstring (L, 2, &len);
	top_n = luaL_optinteger (L, 3, 5);

	words = Extract (*handle, src, len, top_n); 

	lua_newtable(L);

	for (i=0, pi = words; pi && pi->word; pi++, i++) {

		lua_pushlstring (L, pi->word, pi->len);
		lua_rawseti (L, -2, i + 1);
	}

	FreeWords(words);

	return 1;
}

static int
extractor_destory (lua_State *L)
{
	Extractor **handle;

	handle = luaL_checkudata (L, 1, EXTRACTOR_METATABLE);

	if (*handle)
	{
		FreeExtractor (*handle);
		*handle = NULL;
	}

	return 0;
}

struct luaL_Reg extractor_methods[] =
{
	{ "extract",		lua_Extract },
	{ "destory",		extractor_destory },
	{ "__gc",			extractor_destory },
};

struct luaL_Reg jieba_methods[] =
{
	{ "cut",					lua_Cut },
	{ "cut_with_tag",			lua_CutWithTag },
	{ "cut_without_tagname",	lua_CutWithoutTagName },
	{ "cut_all",				lua_CutAll },
	{ "cut_for_search",			lua_CutForSearch },
	{ "insert_userword",		lua_InsertUserWord },
	{ "insert_userword_freq",	lua_InsertUserWordWithFreq },
	{ "delete_userword",		lua_DeleteUserWord },
	{ "lookup_tag",				lua_LookupTag },
	{ "destory",				destory },
	{ "__gc",					destory },
	{ NULL, NULL }
};
