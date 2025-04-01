#include <stdio.h>
#include <string.h>
#include <unistd.h>

const int screen_width = 100;               // 屏幕长
const int screen_height = 25;               // 屏幕宽
const float theta_spacing = 0.01;           // 旋转点的步长
const float phi_spacing = 0.01;             // 旋转圆的步长
const int theta_cnt = 6.28 / theta_spacing; // 旋转点的次数
const int phi_cnt = 6.28 / phi_spacing;     // 旋转圆的次数
const float spin = 0.5;                     // 长宽比
const float R1 = 1;                         // 圆半径
const float R2 = 2;                         // 甜甜圈半径
const float K1 = 20;                        // 参数
const float K2 = 5;                         // 参数

void rotate(float tan, float &x, float &y); // 声明旋转函数
int main() {
  float z_buffer[screen_width * screen_height];
  char b[screen_width * screen_height];

  // 初始化
  float cosphi = 1, sinphi = 0;
  float costheta = 1, sintheta = 0;
  float cosA = 0, sinA = 1;
  float cosB = 1, sinB = 0;

  printf("\x1b[2J"); // 清屏

  for (;;) {
    memset(b, 32, screen_width * screen_height);
    memset(z_buffer, 0, 4 * screen_width * screen_height);

    for (int i_phi = 0; i_phi < phi_cnt; ++i_phi) {
      for (int i_theta = 0; i_theta < theta_cnt; ++i_theta) {
        // 计算甜甜圈坐标
        float circlex = R2 + R1 * costheta;
        float circley = R1 * sintheta;
        float x = circlex * (cosB * cosphi - sinA * sinB * sinphi) -
                  circley * cosA * sinB;
        float y = circlex * (sinB * cosphi + sinA * cosB * sinphi) +
                  circley * cosA * cosB;
        float z = K2 - cosA * circlex * sinphi + circley * sinA;
        float ooz = 1 / z; // "one over z"

        // 计算甜甜圈在屏幕上的坐标
        int xp = (int)(screen_width / 2.0 + K1 * ooz * x);
        int yp = (int)(screen_height / 2.0 - K1 * ooz * spin * y);

        // 计算各点亮度
        int L = 8 * (cosphi * costheta * sinB + cosA * costheta * sinphi -
                     sinA * sintheta +
                     cosB * (cosA * sintheta + costheta * sinA * sinphi));

        // 将各点坐标根据其亮度映射为不同的符号
        int position = xp + screen_width * yp;
        if (screen_height > yp && yp > 0 && xp > 0 && screen_width > xp &&
            ooz > z_buffer[position]) {
          z_buffer[position] = ooz;
          b[position] = ".,-~:;=!*#$@"[L > 0 ? L : 0];
        }

        // 旋转形成圆
        rotate(theta_spacing, costheta, sintheta);
      }

      // 旋转形成甜甜圈
      rotate(phi_spacing, cosphi, sinphi);
    }

    printf("\x1b[H"); // 坐标轴移回原点

    for (int k = 0; k < screen_width * screen_height; ++k) {
      putchar(k % screen_width ? b[k] : 10);
    }
    rotate(0.0704, cosA, sinA); // tan(0.0704)
    rotate(0.0352, cosB, sinB); // tan(0.0352)
    // 画面每一帧之间的间隔
    usleep(30000);
  }
  return 0;
}

// 定义旋转函数
void rotate(float tan, float &x, float &y) {
  float tmp = x;
  x -= tan * y;
  y += tan * tmp;
  tmp = (3 - x * x - y * y) / 2; // tmp这里为修正项
  x *= tmp;
  y *= tmp;
}
