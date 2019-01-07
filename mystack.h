struct snode {
    int info = 0;
    snode* below = nullptr;
};

struct stack {
    snode* base = nullptr;
    snode* top = nullptr;
    int size = 0;
};

bool emptyStack(stack s) {
    if (s.size == 0)
        return 1;
    else return 0;
}

int top(stack s) {
    if (s.top != nullptr)
        return s.top->info;
    else {
        throw "Attempted to get top of empty stack.";
        return -1;
    }
}

void push (stack &s, int info) {
    snode* p = new snode;
    p->info = info;
    
    if (emptyStack(s)) {
        s.top = p;
        s.base = p;
    }
    else {
        p->below = s.top;
        s.top = p;
    }
    s.size++;
}

void pop (stack &s) {
    if (emptyStack(s)) {
        throw "Attempted to pop empty stack.";
        return;
    }
    else {
        snode *p = s.top;
        if (s.size == 1) {
            s.top = nullptr;
            s.base = nullptr;
        }
        else
            s.top = p->below;
        delete p;
        s.size--;
    }
}

stack copyStack (stack &s) {
    stack rev;
    stack cpy;

    snode* p = s.top;
    while (p != nullptr) {
        push(rev, p->info);
        p = p->below;
    }
    p = rev.top;
    while (p != nullptr) {
        push(cpy, p->info);
        p = p->below;
    }
    return cpy;
}