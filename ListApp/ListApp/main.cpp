#include<iostream>
#include<unordered_map>

#include"reader.h"
#include"serializer.h"

static void printList(ListNode* head)
{
	std::unordered_map<ListNode*, int> idx;
	int i = 0;

	for (ListNode* cur = head; cur;cur = cur->next)
	{
		idx[cur] = i++;
	}

	i = 0;
	for (ListNode* cur = head; cur;cur = cur->next, ++i)
	{
		std::string randStr = cur->rand ? std::to_string(idx[cur->rand]) : "nullptr";
		std::cout << " [" << i << "] \"" << cur->data << "\" rand=" << randStr << std::endl;
	}
}

int main()
{
	try
	{
		ListNode* head = readFromFile("inlet.in");
		std::cout << "Original list:" << std::endl;
		printList(head);

		serialize(head, "outlet.out");
		ListNode* deserializedHead = deserialize("outlet.out");
		std::cout << "\nDeserialized list:" << std::endl;
		printList(deserializedHead);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return 1;
	}
	return 0;
}