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
    int count = 0;
	if (index >= size || index < 0)
		return *last;
	else if (empty())
		return DroneRecord(0);
	else {
        while(count < index) {
            curr = curr -> next;
            count++;
        }
		return *curr;
	}
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

    if (empty())
        return false;

    if (index >= size || index < 0)
        return false;

    if (index == 0) {
        first = &value;
        first->next = curr;
        first -> prev = NULL;
        curr = first;
    }
    for (unsigned int i = 0; i < index - 1; i++) {
        curr = curr->next;
    }
    tmp = curr;
    curr = &value;
    curr->prev = tmp;
    curr->next = tmp->next;
    size++;

    return true;
}

bool DronesManager::insert_front(DroneRecord value) {
    DroneRecord *curr = first;

    first = &value;
    first->next = curr;
    first->prev = NULL;
    size++;

    print();

	return true;
}

bool DronesManager::insert_back(DroneRecord value) {
    DroneRecord *curr = last;

    last = &value;
    last->prev = curr;
    last->next = NULL;
    size++;

    return true;
}

bool DronesManager::remove(unsigned int index) {
	return false;
}

bool DronesManager::remove_front() {
	return false;
}

bool DronesManager::remove_back() {
	return false;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
	return false;
}

bool DronesManager::reverse_list() {
	return false;
}

bool DronesManagerSorted::is_sorted_asc() const {
	return false;
}

bool DronesManagerSorted::is_sorted_desc() const {
}

bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
	return false;
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
	return false;
}

void DronesManagerSorted::sort_asc() {
}
    
void DronesManagerSorted::sort_desc() {
}
