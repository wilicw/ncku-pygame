class player {
public:
  void push(int direction) {
    if (direction > 0) {
      // UP
      if (position > 0)
        position -= 5;
    } else {
      // DOWN
      if (position < 360 - length)
        position += 5;
    }
  };
  int get_position() { return position; }
  int get_length() { return length; }

private:
  int position = 0;
  const int length = 100;
};