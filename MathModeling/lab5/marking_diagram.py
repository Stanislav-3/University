from copy import deepcopy
from PyQt5.QtWidgets import *


class Node:
    edges = []

    def __init__(self, places=None, transitions=None, marks=None):
        self.marks = marks
        self.children = []

        # Mark initialization
        if places is not None:
            self.marks = [0] * len(places)
            for place in places:
                self.marks[place.id - 1] = place.mark_count

        # Edges initialization
        if transitions is not None:
            for transition in transitions:
                edge = Edge()
                for edge_in in transition.edges_in:
                    edge.sources.append(edge_in.source.id - 1)
                for edge_out in transition.edges_out:
                    edge.targets.append(edge_out.target.id - 1)

                self.edges.append(edge)

        if marks:
            self.marks = marks

    def __str__(self):
        return f"{self.marks}"


class Edge:
    def __init__(self):
        self.sources = []
        self.targets = []

    def __str__(self):
        return f"s: {self.sources}, t: {self.targets}"


class MarkingDiagram:
    def __init__(self, tree_diagram, places=None, transitions=None):
        self.node = Node(places=places, transitions=transitions)

        print('Start Node:', self.node)

        self.nodes = []
        self.tree_diagram = tree_diagram
        self.tree_diagram.clear()

        topLevel = QTreeWidgetItem(self.tree_diagram)
        topLevel.setText(0, self.node.__str__())
        self.tree_diagram.addTopLevelItem(topLevel)

        self.build(self.node, topLevel)

    def build(self, node: Node, parentTreeItem=None):
        print('In', node)
        self.nodes.append(node)
        is_new_node_list = []

        for edge in node.edges:
            if not self.can_transit(node, edge):
                continue

            marks = self.get_transit_marks(node, edge)
            new_node = Node(marks=marks)

            existing_node = self.find_node(marks)

            if existing_node is not None:
                node.children.append(existing_node)
                is_new_node_list.append(False)
            else:
                node.children.append(new_node)
                is_new_node_list.append(True)

        for i, child_ in enumerate(node.children):
            # QTreeWidget
            child = QTreeWidgetItem(parentTreeItem)
            child.setText(0, child_.__str__())
            # parentTreeItem.addChild(child)

            # Recursion
            if is_new_node_list[i]:
                self.build(child_, child)

    def find_node(self, marks):
        for node in self.nodes:
            if node.marks == marks:
                return node

        return None

    def can_transit(self, node: Node, edge: Edge):
            if len(edge.sources) == 0 or len(edge.targets) == 0:
                return False

            for source_idx in edge.sources:
                if node.marks[source_idx] == 0:
                    return False

            return True

    def get_transit_marks(self, node, edge):
        marks = deepcopy(node.marks)
        print('edge sources', edge.sources)
        print('edge targets', edge.targets)

        for idx in edge.sources:
            marks[idx] -= 1

        for idx in edge.targets:
            marks[idx] += 1

        return marks

    def find_parallel_execution(self, marks):
        parallel_transitions = []

        parent = self.find_node(marks)
        if parent is None:
            return parallel_transitions

        children = parent.children
        all_parallel = []
        for i in range(len(children)):
            child1 = children[i]
            parallel = [child1]

            for j in range(i + 1, len(children)):
                child2 = children[j]
                for idx in self.find_souce_idxs(parent.marks, child1.marks) \
                           | self.find_souce_idxs(parent.marks, child2.marks):
                    pass

    def find_souce_idxs(self, s, t):
        assert len(s) == len(t)
        idxs = set()

        for i in range(len(s)):
            if t[i] < s[i]:
                idxs.add(i)

        return idxs


if __name__ == 'main':
    edges = [
        Edge(sources=[0, 1], targets=[2, 3]),
        Edge(sources=[2], targets=[4]),
        Edge(sources=[2, 5], targets=[4, 5]),
        Edge(sources=[3], targets=[6]),
        Edge(sources=[6], targets=[1]),
    ]

    node = Node()
    Node.edges = edges
    node.marks = [2, 1, 0, 0, 0, 1, 0]

    diagram = MarkingDiagram()
    diagram.node = node
    diagram.build(node)






