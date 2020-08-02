# Params Checker

***EXPERIMENTAL***

**This algorithm is an idea. The C++ code could not compile too.**

## Goal

The concept checker iters over the program_graph representation of the compiler.

It verifies if all parameters are given

In C++ we could have a definition of a concept according to this:

```cpp
class NGL_Concept : NGL_Data
{
public:
	// ...

private:
	// ...
	std::unordered_map<std::string, NGL_Data*> m_vector_description; // Vector description
	std::vector<NGL_Data*> m_children; // Concept's children in the Program_Graph
}
```

## Algorithm (pseudo code)

Check if the whole program_graph is fully parameterized (required parameters)

```
Giving:
	ProgramGraph program_graph

Algorithm:
	for (program_graph_iter : program_graph)
		for (required_descriptor in program_graph_iter.descriptors())
			if (required_descriptor.value() == nullptr)
				return false
	return true

```

## Code Implementation (according to `Goal`'s definition)

```cpp
template<typename T>
bool contains(std::vector<T>& list, T elem)
{
	for (auto it = list.cbegin(); it != list.cend(); it++)
	{
		if (*it == elem) return true;
	}
	return false;
}


class ProgramGraphIterator
{
public:
	ProgramGraphIterator(const NGL_Data* graph)
		: m_graph(graph)
	{}

	bool iter()
	{
		m_to_explore.push_back(m_graph);
		m_marked.push_back(m_graph);
		while (!m_to_explore.empty())
		{
			NGL_Data* current = m_to_explore.pop_front();
			

			for (auto desc_it = current.m_vector_description.cbegin(); 
				desc_it != current.m_vector_description.cend();
				desc_it++)
			{
				if (n.second == nullptr) return false;
			}


			for (auto& it : current->m_children)
			{
				if (contains(marked, *it)) continue;
				m_to_explore.push_back(&(*it));
			}
			m_marked.push_back(current);
		}

		return true;
	}

private:
	const NGL_Data* m_graph;
	std::vector<NGL_Data*> m_marked;
	std::queue<NGL_Data*> m_to_explore;

}

```