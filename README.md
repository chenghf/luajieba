# luajieba 

[![Author](https://img.shields.io/badge/author-@chenghf-blue?style=flat)](http://www.znlyq.cn/) 
[![Platform](https://img.shields.io/badge/platform-Linux,%20OS%20X-green.svg?style=flat)](https://github.com/chenghf/luajieba)
[![License](https://img.shields.io/badge/license-MIT-yellow.svg?style=flat)](http://chenghf.mit-license.org)

结巴分词lua语言扩展

## 用法示例

下载 cppjieba (tag v5.4.0)

git clone --branch v5.4.0 https://github.com/yanyiwu/cppjieba

下载 limonp (tag v1.0.0)

git clone --branch v1.0.0 https://github.com/yanyiwu/limonp

目录结构如下

```
/--source
  |--cppjieba
  |--limonp
  |--luajieba
```

添加符号连接

```
mkdir luajieba/deps
cd luajieba/deps
ln -s ../../limonp/include/limonp limonp
ls -s ../../cppjieba/include/cppjieba cppjieba
```

编译

```
make
lua example/example.lua
```
## base from
+ [cjieba](https://github.com/yanyiwu/cjieba) C语言版本的结巴分词。
+ [cppjieba](https://github.com/yanyiwu/cppjieba) C++语言版本的结巴分词。
+ [limonp](https://github.com/yanyiwu/limonp)
