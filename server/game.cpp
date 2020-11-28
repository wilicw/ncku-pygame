#include "player.cpp"
#include <string>

class game {
public:
  player p1;
  player p2;
  std::string_view get_info() {
    info = std::to_string(ball_x) + "," + std::to_string(ball_y) + "," +
           std::to_string(p1.get_position()) + "," +
           std::to_string(p2.get_position()) + "," + std::to_string(p1_score) +
           "," + std::to_string(p2_score);
    // printf("%s", info.data());
    return std::string_view(info);
  }
  void init() {
    ball_x = width / 2;
    ball_y = height / 2;
    speed_x = 3;
    speed_y = 3;
  }
  void tick() {
    ball_x += speed_x;
    ball_y += speed_y;
    if (ball_x <= 0) {
      const int p1_pos = p1.get_position();
      if (p1_pos <= ball_y && ball_y <= p1_pos + p1.get_length()) {
        speed_x *= -1;
      } else {
        init();
        p2_score++;
      }
    }
    if (ball_x >= width) {
      const int p2_pos = p2.get_position();
      if (p2_pos <= ball_y && ball_y <= p2_pos + p2.get_length()) {
        speed_x *= -1;
      } else {
        init();
        p1_score++;
      }
    }
    if (ball_y <= 0 || ball_y >= height) {
      speed_y *= -1;
    }
  }

private:
  const int height = 360;
  const int width = 640;
  int ball_x, ball_y, speed_x, speed_y, p1_score = 0, p2_score = 0;
  std::string info = "";
};