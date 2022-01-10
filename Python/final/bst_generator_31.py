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


def BSTGen(tree_head: Node):
    def rec(node):
        if node is None:
            return

        for left_el in rec(node.left):
            yield left_el

        yield node

        for right_el in rec(node.right):
            yield right_el

    for el in rec(tree_head):
        yield el


data = [3, 2, 8, -3, 2, 0, 4]
nodes = [Node(e) for e in data]

tree_head = Node(5)
for i in range(len(nodes)):
    append(tree_head, nodes[i])

for node in BSTGen(tree_head):
    print(node.value)