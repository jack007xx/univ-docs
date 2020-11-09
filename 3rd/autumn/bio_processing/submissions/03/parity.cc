#include <math.h>

#include <iostream>
#include <random>
#include <vector>

using namespace std;

// シグモイドとその微分
double sigmoid(double x) { return (1.0 / (1.0 + exp(-x))); }

double h_out(double x[3], double w1[3][2], int j) {
  double h = 0;
  for (int i = 0; i < 3; i++) {
    h += double(x[i]) * w1[i][j];
  }
  return sigmoid(h);
}
double y_out(double h[3], double w2[3][1]) {
  double y = 0;
  for (int i = 0; i < 3; i++) {
    y += h[i] * w2[i][0];
  }
  return sigmoid(y);
}

int main() {
  // 入力のテスト
  double x[][3] = {
      {0, 0, -1},
      {0, 1, -1},
      {1, 0, -1},
      {1, 1, -1},
  };
  // 重みをランダムに生成する
  double w1[3][2], w2[3][1];
  std::random_device rnd;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) w1[i][j] = (double)rnd() / RAND_MAX;
    w2[i][0] = (double)rnd() / RAND_MAX;
  }

  // // 以下表示部なので、関係なし。
  cout << "重み 入→中" << endl;
  for (auto &&i : w1) {
    for (auto &&j : i) cout << j << ' ';
    cout << endl;
  }
  cout << "重み 中→出" << endl;
  for (auto &&i : w2) {
    for (auto &&j : i) cout << j << ' ';
    cout << endl;
  }

  double lambda = 1;

  // diff(誤差の自乗平均)がtarget以下になると止まる
  double diff = MAXFLOAT, target = 0.001;
  double y, d, y_local[4];

  while (1) {
    diff = 0;
    for (int xi = 0; xi < 4; xi++) {
      // 中間層の値
      double h[3];
      h[0] = h_out(x[xi], w1, 0);
      h[1] = h_out(x[xi], w1, 1);
      h[2] = -1;

      // 出力の値
      y = y_out(h, w2);
      y_local[xi] = y;
      // 正解の値
      d = double(not(int(x[xi][0]) xor int(x[xi][1])));

      // 中→出の重み調整
      for (int i = 0; i < 3; i++) {
        w2[i][0] += lambda * (d - y) * y * (1.0 - y) * h[i];
      }
      // 入→中の重み調整
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
          w1[i][j] += lambda * h[j] * (1.0 - h[j]) * w2[j][0] * (d - y) * y *
                      (1.0 - y) * x[xi][i];
        }
      }
      diff += pow(d - y, 2) / 2.0;
    }
    diff = diff / 4.0;
    if (diff < target) break;
  }

  for (auto &&i : y_local) cout << i << endl;

  // // 以下表示部なので、関係なし。
  cout << "重み 入→中" << endl;
  for (auto &&i : w1) {
    for (auto &&j : i) cout << j << ' ';
    cout << endl;
  }
  cout << "重み 中→出" << endl;
  for (auto &&i : w2) {
    for (auto &&j : i) cout << j << ' ';
    cout << endl;
  }

  return 0;
}
