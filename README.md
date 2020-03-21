注 : この描画プラットフォームは、現在絶賛開発中です。

現在contributionは受け付けておりませんが、開発が十分に進んだ後に随時受付を開始します。

# Cairo Sparkle について

**Cairo Sparkle**  縮めて **CaSp**

CaSpは、C++で動作する[Cairo](https://www.cairographics.org/)ベースの描画プラットフォームです。

描画機能を利用したウインドウアプリケーションを、手軽に作成することができます。

### 主な特徴

 - **Cairoの機能を活かした滑らかで高速な描画機能** 
   
 - **限定(簡潔化)された機能量**
   - 操作のために必要な知識は少なく、入門してからすぐにでも制作に着手できるように設計。
   - そのかわり、操作の柔軟性・自由度はある程度制限しているーーー - - -
   

### To Do (個人用)

 - [x] 動作確認用のCairo Sparkle GUIを(ある程度)実装
 
 - [x] 座標型など、基礎部分で用いる構造体・機能(関数)の実装

 - [x] 基本オブジェクト(座標、スケール、色)の実装

 - [x] 四角形オブジェクトの追加

 - [ ] テキストオブジェクトの追加

 - [x] カメラの追加

 - [ ] 画像オブジェクトの追加

 - [ ] 基本オブジェクト -- 回転機能の追加

 - [ ] Cairo Sparkle GUI の完全版の実装

...随時追加予定。

## Cairo Sparkle GUI

**Cairo Sparkle GUI** は、Cairo Sparkle上の描画処理をウインドウで動作させるための[GTK3](https://www.gtk.org/)ベースのプログラムです。


