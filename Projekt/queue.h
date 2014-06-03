#ifndef QUEUE_H
#define QUEUE_H
#include "song.h"

class Node;
class Queue
{
    private:
        Node *head;
        Node *tail;
        int nrnodes;
    public:
        Queue():head(0), tail(0), nrnodes(0){}
        ~Queue();
        bool isEmpty() const;
        void enQue(Song song);
        bool deQue(Song &song);
        void clearQue();
        void printQue() const;

        // Getters
        int getNrNodes() const {return nrnodes;}
};

#endif // QUEUE_H
