import pytest
from rbtree import RedBlackTree, Color
from errors import Missing, Duplicate, OverallValue


@pytest.fixture(scope="module")
def tree():
    return RedBlackTree()

@pytest.mark.parametrize("key, value", [(13, None),
                                               (17, None),
                                               (11, None),
                                               (16, 15),
                                               (20, 20),
                                               (7, None),
                                               (5, 5),
                                               (12, None)])
def test_insert_correct(tree, key, value):
    tree.insert(key, value)
    assert tree.root.color == Color.BLACK
    assert tree.check_properties(tree.root)


def test_insert_incorrect(tree):
    with pytest.raises(Duplicate):
        tree.insert(13) 

def test_find_min(tree):
    assert tree.find_min().data.key == 5
    assert tree.find_min().data.value == 5

def test_find_max(tree):
    assert tree.find_max().data.key == 20
    assert tree.find_max().data.value == 20

def test_search_correct(tree):
    assert tree.search(16).data.value == 15

@pytest.mark.parametrize("key, answer", [(13, 12),
                                         (16, 13)])
def test_find_nearest_min_correct(tree, key, answer):
    assert tree.find_nearest_min(key).data.key == answer

@pytest.mark.parametrize("key, answer", [(13, 16),
                                         (12, 13)])
def test_find_nearest_max_correct(tree, key, answer):
    assert tree.find_nearest_max(key).data.key == answer

def test_find_nearest_min_incorrect(tree):
    with pytest.raises(OverallValue):
        tree.find_nearest_min(5)

def test_find_nearest_max_incorrect(tree): 
    with pytest.raises(OverallValue):
        tree.find_nearest_max(20)

def test_search_incorrect(tree): 
    with pytest.raises(Missing):
        tree.search(52) 

@pytest.mark.parametrize("key", [(12), (13), (16)])
def test_delete_correct(tree, key):
    tree.delete(key)
    assert tree.check_properties(tree.root)

def test_delete_incorrect(tree):
    with pytest.raises(Missing):
        tree.delete(1)