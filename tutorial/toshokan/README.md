# Toshokanの使い方

### ATTENTION!

本章では、Toshokanのコードを記述したり、デバッグをする際に必要となる事項を解説しています。しかし、 **最初からこの章を全て読み込む必要はありません。** とりあえずはこのページを軽く眺め、概要を頭の片隅に置いてておくだけで十分です。Toshokanを使っている中で困った時に後から読み返してみてください。

本章を後回しにして良い理由は、このページの内容が皆さんにとって本質的では無いからです。今このページを読んでる皆さんの一番の目的は、「ベアメタルプログラミングを通してx86アーキテクチャを理解する事」であり、「Toshokanをどう使うか」はそのための手段に過ぎない事をお忘れなく。


1. [Toshokanのアーキテクチャ](./architecture/)

    Toshokanには、Linux上で実行される'hakase'と、ベアメタル上で実行される'friend'の両者が存在します。また、両者はそれぞれ異なるコア上で実行されています。このページでは、なぜToshokanがこのようなアーキテクチャを採用しているのか、そしてこのアーキテクチャがどのように実現されているかを解説します。

1. [friend上でできる事、できない事](./friend/)

    ベアメタル環境はOSによる一切の支援が受けられません。例えば、printf()等を含む、libcの関数を呼び出す事もできません。もちろん、hakaseによるサポートがあるので、friendでのコード実行は一般的なベアメタルプログラミングよりも遥かに簡単です。それでもなお、一般的なLinuxプログラムができる事で、friendができない事は多く存在します。同時に、friendにしかできない事もあります。このページではその両者について見ていきましょう。

1. [hakaseとfriend間のsymbol解決](./symbol_resolution/)

    Toshokanプログラミングにおいて、hakaseとfriendの双方から同じ変数にアクセスしなければいけない事があるでしょう。friend側で特定の様式と共に定義した変数は、hakase側から参照する事ができます。そのやり方を確認しましょう。

1. [friendからhakaseへのコードのoffloading](./offloading/)

   標準ライブラリ関数等、hakaseでしか実行できない関数を呼び出す際は、offloadingが便利です。そのやり方と、メモリ管理時の注意点を解説します。

1. [Makefileの解説/ビルドとQEMU実行のプロセス](./makefile/)

   各々のサンプルに付属するMakefileの各行が何を目的としているのかを紐解きます。これによって、バイナリがどのようにコンパイルされるか、また実行時にどのような構成でhakaseバイナリが実行されるのかを明確化します。

1. [QEMUモニタを用いたデバッグ](./monitor/)

   friendコードのバグが治らない時は、printfだけに頼るのでは無く、CPUやメモリの情報を直接表示してみましょう。QEMUモニタの接続方法と、簡単な使い方を説明します。

1. [実機実行](./physical_machine/)

   デフォルトではToshokanはQEMU仮想マシン上で動作しますが、物理マシン上で動作させる事も容易に（コード等を変更する事無く）可能です。物理マシン上での設定と、起動方法を解説します。

1. [困った時は](./q_and_a/)

   なぜかToshokanが実行できない、実行したけど、意図しない動作をする。そんな時のためのトラブルシューティングです。

<!--
1. hakaseの活用例

    hakaseは、一般的に高い技術が必要とされるベアメタルプログラミングを極限まで平易にしてくれる物です。皆さんがhakaseを用いて具体的にどのような事ができるか見てみましょう。
-->