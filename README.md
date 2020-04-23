注 : この描画プラットフォームは、現在絶賛(?)開発中です。


# Cairo Sparkle について

**Cairo Sparkle**  縮めて **CaSp**

CaSpは、C++で動作する[Cairo](https://www.cairographics.org/)ベースの描画プラットフォームです。

また、Windowアプリケーション用・デバッグ機能のバックエンドとして[GTK3](https://www.gtk.org/)
を採用しています。

___

## 主な特徴

 - **数多くの出力形式**
   - 単一のプログラムから、**Window アプリケーション、動画、ラスタ・ベクタ画像、PDF資料**...
     いろんな出力形式に対応できる描画ライブラリを目指します。
   - 対応予定の出力形式は、Cairo による PNG、JPG、SVG、PDF と、libavcodec に
     よる MP4、GIF です。WebKitGTK による Web ページも検討中。他にも随時追加予定。
  
 - **Cairoの機能を活かした滑らかで高速な描画機能** 
   - ベクターグラフィックスライブラリCairoにより、滑らかで高速な描画ができます。
   　また図形や画像の回転・拡縮にも対応可能です。

 - **限定(簡潔化)された機能量**
   - 操作のために必要な知識は少なく、入門してからすぐにでも制作に着手できるように設計しています。
  
  
___

## ビルド方法(現状)

まだ正式なビルド環境は整備していません。

#### 環境構築

Ubuntu19.10 での構築例。

・gtk3をインストール

(Cairoはgtk3に組み込まれているので別途インストールする必要はありません。)

・CaSpのcloneをダウンロード

#### 実行

コンパイルするcppファイルは、src/cairo_sparkle.hppを
includeする必要があります。

g++、demo/DEMO.cppでの実行例
(clang++にも対応しています。)

```
g++ -o [生成する実行ファイル] [コンパイルするcppファイル] $(pkg-config --cflags --libs gtk+-3.0) {PATHを通さない場合}(-I [cairo_sparkleのディレクトリ]) -lpng -std=c++17
```


demo/DEMO_blockout.cpp
```
g++ -o DEMO demo/DEMO_blockout.cpp $(pkg-config --cflags --libs gtk+-3.0) -lpng -std=c++17
```

