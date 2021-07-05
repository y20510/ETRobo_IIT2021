# ヘッダファイルの最初に書くこと
#ifndefとは条件によってコンパイルしたりしなかったりを制御できる。

重複定義の回避
ヘッダファイルを作るとき、#ifndefと#endif、および記号定数を定義する#define
という疑似命令を使う。
ヘッダファイルの先頭に

#ifndef "sample_h_"<br>
#define "sample_h_"

を入れておく。
そしてヘッダファイルの最後に次の1行を入れる

#endif

このヘッダファイルが初めてインクルードされた時は
#define "sample_h_"は定義されていない。
したがって下の内容はコンパイルされる。そして#defineによって記号定数
"sample_h_"が定義される。

２回目以降インクルードされるとすでに"sample_h_"は定義されている。そのため
#define以下の内容は無視される。
つまり、１つのプログラムで"sample_h_"が何回インクルードされても定義は１回だけ。
