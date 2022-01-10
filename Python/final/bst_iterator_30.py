class Node:
    def __init__(self, value=0, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right


def append(head: Node, node: Node):
    current = head
    temp = None
    while current is not None:
        temp = current
        if node.value < current.value:
            current = current.left
        else:
            current = current.right

    if node.value < temp.value:
        temp.left = node
    else:
        temp.right = node


class BSTIter:
    def __init__(self, root):
        self.prev_nodes = [(root, True)]  # node, is_left

    def __iter__(self):
        return self

    def __next__(self):
        if len(self.prev_nodes) == 0:
            raise StopIteration

        cur_node, is_left = self.prev_nodes.pop()
        if is_left:
            while cur_node:
                self.prev_nodes.append((cur_node, False))
                cur_node = cur_node.left

            cur_node = self.prev_nodes.pop()[0]

        if cur_node.right:
            self.prev_nodes.append((cur_node.right, True))

        return cur_node


data = [3, 2, 8, -3, 2, 0, 4]
nodes = [Node(e) for e in data]

tree_head = Node(5)
for i in range(len(nodes)):
    append(tree_head, nodes[i])


for node in BSTIter(tree_head):
    print(node.value)