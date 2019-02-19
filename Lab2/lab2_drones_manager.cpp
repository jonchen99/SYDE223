// Jonathan Chen 20722167 && Aman Mathur 20710307
// February 19th, 2019
// SYDE 223 Lab #2

#include "lab2_drones_manager.hpp"

//default constructor
DronesManager::DronesManager() {
    DroneRecord();
    size = 0;
    first = NULL;
    last = NULL;
}

//destructor
DronesManager::~DronesManager() {
    DroneRecord *curr = first;
    DroneRecord *next;

    while (curr != NULL) {
        next = curr->next;
        delete curr;
        curr = next;
    }
}

//overloaded comparison operator
bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
    return lhs.batteryType == rhs.batteryType &&
           lhs.description == rhs.description &&
           lhs.droneID == rhs.droneID &&
           lhs.droneType == rhs.droneType &&
           lhs.manufacturer == rhs.manufacturer &&
           lhs.range == rhs.range &&
           lhs.yearBought == rhs.yearBought;
}

//gets the size of DroneManager
unsigned int DronesManager::get_size() const {
    return size;
}

//checks if DroneManager is empty by checking if the first and last elements point to null
bool DronesManager::empty() const {
    return first == NULL && last == NULL;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
    DroneRecord *curr = first;
    DroneRecord return_object;

    //if it's empty, call the default constructor
    if (empty())
        return_object = DroneRecord(0);

        //if the index is invalid, return the last element
    else if (index >= size || index < 0)
        return_object = *last;

        //otherwise return the instance of DroneManager specified
    else {
        for (int i = 0; i < index; i++)
            curr = curr -> next;
        return_object = *curr;
    }

    return return_object;
}

//searches for a DroneRecord value and returns the index of where it is found
unsigned int DronesManager::search(DroneRecord value) const {
    DroneRecord *curr = first;
    bool is_found = false;
    unsigned int return_value = 0;

    //default if the list is empty
    if (empty())
	    return_value = 0;

    for (unsigned int i = 0; i < size && !is_found; i++) {
        //loops until the value is found and is_found variable is to stop the loop
        if (*curr == value) {
            is_found = true;
            return_value = i;
        } else {
            curr = curr -> next;
        }
    }

    //if it isn't found, returns the size of the list
    if (!is_found)
        return_value = size;

    return return_value;
}

//print function that prints the drone ID value
void DronesManager::print() const {
    DroneRecord *curr = first;
    for (int i = 0; i < size; i++) {
        cout << i+1 << " element is " << curr->droneID << endl;
        if (curr->next != NULL) {
            curr = curr->next;
        }
    }
}

//insert a DroneRecord into DronesManager
bool DronesManager::insert(DroneRecord value, unsigned int index) {
	DroneRecord *curr = first;
    DroneRecord *tmp;
    DroneRecord *new_value = new DroneRecord(value);
    bool insert_valid;

    //if the index is not valid
    if (index > size || index < 0) {
        insert_valid = false;

    //if the index is the first element, use insert front
    } else if (index == 0) {
        insert_front(value);
        insert_valid = true;

    //if the index is the last element, use insert back
    } else if (index == size) {
        insert_back(value);
        insert_valid = true;

    //else iterate until the correct value
    } else {
        for (unsigned int i = 0; i < index - 1; i++) {
            curr = curr->next;
        }
        //inserting the value and rearranging the pointers
        tmp = curr;
        curr = new_value;
        curr->prev = tmp;
        curr->next = tmp->next;
        tmp->next = curr;
        curr->next->prev = curr;

        insert_valid = true;
        size++;
    }
    return insert_valid;
}

//insert a DroneRecord to the front of DronesManager
bool DronesManager::insert_front(DroneRecord value) {
    DroneRecord *curr = first;
    DroneRecord *new_value = new DroneRecord(value);

    if (empty()) {
        first = new_value;
        first->next = NULL;
        first->prev = NULL;
        last = first;
    } else {
        new_value -> next = curr;
        new_value -> prev = NULL;
        curr->prev = new_value;
        first = new_value;
    }
    size++;

    return true;
}

//insert a DroneRecord to the back of DronesManager
bool DronesManager::insert_back(DroneRecord value) {
    DroneRecord *curr = last;
    DroneRecord *new_value = new DroneRecord(value);
    if (empty()) {
        last = new_value;
        last->next = NULL;
        last->prev = NULL;
        first = last;
    } else {
        curr->next = new_value;
        new_value -> next = NULL;
        new_value -> prev = curr;
        last = new_value;
    }
    size++;
    return true;
}

//remove a DroneRecord from DronesManager
bool DronesManager::remove(unsigned int index) {
    DroneRecord *curr = first;
    DroneRecord *tmp;
    bool remove_valid;

    //check if the index is valid
    if (empty() || index >= size || index < 0) {
        remove_valid = false;

    //if the index is the first element, use remove front
    } else if (index == 0) {
        remove_front();
        remove_valid = true;

    //if the index is the last element, use remove back
    } else if (index == size - 1) {
        remove_back();
        remove_valid = true;

    //iterate to the desired index
    } else {
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        //rearranging pointers and deleting the value at the index
        tmp = curr->prev;
        tmp->next = curr->next;
        tmp = curr->next;
        tmp->prev = curr->prev;
        delete curr;
        size--;
        remove_valid = true;
    }

    return remove_valid;
}

//remove a DroneRecord from the front of DronesManager
bool DronesManager::remove_front() {
    DroneRecord *curr = first;
    DroneRecord *tmp;
    bool remove_front_valid;

    //checking if empty
    if (empty()) {
        remove_front_valid = false;

    //removing if there is only one element in the list
    } else if (size == 1)  {
        first = NULL;
        last = NULL;
        delete curr;
        size--;
        remove_front_valid = true;

    //rearranging pointers and removing the instance of DroneRecord
    } else {
        tmp = curr->next;
        tmp->prev = NULL;
        first = tmp;
        size--;
        delete curr;
        remove_front_valid = true;
    }
    return remove_front_valid;
}

//remove a DroneRecord from the back of DronesManager
bool DronesManager::remove_back() {
    DroneRecord *curr = last;
    DroneRecord *tmp;
    bool remove_back_valid;

    if (empty()) {
        remove_back_valid = false;

    } else if (size == 1) {
        first = NULL;
        last = NULL;
        size--;
        delete curr;
        remove_back_valid = true;

    } else {
        tmp = curr->prev;
        tmp->next = NULL;
        last = tmp;
        size--;
        delete curr;
        remove_back_valid = true;
    }

	return remove_back_valid;
}

//replace an instance of DroneRecord with another instance
bool DronesManager::replace(unsigned int index, DroneRecord value) {
    DroneRecord *curr = first;
    DroneRecord *tmp;
    DroneRecord *new_value = new DroneRecord(value);

    bool replace_valid;

    //checking if the index is valid
    if (empty() || index >= size || index < 0) {
        replace_valid = false;

    //using remove front and insert front to replace the value at the beginning of DronesManager
    }  else if (index == 0) {
        remove_front();
        insert_front(*new_value);
        replace_valid = true;

    //using remove back and insert back to replace the value at the end of DronesManager
    } else if (index == size-1) {
        remove_back();
        insert_back(*new_value);
        replace_valid = true;

    //iterating to the desired index
    } else {
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }

        //rearranging pointers and inserting new DroneRecord
        tmp = curr->prev;
        tmp->next = new_value;
        tmp->next->next = curr->next;
        curr->next->prev = tmp->next;
        tmp->next->prev = tmp;
        replace_valid = true;
    }

    return replace_valid;
}

//reverse the list
bool DronesManager::reverse_list() {
    DroneRecord *curr = first;

    while (curr != NULL) {
        DroneRecord *tmp = curr->next;
        curr->next = curr->prev;
        curr->prev = tmp;
        if (tmp == NULL) {
            last = first;
            first = curr;
        }
        curr = tmp;
    }
    return true;
}

//check if DronesManager is sorted in ascending fashion
bool DronesManagerSorted::is_sorted_asc() const {
    bool is_sorted = true;
    DroneRecord *curr = first;

    if (empty())
        is_sorted = true;

    //checking if it is sorted
    else {
        for (int i = 0; i < size-1 && is_sorted; i++) {
            if (curr->droneID > curr->next->droneID)
                is_sorted = false;
            curr = curr->next;
        }
    }
	return is_sorted;
}

//check if DronesManager is sorted in descending fashion
bool DronesManagerSorted::is_sorted_desc() const {
    bool is_sorted = true;
    DroneRecord *curr = last;

    if (empty())
        is_sorted = true;

    //checking if sorted
    else {
        for (int i = 0; i < size-1 && is_sorted; i++) {
            if (curr->droneID > curr->prev->droneID)
                is_sorted = false;
            curr = curr->prev;
        }
    }
    return is_sorted;
}

//insert a value so that DronesManager is sorted in ascending fashion
bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
    DroneRecord *curr = first;
    bool sorted_asc;
    bool dont_stop_loop = true;
    int index = 0;

    //checks if the list is already sorted
    if (!is_sorted_asc()) {
        sorted_asc = false;

    //inserting at the front of an empty list
    } else if (empty()) {
        insert_front(val);
        sorted_asc = true;

    } else {
        //iterating to the correct index and using the insert function to insert the desired value
        for (int i = 0; i < size && dont_stop_loop; i++) {

            if (val.droneID > curr->droneID) {
                curr = curr->next;
                index = size;
            } else {
                index = i;
                dont_stop_loop = false;
            }
        }
        sorted_asc = true;
        insert(val, index);
    }

	return sorted_asc;
}

//insert a value so that DronesManager is sorted in descending fashion
bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
    DroneRecord *curr = first;
    bool sorted_desc;
    bool dont_stop_loop = true;
    int index = 0;

    if (!is_sorted_desc()) {
        sorted_desc = false;

    } else if (empty()) {
        insert_front(val);
        sorted_desc = true;

    } else {
        for (int i = 0; i < size && dont_stop_loop; i++) {

            if (val.droneID < curr->droneID) {
                curr = curr->next;
                index = size;
            } else {
                index = i;
                dont_stop_loop = false;
            }
        }
        sorted_desc = true;
        insert(val, index);
    }

	return sorted_desc;
}

//sorts DronesManager in ascending fashion
void DronesManagerSorted::sort_asc() {
    DroneRecord *curr;
    DroneRecord *prev;
    DroneRecord *next;

    //using a bubble sort
    for (int i = 0; i < size; i++) {
        curr = first;
        while (curr->next != NULL) {
            if (curr->droneID > curr->next->droneID) {
                next = curr->next;
                prev = curr->prev;

                if (curr == first)
                    first = next;
                if (curr->next == last)
                    last = curr;
                if (prev != NULL)
                    prev->next = next;
                if (curr->next->next != NULL)
                    next->next->prev = curr;

                //rearranging pointers
                curr->next = next->next;
                curr->prev = next;
                next->next = curr;
                next->prev = prev;
                curr = next;
            }
            curr = curr->next;
        }
    }
}

//sorts DronesManager in descending fashion
void DronesManagerSorted::sort_desc() {
    DroneRecord *curr;
    DroneRecord *prev;
    DroneRecord *next;

    //using a bubble sort
    for (int i = 0; i < size; i++) {
        curr = first;
        while (curr->next != NULL) {
            if (curr->droneID < curr->next->droneID) {
                next = curr->next;
                prev = curr->prev;

                if (curr == first)
                    first = next;
                if (curr->next == last)
                    last = curr;
                if (prev != NULL)
                    prev->next = next;
                if (curr->next->next != NULL)
                    next->next->prev = curr;

                //rearranging pointers
                curr->next = next->next;
                curr->prev = next;
                next->next = curr;
                next->prev = prev;
                curr = next;
            }
            curr = curr->next;
        }
    }
}
