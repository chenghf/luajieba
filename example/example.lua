local jieba = require "jieba"

local jieba_dict = './dict/jieba.dict.utf8'
local hmm_dict = './dict/hmm_model.utf8'
local user_dict = './dict/user.dict.utf8'
local idf_dict = './dict/idf.utf8'
local stop_word = './dict/stop_words.utf8'

function out_put (words, title)

	print (title)
	for k, v in pairs (words) do
		print (k, v)
	end
end

local cws, err = jieba.new (jieba_dict, hmm_dict, user_dict, idf_dict, stop_word)

-- print (cws, err)

local str = '河南郑州新郑轩辕故里拜祖大典'

local words = cws:cut (str)
out_put (words, 'cut')

str = '江苏南京市长江大桥'

words = cws:cut (str)
out_put (words, 'cut')

local tag = cws:lookup_tag ('故人')
print (tag)

str = '人艰不拆'

words = cws:cut (str)
out_put (words, 'cut')

cws:insert_userword (str)
words = cws:cut (str)
out_put (words, 'user word')

cws:delete_userword (str)

words = cws:cut_all (str)
out_put (words, 'cut all')

str = '搜索引擎模式，在精确模式的基础上，对长词再次切分，提高召回率，适合用于搜索引擎分词。hello word! this is test message.'
words = cws:cut_for_search (str)
out_put (words, 'cur for search')

words = cws:cut_without_tagname (str, 'x')
out_put (words, 'cur without tag x')

words = cws:cut_with_tag (str)
print ('cut with tag')
for k, v in pairs (words) do
	print (k, v.word, v.tag)
end

local str1 = '搜索引擎模式，在精确模式的基础上，对长词再次切分，提高召回率，适合用于搜索引擎分词。hello word!'
local extracor, err = jieba.extractor (jieba_dict, hmm_dict, user_dict, idf_dict, stop_word)
-- print (extracor, err)

words = extracor:extract (str1)
out_put (words, 'extract exapmle')
