# ������������ ������ �1
## ����: 
����������� ���������� ��� ������ � ���������� ������ ��� �� ��������� ������������ ����� ����������������
## ������:
���. ������� ������ � ���. �������� ������ �� ����. ����� ������ � ����.
## �����������:
_���_ � ��������� ������ ��� �������� ������ �����, �������������� �� ���� ����������� ������ � ��������� �� �����.

_������_ � ������� ������������ ����. ��������� �������� ������� �������� ����� ����� ����� ������, ������������ � ���������� ������.
����������
### ����� Bor
� ������� ���� ����������� ����� ```Bor```, � ������� ���������� �������� ����� � ��������� �������� �������. ������ ���� �������� �������� ```WordEnd```, ������� �������� �� ����������� ����� �����, � ������ ```children``` �� 26 ���������� ��� ������ ����� ����������� ��������.
```c++
#include <iostream>
#include <vector>
class Bor {
private:
	struct BorNode {
		std::vector<BorNode*> children;
		bool WordEnd;
		BorNode() : children(26, NULL), WordEnd(false){} 
	};
	BorNode* root;
	void delBor(BorNode* node);
	int Index(char ch) const;
	bool removeHelper(BorNode* root, const std::string& word, int depth);
public:
	Bor();
	~Bor();
	void insert(const std::string& word);
	bool search(const std::string& word) const;
	void remove(const std::string& word);
};
void menu();
```
### ������� ������� �������� � ���  
## ������ ������� `Bor::insert`

��� ������� ��������� ����� � ��� (���������� ������). ������� �������� ��� ���������:

```cpp
void Bor::insert(const std::string& word) {
```
������� `insert` ��������� �� ���� ������ `word` (�����), ������� ����� �������� � ���.

```cpp
    BorNode* node = root;
```
������� ��������� `node` � ������������� ��� � ������ ������ (`root`). �� ����� ������������ �� ������, ������� � ��������� ����.

```cpp
    for (char ch : word) {
```
��������� ���� `for`, ������� ���������� ������ ������ `ch` �� ������ `word`.

```cpp
        int index = Index(ch);
```
��������� ������ `index` ��� ������� `ch`, ������� ����������, � ����� ������ ������� `children` (��������) ������ ���������� ���� ������.

```cpp
        if (!node->children[index]) {
            node->children[index] = new BorNode;
        }
```
���� � `children[index]` ��� ��� ���� (�. �. ��������� `NULL`), ������� ����� ���� `BorNode` � ��������� ��� � ���� �����.

```cpp
        node = node->children[index];
```
��������� � ���������� ���� (������������ ������ � ������).

```cpp
    }
```
����� ���������� ����� ���� ���� �� ������ �������, � �� ��������� � ����, ������� ������������� ���������� ������� ������������ �����.

```cpp
    node->WordEnd = true;
```
�������� ������� ���� ��� ����� ����� (`WordEnd = true`). ��� ��������, ��� � ���� ���� ������������� ����������� �����, � �� ������ ��� �����.


��� ������ ���� ������� � ������� **Markdown**:  

---

## `Bor::search`

��� ������� ��������� **����� �����** � ����.  

### ���:
```cpp
bool Bor::search(const std::string& word) const {
    BorNode* node = root;
    for (char ch : word) {
        int index = Index(ch);
        if (!node->children[index]) {
            return false;
        }
        node = node->children[index];
    }
    return node->WordEnd;
}
```

### ������:
1. **�������� ����� � ��������� ����**:
   ```cpp
   BorNode* node = root;
   ```
   ������������� `node` � ������.

2. **���� �� ������� ������� �����**:
   ```cpp
   for (char ch : word) {
   ```
   ���������� ������� ������.

3. **��������� ������ �������**:
   ```cpp
   int index = Index(ch);
   ```
   ������ ���������� ��������� ������� � ������� `children`.

4. **���������, ���������� �� ������ ����**:
   ```cpp
   if (!node->children[index]) {
       return false;
   }
   ```
   ���� ���� �����������, ������ ����� **�� �������**.

5. **��������� � ���������� ����**:
   ```cpp
   node = node->children[index];
   ```

6. **���������, �������� �� ���� ������ �����**:
   ```cpp
   return node->WordEnd;
   ```
   ���� `WordEnd = true`, ����� **����������** � ����.

---

## `Bor::delBor`

��� ������� **���������� �������** ��� ���� ������.

### ���:
```cpp
void Bor::delBor(BorNode* node) {
    for (BorNode* child : node->children) {
        if (child != NULL) {
            delBor(child);
        }
    }
    delete node;
}
```

### ������:
1. **���������� ���� �������� ����**:
   ```cpp
   for (BorNode* child : node->children) {
   ```
   �������� �� ���� �������� �����.

2. **���������� ������� ������� �������**:
   ```cpp
   if (child != NULL) {
       delBor(child);
   }
   ```
   ���� `child` �� `NULL`, �������� `delBor(child)`.

3. **������� ��� ����**:
   ```cpp
   delete node;
   ```
   ����� �������� ���� �������� ������� ��� ����.

---

## `Bor::removeHelper`

��� ������� **�������� ������� �����** �� ����.

### ���:
```cpp
bool Bor::removeHelper(BorNode* node, const std::string& word, int depth) {
    if (!node) return false;
    if (depth == word.size()) {
        if (!node->WordEnd) return false; 
        node->WordEnd = false;
        return node->children.empty(); 
    }

    int index = Index(word[depth]);
    if (index == -1 || !node->children[index]) return false;

    bool shouldDeleteChild = removeHelper(node->children[index], word, depth + 1);

    if (shouldDeleteChild) {
        delete node->children[index];
        node->children[index] = NULL;
        return node->children.empty() && !node->WordEnd;
    }

    return false;
}
```

### ������:
1. **������� ������**: ���� `node == NULL`, ������� `false`.

2. **���� ����� �� ����� �����**:
   ```cpp
   if (depth == word.size()) {
   ```
   ���������, ��� �� � ��������� ������� �����.

3. **������� ����� ����� �����**:
   ```cpp
   node->WordEnd = false;
   ```
   ������� ���� `WordEnd`.

4. **���������� ���������� �� ������**:
   ```cpp
   bool shouldDeleteChild = removeHelper(node->children[index], word, depth + 1);
   ```
   �������� �������� ���������� �������.

5. **���� ������� ����, ������� ���**:
   ```cpp
   if (shouldDeleteChild) {
       delete node->children[index];
       node->children[index] = NULL;
   }
   ```
   ���� ���� **������ �� �����**, ������� ���.

---

## `Bor::remove`

������� **������� �����**, ��������� `removeHelper`.

### ���:
```cpp
void Bor::remove(const std::string& word) {
    removeHelper(root, word, 0);
}
```

### ������:
1. ������ �������� `removeHelper` � ���������� ����.

---

## `Bor::Index`

������� **���������� ������ �������** � ������� `children`.

### ���:
```cpp
int Bor::Index(char ch) const {
    if (ch >= 'a' && ch <= 'z') return ch - 'a';      
    if (ch >= 'A' && ch <= 'Z') return ch - 'A';       
    return -1; 
}
```

### ������:
1. **��� �������� ���� (a-z)**:
   ```cpp
   if (ch >= 'a' && ch <= 'z') return ch - 'a';
   ```
   ������ �� `0` �� `25`.

2. **��� ��������� ���� (A-Z)**:
   ```cpp
   if (ch >= 'A' && ch <= 'Z') return ch - 'A';
   ```
   ������ �� `0` �� `25`.

3. **����� ���������� `-1`** (������ �� ��������������).

---

## `menu()`

������� **������� ����** ��� ������ � �����.

### ���:
```cpp
void menu() {
    Bor bor;
    int sel;
    std::string word;
    while (true) {
        std::cout << "Select option: " << std::endl;
        std::cout << "1. Add string" << std::endl;
        std::cout << "2. Search string" << std::endl;
        std::cout << "3. Remove string" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cin >> sel;
        switch (sel)
        {
        case 1: {
            std::cout << "Enter string: ";
            std::cin >> word;
            bor.insert(word);
            break;
        }
        case 2: {
            std::cout << "Enter string: ";
            std::cin >> word;
            if (bor.search(word)) {
                std::cout << "The word exists in the bor." << std::endl;
            }
            else {
                std::cout << "The word does not exist in the bor." << std::endl;
            }
            break;
        }
        case 3: {
            std::cout << "Enter string: ";
            std::cin >> word;
            bor.remove(word);
            std::cout << "Word removed.";
            break;
        }
        case 4: {
            return;
        }
        default:
            std::cout << "Incorrect option";
            break;
        }
    }
}
```

### ������:
1. **������� ���� � ���� ���� �������**:
   ```cpp
   std::cout << "Select option: " << std::endl;
   std::cin >> sel;
   ```

2. **��������� �����**:
   ```cpp
   case 1:
       std::cin >> word;
       bor.insert(word);
   ```

3. **���� �����**:
   ```cpp
   case 2:
       std::cin >> word;
       if (bor.search(word)) ...
   ```

4. **������� �����**:
   ```cpp
   case 3:
       std::cin >> word;
       bor.remove(word);
   ```

5. **��������� ������**:
   ```cpp
   case 4:
       return;
   ```

---

### �����
������������� ������� ��������� ���������� ���������, ������� � ������ ������ � ����.
