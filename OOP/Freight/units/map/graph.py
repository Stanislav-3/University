import threading

from units.map.node import Node
from decorators.cached import cached
from concurrent.futures import ThreadPoolExecutor

class Graph:
    def __init__(self, name):
        if len(name) >= 50:
            raise Exception('Too large map name. Should be < 15 symbols')
        self.name = name
        self.nodes = []

    def __iter__(self):
        self.n = 0
        return self

    def __next__(self):
        if len(self.nodes) <= self.n:
            raise StopIteration
        else:
            self.n += 1
            return self.nodes[self.n - 1]

    def veiw_graph(self):
        for node in self:
            print(f"{node.name:}", end= " | ")
            for j in range(len(node.neighbors)):
                print(f"{node.neighbors[j][0]}"
                f"->{node.neighbors[j][1].distance}/{node.neighbors[j][1].max_speed}   ", end="")
            print()

    def view_graph(self, map_name = True, bullets = True):
        if map_name == True:
            print(self.name, ':')
        bullets = "* " if bullets == True else ''

        for node in self:
            print(f"{bullets}{node.name:}", end= " | ")
            for j in range(len(node.neighbors)):
                print(f"{node.neighbors[j][0]} ", end="")
            print()

    def add_nodes(self, node_name_1, node_name_2, distance, max_speed = 90):
        if (node_name_1 == node_name_2):
            return

        node_1, node_2 = None, None
        for node in self:
            if (node.name == node_name_1):
                node_1 = node
            if (node.name == node_name_2):
                node_2 = node
            if node_1 is not None and node_2 is not None:
                break

        if node_1 is None:
            node1 = Node(node_name_1)
            node1.add_neighbor(node_name_2, distance, max_speed)
            self.nodes.append(node1)
        else:
            node_1.add_neighbor(node_name_2, distance, max_speed)

        if node_2 is None:
            node2 = Node(node_name_2)
            node2.add_neighbor(node_name_1, distance, max_speed)
            self.nodes.append(node2)
        else:
            node_2.add_neighbor(node_name_1, distance, max_speed)

    def delete_node(self, name):
        i = 0
        while i < len(self.nodes):
            if self.nodes[i].name == name:
                del self.nodes[i]
            else:
                j = 0
                while(j < len(self.nodes[i].neighbors)):
                    if self.nodes[i].neighbors[j][0] == name:
                        del self.nodes[i].neighbors[j]
                        j -= 1
                        if len(self.nodes[i].neighbors) == 0:
                            del self.nodes[i]
                            i -= 1
                            break
                    j += 1
                i += 1

    def delete_arc(self, name1, name2):
        i = self.get_index(name1)
        for j in range(len(self.nodes[i].neighbors)):
            if self.nodes[i].neighbors[j][0] == name2:
                self.nodes[i].neighbors.remove(self.nodes[i].neighbors[j])
                break

        i = self.get_index(name2)
        for j in range(len(self.nodes[i].neighbors)):
            if self.nodes[i].neighbors[j][0] == name1:
                self.nodes[i].neighbors.remove(self.nodes[i].neighbors[j])
                break

    def get_index(self, name):
        for count, value in enumerate(self.nodes):
            if value.name == name:
                return count

    def get_arc_attributes(self, name1, name2):
        for node in self:
            if node.name == name1:
                for j in range(len(node.neighbors)):
                    if name2 == node.neighbors[j][0]:
                        return node.neighbors[j][1]
            elif node.name == name2:
                for j in range(len(node.neighbors)):
                    if name1 == node.neighbors[j][0]:
                        return node.neighbors[j][1]

    def get_route(self, source, target, via_time = True):
        source_exists, target_exists = False, False
        for node in self:
            if source == node.name:
                source_exists = True
            if target == node.name:
                target_exists = True

        if not source_exists:
            raise Exception(f'City "{source}" doesn\'t exist..."')
        if not target_exists:
            raise Exception(f'City "{target}" doesn\'t exist..."')


        w = [float("inf")] * len(self.nodes)
        w[self.get_index(source)] = 0.

        u = [False] * len(self.nodes)
        p = [None] * len(self.nodes)

        for _ in self:
            curr = -1
            for j in range(len(self.nodes)):
                if not u[j] and (curr == -1 or w[j] < w[curr]):
                    curr = j

            if w[curr] == float("inf"):
                break

            u[curr] = True

            for j in range(len(self.nodes[curr].neighbors)):
                with ThreadPoolExecutor() as executor:
                    th1 = executor.submit(self.get_index, self.nodes[curr].neighbors[j][0])

                neighbor = th1.result()
                arc_attributes = self.nodes[curr].neighbors[j][1]

                if via_time == True:
                    weight = arc_attributes.distance / arc_attributes.max_speed
                else:
                    weight = arc_attributes.distance

                if w[curr] + weight < w[neighbor]:
                    w[neighbor] = w[curr] + weight
                    p[neighbor] = curr

        route = Graph(f"Route: {source} -> {target}")
        v_i = self.get_index(target)

        while(self.nodes[v_i].name != source):
            name_1 = self.nodes[v_i].name
            name_2 = self.nodes[p[v_i]].name
            road_attributes = self.get_arc_attributes(name_1, name_2)
            route.add_nodes(name_1, name_2, road_attributes.distance, road_attributes.max_speed)
            v_i = p[v_i]

        return route

    @cached
    def get_route_info(self, source, target):
        route = self.get_route(source, target)
        distance = 0
        speed = 0
        count = 0
        while(len(route.nodes)):
            for i in range(len(route.nodes[0].neighbors)):
                node = route.nodes[0].neighbors[i]
                node_name, arc_attributes = node[0], node[1]

                distance += arc_attributes.distance
                speed += arc_attributes.max_speed
                count += 1

            route.delete_node(route.nodes[0].name)

        speed /= count
        return (distance, distance / speed)

