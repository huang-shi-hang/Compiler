# 使用flex创建一个lexer

## 使用方式

```shell
cmake ../
make
./Lexer
```


# 使用flex&bison创建一个parser并且生成语法树

## 使用方式
```shell
cd build
cmake ../
make
./PARSER input.c
```

## Compiler的运行

进入compiler的build目录,运行下面的命令，即可在input.s中看到相应的汇编。

```shell
cd compiler/build
./COMPILER input.c > input.s
```

## IR的运行

进入IR的build目录，运行下面的命令， 即可在IR的四元组和相应的常量表，符号表。

```shell
cd IR/build
./IR input.c
```

