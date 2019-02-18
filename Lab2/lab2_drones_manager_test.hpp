#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "lab2_drones_manager.hpp"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {
public:
	// PURPOSE: New empty list is valid
	bool test1() {
		DronesManager manager;
		ASSERT_TRUE(manager.get_size() == 0)
		ASSERT_TRUE(manager.empty() == true)
		ASSERT_TRUE(manager.first == NULL)
		ASSERT_TRUE(manager.last == NULL)
	    return true;
	}
	
	// PURPOSE: insert_front() and insert_back() on zero-element list
	bool test2() {
        DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(100));

		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)
		ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last)
		ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
		ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)
		ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))
	    return true;
	}


    // JONATHAN
	// PURPOSE: select() and search() work properly
	bool test3() {
        DronesManager manager1, manager2;
        manager1.insert_front(DronesManager::DroneRecord(100));
        manager1.insert(DronesManager::DroneRecord(200),1);
        manager1.insert_back(DronesManager::DroneRecord(300));
        ASSERT_TRUE(manager1.get_size() == 3)
        ASSERT_TRUE(manager1.select(0) == DronesManager::DroneRecord(100) && manager1.select(1) == DronesManager::DroneRecord(200) && manager1.select(2) == DronesManager::DroneRecord(300))
        ASSERT_TRUE(manager2.select(0) == DronesManager::DroneRecord(0))
        ASSERT_TRUE(manager1.select(3) == DronesManager::DroneRecord(300) && manager1.select(1000) == DronesManager::DroneRecord(300) && manager1.select(-100) == DronesManager::DroneRecord(300))
        ASSERT_TRUE(manager1.search(100) == 0 && manager1.search(200) == 1 && manager1.search(300) == 2)
        ASSERT_TRUE(manager2.search(0) == 0 && manager2.search(1000) == 0)
        ASSERT_TRUE(manager1.search(1000) == 3 && manager1.search(-1) == 3)
        return true;
	}

    // AMAN
	// PURPOSE: remove_front() and remove_back() on one-element list
	bool test4() {
        DronesManager manager1, manager2, manager3, manager4, manager5, manager6;

        //Test remove front after insert_front
        manager1.insert_front(DronesManager::DroneRecord(100));
        manager1.remove_front();

        //Test remove back after insert_front
        manager2.insert_front(DronesManager::DroneRecord(100));
        manager2.remove_back();

        //Test remove front after insert_back
        manager3.insert_back(DronesManager::DroneRecord(100));
        manager3.remove_front();

        //Test remove back after insert_back
        manager4.insert_back(DronesManager::DroneRecord(100));
        manager4.remove_back();

        //Test remove front after insert
        manager5.insert(DronesManager::DroneRecord(100),0);
        manager5.remove_front();

        //Test remove back after insert
        manager6.insert(DronesManager::DroneRecord(100),0);
        manager6.remove_back();

        ASSERT_TRUE(manager1.get_size() == 0)
        ASSERT_TRUE(manager2.get_size() == 0)
        ASSERT_TRUE(manager3.get_size() == 0)
        ASSERT_TRUE(manager4.get_size() == 0)
        ASSERT_TRUE(manager5.get_size() == 0)
        ASSERT_TRUE(manager6.get_size() == 0)

        return true;
	}

    // TODO: AMAN
	// PURPOSE: replace() and reverse_list() work properly
	bool test5() {
	    return false;
	}

    // JONATHAN
	// PURPOSE: insert_front() keeps moving elements forward
	bool test6() {
        DronesManager manager1;
        manager1.insert_front(DronesManager::DroneRecord(100));
        manager1.insert_front(DronesManager::DroneRecord(200));
        manager1.insert_front(DronesManager::DroneRecord(300));
        manager1.insert_front(DronesManager::DroneRecord(400));

        ASSERT_TRUE(manager1.get_size() == 4)
        ASSERT_TRUE(manager1.select(0) == DronesManager::DroneRecord(400) && manager1.select(1) == DronesManager::DroneRecord(300) && manager1.select(2) == DronesManager::DroneRecord(200))
        ASSERT_TRUE(manager1.select(3) == DronesManager::DroneRecord(100))
        ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)

        return true;
	}

    // TODO: AMAN
    // AMAN
	// PURPOSE: inserting at different positions in the list
	bool test7() {
	    return false;
	}

    // JONATHAN
	// PURPOSE: try to remove too many elements, then add a few elements
	bool test8() {
        DronesManager manager1,manager2;
        manager1.insert_front(DronesManager::DroneRecord(100));
        manager1.insert(DronesManager::DroneRecord(200),1);
        manager1.insert(DronesManager::DroneRecord(300),2);
        manager1.insert_back(DronesManager::DroneRecord(400));
        manager2.insert_front(DronesManager::DroneRecord(200));
        manager2.insert_back(DronesManager::DroneRecord(300));

        ASSERT_TRUE(manager1.get_size() == 4)
        ASSERT_TRUE(manager1.remove(3))
        ASSERT_TRUE(manager1.select(0) == DronesManager::DroneRecord(100) && manager1.select(1) == DronesManager::DroneRecord(200) && manager1.select(2) == DronesManager::DroneRecord(300))

        manager1.remove_back();
        manager1.remove_front();
        manager1.remove(0);

        ASSERT_FALSE(manager1.remove_front())
        ASSERT_FALSE(manager1.remove_back())
        ASSERT_FALSE(manager1.remove(1))

        manager1.insert_front(DronesManager::DroneRecord(100));
        manager1.insert(DronesManager::DroneRecord(200),1);
        manager1.insert(DronesManager::DroneRecord(300),2);
        manager1.insert_back(DronesManager::DroneRecord(400));

        ASSERT_FALSE(manager1.remove(4) && manager1.remove(1000) && manager1.remove(-1))
        ASSERT_TRUE(manager1.remove(0) && manager1.remove(2))
        ASSERT_TRUE(manager1.select(0) == 200 && manager1.select(1) == 300)
        ASSERT_TRUE(manager1.first->droneID == manager2.first->droneID && manager1.last->droneID == manager2.last->droneID)
        ASSERT_TRUE(manager1.first->next->droneID == manager2.select(1) && manager1.last->next == NULL && manager1.first->prev == NULL)
        return true;
	}

    // TODO: AMAN
    // AMAN
	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
		return false;
	}    

    // JONATHAN
	// PURPOSE: inserts into an unsorted list, then sort the list
	bool test10() {
        DronesManagerSorted manager1,manager2;
        manager1.insert_front(DronesManager::DroneRecord(300));
        manager1.insert(DronesManager::DroneRecord(200),1);
        manager1.insert(DronesManager::DroneRecord(400),2);
        manager1.insert_back(DronesManager::DroneRecord(100));
        manager1.sort_asc();

        manager2.insert_front(DronesManager::DroneRecord(200));
        manager2.insert(DronesManager::DroneRecord(300),1);
        manager2.insert(DronesManager::DroneRecord(100),2);
        manager2.insert_back(DronesManager::DroneRecord(400));
        manager2.sort_desc();

        ASSERT_TRUE(manager1.get_size() == 4)
        ASSERT_TRUE(manager1.first->droneID == 100 && manager1.first->prev == NULL && manager1.first->next->droneID == manager1.select(1))
        ASSERT_TRUE(manager1.last->droneID == 400 && manager1.last->next == NULL && manager1.last->prev->droneID == manager1.select(2))
        ASSERT_TRUE(manager1.select(0) == DronesManager::DroneRecord(100) && manager1.select(1) == DronesManager::DroneRecord(200))
        ASSERT_TRUE(manager1.select(2) == DronesManager::DroneRecord(300) && manager1.select(3) == DronesManager::DroneRecord(400))

        ASSERT_TRUE(manager2.get_size() == 4)
        ASSERT_TRUE(manager2.first->droneID == 400 && manager2.first->prev == NULL && manager2.first->next->droneID == manager2.select(1))
        ASSERT_TRUE(manager2.last->droneID == 100 && manager2.last->next == NULL && manager2.last->prev->droneID == manager2.select(2))
        ASSERT_TRUE(manager2.select(0) == DronesManager::DroneRecord(400) && manager2.select(1) == DronesManager::DroneRecord(300))
        ASSERT_TRUE(manager2.select(2) == DronesManager::DroneRecord(200) && manager2.select(3) == DronesManager::DroneRecord(100))
	   return true;
	}

    // TODO: AMAN
    // AMAN
	// PURPOSE: insert and remove into sorted manager in ascending order
	bool test11() {
	   return false;
	}

    // TODO: Inserting the value 200 isn't working
    // JONATHAN
	// PURPOSE: insert and remove into sorted manager in descending order
	bool test12() {
        DronesManagerSorted manager1, manager2;
        manager1.insert_sorted_desc(DronesManager::DroneRecord(300));
        manager1.insert_sorted_desc(DronesManager::DroneRecord(100));
        manager1.insert_sorted_desc(DronesManager::DroneRecord(200));
        manager1.print();
        cout << manager1.last->prev->droneID << endl;

        ASSERT_TRUE(manager1.get_size() == 3)
        ASSERT_TRUE(manager1.first->droneID == 100 && manager1.first->prev == NULL && manager1.first->next->droneID == manager1.select(1) && manager1.first->next->droneID == 200)
        ASSERT_TRUE(manager1.last->droneID == 300  && manager1.last->next == NULL && manager1.last->prev->droneID == 200)
	   return true;
	}  
};

#endif
