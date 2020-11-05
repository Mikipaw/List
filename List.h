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
    int     next = 0;
    int     prev = 0;
    double  item = 0;
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
    List_elem* head = data;
    List_elem* tail = data;
    size_t  size     = 0;
    size_t  capacity = 0;


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
     * @method Dump();
     * @brief The method prints information about the list.
     * @return nothing?
     */
    void Dump() const;



    ~List(){
        delete [] data;
    }

private:
    void Expand(bool* success = nullptr);

    void Fill_new_elems();

    size_t FindFree(int pos) const;

};



#endif //LIST_LIST_H
