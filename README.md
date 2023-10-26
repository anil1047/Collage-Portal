# RegistrationSystem
Registration System is a group project using C++. Registration System work as its name, a registration system for students. The application contains three data structures (binary search tree, heap, and a hashtable). Data will be read and store in the three data structures. A control manager will manage the insert, update, and delete each Object on all the data structures. There also helpers objects (File-Reader, Student, and Data) was implemented to ensure program security and abstract design. The idea with three data sucture is for back up and Optimized Search Engine. Each data sucture is perform diffrent on each Search.


![img](https://github.com/Anil /Registration_System/blob/main/images/UML.jpg)

## Technology
- C++
- Pointer
- Object-Oriented Design
- Encapsulation
- Pollymorphism
- Data Structures
- Algorithm
- Memory Management

## How It Works? 

Once we start the project, a menu opens showing us various options including Modify, Delete, view, fetch recent deletes, serach by student id etc. It reads data from the storage data structures. In Modify we have further options to Insert, Delete, and Update the records. Once we enter the details, a check is performed to validate the inserted data is in accordance with our schema or not. If yes, we store the data in three type of data structures, a heap, a BST and a hash table. These offer us different features and help us to optimize the time complexity at the cost of extra memory. BST is used to check for a record in logN time complexity, wheres if hash table store the details the record of students with key as their roll number. So, if we have student id, we can directly search in hash table in O(constant) time complexity. Heap is used to keep track of most frequent searches, recent deleted etc. We use cpp file handlers to read and write data to file on succesfull validation to store data. 


## Authors

* **Ashok Kumar Saini** - *Initial work* - [Project](https://github.com/sainiAshokKumar)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone whose code was used
* Inspiration
* etc

