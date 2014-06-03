#include <iostream>
#include "queue.h"
#include "song.h"
using namespace std;

class Node
{
    public:
        Node *next;
        Song song;
        Node(Node *n, Song song):next(n), song(song){}
};

// Destruktor
Queue::~Queue()
{
    while(!isEmpty())
    {
        Node *tmp = head;
        head = head->next;
        delete tmp;
    }
}

// Returnerar true om kön är tom
bool Queue::isEmpty() const
{
    return head == 0;
}

// Lägg till en nod sist i kön
void Queue::enQue(Song song)
{
    Node *pNew = new Node(0, song);

    if(isEmpty())
        head = pNew;
    else
        tail->next = pNew;

    tail = pNew;

    nrnodes++;
}

// Ta bort en nod först i kön
bool Queue::deQue(Song &song)
{
    if(isEmpty())
        return false;

    Node *pDel = head;
    song = pDel->song;
    head = head->next;

    if(isEmpty())
        tail = 0;

    delete pDel;
    nrnodes--;

    return true;
}

// Rensa kön
void Queue::clearQue()
{
    // Skapa en temporär pekare till första noden
    Node *pDel = head;

    // Gå igenom listan från första noden och radera noder en efter en
    while(pDel != nullptr)
    {
        // Radera head-noden
        head = tail->next;
        delete pDel;

        // Uppdatera head-noden
        pDel = head;
    }
    // Nollställ head och tail-noderna
    tail = head = nullptr;
}

// Skriv ut kön
void Queue::printQue() const
{
    for(Node *p = head; p; p = p->next)
    {
        cout << p->song.getTitle() << "|" << p->song.getArtist() << "|" << p->song.getDuration() << endl;
    }
}
