#include <stdio.h>
#include <stdlib.h>

#include "lib/jieba.h"
#include <string.h>

const char* DICT_PATH = "./dict/jieba.dict.utf8";
const char* HMM_PATH = "./dict/hmm_model.utf8";
const char* USER_DICT = "./dict/user.dict.utf8";
const char* IDF_PATH = "./dict/idf.utf8";
const char* STOP_WORDS_PATH = "./dict/stop_words.utf8";

void CutDemo() {
  printf("CutDemo:\n");
  // init will take a few seconds to load dicts.
  Jieba handle = NewJieba(DICT_PATH, HMM_PATH, USER_DICT, IDF_PATH, STOP_WORDS_PATH); 

  const char* s = "江苏南京市长江大桥";
  size_t len = strlen(s);
  CJiebaWord* words = Cut(handle, s, len); 
  CJiebaWord* x;
  
  int i=1;
  char *pi;

  for (x = words, i=1; x && x->word; x++, i++) {

	pi = malloc (x->len + 1);
	memset (pi, 0, x->len + 1);
	strncpy (pi, x->word, x->len);
	
    printf("%d %d %s\n", i, x->len, pi);
	free (pi);
  }

  for (x = words; x && x->word; x++) {
    printf("%*.*s\n", x->len, x->len, x->word);
  }
  FreeWords(words);
  FreeJieba(handle);
}

void CutWithTagDemo() {
  printf("CutWithTagDemo:\n");
  // init will take a few seconds to load dicts.
  Jieba handle = NewJieba(DICT_PATH, HMM_PATH, USER_DICT, IDF_PATH, STOP_WORDS_PATH);

  const char* s = "我是拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上CEO，走上人生巅峰。";
  size_t len = strlen(s);
  CJiebaWordWithTag* words = CutWithTag(handle, s, len);
  CJiebaWordWithTag* x;

  for (x = words; x->word; x++) {
    printf("%*.*s %s\n", x->len, x->len, x->word, x->tag);
  }

  FreeWordTag (words);
  FreeJieba(handle);
}

void CutWithoutTagNameDemo() {
  printf("CutWithoutTagNameDemo:\n");
  // init will take a few seconds to load dicts.
  Jieba handle = NewJieba(DICT_PATH, HMM_PATH, USER_DICT, IDF_PATH, STOP_WORDS_PATH);

  const char* s = "我是拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上CEO，走上人生巅峰。";
  size_t len = strlen(s);
  CJiebaWord* words = CutWithoutTagName(handle, s, len, "x");
  CJiebaWord* x;
  for (x = words; x->word; x++) {
    printf("%*.*s\n", x->len, x->len, x->word);
  }
  FreeWords(words);
  FreeJieba(handle);
}

void ExtractDemo() {
  printf("ExtractDemo:\n");

  // init will take a few seconds to load dicts.
  Extractor handle = NewExtractor(DICT_PATH, 
        HMM_PATH, 
        IDF_PATH,
        STOP_WORDS_PATH,
        USER_DICT); 

  const char* s = "我是拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上CEO，走上人生巅峰。";
  size_t top_n = 5;
  CJiebaWord* words = Extract(handle, s, strlen(s), top_n); 
  CJiebaWord* x;
  for (x = words; x && x->word; x++) {
    printf("%*.*s\n", x->len, x->len, x->word);
  }
  FreeWords(words);
  FreeExtractor(handle);
}

void UserWordDemo()
{
  printf("UserWordDemo:\n");
  Jieba handle = NewJieba(DICT_PATH, HMM_PATH, USER_DICT, IDF_PATH, STOP_WORDS_PATH);

  const char* s = "人艰不拆";
  size_t len = strlen(s);

  CJiebaWord* words = Cut(handle, s, len);
  CJiebaWord* x;
  for (x = words; x->word; x++) {
    printf("%*.*s\n", x->len, x->len, x->word);
  }
  FreeWords(words);

  InsertUserWord(handle, "人艰不拆");
  words = Cut(handle, s, len);
  for (x = words; x->word; x++) {
    printf("%*.*s\n", x->len, x->len, x->word);
  }
  FreeWords(words);

  FreeJieba(handle);
}

void LookupTagDemo ()
{
  printf("LookupTagDemo:\n");
  Jieba handle = NewJieba(DICT_PATH, HMM_PATH, USER_DICT, IDF_PATH, STOP_WORDS_PATH);

  const char* s = "此时此刻";

  char *tag = LookupTag (handle, s);
  printf ("%s\n", tag);

  free (tag);
 
  FreeJieba(handle);
}

void CutAllDemo() {
	printf("CutAllDemo:\n");

	Jieba handle = NewJieba(DICT_PATH, HMM_PATH, USER_DICT, IDF_PATH, STOP_WORDS_PATH);

	const char* s = "我是拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上CEO，走上人生巅峰。";
	size_t len = strlen(s);
	size_t cnt = 0;

	char* words = CutAll(handle, s, len, &cnt);
	char *pi = words;

	len = strlen (pi);
	while (len > 0)
	{
		printf ("%s\n", pi);

		pi += len + 1;
		len = strlen (pi);
	}

	free (words);

	const char* src = "搜索引擎模式，在精确模式的基础上，对长词再次切分，提高召回率，适合用于搜索引擎分词。";
	size_t slen = strlen(src);

	words = CutAll (handle, src, slen, &cnt);

	pi = words;
	len = strlen (pi);
	while (len > 0)
	{
		printf ("%s\n", pi);

		pi += len + 1;
		len = strlen (pi);
	}

	free (words);

	FreeJieba(handle);
}

void CutForSearchDemo() {
	printf("CutForSearchDemo:\n");

	Jieba handle = NewJieba(DICT_PATH, HMM_PATH, USER_DICT, IDF_PATH, STOP_WORDS_PATH);

	const char* s = "我是拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上CEO，走上人生巅峰。";
	size_t len = strlen(s);

	size_t cnt = 0;

	char* words = CutForSearch (handle, s, len, &cnt);
	char *pi = words;

	len = strlen (pi);
	while (len > 0)
	{
		printf ("%s\n", pi);

		pi += len + 1;
		len = strlen (pi);
	}

	free (words);

	FreeJieba(handle);
}

int main(int argc, char** argv) {
//  CutDemo();
//  CutWithoutTagNameDemo();
//  CutWithTagDemo ();
//  ExtractDemo();
//  UserWordDemo();
//  LookupTagDemo ();
	CutAllDemo ();
	CutForSearchDemo();
  return 0;
}
