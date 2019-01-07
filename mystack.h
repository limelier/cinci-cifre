struct snode {
    int info = 0;
    snode* below = nullptr;
    snode* above = nullptr;
};

struct stack {
    snode* base = nullptr;
    snode* top = nullptr;
    int size = 0;
};

void push (stack &s, int info) {
    snode* p;
    p = new snode;
    
    p->info = info;
    
    if (s.size == 0) {
        s.base = p;
        s.top = p;
        s.size = 1;
    } else {
        s.top->above = p;
        p->below = s.top;
        s.top = p;
        s.size++;
    }
}

void pop (stack &s) {
    if (s.size > 0) {
        snode* p = s.top;
        if (s.size == 1) {
            s.top = nullptr;
            s.base = nullptr;
        } 
        else {
            s.top = p->below;
            s.top->above = nullptr;
        }
        delete p;
        s.size--;
    }
}