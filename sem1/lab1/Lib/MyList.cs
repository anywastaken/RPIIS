
using System.Collections;
using System.Collections.Generic;

namespace Lib
{
    public class MyList<T>
    {
        private DoublyNode<T> head; // головной/первый элемент
        private DoublyNode<T> tail; // последний/хвостовой элемент
        private int count;  // количество элементов в списке

        // добавление элемента
        public void Add(T data)
        {
            DoublyNode<T> node = new DoublyNode<T>(data);
            if (head == null)
                head = node;
            else
            {
                tail.Next = node;
                node.Previous = tail;
            }
            tail = node;
            count++;
        }

        public void AddFirst(T data)
        {
            DoublyNode<T> node = new DoublyNode<T>(data);
            DoublyNode<T> temp = head;
            node.Next = temp;
            head = node;
            if (count == 0)
                tail = head;
            else
                temp.Previous = node;
            count++;
        }
        public void print()
        {
            DoublyNode<T> print = head;
            while (print != null)
            {
                Console.Write(" " + print.Data);
                print = print.Next;
            }
            Console.WriteLine();
        }

        public bool RemoveElement(T data)
        {
            DoublyNode<T> current = head;
            while (current != null) // проходим по всему списку
            {
                if (current.Data.Equals(data)) // сравниваем 
                {
                    break;
                }
                current = current.Next;
            }
            if (current != null) // будет выполняться только если нашли элемент
            {                    // если элемент не найден то элемент равна НУЛ
                if (current.Next != null)
                {
                    current.Next.Previous = current.Previous;
                }
                else
                {
                    tail = current.Previous;
                }
                if (current.Previous != null)
                {
                    current.Previous.Next = current.Next;
                }
                else
                {
                    head = current.Next;
                }
                count--;
                return true;
            }
            return false;
        }

        public int Count { get { return count; } }
        public bool IsPUSTO { get { return count == 0; } }

        public void Clear()
        {
            head = null;
            tail = null;
            count = 0;
        }

        public bool search(T data)
        {
            DoublyNode<T> current = head;
            while (current != null)
            {
                if (current.Data.Equals(data))
                    return true;
                current = current.Next;
            }
            return false;
        }

        public void SortMintoMax()
        {
            if (head == null || head.Next == null)
            {
                return;
            }

            bool swapped;
            do
            {
                swapped = false;
                DoublyNode<T> current = head;

                while (current.Next != null)
                {
                    if (Comparer<T>.Default.Compare(current.Data, current.Next.Data) > 0)
                    {
                        T temp = current.Data;
                        current.Data = current.Next.Data;
                        current.Next.Data = temp;
                        swapped = true;
                    }
                    current = current.Next;
                }
            } while (swapped);
        }

        public void mergeList(MyList<T> list1, MyList<T> list2) // сливание списков
        {
            if (list1.IsPUSTO && list2.IsPUSTO)
            {
                return;
            }
            if (list1.IsPUSTO)
            {
                list1.head = list2.head;
                list1.tail = list2.tail;
                list1.count = list2.count;
                return;
            }
            if (list2.IsPUSTO)
            {
                return;
            }

            list1.tail.Next = list2.head;
            list2.head.Previous = list1.tail;
            list1.tail = list2.tail;
            list1.count += list2.count;

            list2.head = null;
            list2.tail = null;
            list2.count = 0;
        }

        public MyList<T> FindIntersection(MyList<T> list1, MyList<T> list2) // пересечение
        {
            MyList<T> intersection = new MyList<T>();
            DoublyNode<T> current1 = list1.head;

            while (current1 != null)
            {
                DoublyNode<T> current2 = list2.head;
                while (current2 != null)
                {
                    if (current1.Data.Equals(current2.Data))
                    {
                        intersection.Add(current1.Data);
                        break;
                    }
                    current2 = current2.Next;
                }
                current1 = current1.Next;
            }

            return intersection;

        }
    }
}




