
from env import HEIGHT


class Spot:
    def __init__(self, value_x=0, value_y=0, radius=5):
        self.value_x = value_x
        self.value_y = value_y
        self.radius = radius
        # self.pos_x = 0
        # self.pos_y = 0

    def get_pos(self):
        return int(self.value_x), int(self.value_y)
