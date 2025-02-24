#include "pch.h"
#include "D:\Уник\Пиовис\lab1\lab1\queue.cpp"
using namespace std;


// Тестирование функции dobavqueue и др.
TEST(QueueTest, QueueOperacii) {
    Element* pervyi = nullptr;
    Element* posled = nullptr;

    // Добавление элементов
    dobavqueue(pervyi, posled, "Element 1");
    dobavqueue(pervyi, posled, "Element 2");
    dobavqueue(pervyi, posled, "Element 3");

    // Содержимое очереди
    viewqueue(pervyi); // Ожидается: "Содержимое очереди: Element 1 Element 2 Element 3"

    // Взять элемент (1)
    string value = vziatqueue(pervyi, posled);
    cout << "Взятый элемент: " << value << endl; // Выводим взятый элемент
    ASSERT_EQ(value, "Element 1"); // Ожидается: "Element 1"

    // Содержимое очереди после взятия элемента
    viewqueue(pervyi); // Ожидается: "Содержимое очереди: Element 2 Element 3"

    // Очистка всех элементов
    clearqueue(pervyi, posled);

    // Содержимое очереди после очистки
    viewqueue(pervyi); // Ожидается: "Очередь пуста."
}

// Тестирование функции isEmpty
TEST(IsEmptyTest, ProsmotrEmptyQueue) {
    Element* pervyi = nullptr;
    Element* posled = nullptr;

    ASSERT_TRUE(isEmpty(pervyi));

    dobavqueue(pervyi, posled, "Element 1");

    ASSERT_FALSE(isEmpty(pervyi));
}

// Тестирование функции clearqueue
TEST(ClearQueueTest, ClearQueue) {
    Element* pervyi = nullptr;
    Element* posled = nullptr;
    dobavqueue(pervyi, posled, "Element 1");
    dobavqueue(pervyi, posled, "Element 2");

    clearqueue(pervyi, posled);

    ASSERT_TRUE(isEmpty(pervyi));
    ASSERT_TRUE(isEmpty(posled));
}

// Тестирование функции vziatqueue 
TEST(DequeueTest, ProsmotrAfterDequeue) {
    Element* pervyi = nullptr;
    Element* posled = nullptr;

    // Добавление элементов
    dobavqueue(pervyi, posled, "Element 1");
    dobavqueue(pervyi, posled, "Element 2");
    dobavqueue(pervyi, posled, "Element 3");

    // Взять один элемент
    string value = vziatqueue(pervyi, posled);
    cout << "Взятый элемент: " << value << endl; // Выводим взятый элемент
    ASSERT_EQ(value, "Element 1"); // Ожидается: "Element 1"

    // Содержимое очереди после взятия элемента
    viewqueue(pervyi); // Ожидается: "Содержимое очереди: Element 2 Element 3"

    // Очистка всех элементов
    clearqueue(pervyi, posled);

    // Содержимое очереди после очистки
    viewqueue(pervyi); // Ожидается: "Очередь пуста."
}

int main(int argc, char** argv) {
    setlocale(0, "");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
