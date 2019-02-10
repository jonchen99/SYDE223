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
	return size;
}

bool DronesManager::empty() const {
	return first == NULL && last == NULL;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
    DroneRecord *curr = first;
    DroneRecord return_object;

    if (empty())
        return_object = DroneRecord(0);
    else if (index >= size || index < 0)
        return_object = *last;
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

void DronesManager::print() const {
    DroneRecord *curr = first;
    for (int i = 0; i < size; i++) {
        cout << i+1 << " element is " << curr->droneID << endl;
        if (curr->next != NULL) {
            curr = curr->next;
        }
    }
}

//try to get insert_front and insert_back to work here
bool DronesManager::insert(DroneRecord value, unsigned int index) {
	DroneRecord *curr = first;
    DroneRecord *tmp;
    bool insert_valid;

    if (index > size || index < 0) {
        insert_valid = false;

    } else if (index == 0) {
//        insert_front(value);
//        insert_valid = true;
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
        insert_valid = true;
    } else if (index == size) {
        curr = last;
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
        insert_valid = true;
    } else {

        for (unsigned int i = 0; i < index - 1; i++) {
            curr = curr->next;
        }

        tmp = curr;
        curr = &value;
        curr->prev = tmp;
        curr->next = tmp->next;
        tmp->next = curr;

        insert_valid = true;
        size++;
    }
    return insert_valid;
}

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
        curr->next = &value;
        value.next = NULL;
        value.prev = curr;
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
        //delete curr;
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
        //delete curr;
        size--;
        remove_front_valid = true;
    } else {
        tmp = curr->next;
        tmp->prev = NULL;
        first = tmp;
        size--;
        //delete curr;
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
        //delete curr;
        remove_back_valid = true;
    } else {
        tmp = curr->prev;
        tmp->next = NULL;
        last = tmp;
        size--;
        //delete curr;
        remove_back_valid = true;
    }

	return remove_back_valid;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
    DroneRecord *curr = first;
    DroneRecord *tmp;
    bool replace_valid;
    if (empty() || index > size || index < 0) {
        replace_valid = false;
    }  else {
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        tmp = curr->prev;
        tmp->next = &value;
        tmp->next->next = curr->next;
        curr->next->prev = tmp->next;
        tmp->next->prev = tmp;
        replace_valid = true;
    }

    return replace_valid;
}

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

bool DronesManagerSorted::is_sorted_asc() const {
    bool is_sorted = true;
    DroneRecord *curr = first;

    if (empty())
        is_sorted = true;
    else {
        for (int i = 0; i < size-1 && is_sorted; i++) {
            if (curr->droneID > curr->next->droneID)
                is_sorted = false;
            curr = curr->next;
        }
    }
	return is_sorted;
}

bool DronesManagerSorted::is_sorted_desc() const {
    bool is_sorted = true;
    DroneRecord *curr = last;

    if (empty())
        is_sorted = true;
    else {
        for (int i = 0; i < size-1 && is_sorted; i++) {
            if (curr->droneID < curr->prev->droneID)
                is_sorted = false;
            curr = curr->prev;
        }
    }
    return is_sorted;
}

bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
    DroneRecord *curr = first;
    bool sorted_asc;
    bool dont_stop_loop = true;

    if (!is_sorted_asc()) {
        sorted_asc = false;

    } else if (empty()) {
        insert_front(val);
        sorted_asc = true;

    } else {
        for (int i = 0; i < size && dont_stop_loop; i++) {
            if (val.droneID > curr->droneID) {
                curr = curr->next;
            } else {
                //this won't work because it can't call insert
                insert(val, i);
                sorted_asc = true;
                dont_stop_loop = false;
            }
        }
    }

	return sorted_asc;
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
    DroneRecord *curr = first;
    bool sorted_desc;
    bool dont_stop_loop = true;

    if (!is_sorted_desc()) {
        sorted_desc = false;
    } else if (empty()) {
        insert_front(val);
        sorted_desc = true;
    } else {
        for (int i = size-1; i > 0 && dont_stop_loop; i--) {
            if (val.droneID < curr->droneID) {
                curr = curr->prev;
            } else {
                insert(val,i);
                sorted_desc = true;
                dont_stop_loop = false;
            }
        }
    }

	return sorted_desc;
}

void DronesManagerSorted::sort_asc() {
    DroneRecord *curr = first;
    DroneRecord *next;
    while (curr != NULL) {
        next = curr->next;
        curr->prev = NULL;
        curr->next = NULL;
        insert_sorted_asc(*curr);
        curr = next;
    }
}
    
void DronesManagerSorted::sort_desc() {
    DroneRecord *curr = last;
    DroneRecord *prev;

    while (curr != NULL) {
        prev = curr->prev;
        curr->next = NULL;
        curr->prev = NULL;
        insert_sorted_desc(*curr);
        curr = prev;
    }
}
