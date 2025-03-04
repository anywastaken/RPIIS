namespace Lib
{
    public class DoublyNode<T>
    {
        public T Data { get; set; }
        public DoublyNode<T> Previous { get; set; } // хранит ссылку
        public DoublyNode<T> Next { get; set; }
        public DoublyNode(T data)
        {
            this.Data = data;
        }

        public DoublyNode()
        {

        }
    }

}