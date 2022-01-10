from units.map.arc import Arc


class Node():
    def __init__(self, name):
        if len(name) >= 15:
            raise Exception('Too large city name...')
        self.name = name
        self.neighbors = []

    def add_neighbor(self, node_name, distance, max_speed = 90):
        for i in range(len(self.neighbors)):
            if self.neighbors[i][0] == node_name:
                return False

        self.neighbors.append((node_name, Arc(distance, max_speed)))
        return True

    def delete_neighbor(self, node_name):
        for i in range(len(self.neighbors)):
            if self.neighbors[i][0] == node_name:
                self.neighbors.pop(i)
                return True

        return False
