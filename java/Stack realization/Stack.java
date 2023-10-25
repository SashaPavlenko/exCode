package ru.sfedu.mmcs.stack;

public class Stack<T> {
    private T[] a;
    private int top, size;

    public Stack() {
        a = (T[]) new Object[100];
        size = a.length;
        top = 0;
    }

    public boolean isEmpty() {
        return top == 0;
    }

    public void push(T elem) throws Exception {
        if (top == size) {
            throw new Exception("Stack overflew");
        }

        a[top++] = elem;
    }

    public T pop() throws Exception {
        if (this.isEmpty()) {
            throw new Exception("Stack is empty");
        }
        return a[--top];
    }

    public T peek() throws Exception {
        if (this.isEmpty()) {
            throw new Exception("Stack is empty");
        }
        return a[top-1];
    }

    public int getSize() {
        return size;
    }

    protected int getTop() {
        return top;
    }
}
