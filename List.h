//
// Created by mikipaw on 02.11.2020.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <cstdio>
#include <cstdlib>

#include "ErrorList.h"
#include <cstring>

/*!
 * @struct List_elem
 * @brief Just an element of list.
 * @param next an integer - 'pointer' to next element in list.
 * @param prev an integer - 'pointer' to previous element in list.
 * @param item a double - element in list.
 */
struct List_elem {
    int     next = -1;
    int     prev = -1;
    double  item =  0;
    bool    free = true;
};

/*!
 * @class List
 * @brief This class contains some elements.
 * @param data a List_elem* - array with elements.
 * @param head a List_elem* - pointer to first elem.
 * @param tail a List_elem* - pointer to last element.
 * @param size a size_t - number of elements in list.
 * @param capacity a size_t - capacity.
 */

class List{

private:
    List_elem* data = nullptr;
    size_t  head        = 0;
    size_t  tail        = 0;
    size_t  size        = 0;
    size_t  capacity    = 0;
    size_t  bhead       = 1;

public:

    /*!
     * List(size_t new_capacity);
     * @brief Classic constructor.
     * @param new_capacity
     */
    explicit
    List(size_t new_capacity):
            capacity    (new_capacity),
            data        (new List_elem[new_capacity])
            {
                Fill_new_elems();
                data[0].prev = 0;
                //head = &data[capacity/2];
                //tail = &data[capacity/2];
            }

    /*!
     * @method Insert(int pos, const double& value);
     * @brief The method inserts element in position pos.
     * @param pos an integer - position.
     * @param value a double - element to insert in list.
     * @return an integer - position of added element.
     */
    int Insert(int pos, double value);

    /*!
     * @method Delete_elem(int pos);
     * @brief The method deletes element in position pos.
     * @param pos an integer - position of deleting element.
     * @return an integer - position
     */
    int Delete_elem(int pos);

    /*!
     * @method Dump() const;
     * @brief The method prints information about the list.
     * @return nothing?
     */
    void Dump() const;

    List& operator=(const List& list)   = delete;
    List           (const List&)        = delete;

    ~List(){
        delete[] data;
    }

    [[nodiscard]] size_t Get_tail() const { return tail; }
    [[nodiscard]] size_t Get_head() const { return head; }

private:
    /*!
     * @method Expand(bool* succes = nullptr);
     * @brief The method expands the list.
     * @param success - success of the operation.
     * @return nothing.
     */
    void Expand(bool* success = nullptr);

    /*!
     * @method Fill_new_elems();
     * @brief The method fills the list by empty elements.
     * @return nothing.
     */
    void Fill_new_elems();

    /*!
     * @method Find_Free(int pos) const;
     * @brief The method finds free place for inserting element.
     * @param pos an integer.
     * @complexity O(N).
     * @return size_t - position found.
     */
    size_t FindFree(int pos) const;

    /*!
     * @method List_OK();
     * @brief Classic verifier for the list.
     * @return ERROR CODE.
     */
    int List_OK();
};



#endif //LIST_LIST_H
