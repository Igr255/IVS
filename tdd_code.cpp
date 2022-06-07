//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     IGOR HANUS <xhanus19@stud.fit.vutbr.cz>
// $Date:       $2021-23-02
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//



PriorityQueue::PriorityQueue()
{
}

PriorityQueue::~PriorityQueue()
{
    Element_t* current = m_pHead;
    Element_t* next = nullptr;

    while (current != nullptr)
    {
        next = current->pNext;
        free(current);
        current = next;
    }
    // removing the value saved in m_pHead
    m_pHead = nullptr;
}

void PriorityQueue::Insert(int value)
{
    // creating m_pHead if the queue is empty
    if (m_pHead == nullptr) {
        Element_t  *element = new Element_t();
        element->value = value;
        element->pNext = nullptr;

        m_pHead = element;
    }
    else {
        bool isLast = false;

        Element_t *currentElement = m_pHead;
        Element_t *prevElement = nullptr;

        Element_t * element = new Element_t();

        element->value = value;
        element->pNext = nullptr;

        // looking for the correct placement of the inserted element
        while (currentElement->value > element->value) {
            prevElement = currentElement;
            if (currentElement->pNext == nullptr) {
                isLast = true;
                break;
            }
            currentElement = currentElement->pNext;
        }
        // if the currentElement element is m_pHead then inserted element becomes m_pHead
        // otherwise the element has a previous element pointing at it (else clause)
        if (currentElement == m_pHead)
            m_pHead = element;
        else
            prevElement->pNext = element;
        // check if the inserted element is the lowest in value
        if (!isLast)
            element->pNext = currentElement;
    }
}

bool PriorityQueue::Remove(int value)
{
    Element_t* currentElement = m_pHead;
    Element_t* prevElement = nullptr;

    // checking if the queue is not empty
    if (m_pHead != nullptr) {
        while (currentElement != nullptr) {
            // finding the inserted value
            if (currentElement->value == value) {
                if (prevElement != nullptr) {
                    // changing the pointer of the previous element tho the one after the current element
                    prevElement->pNext = currentElement->pNext;
                    delete currentElement;
                } else {
                    // if the current element (prevElement == currentElement) has no next element then it is m_pHead
                    m_pHead = currentElement->pNext;
                }
                return true;
            }

            prevElement = currentElement;
            currentElement = currentElement->pNext;
        }
    }
    return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    auto currentElement = m_pHead;

    if (m_pHead != nullptr) {
        while (currentElement != nullptr) {
            if (currentElement->value == value) {
                return currentElement;
            }
            currentElement = currentElement->pNext;
        }
    }
    return nullptr;
}

size_t PriorityQueue::Length()
{
    auto currentElement = m_pHead;
    int i = 0;

    if (m_pHead != nullptr) {
        while (currentElement != nullptr) {
            i++;
            currentElement = currentElement->pNext;
        }
    }
    return i;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
