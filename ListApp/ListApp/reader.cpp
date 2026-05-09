#include"reader.h"

#include<fstream>
#include<vector>
#include<stdexcept>

ListNode* readFromFile(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		throw std::runtime_error("Cannot open file: " + fileName);
	}

	struct Entry
	{
		std::string data;
		int randIdx;
	};
	std::vector<Entry> entries;
	std::string line;

	while (std::getline(file, line)) 
	{
		if (line.empty()) continue;

		size_t sep = line.rfind(';');
		if (sep == std::string::npos)
		{
			throw std::runtime_error("Bad format, no ';' in: " + line);
		}

		Entry e;
		e.data = line.substr(0,sep);
		e.randIdx = std::stoi(line.substr(sep + 1));
		entries.push_back(std::move(e));
	}

	if (entries.empty())
	{
		return nullptr;
	}

	const size_t n = entries.size();
	std::vector<ListNode*> nodes(n);

	for (size_t i = 0; i < n; ++i)
	{
		nodes[i] = new ListNode();
		nodes[i]->data = entries[i].data;
	}

	for (size_t i = 0; i < n; ++i)
	{
		if (i > 0) nodes[i]->prev = nodes[i - 1];
		if (i + 1 < n) nodes[i]->next = nodes[i + 1];

		int ri = entries[i].randIdx;
		if (ri >= 0 && ri < static_cast<int>(n))
		{
			nodes[i]->rand = nodes[ri];
		}
	}

	return nodes[0];
}