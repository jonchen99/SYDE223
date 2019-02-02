#include "lab2_drones_manager.hpp"

// TODO: Implement all of the listed functions below

DronesManager::DronesManager() {
	DroneRecord();
}

DronesManager::~DronesManager() {
    DroneRecord *curr = first;
    DroneRecord *next;

    while (curr != NULL) {
        next = curr->next;
        delete curr;
        curr = next;
    }
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
	return first == NULL && first->next == NULL;
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

void DronesManager::print() const {
    DroneRecord *curr = first;
    int count = 1;
    while (curr -> next) {
        cout << count << " element is " << curr << endl;
    }
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
	DroneRecord *curr = first;
    if (index >= size || index < 0)
        return false;

    if (index == 0) {
        first = &value;
    }
    for (unsigned int i = 0; i < index - 1; i++) {
        curr = curr->next;
    }
    int i =2;
    int *ip1;
    ip1 = &i;
}

bool DronesManager::insert_front(DroneRecord value) {
	return false;
}

bool DronesManager::insert_back(DroneRecord value) {
	return false;
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
