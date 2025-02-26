from enum import Enum
from dataclasses import dataclass
from errors import Missing, Duplicate, OverallValue


class Color(str, Enum):
    RED = "red"
    BLACK = "black"


@dataclass
class Info:
    key: int
    value: int


class RedBlackNode:
    def __init__(self, key: int, value: int, color=Color.RED):
        self.data: Info = Info(key, value)
        self.color: Color = color
        self.left: RedBlackNode | None = None
        self.right: RedBlackNode | None = None
        self.parent: RedBlackNode | None = None

    def __str__(self):
        return (
            f"key: {self.data.key}, value: {self.data.value}, color: {self.color.value}"
        )


class RedBlackTree:
    def __init__(self):
        self.NONE = RedBlackNode(key=0, value=0, color=Color.BLACK)
        self._root = self.NONE

    @property
    def root(self) -> RedBlackNode:
        return self._root

    def insert(self, key: int, value: int = None) -> None:
        new_node = RedBlackNode(key, value)
        new_node.left = self.NONE
        new_node.right = self.NONE

        parent = None
        current = self._root
        while current != self.NONE:
            parent = current
            if new_node.data.key < current.data.key:
                current = current.left
            elif new_node.data.key > current.data.key:
                current = current.right
            else:
                raise Duplicate(msg=f"Запись с ключем {key} уже существует")

        new_node.parent = parent

        if parent is None:
            self._root = new_node
        elif new_node.data.key < parent.data.key:
            parent.left = new_node
        else:
            parent.right = new_node

        new_node.color = Color.RED
        self.fix_insert(new_node)

    def fix_insert(self, node: RedBlackNode) -> None:
        while node != self._root and node.parent.color == Color.RED:
            if node.parent == node.parent.parent.left:
                uncle = node.parent.parent.right
                if uncle.color == Color.RED:
                    uncle.color = Color.BLACK
                    node.parent.color = Color.BLACK
                    node.parent.parent.color = Color.RED
                    node = node.parent.parent
                else:
                    if node == node.parent.right:
                        node = node.parent
                        self.left_rotate(node)
                    node.parent.color = Color.BLACK
                    node.parent.parent.color = Color.RED
                    self.right_rotate(node.parent.parent)
            else:
                uncle = node.parent.parent.left
                if uncle.color == Color.RED:
                    uncle.color = Color.BLACK
                    node.parent.color = Color.BLACK
                    node.parent.parent.color = Color.RED
                    node = node.parent.parent
                else:
                    if node == node.parent.left:
                        node = node.parent
                        self.right_rotate(node)
                    node.parent.color = Color.BLACK
                    node.parent.parent.color = Color.RED
                    self.right_rotate(node.parent.parent)
        self._root.color = Color.BLACK

    def left_rotate(self, x: RedBlackNode) -> None:
        y = x.left
        x.right = y.left
        if y.left != self.NONE:
            y.left.parent = x
        y.parent = x.parent
        if x.parent is None:
            self._root = y
        elif x == x.parent.left:
            x.parent.left = y
        else:
            x.paernt.right = y
        y.left = x
        x.parent = y

    def right_rotate(self, y: RedBlackNode) -> None:
        x = y.left
        y.left = x.right
        if x.right != self.NONE:
            x.right.parent = y
        x.parent = y.parent
        if y.parent is None:
            self._root = x
        elif y == y.parent.right:
            y.parent.right = x
        else:
            y.parent.left = x
        x.right = y
        y.parent = x

    def pre_order_traversal(self, node: RedBlackNode = None) -> None:
        if node is None:
            node = self._root
        if node != self.NONE:
            print(node)
            self.pre_order_traversal(node.left)
            self.pre_order_traversal(node.right)

    def post_order_traversal(self, node: RedBlackNode = None) -> None:
        if node is None:
            node = self._root
        if node != self.NONE:
            self.post_order_traversal(node.left)
            self.post_order_traversal(node.right)
            print(node)

    def in_order_traversal(self, node: RedBlackNode = None) -> None:
        if node is None:
            node = self._root
        if node != self.NONE:
            self.in_order_traversal(node.left)
            print(node)
            self.in_order_traversal(node.right)

    def search(self, key: int) -> RedBlackNode:
        current = self._root
        while current != self.NONE:
            if key < current.data.key:
                current = current.left
            elif key > current.data.key:
                current = current.right
            else:
                return current
        raise Missing(msg=f"Элемента с ключем {key} не существует")

    def transplant(self, u: RedBlackNode, v: RedBlackNode) -> None:
        if u.parent is None:
            self._root = v
        elif u == u.parent.left:
            u.parent.left = v
        else:
            u.parent.right = v
        if v != self.NONE:
            v.parent = u.parent

    def delete(self, key: int) -> None:
        z = self.search(key)

        y = z
        y_original_color = y.color
        if z.left == self.NONE:
            x = z.right
            self.transplant(z, z.right)
        elif z.right == self.NONE:
            x = z.left
            self.transplant(z, z.left)
        else:
            y = self.find_min(z.right)  # Преемник
            y_original_color = y.color
            x = y.right
            if y.parent == z:
                x.parent = y
            else:
                self.transplant(y, y.right)
                y.right = z.right
                y.right.parent = y
            self.transplant(z, y)
            y.left = z.left
            y.left.parent = y
            y.color = z.color

        if x == self.NONE:
            x = self._root

        if y_original_color == Color.BLACK:
            self.fix_delete(x)

    def fix_delete(self, x: RedBlackNode) -> None:
        while x != self._root and x.color == Color.BLACK:
            if x == x.parent.left:
                w = x.parent.right
                if w.color:  # Случай 1: брат x - красный
                    w.color = Color.BLACK
                    x.parent.color = Color.RED
                    self.left_rotate(x.parent)
                    w = x.parent.right
                if (
                    w.left.color == Color.BLACK and w.right.color == Color.BLACK
                ):  # Случай 2: оба ребенка w черные
                    w.color = Color.RED
                    x = x.parent
                else:
                    if (
                        w.right.color == Color.BLACK
                    ):  # Случай 3: левый ребенок w красный, правый — черный
                        w.left.color = Color.BLACK
                        w.color = Color.RED
                        self.right_rotate(w)
                        w = x.parent.right
                    w.color = x.parent.color  # Случай 4: правый ребенок w красный
                    x.parent.color = Color.BLACK
                    w.right.color = Color.BLACK
                    self.left_rotate(x.parent)
                    x = self._root
            else:
                w = x.parent.left
                if w.color:
                    w.color = Color.BLACK
                    x.parent.color = Color.RED
                    self.right_rotate(x.parent)
                    w = x.parent.left
                if w.right.color == Color.BLACK and w.left.color == Color.BLACK:
                    w.color = Color.RED
                    x = x.parent
                else:
                    if w.left.color == Color.BLACK:
                        w.right.color = Color.BLACK
                        w.color = Color.RED
                        self.left_rotate(w)
                        w = x.parent.left
                    w.color = x.parent.color
                    x.parent.color = Color.BLACK
                    w.left.color = Color.BLACK
                    self.right_rotate(x.parent)
                    x = self._root
        x.color = Color.BLACK

    def find_min(self, node: RedBlackNode = None) -> RedBlackNode | None:
        if node is None:
            current = self._root
        else:
            current = node
        while current.left != self.NONE:
            current = current.left
        return current

    def find_max(self, node: RedBlackNode = None) -> RedBlackNode:
        if node is None:
            current = self._root
        else:
            current = node
        while current.right != self.NONE:
            current = current.right
        return current

    def find_nearest_max(self, key: int) -> RedBlackNode | None:
        node = self.search(key)
        if node is None:
            return
        if node.right != self.NONE:
            return self.find_min(node.right)
        else:
            while node != node.parent.left:
                node = node.parent
                if node == self._root:
                    raise OverallValue(msg=f"Элемент с ключом {key} наибольший")
            return node.parent

    def find_nearest_min(self, key: int) -> RedBlackNode | None:
        node = self.search(key)
        if node is None:
            return
        if node.left != self.NONE:
            return self.find_max(node.left)
        else:
            while node != node.parent.right:
                node = node.parent
                if node == self._root:
                    raise OverallValue(msg=f"Элемент с ключом {key} наименьший")
            return node.parent

    def check_properties(
        self, node: RedBlackNode, black_count=0, black_counts=None
    ) -> bool:
        if black_counts is None:
            black_counts = []
        if node == self.NONE:
            black_counts.append(black_count)
            return True
        if node.parent is None and node.color == Color.RED:
            return False
        if node.color == Color.RED:
            if node.left and node.left.color == Color.RED:
                return False
            if node.right and node.right.color == Color.RED:
                return False
        else:
            black_count += 1

        left_check = self.check_properties(node.left, black_count, black_counts)
        right_check = self.check_properties(node.right, black_count, black_counts)

        if left_check and right_check:
            return len(set(black_counts)) == 1
        return False


tree = RedBlackTree()
for i in range(10, 0, -1):
    tree.insert(i)
# print(tree.find_max(), tree.find_min(), sep="\n")
tree.insert(11, None)
tree.pre_order_traversal()
print(tree.check_properties(tree.root))
