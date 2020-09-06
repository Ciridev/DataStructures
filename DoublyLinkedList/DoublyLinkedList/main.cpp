#include <iostream>
#include "DoublyLinkedList.h"

int main()
{
	// Sample code
	
	DoublyLinkedList<int> dllint;
	dllint.PushBack(3);
	dllint.PushFront(1);
	dllint.PopBack();
	
	for(auto& elem : dllint)
		std::cout << elem << std::endl;
	
	return 0;
}
