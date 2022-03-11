#include <bits/stdc++.h>

using namespace std;

class Nod
{
private:
    char info;
    Nod* next;
public:
    Nod()
    {
        info = '\0';
        next = NULL;
    }
    Nod(char info)
    {
        this->info = info;
        next = NULL;
    }
    Nod(char info, Nod* next)
    {
        this->info = info;
        this->next = next;
    }
    void SetInfo(char info)
    {
        this->info = info;
    }
    void SetNext(Nod* next)
    {
        this->next = next;
    }
    char GetInfo()
    {
        return info;
    }
    Nod* GetNext()
    {
        return next;
    }
};

class Stiva_de_caractere
{
private:
    Nod *top;
public:
    Stiva_de_caractere()
    {
        top = NULL;
    }
    Stiva_de_caractere(char c)
    {
        top = new Nod(c);
    }
    Stiva_de_caractere(char s[])
    {
        top = new Nod(s[0]);
        Nod *p;
        for(int i = 1; s[i]; i++)
        {
            p = new Nod(s[i], top);
            top = p;
        }
    }
    void Push(char info)
    {
        if(top == NULL)
            top = new Nod(info);
        else
        {
            Nod* p = new Nod(info, top);
            top = p;
        }
    }
    void Pop()
    {
        if(top != NULL)
        {
            if(top->GetNext() != NULL)
            {
                Nod* p = top;
                top = top->GetNext();
                delete p;
            }
            else
            {
                delete top;
                top = NULL;
            }
        }
    }
    bool isEmpty()
    {
        return (top == NULL);
    }
    char Top()
    {
        return top->GetInfo();
    }
    Stiva_de_caractere(const Stiva_de_caractere& Stack)
    {
        Nod* p = Stack.top;
        Stiva_de_caractere temp_stack;
        while(p != NULL)
        {
            temp_stack.Push(p->GetInfo());
            p = p->GetNext();
        }
        top = new Nod(temp_stack.Top());
        temp_stack.Pop();
        while(!temp_stack.isEmpty())
        {
            p = new Nod;
            p->SetInfo(temp_stack.Top());
            p->SetNext(top);
            top = p;
            temp_stack.Pop();
        }
    }
    ~Stiva_de_caractere()
    {
        while(!isEmpty())
            Pop();
    }
    void Reverse()
    {
        Stiva_de_caractere temp_stack;
        Nod* p = top;
        while(p != NULL)
        {
            temp_stack.Push(p->GetInfo());
            p = p->GetNext();
        }
        p = top;
        while(!temp_stack.isEmpty())
        {
            p->SetInfo(temp_stack.Top());
            p = p->GetNext();
            temp_stack.Pop();
        }
    }
    Stiva_de_caractere& operator= (const Stiva_de_caractere& Stack)
    {
        Stiva_de_caractere temp_Stack;
        Nod* p = Stack.top;
        while(p != NULL)
        {
            temp_Stack.Push(p->GetInfo());
            p = p->GetNext();
        }
        while(!isEmpty())
            Pop();
        while(!temp_Stack.isEmpty())
        {
            Push(temp_Stack.Top());
            temp_Stack.Pop();
        }
        return *this;
    }
    friend Stiva_de_caractere operator- (const Stiva_de_caractere&, const Stiva_de_caractere&);
    friend istream& operator>> (istream& in, Stiva_de_caractere&);
    friend ostream& operator<< (ostream& out, Stiva_de_caractere&);
};

Stiva_de_caractere operator- (const Stiva_de_caractere& stack1, const Stiva_de_caractere& stack2)
{
    char c1, c2;
    Stiva_de_caractere Stack;
    Nod *p = stack1.top, *q = stack2.top;
    while(p != NULL and q != NULL)
    {
        c1 = p->GetInfo();
        c2 = q->GetInfo();
        if(c1 > c2)
            Stack.Push(c1);
        else
            Stack.Push(c2);
        p = p->GetNext();
        q = q->GetNext();
    }
    return Stack;
}

inline ostream& operator<< (ostream& out, Stiva_de_caractere& Stack)
{
    while(!Stack.isEmpty())
    {
        out << Stack.Top() << ' ';
        Stack.Pop();
    }
    return out;
}

inline istream& operator>> (istream& in, Stiva_de_caractere& Stack)
{
    while(!Stack.isEmpty())
        Stack.Pop();
    string line;
    getline(in, line);
    for(char c : line)
        Stack.Push(c);
    return in;
}
void PrintCaption()
{
    const char DELIMITER[]="\n<------------------------------------------>\n";
    printf("For calling an instruction you have to specify it and then on the next line you have to introduce the input data\n");
    printf("List of instructions:\n");
    printf("ADD - Add one stack\n");
    printf("ADD n - Add n stacks, where n is specified by the user and the stacks are separated with ~\n");
    printf("PRINT - Print the last stack added\n");
    printf("PRINT ALL - Print all stacks\n");
    printf("PRINT n - Print the n-th stack, where n is specified by the user\n");
    printf("PRINT N - Print how many stacks are created\n");
    printf("REVERSE - Reverse the last stack added\n");
    printf("REVERSE n - Reverse the n-th stack\n");
    printf("REVERSE STRING - Reverse a given string\n");
    printf("SUBTRACT x y - Subtract the stacks with the indexes x and y, where x and y are specified by the user and the result is added to the vector\n");
    printf("DELETE - Delete the last stack added\n");
    printf("DELETE n - Delete the n-th stack, where n is specified by the user\n");
    printf("DELETE ALL - Delete all stacks added\n");
    printf("EXIT - Close the program\n");
    printf("%s\n", DELIMITER);
    return;
}

void Add_N_Stacks(vector < Stiva_de_caractere >& Stack_Vector, int nr, int &n)
{
    Stiva_de_caractere temp_stack;
    while(nr)
    {
        nr--;
        n++;
        cin >> temp_stack;
        Stack_Vector.push_back(temp_stack);
    }
    cout << "Stacks successfully stored\n";
    return;
}

void Add_Stack(vector < Stiva_de_caractere >& Stack_Vector, int &n)
{
    n++;
    Stiva_de_caractere temp_stack;
    cin >> temp_stack;
    Stack_Vector.push_back(temp_stack);
    cout << "Stack successfully stored\n";
    return;
}

void Print_Last(const vector < Stiva_de_caractere >& Stack_Vector, int n)
{
    if(!Stack_Vector.empty())
    {
        cout << "The last stack is:\n";
        Stiva_de_caractere temp_stack;
        temp_stack = Stack_Vector[n];
        cout << temp_stack << '\n';
    }
    else
        cout << "There is no stack to be printed\n";
    return;
}

void Print_All(const vector < Stiva_de_caractere >& Stack_Vector, int n)
{
    if(!Stack_Vector.empty())
    {
        cout << "Vector contains:\n";
        Stiva_de_caractere temp_stack;
        for(int i = 0; i <= n; i++)
        {
            temp_stack = Stack_Vector[i];
            cout << temp_stack << '\n';
        }
    }
    else
        cout << "There are no stacks to be printed\n";
    return;
}

void Print_Stack_Number(int n)
{
    printf("There are %d stacks stored\n", n + 1);
    return;
}

void Print_Specified_Stack(const vector < Stiva_de_caractere >& Stack_Vector, int n, int index)
{
    if(index <= n + 1)
    {
        printf("The stack with the index %d is:\n", index);
        Stiva_de_caractere temp_stack;
        temp_stack = Stack_Vector[index - 1];
        cout << temp_stack << '\n';
    }
    else
        printf("The stack with index %d doesn't exist\n", index);
}

void Reverse_Last_Stack(vector < Stiva_de_caractere >& Stack_Vector, int n)
{
    if(!Stack_Vector.empty())
    {
        Stack_Vector[n].Reverse();
        cout << "Last stack successfully reversed\n";
    }
    else
        cout << "There is no stack to reverse\n";
    return;
}

void Reverse_Specified_Stack(vector < Stiva_de_caractere >& Stack_Vector, int n, int index)
{
    if(index <= n + 1)
    {
        Stack_Vector[index - 1].Reverse();
        printf("The stack with the index %d successfully reversed\n", index);
    }
    else
        printf("The stack with index %d doesn't exist\n", index);
}

void Subtract_Stacks(vector < Stiva_de_caractere >& Stack_Vector, int &n, int x, int y)
{
    if(x > n + 1 or y > n + 1)
    {
        cout << "One or both stacks specified don't exist\n";
    }
    else
    {
        n++;
        Stiva_de_caractere temp_stack;
        temp_stack = Stack_Vector[x - 1] - Stack_Vector[y - 1];
        Stack_Vector.push_back(temp_stack);
        cout << "Stacks successfully subtracted\n";
    }
    return;
}

void Delete_Last_Stack(vector < Stiva_de_caractere >& Stack_Vector, int& n)
{
    if(!Stack_Vector.empty())
    {
        Stack_Vector.pop_back();
        n--;
        cout << "Last stack has been deleted successfully\n";
    }
    else
        cout << "There is no stack to be deleted\n";
    return;
}

void Delete_All_Stacks(vector < Stiva_de_caractere >& Stack_Vector, int& n)
{
    Stack_Vector.clear();
    cout << "All stacks have been deleted successfully\n";
    return;
}

void Delete_Specified_Stack(vector < Stiva_de_caractere >& Stack_Vector, int& n, int index)
{
    if(index <= n + 1)
    {
        std::vector < Stiva_de_caractere >::iterator it = Stack_Vector.begin() + index;
        Stack_Vector.erase(it);
        n--;
        printf("The stack with the index %d successfully deleted\n", index);
    }
    else
        cout << "The stack specified doesn't exist\n";
}

void Reverse_Specified_String()
{
    cout << "Enter the string that you want to reverse: ";
    Stiva_de_caractere temp_stack;
    cin >> temp_stack;
    temp_stack.Reverse();
    cout <<"\nThe reversed string is: " << temp_stack << '\n';
}

void Run_Instruction(char s[], vector < Stiva_de_caractere >& Stack_Vector, int &n)
{
    const char DELIMITER[]="\n<------------------------------------------>\n";
    char *p;
    p = strtok(s, " ");
    if(p == NULL)
        return;
    if(!strcmp("ADD", p))
    {
        p = strtok(NULL, " ");
        if(p!= NULL and isdigit(p[0]))
            Add_N_Stacks(Stack_Vector, atoi(p), n);
        else
            Add_Stack(Stack_Vector, n);
    }
    else
    {
        if(!strcmp("PRINT", p))
        {
            p = strtok(NULL, " ");
            if(p == NULL)
                Print_Last(Stack_Vector, n);
            else
            {
                if(p[0] == 'A')
                    Print_All(Stack_Vector, n);
                else
                {
                    if(p[0] == 'N')
                        Print_Stack_Number(n);
                    else
                        Print_Specified_Stack(Stack_Vector, n, atoi(p));
                }
            }
        }
        else
        {
            if(!strcmp("EXIT", p))
                exit(0);
            else
            {
                if(!strcmp("REVERSE", p))
                {
                    p = strtok(NULL, " ");
                    if(p == NULL)
                        Reverse_Last_Stack(Stack_Vector, n);
                    else
                    {
                        if(p[0] = 'S')
                            Reverse_Specified_String();
                        else
                            Reverse_Specified_Stack(Stack_Vector, n, atoi(p));
                    }
                }
                else
                {
                    if(!strcmp("DELETE", p))
                    {
                        p = strtok(NULL, " ");
                        if(p == NULL)
                            Delete_Last_Stack(Stack_Vector, n);
                        else
                        {
                            if(p[0] == 'A')
                                Delete_All_Stacks(Stack_Vector, n);
                            else
                                Delete_Specified_Stack(Stack_Vector, n, atoi(p));
                        }
                    }
                    else
                    {
                        p = strtok(NULL, " ");
                        int temp_nr = atoi(p);
                        p = strtok(NULL, " ");
                        Subtract_Stacks(Stack_Vector, n, temp_nr, atoi(p));
                    }
                }
            }
        }

    }
    cout << DELIMITER;
    return;
}

void Run()
{
    int n = -1;
    vector < Stiva_de_caractere > Stack_Vector;
    char s[105];
    while(true)
    {
        cin.getline(s, 105);
        Run_Instruction(s, Stack_Vector, n);
    }
    return;
}

int main()
{
    PrintCaption();
    Run();
    return 0;
}
