extern "C" {
    #include "jieba.h"
}

#include <cstring>
#include "cppjieba/Jieba.hpp"
#include "cppjieba/KeywordExtractor.hpp"

using namespace std;

extern "C" {

Jieba
NewJieba (const char* dict_path,
			const char* hmm_path,
			const char* user_dict,
			const char* idf_path,
			const char* stop_words_path)
{
	Jieba handle = (Jieba) (new cppjieba::Jieba(dict_path,
												hmm_path,
												user_dict,
												idf_path,
												stop_words_path));
	return handle;
}

void
FreeJieba (Jieba handle)
{
	cppjieba::Jieba* x = (cppjieba::Jieba*)handle;
	delete x;
}

CJiebaWord*
Cut (Jieba handle, const char* sentence, size_t len)
{
	cppjieba::Jieba* x = (cppjieba::Jieba*)handle;
	vector<string> words;
	string s(sentence, len);

	x->Cut (s, words);

	CJiebaWord* res = (CJiebaWord*) malloc (sizeof(CJiebaWord) * (words.size() + 1));
	size_t offset = 0;

	for (size_t i = 0; i < words.size(); i++)
	{
		res[i].word = sentence + offset;
		res[i].len = words[i].size();
		offset += res[i].len;
	}

	if (offset != len)
	{
		free(res);
		return NULL;
	}

	res[words.size()].word = NULL;
	res[words.size()].len = 0;
	return res;
}

CJiebaWordWithTag*
CutWithTag (Jieba handle, const char* sentence, size_t len)
{
    cppjieba::Jieba* x = (cppjieba::Jieba*)handle;
    vector<pair<string, string>> tag_words;

    x->Tag (string(sentence, len), tag_words);

    size_t i, offset = 0, buf_size = 0;
	size_t taglen;

	buf_size = sizeof (CJiebaWordWithTag) * (tag_words.size() + 1);

    CJiebaWordWithTag* res = (CJiebaWordWithTag*) malloc(buf_size);
    memset(res, 0, buf_size);

    CJiebaWordWithTag *current = res;
    for(i = 0; i < tag_words.size(); i++, current++) {

        current->word = sentence + offset;
        current->len = tag_words[i].first.size();

		taglen = tag_words[i].second.size();

		if (taglen > MAX_TAG_LEN)
			taglen = MAX_TAG_LEN;

        memcpy(current->tag, tag_words[i].second.data(), taglen);

        offset += tag_words[i].first.size();
    }

    current->word = NULL;
    current->len = 0;
    return res;
}

void FreeWordTag(CJiebaWordWithTag* words) {
	free(words);
}

CJiebaWord*
CutWithoutTagName (Jieba handle, const char* sentence, size_t len, const char* tagname)
{
	cppjieba::Jieba* x = (cppjieba::Jieba*)handle;
	vector<pair<string, string>> tag_words;

	x->Tag (string(sentence, len), tag_words);

	CJiebaWord* res = (CJiebaWord*) malloc (sizeof(CJiebaWord) * (tag_words.size() + 1));
	size_t i, j, offset = 0;

	for (i = 0, j = 0; i < tag_words.size(); i++)
	{
		if (tag_words[i].second != tagname)
		{
			res[j].word = sentence + offset;
			res[j].len = tag_words[i].first.size();
			j++;
		}

		offset += tag_words[i].first.size();
	}

	res[j].word = NULL;
	res[j].len = 0;
	return res;
}

void
FreeWords (CJiebaWord* words) {
	free(words);
}


char *
CutAll (Jieba handle, const char* sentence, size_t len, size_t *cnt)
{
	char *pi, *buf;
	size_t i, wlen, buf_size = 0;

	cppjieba::Jieba* x = (cppjieba::Jieba*)handle;
	vector<string> words;
	string s(sentence, len);

	x->CutAll (s, words);

	*cnt = words.size ();

	if (*cnt <= 0)
	{
		return NULL;
	}

	for (i = 0; i < words.size(); i++)
	{
		buf_size += words[i].size () + 1;
	}

	buf_size++;

	buf = (char *) malloc (buf_size);
	memset (buf, 0, buf_size);

	pi = buf;
	for (size_t i = 0; i < words.size(); i++)
	{
		wlen = words[i].size ();
        memcpy (pi, words[i].data(), wlen);
		pi += wlen + 1;
	}

	return buf;
}

char *
CutForSearch (Jieba handle, const char* sentence, size_t len, size_t *cnt)
{
	char *pi, *buf;
	size_t i, wlen, buf_size = 0;

	cppjieba::Jieba* x = (cppjieba::Jieba*)handle;
	vector<string> words;
	string s(sentence, len);

	x->CutForSearch (s, words);

	*cnt = words.size ();

	if (*cnt <= 0)
	{
		return NULL;
	}

	for (i = 0; i < words.size(); i++)
	{
		buf_size += words[i].size () + 1;
	}

	buf_size++;

	buf = (char *) malloc (buf_size);
	memset (buf, 0, buf_size);

	pi = buf;
	for (size_t i = 0; i < words.size(); i++)
	{
		wlen = words[i].size ();
        memcpy (pi, words[i].data(), wlen);
		pi += wlen + 1;
	}

	return buf;
}

char *
LookupTag (Jieba handle, const char *word)
{
	string tag;
	char *buf = NULL;
	size_t len;

	cppjieba::Jieba* x = (cppjieba::Jieba*)handle;

	tag = x->LookupTag (string(word));
	len = tag.length ();

	buf = (char *) malloc (len + 1);

	memset (buf, 0, len + 1);

	strncpy (buf, tag.c_str(), len);

	return buf;
}

bool
InsertUserWordWithFreq (Jieba handle, const char* word, int freq)
{
	cppjieba::Jieba* x = (cppjieba::Jieba*)handle;

	return x->InsertUserWord(string(word), freq);
}

bool
InsertUserWord (Jieba handle, const char* word)
{
	cppjieba::Jieba* x = (cppjieba::Jieba*)handle;

	return x->InsertUserWord(string(word));
}

bool
DeleteUserWord (Jieba handle, const char* word)
{
	cppjieba::Jieba* x = (cppjieba::Jieba*)handle;
	return x->DeleteUserWord(string(word));
}

Extractor NewExtractor(const char* dict_path, const char* hmm_path, const char* idf_path,
						const char* stop_word_path, const char* user_dict_path)
{
	Extractor handle = (Extractor) (new cppjieba::KeywordExtractor(dict_path, 
																	hmm_path, 
																	idf_path,
																	stop_word_path,
																	user_dict_path));
  return handle;
}

void
FreeExtractor (Extractor handle)
{
  cppjieba::KeywordExtractor* x = (cppjieba::KeywordExtractor*)handle;
  delete x;
}

CJiebaWord*
Extract (Extractor handle, const char* sentence, size_t len, size_t topn)
{
	cppjieba::KeywordExtractor* x = (cppjieba::KeywordExtractor*)handle;
	vector<cppjieba::KeywordExtractor::Word> words;

	x->Extract (sentence, words, topn);

	CJiebaWord* res = (CJiebaWord*) malloc (sizeof(CJiebaWord) * (words.size() + 1));

	for (size_t i = 0; i < words.size(); i++)
	{
		assert(words[i].offsets.size() > 0);
		size_t offset = words[i].offsets[0];

		assert(offset < len);

		res[i].word = sentence + offset;
		res[i].len = words[i].word.size();
	}

	res[words.size()].word = NULL;
	res[words.size()].len = 0;
	return res;
}

} // extern "C"
