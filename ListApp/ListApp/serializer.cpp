#include"serializer.h"

#include<fstream>
#include<vector>
#include<stdexcept>
#include<unordered_map>
#include<cstdint>

void serialize(ListNode* head, const std::string& fileName)
{
	std::ofstream file(fileName,std::ios::binary);
	if (!file.is_open())
	{
		throw std::runtime_error("Cannot open output file: " + fileName);
	}

	std::unordered_map<ListNode*, int32_t> indexMap;
	std::vector<ListNode*> nodes;

	for (ListNode* cur = head; cur;cur = cur->next)
	{
		indexMap[cur] = static_cast<int32_t>(nodes.size());
		nodes.push_back(cur);
	}
	auto count = static_cast<uint32_t>(nodes.size());
	file.write(reinterpret_cast<const char*>(&count), sizeof(count));

	for (ListNode* node : nodes)
	{
		auto dataLen = static_cast<uint32_t>(node->data.size());
		file.write(reinterpret_cast<const char*>(&dataLen), sizeof(dataLen));
		file.write(node->data.data(), dataLen);

		int32_t randIdx = node->rand ? indexMap.at(node->rand) : -1;
		file.write(reinterpret_cast<const char*>(&randIdx), sizeof(randIdx));
	}
}

ListNode* deserialize(const std::string& fileName)
{
	std::ifstream file(fileName, std::ios::binary);
	if (!file.is_open())
	{
		throw std::runtime_error("Cannot open file: " + fileName);
	}

	uint32_t count = 0;
	file.read(reinterpret_cast<char*>(&count), sizeof(count));
	if (count == 0)
	{
		return nullptr;
	}

	std::vector<ListNode*> nodes(count);
	std::vector<int32_t> randIndices(count);

	for (uint32_t i = 0; i < count; ++i)
	{
		nodes[i] = new ListNode();


		uint32_t dataLen = 0;
		file.read(reinterpret_cast<char*>(&dataLen), sizeof(dataLen));
		nodes[i]->data.resize(dataLen);
		file.read(nodes[i]->data.data(), static_cast<std::streamsize>(dataLen));
		file.read(reinterpret_cast<char*>(&randIndices[i]), sizeof(int32_t));
	}

	for (uint32_t i = 0; i < count; ++i)
	{
		if (i > 0) nodes[i]->prev = nodes[i - 1];
		if (i + 1 < count) nodes[i]->next = nodes[i + 1];
		if (randIndices[i] >= 0) nodes[i]->rand = nodes[randIndices[i]];
	}

	return nodes[0];
}