
from env import HEIGHT


class Player:
    def __init__(self):
        self.value_y = HEIGHT/2

    def get_pos(self):
        return int(self.value_y)
