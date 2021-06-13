//
// Created by mikipaw on 03.11.2020.
//

#include <cmath>
#include "List.h"


int List::Insert(int pos, double value) {
    size_t new_pos = bhead;
    bhead = data[new_pos].next;

    if(size == 0) {
        data[new_pos].prev = 0;
        data[new_pos].next = -1;
        data[0].next = new_pos;
        data[new_pos].item = value;
        size++;
        data[0].free = false;
        data[1].free = false;
        return new_pos;
    }

    if(data[pos].free) return OUT_OF_RANGE;

    if(size == capacity) Expand();

    //size_t new_pos = FindFree(pos);
    data[new_pos].next = data[pos].next;
    data[data[pos].next].prev = new_pos;
    data[pos].next = new_pos;
    data[new_pos].prev = pos;

    data[new_pos].item = value;
    data[new_pos].free = false;

    size++;

    if(data[new_pos].prev ==  0) head = new_pos;
    if(data[new_pos].next == -1) tail = new_pos;

    return new_pos;
}


void List::Expand(bool* success) {
    *success = true;
    if(capacity < 16) {
        capacity = 16;
        data = (List_elem*) realloc(data, (1 + capacity) * sizeof(List_elem));
        if (data == nullptr) *success = false;
        Fill_new_elems();
        return;
    }
    else {
        capacity*=2;
        data = (List_elem*) realloc(data, capacity * sizeof(List_elem));
        Fill_new_elems();
    }

}


size_t List::FindFree(int pos) const {
    while (data[pos].prev != -1) pos++;
    return pos;
}

void List::Dump() const {
    //printf("%lf\t%lf\n", data[0].item, data[1].item);
    FILE* Graph = fopen("Graph1.dot", "wb");
    if(Graph == nullptr) fprintf(stderr, "Error opening file!\n");

    const char* DEFAULT_TEXT = "digraph G{\n"
                               "edge [color = \"darkgreen\"];\n"
                               "rankdir = \"LR\";\n"
                               "node [shape = record];\n"
                               "node [color = \"#000000\", shape = record];\n"
                               "node0 [style = \"filled\", fillcolor = \"#FF019A\"];\n"
                               "node0 [label = \"<f1> BEGIN\"];\n"
                               "nodeend [style = \"filled\", fillcolor = \"#9F019A\"];\n"
                               "nodeend [label = \"<f1> END\"];\n"
                               "node [color = \"#000000\", shape = record];\n"
                               "nodeinvzero [style = \"filled\", fillcolor = \"#FF019A\"];\n"
                               "nodeinvzero [label = \"<f1> INVALID_ZERO\"];\n\0";
    fwrite(DEFAULT_TEXT, sizeof(char), strlen(DEFAULT_TEXT), Graph);

    const char* color = "gold";
    for(int i = 1; i <= capacity; ++i) {
        fprintf(Graph, "node[color = \"#000000\", shape = record];\n");

        if(i % 2 == 0) color = "gold";
        else color = "grey";
        fprintf(Graph, "node%d[ style = \"filled\", fillcolor = \"%s\"];\n", i, color);
        data[capacity].item = 0;
        data[capacity].prev = -1;
        fprintf(Graph,
                "node%d [label=\"<f0> prev (%d)|<f1> num (%d)|<f2> next (%d)|<f3> data (%lf)\"];\n",
                i, data[i].prev, i, data[i].next, data[i].item);
        if(data[i].next != -1) {
            fprintf(Graph, "node%d:f2 -> node%d:f1;\n", i, data[i].next);
            fprintf(Graph, "node%d:f0 -> node%d:f1;\n", data[i].next, i);
        }
        else if(data[i].prev != -1) fprintf(Graph, "node%d:f2 -> nodeend;\n", i);
    }
    fprintf(Graph, "node0       -> node%d:f1;\n",   data[0].next);
    fprintf(Graph, "node%d [style = \"filled\", fillcolor = \"cyan\"];\n", capacity + 1);
    fprintf(Graph, "node%d [label=\"BORDER\"];\n", capacity + 1);

    fprintf(Graph, "\n}");
    fclose(Graph);

}

int List::Delete_elem(int pos) {
    if (pos >= capacity)        return OUT_OF_RANGE;
    if (data[pos].prev == -1)   return UNAVAILABLE_ELEMENT;

    data[data[pos].prev].next = data[pos].next;
    data[data[pos].next].prev = data[pos].prev;

    data[pos].next = bhead;
    bhead = pos;
    data[pos].prev = -1;

    data[pos].item = NAN;
    data[pos].free = true;

    size--;

    return ALL_OK;
}

void List::Fill_new_elems() {
    for(size_t i = size + 1; i <= capacity; ++i) {
        data[i].next =  i + 1;
        }
}

int List::List_OK() {
    size_t curr_element = 0;
    for(curr_element = head; curr_element != tail; curr_element = data[curr_element].next) {
        if(data[data[curr_element].next].prev != curr_element) return INVALID_GRAPH;
    }

    return ALL_OK;
}


