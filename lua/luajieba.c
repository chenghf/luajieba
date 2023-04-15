#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "luajieba.h"

#include "lib/jieba.h"

static int
check_file (lua_State *L, const char *fname)
{
	FILE *fp;

	fp = fopen (fname, "r");
	if (fp == NULL)
	{
		lua_pushnil (L);
		lua_pushfstring (L, "%s not found.", fname);
		return 2;
	}

	fclose (fp);

	return 0;
}

static int
new_jieba (lua_State *L)
{
	Jieba **handle = NULL;

	int i, retval;

	const char *dict_path[] = { NULL, NULL, NULL, NULL, NULL };

	dict_path[0] = luaL_checkstring (L, 1);	// dict_path
	dict_path[1] = luaL_checkstring (L, 2);	// hmm_path
	dict_path[2] = luaL_checkstring (L, 3);	// user_dict
	dict_path[3] = luaL_checkstring (L, 4);	// idf_path
	dict_path[4] = luaL_checkstring (L, 5);	// stop_words_path

	for (i=0; i<5; i++)
	{
		retval = check_file (L, dict_path[i]);

		if (retval != 0)
		{
			return retval;
		}
	}

	handle = lua_newuserdata(L, sizeof(Jieba *));

	*handle = NewJieba (dict_path[0], dict_path[1], dict_path[2], dict_path[3], dict_path[4]);

	luaL_setmetatable (L, JIEBA_METATABLE);
	lua_pushstring (L, "init jieba success");

	return 2;
}

static int
new_extractor (lua_State *L)
{
	Extractor **handle = NULL;

	int i, retval;

	const char *dict_path[] = { NULL, NULL, NULL, NULL, NULL };

	dict_path[0] = luaL_checkstring (L, 1);	// dict_path
	dict_path[1] = luaL_checkstring (L, 2);	// hmm_path
	dict_path[2] = luaL_checkstring (L, 3);	// user_dict
	dict_path[3] = luaL_checkstring (L, 4);	// idf_path
	dict_path[4] = luaL_checkstring (L, 5);	// stop_words_path

	for (i=0; i<5; i++)
	{
		retval = check_file (L, dict_path[i]);

		if (retval != 0)
		{
			return retval;
		}
	}

	handle = lua_newuserdata(L, sizeof(Extractor *));

	*handle = NewExtractor (dict_path[0], dict_path[1], dict_path[3], dict_path[4], dict_path[2]); 

	luaL_setmetatable (L, EXTRACTOR_METATABLE);
	lua_pushstring (L, "init extractor success");

	return 2;
}

int
luaopen_jieba (lua_State *L)
{
	struct luaL_Reg luajieba[] =
	{
		{ "new",		new_jieba },
		{ "extractor",	new_extractor},
		{ NULL, NULL }
	};

	luaL_newlib (L, luajieba);

	if (luaL_newmetatable(L, JIEBA_METATABLE)) {
		luaL_setfuncs(L, jieba_methods, 0);

		lua_pushliteral(L, "__index");
		lua_pushvalue(L, -2);
		lua_settable(L, -3);

		lua_pushliteral(L, "__metatable");
		lua_pushliteral(L, "must not access this metatable");
		lua_settable(L, -3);
	}
	lua_pop(L, 1);

	if (luaL_newmetatable(L, EXTRACTOR_METATABLE)) {
		luaL_setfuncs(L, extractor_methods, 0);

		lua_pushliteral(L, "__index");
		lua_pushvalue(L, -2);
		lua_settable(L, -3);

		lua_pushliteral(L, "__metatable");
		lua_pushliteral(L, "must not access this metatable");
		lua_settable(L, -3);
	}
	lua_pop(L, 1);

	lua_pushliteral(L, "_VERSION");
	lua_pushliteral(L, "lua jieba 0.0.1");
	lua_settable(L, -3);
	return 1;
}
