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

	// PURPOSE: replace() and reverse_list() work properly
	bool test5() {
        DronesManager manager;
        const int num_elems = 8;
        for (int i = 0; i < num_elems; i++) {
            ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(i)))
        }

        ASSERT_TRUE(manager.replace(0, DronesManager::DroneRecord(100)))
        ASSERT_TRUE(manager.replace(2, DronesManager::DroneRecord(200)))
        ASSERT_TRUE(manager.replace(7, DronesManager::DroneRecord(300)))
        ASSERT_TRUE(*manager.first == DronesManager::DroneRecord(100))
        ASSERT_TRUE(*manager.last == DronesManager::DroneRecord(300))
        ASSERT_TRUE(*(manager.first->next->next) == DronesManager::DroneRecord(200))

        int test_values[8] = {10, 6, 5, 4, 9, 2, 1, 8};
        ASSERT_TRUE(manager.reverse_list());
        for (int i = 0; i < num_elems; i++) {
            ASSERT_TRUE(manager.select(i) == DronesManager::DroneRecord(test_values[i]))
        }

        ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)

	    return true;
	}

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
        ASSERT_TRUE(manager1.first->droneID == 400 && manager1.first->prev == NULL && manager1.first->next->droneID == manager1.select(1) && manager1.first->next->droneID == 300)
        ASSERT_TRUE(manager1.last->droneID == 100 && manager1.last->next == NULL && manager1.last->prev->droneID == manager1.select(2) && manager1.last->prev->droneID == 200)

        return true;
	}

	// PURPOSE: inserting at different positions in the list
	bool test7() {
        DronesManager manager;
        const int num_elems = 5;
        for (int i = 0; i < num_elems; i++) {
            ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(i)))
        }

        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(20), 0));
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(30), 6));
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(40), 4));
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(20), 0));
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(30), 3));
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(40), 10));
        ASSERT_TRUE(manager.get_size() == 11);

        return true;
	}

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

	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
        DronesManager manager1;
        ASSERT_FALSE(manager1.insert(DronesManager::DroneRecord(100),1));
        ASSERT_TRUE(manager1.insert(DronesManager::DroneRecord(200),0));
        ASSERT_FALSE(manager1.insert(DronesManager::DroneRecord(300),-2));
        ASSERT_FALSE(manager1.insert(DronesManager::DroneRecord(400),8));
        ASSERT_TRUE(manager1.insert(DronesManager::DroneRecord(500),1));
        ASSERT_FALSE(manager1.insert(DronesManager::DroneRecord(600),-1));
        ASSERT_FALSE(manager1.insert(DronesManager::DroneRecord(700),4));
        ASSERT_TRUE(manager1.insert(DronesManager::DroneRecord(500),0));
        ASSERT_TRUE(manager1.remove(2));
        ASSERT_FALSE(manager1.remove(-2));
        ASSERT_FALSE(manager1.remove(9));
        ASSERT_TRUE(manager1.remove(0));


        return true;
	}    

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

	// PURPOSE: insert and remove into sorted manager in ascending order
	bool test11() {
        DronesManagerSorted manager1, manager2;
        manager1.insert_sorted_asc(DronesManager::DroneRecord(300));
        manager1.insert_sorted_asc(DronesManager::DroneRecord(100));
        manager1.insert_sorted_asc(DronesManager::DroneRecord(200));

        ASSERT_TRUE(manager1.get_size() == 3)
        ASSERT_TRUE(manager1.first->droneID == 100 && manager1.first->prev == NULL && manager1.first->next->droneID == manager1.select(1) && manager1.first->next->droneID == 200)
        ASSERT_TRUE(manager1.last->droneID == 300  && manager1.last->next == NULL &&  manager1.last->prev->droneID == manager1.select(1) && manager1.last->prev->droneID == 200)

        manager1.remove_back();
        manager1.remove_front();

        ASSERT_TRUE(manager1.get_size() == 1)
        ASSERT_TRUE(manager1.first->droneID == 200 && manager1.first->prev == NULL && manager1.first->next == NULL)

        manager1.insert_sorted_asc(DronesManager::DroneRecord(400));
        manager1.insert_sorted_asc(DronesManager::DroneRecord(100));
        manager1.insert_sorted_asc(DronesManager::DroneRecord(300));

        ASSERT_TRUE(manager1.get_size() == 4)
        ASSERT_TRUE(manager1.first->droneID == 100 && manager1.first->prev == NULL && manager1.first->next->droneID == manager1.select(1) && manager1.first->next->droneID == 200)
        ASSERT_TRUE(manager1.last->droneID == 400  && manager1.last->next == NULL &&  manager1.last->prev->droneID == manager1.select(2) && manager1.last->prev->droneID == 300)
        return true;	}

	// PURPOSE: insert and remove into sorted manager in descending order
	bool test12() {
        DronesManagerSorted manager1, manager2;
        manager1.insert_sorted_desc(DronesManager::DroneRecord(300));
        manager1.insert_sorted_desc(DronesManager::DroneRecord(100));
        manager1.insert_sorted_desc(DronesManager::DroneRecord(200));

        ASSERT_TRUE(manager1.get_size() == 3)
        ASSERT_TRUE(manager1.first->droneID == 300 && manager1.first->prev == NULL && manager1.first->next->droneID == manager1.select(1) && manager1.first->next->droneID == 200)
        ASSERT_TRUE(manager1.last->droneID == 100  && manager1.last->next == NULL &&  manager1.last->prev->droneID == manager1.select(1) && manager1.last->prev->droneID == 200)

        manager1.remove_back();
        manager1.remove_front();

        ASSERT_TRUE(manager1.get_size() == 1)
        ASSERT_TRUE(manager1.first->droneID == 200 && manager1.first->prev == NULL && manager1.first->next == NULL)

        manager1.insert_sorted_desc(DronesManager::DroneRecord(400));
        manager1.insert_sorted_desc(DronesManager::DroneRecord(100));
        manager1.insert_sorted_desc(DronesManager::DroneRecord(300));

        ASSERT_TRUE(manager1.get_size() == 4)
        ASSERT_TRUE(manager1.first->droneID == 400 && manager1.first->prev == NULL && manager1.first->next->droneID == manager1.select(1) && manager1.first->next->droneID == 300)
        ASSERT_TRUE(manager1.last->droneID == 100  && manager1.last->next == NULL &&  manager1.last->prev->droneID == manager1.select(2) && manager1.last->prev->droneID == 200)
	   return true;
	}  
};

#endif
