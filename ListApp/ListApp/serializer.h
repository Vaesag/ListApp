#pragma once
#include"list_node.h"

void serialize(ListNode* head, const std::string& fileName);
ListNode* deserialize(const std::string& fileName);