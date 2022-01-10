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


def depth(node: Node):
    if node is None:
        return 0

    return max(depth(node.left), depth(node.left)) + 1


head = Node(9)
# append(head, Node(4))
# append(head, Node(11))
# append(head, Node(3))
# append(head, Node(57))
# append(head, Node(1))
# append(head, Node(2))
# append(head, Node(20))
# append(head, Node(8))

print(depth(head))
