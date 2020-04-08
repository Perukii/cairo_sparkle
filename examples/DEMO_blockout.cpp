

#include "src/cairo_sparkle.cpp"
#include <cmath>
#include <algorithm>

#define board_x 8
#define board_y 10
#define life_max 9

// GUIホスト・メインサーフェスの定義
casp_window_host host;
casp_surface surface;

// ブロックのクラス
class block : public casp_rect {
  public:
    bool isbroken;
    void setup_flag() { isbroken = false; }
};

// ~~~ 各オブジェクトの定義 ~~~

casp_rect player, stage, sphere;
block blocks[board_y][board_x];
casp_text score, life;

// ~~~ 物理・スコア計算用の変数の定義 ~~~

double sphere_angle, sphere_speed;
int times, broken, life_rest;
casp_rgb main_color = casp_rgb(0.2, 0.2, 0.2, 1.0);
casp_rgb text_color = casp_rgb(0.4, 0.4, 0.4, 1.0);

void setup_game() {

    times = 0;
    broken = 0;
    life_rest = life_max;

    // 矩形オブジェクトのセットアップ (x,y,w,h,color,pivotx,pivoty)
    player.setup_rect(0.0, 8.5, 2.0, 0.5, main_color, 0.5, 0.0);
    stage.setup_rect(0.0, 0.5, surface.scale_range.x - 1.0,
                     surface.scale_range.y, casp_rgb_null);
    sphere.setup_rect(0.0, 8.3, 0.25, 0.25, casp_rgb_white, 0.5, 1.0);

    // 枠線のセットアップ (w,color)
    stage.setup_stroke(0.1, main_color);
    sphere.setup_stroke(0.06, main_color);

    // テキストのセットアップ (テキスト,x,y,w,h,color,pivotx,pivoty)
    score.setup_text("", -3.0, 1.0, casp_auto, 1.0, text_color);
    life.setup_text("", -3.0, 2.5, casp_auto, 1.0, text_color);

    // ブロックのセットアップ
    for (int iy = 0; iy < board_y; iy++) {
        for (int ix = 0; ix < board_x; ix++) {
            blocks[iy][ix].setup_rect(0.55 - surface.scale_range.x * 0.5 +
                                          (stage.xywh.w / board_x * ix) * 0.99,
                                      0.6 - surface.scale_range.y * 0.5 +
                                          0.78 * iy,
                                      stage.xywh.w / board_x, 0.75,
                                      casp_rgb(0.4, 0.4, 0.4, 1.0), 0, 0);
            blocks[iy][ix].setup_stroke(0.1, casp_rgb_white);
            blocks[iy][ix].setup_flag();
        }
    }
}

void sphere_process(casp_xy<double> *_tar_xy) {
    _tar_xy->x += std::sin(sphere_angle) * sphere_speed;
    _tar_xy->y -= std::cos(sphere_angle) * sphere_speed;
}

bool sphere_collision(casp_rect *_tar_rect, casp_xy<double> _tar_xy) {
    sphere_process(&_tar_xy);
    return _tar_rect->on_point(_tar_xy);
}

bool sphere_collision_all() {

    for (int iy = 0; iy < board_y; iy++) {
        for (int ix = 0; ix < board_x; ix++) {
            if (sphere_collision(&blocks[iy][ix], sphere.xywh) == true) {
                blocks[iy][ix].isbroken = true;
                return false;
            }
        }
    }

    return sphere_collision(&stage, sphere.xywh) == true and
           (sphere_collision(&player, sphere.xywh) == false or
            player.xywh.x >= sphere.xywh.y);
}

void casp_main() {

    times += (times != 0);

    sphere_speed += 0.00015;

    double stage_width=(stage.xywh.w-player.xywh.w)*0.5;
    player.xywh.x = std::clamp(host.mouse_pos.x, -stage_width, stage_width);

    if (times == 0) {
        sphere.xywh.x = player.xywh.x;
        sphere.xywh.y = player.xywh.y;
        sphere_angle = M_PI * 0.25;
        sphere_speed = std::max(sphere_speed * 0.75, 0.2);

        if (host.get_button_press(1) == true)
            times = 1;
    }

    else if (broken != board_x * board_y) {

        int ref_flag = 0;

        double sphere_angle_st = sphere_angle;

        while (!sphere_collision_all()) {

            if (++ref_flag <= 3) {
                sphere_angle = sphere_angle_st * (ref_flag <= 2 ? -1 : 1) +
                               M_PI * (ref_flag % 2);
            } else
                break;
        }
        // 玉を動かす
        sphere_process(&sphere.xywh);
    }

    // 玉を落とした時
    if (sphere.xywh.y >= surface.scale_range.y * 0.5) {
        life_rest--;
        times = 0;
        if (life_rest < 0)
            setup_game();
    }

    
    //host.surface -> zoom = 1.1;
    //host.surface -> xy = casp_xy<double>(sphere.xywh)*casp_xy<double>(0.1,0.1);

    // ==== INPUT =====

    host.debug_QWEASD();

    if (host.get_key_press(32)) {
        host.write_png(
            "/home/tada/Documents/Codes/CASP/cairo_sparkle/test.png");
    }
}

void casp_draw() {
    // ==== DRAW ====

    surface.fill_white();

    for (int iy = 0; iy < board_y; iy++) {
        for (int ix = 0; ix < board_x; ix++) {
            if (blocks[iy][ix].isbroken == false)
                blocks[iy][ix].draw_rect();
            else {
                if (blocks[iy][ix].xywh.x != 0)
                    broken++;
                blocks[iy][ix].xywh = {0, 0, 0, 0};
            }
        }
    }

    score.text = "SCORE : " + std::to_string(broken * 100);
    life.text = "REST : " + std::to_string(life_rest);

    player.draw_rect();
    sphere.draw_rect();
    stage.draw_rect();

    score.draw_text();
    life.draw_text();

    if (broken == board_x * board_y) {
        casp_text("CONGRATULATIONS !", -6.0, -4.5, casp_auto, 1.2, text_color,
                  0.0, 0.0).draw_text();
        if (host.get_button_press(1) == true)
            setup_game();
    }
}

int main(int _argc, char **_argv) {

    casp_init(_argc, _argv);
    host.setup(&surface, 500, 700, casp_translate_norm_w);
    casp_default_surface(&surface);
    setup_game();
    host.run();
}