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
	
	// TODO: Implement all of the test cases below

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
        DronesManager manager1;
        manager1.insert_front(DronesManager::DroneRecord(100));
        manager1.insert(DronesManager::DroneRecord(200),1);

        //manager1.remove_back();
	    return false;
	}

    // AMAN
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

    // AMAN
	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
		return false;
	}    

    // JONATHAN
	// PURPOSE: inserts into an unsorted list, then sort the list
	bool test10() {
        DronesManagerSorted manager1;
//        manager1.insert_front(DronesManager::DroneRecord(300));
//        manager1.insert(DronesManager::DroneRecord(200),1);
//        manager1.insert(DronesManager::DroneRecord(400),2);
//        manager1.insert_back(DronesManager::DroneRecord(100));
        //manager1.sort_asc();
        manager1.insert_front(DronesManager::DroneRecord(100));
        manager1.insert(DronesManager::DroneRecord(200),1);
        manager1.insert(DronesManager::DroneRecord(300),2);
        manager1.insert_back(DronesManager::DroneRecord(400));
        manager1.insert_sorted_asc(DronesManager::DroneRecord(350));
        //manager1.print();

        ASSERT_TRUE(manager1.get_size() == 4)
        //ASSERT_TRUE(manager1.select(0) == DronesManager::DroneRecord(100) && manager1.select(1) == DronesManager::DroneRecord(200) && manager1.select(2) == DronesManager::DroneRecord(300))
        //ASSERT_TRUE(manager1.select(3) == 400)
//        ASSERT_FALSE(manager1.is_sorted_asc())
	   return true;
	}  

    // AMAN
	// PURPOSE: insert and remove into sorted manager in ascending order
	bool test11() {
	   return false;
	}

    // JONATHAN
	// PURPOSE: insert and remove into sorted manager in descending order
	bool test12() {
	   return false;
	}  
};

#endif
