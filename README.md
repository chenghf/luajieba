# luajieba 

[![Author](https://img.shields.io/badge/author-@chenghf-blue?style=flat)](http://www.znlyq.cn/) 
[![License](https://img.shields.io/badge/license-MIT-yellow.svg?style=flat)](http://chenghf.mit-license.org)

结巴分词lua语言扩展

## 用法示例

首先下载 cppjieba 和 limonp, 添加符号连接

例如:
```
cd luajieba/deps
ln -s ../../cppjieba-5.1.0/include/limonp limonp
ln -s ../../cppjieba-5.1.0/include/cppjieba cppjieba
```

编译

```
make
lua example/example.lua

```
## base from
+ [cjieba] C语言版本的结巴分词。
+ [cppjieba] C++语言版本的结巴分词。
+ [limonp]:https://github.com/yanyiwu/limonp
