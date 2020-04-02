#include <stdexcept>
#include "todolist.h"
using namespace std;


DailyTodoList::DailyTodoList()
{
    data_ = new Item * [5];
    cap_ = 5;
    priorityHead_ = NULL;
    // [TO BE COMPLETED]
    //===========================
    // Add any addition code here

    for(size_t i = 0; i < cap_; i++)
    {
        data_[i] = NULL;
    }
    priority_items_num_ = 0;
    
}


DailyTodoList::~DailyTodoList()
{
    Item * next;
    Item * cur;

    for(size_t i = 0; i < cap_; i++)
    {
        if(data_[i] != NULL)
        {
            cur = data_[i];
            while( cur != NULL)
            {
                next = cur->nextItem;
                delete cur;
                cur = next;
            }
        }
    }

    delete [] data_;  
    

}

/**
      *  Inserts a new value into the end of the given day's to-do list.
      *  [COMPLETED]
      *
      *  @param[in] dayIndex
      *    Day index of the to-do list that val should be inserted into.
      *    If dayIndex is beyond the current size of the data array, it should
      *    be resized and the items transferred to the new larger data array.
      *  @param[in] val
      *    String value to insert
      *  @param[in] highPriority
      *    True if this value should also be added to the end of the high
      *    priority list
      *  @throws std::bad_alloc
      *    Memory could not be allocated
      *
      *  Required complexity: Should run in worst-case time O(n+k)
      *       where n is the size of the data array and k is the length of
      *       the given day's to do list.
      *       *However*, if a sequence of inserts is performed on sequential
      *       days (d, d+1, d+2, ...) the amortized runtime of insert should be
      *       O(k) where k is the average length of the to-do lists for given days.
      */

void DailyTodoList::push_back(size_t dayIndex, const std::string& val, bool highPriority)
{
    if (dayIndex < cap_)
    {
        this->insert(dayIndex, this->numItemsOnDay(dayIndex), val, highPriority);
    }
    else 
    {
        this->insert(dayIndex, 0, val, highPriority);
    }
    
}


/**
     *  Inserts a new value into the given day's to-do list
     *  at the desired location. 
     *  [TO BE WRITTEN]
     *
     *  @param[in] dayIndex
     *    Day index of the to-do list that val should be inserted into.
     *    If dayIndex is beyond the current size of the data array, it should 
     *    be resized and the items transferred to the new larger data array.
     *  @param[in] loc
     *    Location to insert the new value in the given day's to-do list 
     *  @param[in] val
     *    String value to insert
     *  @param[in] highPriority
     *    True if this value should also be added to the end of the high
     *    priority list
     *  @throws std::out_of_range
     *    If the location is beyond the end of the given to-do list.  
     *  @throws std::bad_alloc
     *    Memory could not be allocated 
     *
     *  Required complexity: Should run in worst-case time O(n+loc)
     *       where n is the size of the data array and loc is the index at  
     *       which to insert in the given day's to do list.  
     *       *However*, if a sequence of insertions is performed on sequential 
     *       days (d, d+1, d+2, ...) to locations (l, l', l'') then the amortized 
     *       runtime of insert should be O(average of l, l', l'', etc).
     */
void DailyTodoList::insert(size_t dayIndex, size_t loc, const std::string& val, bool highPriority)
{

    Item ** new_data = NULL;
    //check if the given index is greater than current capacity
    if(dayIndex >= cap_)
    {
        try {
            new_data = new Item * [dayIndex*2];
        }
        catch (std::bad_alloc& e){
            throw std::bad_alloc();
        }

        //transfer the old array to new array
        for(size_t i = 0; i<dayIndex*2;i++)
        {
           new_data[i] = NULL;
        }
        for(size_t i = 0; i<cap_;i++)
            new_data[i] = data_[i]; 
        delete[] data_;
        //update variables after resizing
        cap_ = dayIndex*2;
        data_ = new_data;
    }

    //check if loc is within the bounds
    if(loc > this->numItemsOnDay(dayIndex))
    { 
        throw std::out_of_range("dayIndex is invalid");
    }


    size_t cur = 0;
    Item * cur_item = data_[dayIndex];
    Item * prev_item = NULL;
    Item * newItem;
    Item * priorityTail;

    //move pointer to loc position
    while(cur < loc)
    {
        prev_item = cur_item;
        cur_item = cur_item->nextItem;
        cur++;
    }

    try {
        //create a new item having val and cur_time as its next item
         newItem = new Item(val,cur_item,NULL); 
    }

    catch (std::exception& e){
        throw std::bad_alloc();
    }

    if(prev_item == NULL)
    {
        data_[dayIndex] = newItem;
    }

    else
    {
        prev_item->nextItem = newItem;
    }

    priorityTail = priorityHead_;
    Item * prevPriority = NULL;

    if(highPriority)
    {
        //move to tail
        while(priorityTail != NULL)
        {
            prevPriority = priorityTail;
            priorityTail = priorityTail->nextPriorityItem;
        }

        //add as first item
        if(prevPriority == NULL)
        {
            priorityHead_ = newItem; 
        }
        else
        {
            prevPriority->nextPriorityItem = newItem;
        }

        ++priority_items_num_;
    }



}


/**
     *  Removes the value at the specified location in the given day's 
     *  to-do list
     *  [TO BE WRITTEN]
     *
     *  @param[in] dayIndex
     *    Day index of the to-do list to remove from
     *  @param[in] loc
     *    Location to remove in the given day's to-do list 
     *  @throws std::out_of_range
     *    If the location is invalid.
     *
     *  Required complexity: Should run in time O(loc+p) where n is the size of 
     *  the data array and loc is the length of the to-do list for the given day,
     *  and p is the length of the high priority list.
     */

void DailyTodoList::remove(size_t dayIndex, size_t loc)
{
    if(dayIndex >= cap_ || loc >= this->numItemsOnDay(dayIndex))
    { 
        throw std::out_of_range("location is invalid");
    }

    size_t cur = 0;
    Item * cur_item = data_[dayIndex];
    Item * prev_item = NULL;

    //move to loc
    while(cur < loc)
    {
        prev_item = cur_item;
        cur_item = cur_item->nextItem;
        cur++;
    }

    //remove first
    if(prev_item == NULL)
    {
        data_[dayIndex] = cur_item->nextItem;
    }

    else
    {
        prev_item->nextItem = cur_item->nextItem;
    }

    Item * priorityTail = priorityHead_;
    Item * prevPriority = NULL;

    //move to current item
    while(priorityTail != NULL && priorityTail != cur_item)
    {
        prevPriority = priorityTail;
        priorityTail = priorityTail->nextPriorityItem;
    }

    if(priorityTail != NULL)
    {

        //remove non-first
        if(prevPriority != NULL)
            prevPriority->nextPriorityItem = cur_item->nextPriorityItem;
        else
            priorityHead_ = cur_item->nextPriorityItem;

        --priority_items_num_;
    }

    delete cur_item;

}

/**
     *  Returns the number of days / to-do lists stored
     *  Days range from 0 to n-1 and represent the size/capacity
     *  of the array storing the to-do lists for each day.
     *  [TO BE WRITTEN]
     *
     *  Required Complexity: O(1)
     */
size_t DailyTodoList::numDays() const
{
    return cap_;
}


/**
     *  Returns the number of items in the to-do list for the given day
     *  [TO BE WRITTEN]
     *
     *  @param[in] dayIndex
     *    Index of the day to return the number of to-do list items
     *  @throws std::out_of_range
     *    If the dayIndex is invalid.
     *
     *  Required Complexity: O(k) where k is the length of the to-do list
     *                       for the given day
     */
size_t DailyTodoList::numItemsOnDay(size_t dayIndex) const
{
    if(dayIndex < cap_)
    {
        size_t cur = 0;
        Item * cur_item = data_[dayIndex];
        //count until end
        while(cur_item != NULL)
        {
            cur_item = cur_item->nextItem;
            cur++;
        }

        return cur;
    }
    else
    { 
        throw std::out_of_range("dayIndex is invalid");
    }

}


/**
     *  Returns true if the to-do list for the given day is empty
     *  [TO BE WRITTEN]
     *
     *  @param[in] dayIndex
     *    Index of the desired to-do list 
     *  @returns true if the to-do list for the given day is empty,
     *     and false otherwise.
     *  @throws std::out_of_range
     *    If the dayIndex is invalid.
     *
     *  Required Complexity: O(1) 
     */
bool DailyTodoList::empty(size_t dayIndex) const
{
    if(dayIndex < cap_)
    {
        //if head is null
        if(data_[dayIndex] == NULL)
        {
            return true;
        }
        return false;
    }
    else
    { 
        throw std::out_of_range("dayIndex is invalid");
    }

}

/**
     *  Returns the to-do value for the given day and location in that
     *  day's to-do list.
     *  [TO BE WRITTEN]
     *
     *  @param[in] dayIndex
     *    Index of the day's to-do list 
     *  @param[in] loc
     *    Location of the item to get from the given day's to-do list
     *  @returns the to-do value
     *  @throws std::out_of_range
     *    If the dayIndex is invalid.
     *
     *  Required Complexity: O(loc) 
     */
const std::string& DailyTodoList::getNormalVal(size_t dayIndex, size_t loc) const
{
    if(dayIndex < cap_ && loc < this->numItemsOnDay(dayIndex) )
    {
        size_t cur = 0;
        Item * cur_item = data_[dayIndex];
        //move to  loc
        while(cur < loc)
        {
            cur_item = cur_item->nextItem;
            cur++;
        }

        return cur_item->val;
    }

    else
    { 
        throw std::out_of_range("dayIndex is invalid");
    }


}


std::string& DailyTodoList::getNormalVal(size_t dayIndex, size_t loc)
{
    if(dayIndex < cap_ && loc < this->numItemsOnDay(dayIndex) )
    {
        size_t cur = 0;
        Item * cur_item = data_[dayIndex];
        while(cur < loc)
        {
            cur_item = cur_item->nextItem;
            cur++;
        }

        return cur_item->val;
    }

    else
    { 
        throw std::out_of_range("dayIndex is invalid");
    }

}


/**
     *  Returns the number of values in the high priority list
     *  [TO BE WRITTEN]
     *
     *  Required Complexity: O(1)
     */
size_t DailyTodoList::numPriorityItems() const
{
    return priority_items_num_;
}


/**
     *  Returns the to-do value for the given location in the high 
     *  priority list.
     *  [TO BE WRITTEN]
     *
     *  @param[in] priorityLoc
     *    Location of the item to get from the high priority list
     *  @returns the to-do value
     *  @throws std::out_of_range
     *    If priorityLoc is invalid.
     *
     *
     *  Required Complexity: O(priorityLoc)
     */
const std::string& DailyTodoList::getPriorityVal(size_t priorityLoc) const
{

    if(priorityLoc < this->numPriorityItems() )
    {
        size_t cur = 0;
        Item * cur_item = priorityHead_;
        //move to priority loc
        while(cur < priorityLoc)
        {
            cur_item = cur_item->nextPriorityItem;
            cur++;
        }

        return cur_item->val;
    }

    else
    { 
        throw std::out_of_range("priorityLoc is invalid");
    }

}

