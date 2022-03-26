package ru.sfedu.mmcs.stack;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class StackTest {

    private Stack<Integer> emptyIntStack;
    private Stack<Integer> intStack;
    private Stack<Integer> intTestStack;
    @BeforeEach
    void setUp() throws Exception {
        emptyIntStack = new Stack<>();

        intStack = new Stack<>();
        intStack.push(1);
        intStack.push(2);
        intStack.push(3);

        intTestStack = new Stack<>();
    }

    @Test
    void isEmpty() {
        Assertions.assertAll(
                () -> assertEquals(true, emptyIntStack.isEmpty()),
                () -> assertEquals(false, intStack.isEmpty())
        );
    }

    @Test
    void push() throws Exception {
        assertEquals(true, intTestStack.isEmpty());
        intTestStack.push(1);
        intTestStack.push(2);

        assertEquals(false, intTestStack.isEmpty());
        assertEquals(100, intTestStack.getSize());
        assertEquals(2, intTestStack.getTop());
    }

//    @Test(expected)

    @Test
    void pop() throws Exception {
        assertEquals(3, intStack.pop());
        assertEquals(2, intStack.pop());
        assertEquals(1, intStack.pop());
        assertEquals(true, intStack.isEmpty());

    }

    @Test
    void peek() throws Exception {
        assertEquals(3, intStack.peek());
    }
}