
#include "src/cairo_sparkle.cpp"

c_host host; // host:ウインドウ作成機能・出力機能等のシステム的な機能を一括管理
c_rect rect; // rect(矩形)

void main_loop(){ // メインループ:タスクが終了するまで繰り返し実行される
    rect.xywh.x+=0.01; // rectを右に進める 
    rect.draw_rect();  // rectを描画

    if(host.get_key_press(32))     // スペースキーを押したら、その時点の
       host.write_png("test.png"); // 描画内容を「test.png」に出力
}

int main() {
    host.setup_host({500, 500}); // hostのセットアップ(解像度:500x500)
    host.set_titlebar("THANKS"); // hostにタイトルバーを追加
    host.set_background(casp_rgb(1.0, 1.0, 1.0, 1.0)); // hostの背景は白
    rect.setup_rect({0.0, 0.0, 3.0, 3.0}, casp_rgb_adv_skyBlue);
        // rectのセットアップ(位置(0,0),大きさ(3,3),空色)
    host.run(main_loop); // main_loopをメインループとして登録・実行
}

