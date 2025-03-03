#include <iostream>
#include "spisok.h"
using namespace std;

    bool List::is_empty()
    {
        return first==nullptr;
    }

    void List::push_b(int _value)
    {
        Node *temp=new Node(_value);
        if(is_empty())
        {
            first=temp;
            last=temp;
            return;
        }
      last->next=temp;
      last=temp;
    }
    void List::Print()
    {
        Node *p=first;
        while(p!=nullptr)
        {
            cout<<p->value<<' ';
            p=p->next;
        }
        cout<<"\n\n";
    }
    bool List::find(int _value)
    {
        Node* temp = first;
        while (temp != nullptr && temp->value != _value)
        {
            temp = temp->next;
        }
        if (temp == nullptr)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    void List::Remove_first()
    {
        if(is_empty())
        {
            return;
        }
        Node* p = first;
        first = p->next;
        delete p;
    }

    void List::Remove_last()
    {
        if(is_empty()) return;
        if (first == last)
        {
            Remove_first();
            return ;
        }
        Node* p = first;
        while (p->next != last)
        {
            p = p->next;
        }
        p->next = nullptr;
        delete last;
        last = p;
    }

    void List::Remove(int _val) {
        if (is_empty()) return;
        if (first->value == _val) {
            Remove_first();
            return;
        }
        else if (last->value == _val) {
                Remove_last();
            return;
        }
        Node* slow = first;
        Node* fast = first->next;
        while (fast && fast->value != _val) {
            fast = fast->next;
            slow = slow->next;
        }
        if (!fast) {
            return;
        }
        slow->next = fast->next;
        delete fast;
    }

    Node* List::operator[](int index)
    {
      if(is_empty()) return nullptr;
      
      Node *p=first;
      for(int i=0;i<index;i++)
      {
        p=p->next;
        if(p==nullptr) return nullptr;
      }
      return p;
    }

    void List::Sort()
    {
        Node* temp = first;
        while (temp != nullptr)
        {
            Node* current = first;
            while (current->next != nullptr)
            {
                if (current->value >= current->next->value) 
                {
                   swap(current->value, current->next->value);
                }
                current = current->next;
            }
            temp = temp->next;
        }
    }
    int List::Get_size()
    {
        Node *p=first;int size=0;
        if(is_empty()) return 0;
        while(p!=nullptr)
        {
p=p->next;
size++;
        }
        return size;
    }
    void List::intersection_list(Node *current2)
    {
        List a1;
        List b1;
        List result;

        Node *current1=this->first;//Копируем элементы 1-ого списка
        while(current1!=nullptr)
        {
            a1.push_b(current1->value);
            current1=current1->next;
        }
        while(current2!=nullptr)
        {
            b1.push_b(current2->value);
            current2=current2->next;
        }
        Node *current3=a1.first;
        while(current3!=nullptr)
        {
            Node *current4=b1.first;
            while(current4!=nullptr)
            {
                if(current3->value==current4->value)
                {
                    result.push_b(current3->value);
                    a1.Remove(current3->value);
                    b1.Remove(current4->value);
                    current3=a1.first;
                    break;
                }
                current4=current4->next;    
            }
            if(current3!=nullptr)
            current3=current3->next;
        } 
        a1.~List();
        b1.~List();  
        result.Sort();
        result.Print();
        
    }

    void List::union_list(Node *current2)
    {
        List a1;
        List b1;
        List result;

        Node *current1=this->first;//Копируем элементы 1-ого списка
        while(current1!=nullptr)
        {
            a1.push_b(current1->value);
            current1=current1->next;
        }
        while(current2!=nullptr)
        {
            b1.push_b(current2->value);
            current2=current2->next;
        }
        Node *current3=a1.first;
        while(current3!=nullptr)
        {
            Node *current4=b1.first;
            while(current4!=nullptr)
            {
                if(current3->value == current4->value)
                {
                    result.push_b(current3->value);
                    a1.Remove(current3->value);
                    b1.Remove(current4->value);
                    current3=a1.first;
                    break;
                }
                current4=current4->next;    
            }
            if(current3!=nullptr)
            current3=current3->next;
            
        } 

        for(Node *current5=a1.first;current5!=nullptr;current5=current5->next)
        {
            result.push_b(current5->value);
        }
        for(Node *current6=b1.first;current6!=nullptr;current6=current6->next)
        {
            result.push_b(current6->value);
        }
        result.Sort();  
        result.Print();
    }
    int main()
    {
        List a;List b;
        a.push_b(1);
        a.push_b(2);
        a.push_b(2);
        b.push_b(1);
        b.push_b(2);
        List result1;
        result1.Print();

        a.intersection_list(b.first);
        a.union_list(b.first);
        
        return 0;
    }