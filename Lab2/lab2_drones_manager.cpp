#include "lab2_drones_manager.hpp"

// TODO: Implement all of the listed functions below

DronesManager::DronesManager() {
	DroneRecord();
    size = 0;
    first = NULL;
    last = NULL;
}

DronesManager::~DronesManager() {
//    DroneRecord *curr = first;
//    DroneRecord *next;
//
//    while (curr != NULL) {
//        next = curr->next;
//        delete curr;
//        curr = next;
//    }
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
	return lhs.batteryType == rhs.batteryType &&
			   lhs.description == rhs.description &&
			   lhs.droneID == rhs.droneID &&
			   lhs.droneType == rhs.droneType &&
			   lhs.manufacturer == rhs.manufacturer &&
			   lhs.range == rhs.range &&
			   lhs.yearBought == rhs.yearBought;
}

unsigned int DronesManager::get_size() const {
//	int count = 0;
//	DroneRecord *cur_ptr = first;
//	while (cur_ptr -> next) {
//		count++;
//		cur_ptr = cur_ptr -> next;
//	}
	return size;
}

bool DronesManager::empty() const {
	return first == NULL && last == NULL;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
    DroneRecord *curr = first;
    DroneRecord return_object;
	if (index >= size || index < 0)
		return_object = *last;
	else if (empty())
        return_object = DroneRecord(0);
	else {
        for (int i = 0; i < index; i++)
            curr = curr -> next;
		return_object = *curr;
	}

    return return_object;
}

unsigned int DronesManager::search(DroneRecord value) const {
    DroneRecord *curr = first;
    bool is_found = false;
    unsigned int return_value = 0;
    if (empty())
	    return_value = 0;

    for (unsigned int i = 0; i < size && !is_found; i++) {
        if (*curr == value) {
            is_found = true;
            return_value = i;
        } else {
            curr = curr -> next;
        }
    }

    if (!is_found)
        return_value = size;

    return return_value;
}

//NEEDS TO BE FIXED: prints the address instead of the value
void DronesManager::print() const {
    DroneRecord *curr = first;
    for (int i = 0; i < size; i++) {
        cout << i+1 << " element is " << curr << endl;
    }
}

//not sure if this is right, may need to set last. Also can you use insert to insert front or insert back?
bool DronesManager::insert(DroneRecord value, unsigned int index) {
	DroneRecord *curr = first;
    DroneRecord *tmp;
    bool insert_valid;

    if (empty() || index >= size || index < 0) {
        insert_valid = false;
    } else if (index == 0) {
        insert_front(value);
        insert_valid = true;
    } else if (index == size-1) {
        insert_back(value);
        insert_valid = true;
    } else {
        for (unsigned int i = 0; i < index - 1; i++) {
            curr = curr->next;
        }
        tmp = curr;
        curr = &value;
        curr->prev = tmp;
        curr->next = tmp->next;
        insert_valid = true;
        size++;
    }
    return insert_valid;
}

//prints the memory address instead of printing the dereferenced value
bool DronesManager::insert_front(DroneRecord value) {
    DroneRecord *curr = first;
    if (empty()) {
        first = &value;
        first->next = NULL;
        first->prev = NULL;
        last = first;
    } else {
        value.next = curr;
        value.prev = NULL;
        curr->prev = &value;
        first = &value;
    }
    size++;
	return true;
}

bool DronesManager::insert_back(DroneRecord value) {
    DroneRecord *curr = last;
    if (empty()) {
        last = &value;
        last->next = NULL;
        last->prev = NULL;
        first = last;
    } else {
        value.next = NULL;
        value.prev = curr;
        curr->next = &value;
        last = &value;
    }
    size++;
    return true;
}

bool DronesManager::remove(unsigned int index) {
    DroneRecord *curr = first;
    DroneRecord *tmp;
    bool remove_valid;
    if (empty() || index >= size || index < 0) {
        remove_valid = false;
    } else if (index == 0) {
        remove_front();
        remove_valid = true;
    } else if (index == size - 1) {
        remove_back();
        remove_valid = true;
    } else {
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
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

bool DronesManager::remove_front() {
    DroneRecord *curr = first;
    DroneRecord *tmp;
    bool remove_front_valid;
    if (empty()) {
        remove_front_valid = false;
    } else if (size == 1)  {
        first = NULL;
        last = NULL;
        delete curr;
        size--;
        remove_front_valid = true;
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

bool DronesManager::replace(unsigned int index, DroneRecord value) {
    DroneRecord *curr = first;
    DroneRecord *tmp;
    bool replace_valid;
    if (empty() || index >= size || index < 0) {
        replace_valid = false;
    }  else {
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        tmp = curr->prev;
        tmp->next = &value;
        tmp->next->next = curr;
        curr->prev = tmp->next;
        size++;
        replace_valid = true;
    }

    return replace_valid;
}

bool DronesManager::reverse_list() {
    for (int i = size-1; i >= 0; i--) {

    }
	return false;
}

bool DronesManagerSorted::is_sorted_asc() const {
    bool is_sorted = true;
//    DroneRecord *curr = first;
//
//    if (is_empty())
//        return true;
//
//    for (int i = 0; i < size-2 && is_sorted; i++) {
//        if (curr < curr->next)
//            is_sorted = false;
//    }
	return false;
}

bool DronesManagerSorted::is_sorted_desc() const {
    bool is_sorted = true;
//    DroneRecord *curr = last;
//
//    if (is_empty())
//        return true;
//
//    for (int i = size-1; i > 0 && is_sorted; i--) {
//        if (curr > curr->prev)
//            is_sorted = false;
//    }
    return is_sorted;
}

bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
//    DroneRecord *curr = first;
//
//    if (!is_sorted_asc())
//        return false;



	return false;
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
	return false;
}

void DronesManagerSorted::sort_asc() {
}
    
void DronesManagerSorted::sort_desc() {
}
