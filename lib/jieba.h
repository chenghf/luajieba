#ifndef CJIEBA_C_API_H
#define CJIEBA_C_API_H

#include <stdlib.h>
#include <stdbool.h>

#define MAX_TAG_LEN	7

typedef void* Jieba;
Jieba NewJieba(const char* dict_path, const char* hmm_path, const char* user_dict, const char* idf_path, const char* stop_word_path);
void FreeJieba(Jieba);

typedef struct {
  const char* word;
  size_t len;
} CJiebaWord;

typedef struct {
  const char* word;
  size_t len;
  char tag[MAX_TAG_LEN+1];
} CJiebaWordWithTag;

CJiebaWord* Cut(Jieba handle, const char* sentence, size_t len);

CJiebaWord* CutWithoutTagName(Jieba, const char*, size_t, const char*);

void FreeWords(CJiebaWord* words);

CJiebaWordWithTag* CutWithTag(Jieba, const char*, size_t);

void FreeWordTag(CJiebaWordWithTag* words);

char* CutAll (Jieba handle, const char* sentence, size_t len, size_t *cnt);
char* CutForSearch (Jieba handle, const char* sentence, size_t len, size_t *cnt);

char* LookupTag (Jieba handle, const char *word);

bool InsertUserWordWithFreq (Jieba handle, const char* word, int freq);
bool InsertUserWord (Jieba handle, const char* word);
bool DeleteUserWord (Jieba handle, const char* word);

typedef void* Extractor;

Extractor NewExtractor(const char* dict_path,
      const char* hmm_path,
      const char* idf_path,
      const char* stop_word_path,
      const char* user_dict_path);

CJiebaWord* Extract(Extractor handle, const char* sentence, size_t len, size_t topn);

void FreeExtractor(Extractor handle);

#endif
